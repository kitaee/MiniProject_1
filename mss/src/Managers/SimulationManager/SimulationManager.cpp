#include "SimulationManager.h"
#include "SimulationManagerIntelliVal.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <utility>

using namespace nframework::intellival::DeployScenarioRequest;

namespace
{
    constexpr double kEarthRadiusKm = 6371.0;
    constexpr double kDefaultMissileVelocityMps = 650.0;
    constexpr double kLethalRadiusKm = 0.70;

    double toRadians(double degrees)
    {
        return degrees * 3.14159265358979323846 / 180.0;
    }

    double toDegrees(double radians)
    {
        return radians * 180.0 / 3.14159265358979323846;
    }

    double normalizeBearing(double degrees)
    {
        auto value = std::fmod(degrees, 360.0);
        return value < 0.0 ? value + 360.0 : value;
    }

    double normalizeLongitude(double degrees)
    {
        auto value = std::fmod(degrees + 540.0, 360.0);
        if (value < 0.0)
            value += 360.0;
        return value - 180.0;
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

    double bearingDegrees(double fromLat, double fromLon, double toLat, double toLon)
    {
        const auto lat1 = toRadians(fromLat);
        const auto lat2 = toRadians(toLat);
        const auto deltaLon = toRadians(toLon - fromLon);
        const auto y = std::sin(deltaLon) * std::cos(lat2);
        const auto x = std::cos(lat1) * std::sin(lat2)
            - std::sin(lat1) * std::cos(lat2) * std::cos(deltaLon);
        return normalizeBearing(toDegrees(std::atan2(y, x)));
    }

    std::pair<double, double> destinationPoint(double lat, double lon, double bearing, double distanceKm)
    {
        const auto angularDistance = distanceKm / kEarthRadiusKm;
        const auto bearingRad = toRadians(normalizeBearing(bearing));
        const auto lat1 = toRadians(lat);
        const auto lon1 = toRadians(lon);

        const auto lat2 = std::asin(
            std::sin(lat1) * std::cos(angularDistance)
            + std::cos(lat1) * std::sin(angularDistance) * std::cos(bearingRad));
        const auto lon2 = lon1 + std::atan2(
            std::sin(bearingRad) * std::sin(angularDistance) * std::cos(lat1),
            std::cos(angularDistance) - std::sin(lat1) * std::sin(lat2));

        return { toDegrees(lat2), normalizeLongitude(toDegrees(lon2)) };
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
    handleObjectUpdate(nomMsg);
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
    scenario.deployed = true;
    target.id = scenario.airthreatId;
    target.lat = readFloat(nomMsg, L"Airthreat.EndLatitude", target.lat);
    target.lon = readFloat(nomMsg, L"Airthreat.EndLongitude", target.lon);
    target.alt = 10.0f;
    target.valid = true;
    missile.launched = false;
    missile.detonated = false;
}

void SimulationManager::handleLaunchMissile(std::shared_ptr<NOM> nomMsg)
{
    std::lock_guard<std::mutex> lock(stateMutex);
    missile.id = readUInt(nomMsg, L"MissleID", missile.id);
    missile.lat = readFloat(nomMsg, L"LCSXpos", missile.lat);
    missile.lon = readFloat(nomMsg, L"LCSYPos", missile.lon);
    missile.alt = readFloat(nomMsg, L"LCSZPos", missile.alt);
    missile.velocity = static_cast<float>(kDefaultMissileVelocityMps);
    missile.launched = true;
    missile.detonated = false;

    target.id = readUInt(nomMsg, L"AirthreatID", target.id);
    target.lat = readFloat(nomMsg, L"AirthreatXpos", target.lat);
    target.lon = readFloat(nomMsg, L"AirthreatYPos", target.lon);
    target.alt = readFloat(nomMsg, L"AirthreatZPos", target.alt);
    target.valid = true;
}

void SimulationManager::handleObjectUpdate(std::shared_ptr<NOM> nomMsg)
{
    if (nomMsg->getName() != L"UplinkInfo" && nomMsg->getName() != L"UplinkInfo_5301")
        return;

    std::lock_guard<std::mutex> lock(stateMutex);
    target.id = readUInt(nomMsg, L"UplinkInfo.AirthreatID", target.id);
    target.lat = readFloat(nomMsg, L"UplinkInfo.AirthreatXpos", target.lat);
    target.lon = readFloat(nomMsg, L"UplinkInfo.AirthreatYPos", target.lon);
    target.alt = readFloat(nomMsg, L"UplinkInfo.AirthreatZPos", target.alt);
    target.velocity = readFloat(nomMsg, L"UplinkInfo.AirthreatVelocity", target.velocity);
    target.valid = true;
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
        MissileState currentMissile;
        uint32_t killedMissileId = 0;
        uint32_t killedTargetId = 0;
        bool shouldPublish = false;

        {
            std::lock_guard<std::mutex> lock(stateMutex);
            if (missile.launched && !missile.detonated && target.valid)
            {
                const double distanceKm = haversineKm(missile.lat, missile.lon, target.lat, target.lon);
                const double velocityMps = missile.velocity > 0.0f
                    ? static_cast<double>(missile.velocity)
                    : kDefaultMissileVelocityMps;
                const double stepKm = velocityMps / 1000.0;
                if (distanceKm <= std::max(kLethalRadiusKm, stepKm))
                {
                    missile.lat = target.lat;
                    missile.lon = target.lon;
                    missile.alt = target.alt;
                    missile.detonated = true;
                    missile.launched = false;
                    killedMissileId = missile.id;
                    killedTargetId = target.id;
                }
                else
                {
                    const double bearing = bearingDegrees(missile.lat, missile.lon, target.lat, target.lon);
                    const double step = std::min(stepKm, distanceKm);
                    const double ratio = step / distanceKm;
                    const auto nextPoint = destinationPoint(missile.lat, missile.lon, bearing, step);
                    missile.lat = static_cast<float>(nextPoint.first);
                    missile.lon = static_cast<float>(nextPoint.second);
                    missile.alt = static_cast<float>(missile.alt + (target.alt - missile.alt) * ratio);
                }

                currentMissile = missile;
                shouldPublish = true;
            }
        }

        if (shouldPublish)
            publishDownlinkInfo(currentMissile);

        if (killedMissileId != 0)
            sendDetonationInfo(killedMissileId, killedTargetId);

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

void SimulationManager::publishDownlinkInfo(const MissileState& currentMissile)
{
    if (!meb)
        return;

    auto downlink = getRegisteredObject(L"DownlinkInfo");
    if (!downlink)
    {
        ntcout << L"  DownlinkInfo skipped: NOM instance not found." << std::endl;
        return;
    }

    nframework::nom::NUInteger messageId(downlink->getMessageID());
    nframework::nom::NUInteger messageLength(downlink->getLength());
    nframework::nom::NUInteger missileId(currentMissile.id);
    nframework::nom::NFloat velocity(currentMissile.velocity);
    nframework::nom::NFloat missileX(currentMissile.lat);
    nframework::nom::NFloat missileY(currentMissile.lon);
    nframework::nom::NFloat missileZ(currentMissile.alt);

    downlink->setValue(L"MessageHeader.MessageID", &messageId);
    downlink->setValue(L"MessageHeader.MessageLength", &messageLength);
    downlink->setValue(L"DownlinkInfo.MissleID", &missileId);
    downlink->setValue(L"DownlinkInfo.MissileVelocity", &velocity);
    downlink->setValue(L"DownlinkInfo.MissleXPos", &missileX);
    downlink->setValue(L"DownlinkInfo.MissleYPos", &missileY);
    downlink->setValue(L"DownlinkInfo.MissleZPos", &missileZ);

    sendMsg(downlink);
    ntcout << L"  DownlinkInfo published missile=" << currentMissile.id << std::endl;
}

void SimulationManager::sendDetonationInfo(uint32_t missileIdValue, uint32_t targetIdValue)
{
    if (!meb)
        return;

    auto detonation = meb->getNOMInstance(name, L"DetonationInfo");
    if (!detonation)
    {
        ntcout << L"  DetonationInfo skipped: NOM instance not found." << std::endl;
        return;
    }

    nframework::nom::NUInteger messageId(detonation->getMessageID());
    nframework::nom::NUInteger messageLength(detonation->getLength());
    nframework::nom::NUInteger missileId(missileIdValue);
    nframework::nom::NUInteger targetId(targetIdValue);

    detonation->setValue(L"MessageHeader.MessageID", &messageId);
    detonation->setValue(L"MessageHeader.MessageLength", &messageLength);
    detonation->setValue(L"MissleID", &missileId);
    detonation->setValue(L"TargetID", &targetId);

    sendMsg(detonation);
    ntcout << L"  DetonationInfo sent missile=" << missileIdValue << L" target=" << targetIdValue << std::endl;
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
            missile.launched = false;
            missile.detonated = false;
        }
        ntcout << L"  StopSimulationRequest received. Simulation state=STOPPED" << std::endl;
    }
    else if (nomMsg->getName() == L"LaunchMissile")
    {
        handleLaunchMissile(nomMsg);
        startSimulationLoop();
        ntcout << L"  LaunchMissile received. Missile state=LAUNCHED" << std::endl;
    }
    else if (nomMsg->getName() == L"UplinkInfo" || nomMsg->getName() == L"UplinkInfo_5301")
    {
        handleObjectUpdate(nomMsg);
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
