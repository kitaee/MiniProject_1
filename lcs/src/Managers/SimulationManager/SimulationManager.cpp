#include "SimulationManager.h"
#include "SimulationManagerIntelliVal.h"

using namespace nframework::intellival::DeployScenarioRequest;

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
    delete mec;
    mec = nullptr;
    meb = nullptr;
    registeredMsgMap.clear();
    discoveredMsgMap.clear();
}

std::shared_ptr<NOM> SimulationManager::registerMsg(std::wstring msgName)
{
    std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
    registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
    return nomMsg;
}

void SimulationManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void SimulationManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }

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
    scenario.targetLat = readFloat(nomMsg, L"Airthreat.EndLatitude", scenario.targetLat);
    scenario.targetLon = readFloat(nomMsg, L"Airthreat.EndLongitude", scenario.targetLon);
    scenario.launcherLat = readFloat(nomMsg, L"LauncherPositionLatitude", scenario.launcherLat);
    scenario.launcherLon = readFloat(nomMsg, L"LauncherPositionLongitude", scenario.launcherLon);
    scenario.launcherAlt = 0.0f;
    scenario.nextMissileId = 1u;
    scenario.missileQuantity = 4u;
    scenario.deployed = true;
}

void SimulationManager::sendMissileQuantityInfo()
{
    if (!meb)
        return;

    auto quantity = meb->getNOMInstance(name, L"MissileQuantityInfo");
    if (!quantity)
    {
        ntcout << L"  MissileQuantityInfo skipped: NOM instance not found." << std::endl;
        return;
    }

    uint32_t remaining = 0;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        remaining = scenario.missileQuantity;
    }

    nframework::nom::NUInteger messageId(quantity->getMessageID());
    nframework::nom::NUInteger messageLength(quantity->getLength());
    nframework::nom::NUInteger missileQuantity(remaining);

    quantity->setValue(L"MessageHeader.MessageID", &messageId);
    quantity->setValue(L"MessageHeader.MessageLength", &messageLength);
    quantity->setValue(L"MissileQuantity", &missileQuantity);

    sendMsg(quantity);
    ntcout << L"  MissileQuantityInfo sent quantity=" << remaining << std::endl;
}

void SimulationManager::sendLaunchMissile()
{
    if (!meb)
    {
        ntcout << L"  LaunchMissile skipped: MEB is not set." << std::endl;
        return;
    }

    auto launch = meb->getNOMInstance(name, L"LaunchMissile");
    if (!launch)
    {
        ntcout << L"  LaunchMissile skipped: NOM instance not found." << std::endl;
        return;
    }

    ScenarioState current;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        if (scenario.missileQuantity == 0)
        {
            ntcout << L"  LaunchMissile skipped: no missile remains." << std::endl;
            return;
        }

        scenario.missileQuantity--;
        current = scenario;
        current.nextMissileId = scenario.nextMissileId++;
    }

    nframework::nom::NUInteger messageId(launch->getMessageID());
    nframework::nom::NUInteger messageLength(launch->getLength());
    nframework::nom::NUInteger airthreatId(current.airthreatId);
    nframework::nom::NFloat airthreatX(current.targetLat);
    nframework::nom::NFloat airthreatY(current.targetLon);
    nframework::nom::NFloat airthreatZ(current.targetAlt);
    nframework::nom::NUInteger missileId(current.nextMissileId);
    nframework::nom::NFloat lcsX(current.launcherLat);
    nframework::nom::NFloat lcsY(current.launcherLon);
    nframework::nom::NFloat lcsZ(current.launcherAlt);

    launch->setValue(L"MessageHeader.MessageID", &messageId);
    launch->setValue(L"MessageHeader.MessageLength", &messageLength);
    launch->setValue(L"AirthreatID", &airthreatId);
    launch->setValue(L"AirthreatXpos", &airthreatX);
    launch->setValue(L"AirthreatYPos", &airthreatY);
    launch->setValue(L"AirthreatZPos", &airthreatZ);
    launch->setValue(L"MissleID", &missileId);
    launch->setValue(L"LCSXpos", &lcsX);
    launch->setValue(L"LCSYPos", &lcsY);
    launch->setValue(L"LCSZPos", &lcsZ);

    sendMsg(launch);
    ntcout << L"  LaunchMissile sent (MessageID=" << launch->getMessageID() << L")" << std::endl;
    sendMissileQuantityInfo();
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
        sendMissileQuantityInfo();
    }
    else if (nomMsg->getName() == L"StartSimulationRequest")
    {
        ntcout << L"  StartSimulationRequest received. Simulation state=RUNNING" << std::endl;
    }
    else if (nomMsg->getName() == L"StopSimulationRequest")
    {
        {
            std::lock_guard<std::mutex> lock(stateMutex);
            if (scenario.deployed)
            {
                scenario.nextMissileId = 1u;
                scenario.missileQuantity = 4u;
            }
        }
        sendMissileQuantityInfo();
        ntcout << L"  StopSimulationRequest received. Simulation state=STOPPED" << std::endl;
    }
    else if (nomMsg->getName() == L"LaunchMissileRequest")
    {
        ntcout << L"  LaunchMissileRequest received. Forwarding LaunchMissile." << std::endl;
        sendLaunchMissile();
    }
}

void SimulationManager::setUserName(std::wstring userName) { name = userName; }
tstring SimulationManager::getUserName() { return name; }
void SimulationManager::setData(void*) {}
bool SimulationManager::start() { return true; }
bool SimulationManager::stop() { return true; }
void SimulationManager::setMEBComponent(IMEBComponent* realMEB)
{
    meb = realMEB;
    mec->setMEB(meb);
}

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new SimulationManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }
