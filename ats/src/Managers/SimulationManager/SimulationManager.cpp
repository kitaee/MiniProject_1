#include "SimulationManager.h"
#include "SimulationManagerIntelliVal.h"
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace nframework::intellival::DeployScenarioRequest;

namespace
{
    constexpr double kEarthRadiusKm = 6371.0;
    constexpr double kDefaultAirthreatVelocityMps = 300.0;

    double toRadians(double degrees)
    {
        return degrees * 3.14159265358979323846 / 180.0;
    }

    double haversineKm(double lat1, double lon1, double lat2, double lon2)
    {
        const auto dLat = toRadians(lat2 - lat1);
        const auto dLon = toRadians(lon2 - lon1);
        const auto rLat1 = toRadians(lat1);
        const auto rLat2 = toRadians(lat2);
        const auto a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0)
            + std::cos(rLat1) * std::cos(rLat2) * std::sin(dLon / 2.0) * std::sin(dLon / 2.0);
        const auto clamped = std::min(1.0, std::max(0.0, a));
        return kEarthRadiusKm * 2.0 * std::atan2(std::sqrt(clamped), std::sqrt(1.0 - clamped));
    }
}

SimulationManager::SimulationManager()
{
    initialize();
}

SimulationManager::~SimulationManager()
{
    release();
}

void SimulationManager::initialize()
{
    setUserName(L"SimulationManager");
    mec = new MECComponent;
    mec->setUser(this);
}

void SimulationManager::release()
{
    stopSimulationLoop();
    delete mec;
    mec = nullptr;
    meb = nullptr;
    registeredMsgMap.clear();
    registeredMsgByName.clear();
    discoveredMsgMap.clear();
}

std::shared_ptr<NOM> SimulationManager::registerMsg(std::wstring msgName)
{
    std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
    registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
    registeredMsgByName[nomMsg->getName()] = nomMsg;
    return nomMsg;
}

void SimulationManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void SimulationManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
    if (nomMsg)
        nomMsg->setInstanceName(this->getUserName());
    mec->updateMsg(nomMsg);
}

void SimulationManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
    if (!nomMsg)
        return;

    ntcout << L"[SimulationManager] reflectMsg: " << nomMsg->getName() << std::endl;
}

void SimulationManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
    mec->deleteMsg(nomMsg);
    registeredMsgMap.erase(nomMsg->getInstanceID());
    registeredMsgByName.erase(nomMsg->getName());
}

void SimulationManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void SimulationManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }

uint32_t SimulationManager::readUInt(std::shared_ptr<NOM> nomMsg, const std::wstring& fieldName, uint32_t fallback)
{
    try
    {
        auto* value = nomMsg->getValue(fieldName);
        return value ? value->toUInt() : fallback;
    }
    catch (...)
    {
        return fallback;
    }
}

float SimulationManager::readFloat(std::shared_ptr<NOM> nomMsg, const std::wstring& fieldName, float fallback)
{
    try
    {
        auto* value = nomMsg->getValue(fieldName);
        return value ? value->toFloat() : fallback;
    }
    catch (...)
    {
        return fallback;
    }
}

void SimulationManager::sendScenarioAck()
{
    if (!meb)
    {
        ntcout << L"  ScenarioACK skipped: MEB is not set." << std::endl;
        return;
    }

    auto ack = meb->getNOMInstance(name, L"ScenarioACK");
    if (!ack)
    {
        ntcout << L"  ScenarioACK skipped: NOM instance not found." << std::endl;
        return;
    }

    nframework::nom::NUInteger messageId(ack->getMessageID());
    nframework::nom::NUInteger messageLength(ack->getLength());
    ack->setValue(L"MessageHeader.MessageID", &messageId);
    ack->setValue(L"MessageHeader.MessageLength", &messageLength);

    sendMsg(ack);
    ntcout << L"  ScenarioACK sent (MessageID=" << ack->getMessageID() << L")" << std::endl;
}

void SimulationManager::handleDeployScenario(std::shared_ptr<NOM> nomMsg)
{
    std::lock_guard<std::mutex> lock(stateMutex);
    scenario.airthreatId = readUInt(nomMsg, L"Airthreat.AirthreatID", 1u);
    scenario.startLat = readFloat(nomMsg, L"Airthreat.StartLatitude", scenario.startLat);
    scenario.startLon = readFloat(nomMsg, L"Airthreat.StartLongitude", scenario.startLon);
    scenario.endLat = readFloat(nomMsg, L"Airthreat.EndLatitude", scenario.endLat);
    scenario.endLon = readFloat(nomMsg, L"Airthreat.EndLongitude", scenario.endLon);
    scenario.velocity = readFloat(nomMsg, L"Airthreat.AirthreatVelocity", static_cast<float>(kDefaultAirthreatVelocityMps));
    if (scenario.velocity <= 0.0f)
        scenario.velocity = static_cast<float>(kDefaultAirthreatVelocityMps);
    scenario.progress = 0.0;
    scenario.deployed = true;
    scenario.detonated = false;
}

void SimulationManager::handleDetonation(std::shared_ptr<NOM> nomMsg)
{
    const auto targetId = readUInt(nomMsg, L"TargetID", 0u);
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        if (targetId == 0 || targetId == scenario.airthreatId)
        {
            scenario.detonated = true;
        }
    }

    stopSimulationLoop();
    ntcout << L"  DetonationInfo received. Airthreat state=KILLED" << std::endl;
}

void SimulationManager::startSimulationLoop()
{
    if (simulationRunning.exchange(true))
        return;

    simulationThread = std::thread(&SimulationManager::simulationLoop, this);
}

void SimulationManager::stopSimulationLoop()
{
    simulationRunning = false;
    if (simulationThread.joinable())
        simulationThread.join();
}

void SimulationManager::simulationLoop()
{
    while (simulationRunning)
    {
        publishAirthreatInfo();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

std::shared_ptr<NOM> SimulationManager::getRegisteredObject(const std::wstring& msgName)
{
    const auto itr = registeredMsgByName.find(msgName);
    if (itr != registeredMsgByName.end())
        return itr->second;

    return meb ? meb->getNOMInstance(name, msgName) : nullptr;
}

void SimulationManager::publishAirthreatInfo()
{
    if (!meb)
        return;

    ScenarioState current;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        if (!scenario.deployed || scenario.detonated)
            return;

        current = scenario;

        const auto distanceKm = haversineKm(scenario.startLat, scenario.startLon, scenario.endLat, scenario.endLon);
        if (distanceKm <= 0.001)
        {
            scenario.progress = 1.0;
        }
        else if (scenario.progress < 1.0)
        {
            const auto velocityMps = scenario.velocity > 0.0f ? scenario.velocity : static_cast<float>(kDefaultAirthreatVelocityMps);
            const auto deltaProgress = (static_cast<double>(velocityMps) / 1000.0) / distanceKm;
            scenario.progress = std::min(1.0, scenario.progress + deltaProgress);
        }
    }

    auto atInfo = getRegisteredObject(L"ATInfo");
    if (!atInfo)
    {
        ntcout << L"  ATInfo skipped: NOM instance not found." << std::endl;
        return;
    }

    const auto lat = static_cast<float>(current.startLat + (current.endLat - current.startLat) * current.progress);
    const auto lon = static_cast<float>(current.startLon + (current.endLon - current.startLon) * current.progress);

    nframework::nom::NUInteger messageId(atInfo->getMessageID());
    nframework::nom::NUInteger messageLength(atInfo->getLength());
    nframework::nom::NUInteger airthreatId(current.airthreatId);
    nframework::nom::NFloat airthreatX(lat);
    nframework::nom::NFloat airthreatY(lon);
    nframework::nom::NFloat airthreatZ(10.0f);
    nframework::nom::NFloat velocity(current.velocity);

    atInfo->setValue(L"MessageHeader.MessageID", &messageId);
    atInfo->setValue(L"MessageHeader.MessageLength", &messageLength);
    atInfo->setValue(L"AirthreatID", &airthreatId);
    atInfo->setValue(L"AirthreatXPos", &airthreatX);
    atInfo->setValue(L"AirthreatYPos", &airthreatY);
    atInfo->setValue(L"AirthreatZPos", &airthreatZ);
    atInfo->setValue(L"AirthreatVelocity", &velocity);

    sendMsg(atInfo);
    ntcout << L"  ATInfo published lat=" << lat << L" lon=" << lon << std::endl;
}

void SimulationManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
    if (!nomMsg)
        return;

    ntcout << L"[SimulationManager] recvMsg: " << nomMsg->getName() << std::endl;

    if (nomMsg->getName() == L"DeployScenarioRequest")
    {
        const auto msgId = t_MessageHeader_MessageID(nomMsg->getValue(L"MessageHeader.MessageID"));
        const auto airId = t_Airthreat_AirthreatID(nomMsg->getValue(L"Airthreat.AirthreatID"));
        handleDeployScenario(nomMsg);
        ntcout << L"  DeployScenarioRequest received (MessageID=" << msgId
               << L", AirthreatID=" << airId << L")" << std::endl;
        sendScenarioAck();
    }
    else if (nomMsg->getName() == L"StartSimulationRequest")
    {
        startSimulationLoop();
        ntcout << L"  StartSimulationRequest received. Simulation state=RUNNING" << std::endl;
    }
    else if (nomMsg->getName() == L"StopSimulationRequest")
    {
        stopSimulationLoop();
        {
            std::lock_guard<std::mutex> lock(stateMutex);
            scenario.progress = 0.0;
            scenario.detonated = false;
        }
        ntcout << L"  StopSimulationRequest received. Simulation state=STOPPED" << std::endl;
    }
    else if (nomMsg->getName() == L"DetonationInfo")
    {
        handleDetonation(nomMsg);
    }
}

void SimulationManager::setUserName(std::wstring userName) { name = userName; }
tstring SimulationManager::getUserName() { return name; }
void SimulationManager::setData(void*) {}
bool SimulationManager::start() { return true; }
bool SimulationManager::stop()
{
    stopSimulationLoop();
    return true;
}
void SimulationManager::setMEBComponent(IMEBComponent* realMEB)
{
    meb = realMEB;
    mec->setMEB(meb);
}

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new SimulationManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }
