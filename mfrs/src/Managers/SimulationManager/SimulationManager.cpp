#include "SimulationManager.h"
#include "SimulationManagerIntelliVal.h"
#include <chrono>
#include <cmath>

using namespace nframework::intellival::DeployScenarioRequest;

namespace
{
    constexpr double kEarthRadiusKm = 6371.0;
    constexpr double kRadarRangeKm = 230.0;
    constexpr double kRadarMinAzimuthDeg = -45.0;
    constexpr double kRadarMaxAzimuthDeg = 45.0;

    double toRadians(double degrees) { return degrees * 3.14159265358979323846 / 180.0; }
    double toDegrees(double radians) { return radians * 180.0 / 3.14159265358979323846; }

    double normalizeBearing(double degrees)
    {
        auto value = std::fmod(degrees, 360.0);
        return value < 0.0 ? value + 360.0 : value;
    }

    double relativeToNorth(double degrees)
    {
        auto value = normalizeBearing(degrees);
        return value > 180.0 ? value - 360.0 : value;
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

double SimulationManager::distance2d(float lat1, float lon1, float lat2, float lon2)
{
    const double dx = static_cast<double>(lat1) - static_cast<double>(lat2);
    const double dy = static_cast<double>(lon1) - static_cast<double>(lon2);
    return std::sqrt(dx * dx + dy * dy);
}

bool SimulationManager::isInRadarSector(float radarLat, float radarLon, float targetLat, float targetLon)
{
    const auto lat1 = toRadians(radarLat);
    const auto lat2 = toRadians(targetLat);
    const auto deltaLat = toRadians(static_cast<double>(targetLat) - radarLat);
    const auto deltaLon = toRadians(static_cast<double>(targetLon) - radarLon);

    const auto a = std::sin(deltaLat / 2.0) * std::sin(deltaLat / 2.0)
        + std::cos(lat1) * std::cos(lat2) * std::sin(deltaLon / 2.0) * std::sin(deltaLon / 2.0);
    const auto distanceKm = kEarthRadiusKm * 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    if (distanceKm > kRadarRangeKm)
        return false;

    const auto y = std::sin(deltaLon) * std::cos(lat2);
    const auto x = std::cos(lat1) * std::sin(lat2)
        - std::sin(lat1) * std::cos(lat2) * std::cos(deltaLon);
    const auto azimuth = relativeToNorth(toDegrees(std::atan2(y, x)));
    return azimuth >= kRadarMinAzimuthDeg && azimuth <= kRadarMaxAzimuthDeg;
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
    scenario.radarLat = readFloat(nomMsg, L"RadarPositionLatitude", scenario.radarLat);
    scenario.radarLon = readFloat(nomMsg, L"RadarPositionLongitude", scenario.radarLon);
    scenario.deployed = true;
    target.valid = false;
    target.detected = false;
    missile.valid = false;
}

void SimulationManager::handleObjectUpdate(std::shared_ptr<NOM> nomMsg)
{
    const auto msgName = nomMsg->getName();
    std::lock_guard<std::mutex> lock(stateMutex);

    if (msgName == L"ATInfo")
    {
        target.id = readUInt(nomMsg, L"AirthreatID", target.id);
        target.lat = readFloat(nomMsg, L"AirthreatXPos", target.lat);
        target.lon = readFloat(nomMsg, L"AirthreatYPos", target.lon);
        target.alt = readFloat(nomMsg, L"AirthreatZPos", target.alt);
        target.velocity = readFloat(nomMsg, L"AirthreatVelocity", target.velocity);
        target.valid = true;
    }
    else if (msgName == L"DownlinkInfo_3501" || msgName == L"DownlinkInfo")
    {
        missile.id = readUInt(nomMsg, L"DownlinkInfo.MissleID", missile.id);
        missile.velocity = readFloat(nomMsg, L"DownlinkInfo.MissileVelocity", missile.velocity);
        missile.lat = readFloat(nomMsg, L"DownlinkInfo.MissleXPos", missile.lat);
        missile.lon = readFloat(nomMsg, L"DownlinkInfo.MissleYPos", missile.lon);
        missile.alt = readFloat(nomMsg, L"DownlinkInfo.MissleZPos", missile.alt);
        missile.valid = true;
    }
    else if (msgName == L"UplinkInfo_1501")
    {
        target.id = readUInt(nomMsg, L"UplinkInfo.AirthreatID", target.id);
        target.lat = readFloat(nomMsg, L"UplinkInfo.AirthreatXpos", target.lat);
        target.lon = readFloat(nomMsg, L"UplinkInfo.AirthreatYPos", target.lon);
        target.alt = readFloat(nomMsg, L"UplinkInfo.AirthreatZPos", target.alt);
        target.velocity = readFloat(nomMsg, L"UplinkInfo.AirthreatVelocity", target.velocity);
        target.valid = true;
    }
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
        TargetState currentTarget;
        MissileState currentMissile;
        bool shouldPublishTarget = false;
        bool shouldPublishMissile = false;

        {
            std::lock_guard<std::mutex> lock(stateMutex);
            if (scenario.deployed && target.valid)
            {
                target.detected = isInRadarSector(scenario.radarLat, scenario.radarLon, target.lat, target.lon);
                currentTarget = target;
                shouldPublishTarget = true;
            }

            if (missile.valid)
            {
                currentMissile = missile;
                shouldPublishMissile = true;
            }
        }

        if (shouldPublishTarget)
        {
            publishRadarDetectionInfo(currentTarget);
            publishUplinkInfo(currentTarget, currentMissile);
        }

        if (shouldPublishMissile)
        {
            publishDownlinkInfoToTcc(currentMissile);
        }

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

void SimulationManager::publishRadarDetectionInfo(const TargetState& currentTarget)
{
    if (!meb)
        return;

    auto radar = getRegisteredObject(L"RadarDetectionInfo");
    if (!radar)
    {
        ntcout << L"  RadarDetectionInfo skipped: NOM instance not found." << std::endl;
        return;
    }

    nframework::nom::NUInteger messageId(radar->getMessageID());
    nframework::nom::NUInteger messageLength(radar->getLength());
    nframework::nom::NUInteger targetId(currentTarget.id);
    nframework::nom::NFloat targetX(currentTarget.lat);
    nframework::nom::NFloat targetY(currentTarget.lon);
    nframework::nom::NFloat targetZ(currentTarget.alt);
    nframework::nom::NUInteger detectedFlag(currentTarget.detected ? 1u : 0u);
    nframework::nom::NFloat velocity(currentTarget.velocity);

    radar->setValue(L"MessageHeader.MessageID", &messageId);
    radar->setValue(L"MessageHeader.MessageLength", &messageLength);
    radar->setValue(L"RadarDetection.TargetID", &targetId);
    radar->setValue(L"RadarDetection.TargetXPos", &targetX);
    radar->setValue(L"RadarDetection.TargetYPos", &targetY);
    radar->setValue(L"RadarDetection.TargetZPos", &targetZ);
    radar->setValue(L"RadarDetection.DetectedFlag", &detectedFlag);
    radar->setValue(L"RadarDetection.TargetVelocity", &velocity);

    sendMsg(radar);
    ntcout << L"  RadarDetectionInfo published detected=" << (currentTarget.detected ? 1 : 0) << std::endl;
}

void SimulationManager::publishUplinkInfo(const TargetState& currentTarget, const MissileState& currentMissile)
{
    if (!meb || !currentTarget.detected)
        return;

    auto uplink = getRegisteredObject(L"UplinkInfo_5301");
    if (!uplink)
    {
        ntcout << L"  UplinkInfo_5301 skipped: NOM instance not found." << std::endl;
        return;
    }

    nframework::nom::NUInteger messageId(uplink->getMessageID());
    nframework::nom::NUInteger messageLength(uplink->getLength());
    nframework::nom::NUInteger airthreatId(currentTarget.id);
    nframework::nom::NFloat targetX(currentTarget.lat);
    nframework::nom::NFloat targetY(currentTarget.lon);
    nframework::nom::NFloat targetZ(currentTarget.alt);
    nframework::nom::NUInteger missileId(currentMissile.valid ? currentMissile.id : 1u);
    nframework::nom::NFloat velocity(currentTarget.velocity);

    uplink->setValue(L"MessageHeader.MessageID", &messageId);
    uplink->setValue(L"MessageHeader.MessageLength", &messageLength);
    uplink->setValue(L"UplinkInfo.AirthreatID", &airthreatId);
    uplink->setValue(L"UplinkInfo.AirthreatXpos", &targetX);
    uplink->setValue(L"UplinkInfo.AirthreatYPos", &targetY);
    uplink->setValue(L"UplinkInfo.AirthreatZPos", &targetZ);
    uplink->setValue(L"UplinkInfo.MissileID", &missileId);
    uplink->setValue(L"UplinkInfo.AirthreatVelocity", &velocity);

    sendMsg(uplink);
    ntcout << L"  UplinkInfo_5301 published target=" << currentTarget.id << std::endl;
}

void SimulationManager::publishDownlinkInfoToTcc(const MissileState& currentMissile)
{
    if (!meb)
        return;

    auto downlink = getRegisteredObject(L"DownlinkInfo_5103");
    if (!downlink)
    {
        ntcout << L"  DownlinkInfo_5103 skipped: NOM instance not found." << std::endl;
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
    ntcout << L"  DownlinkInfo_5103 published missile=" << currentMissile.id << std::endl;
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
            target.valid = false;
            target.detected = false;
            missile.valid = false;
        }
        ntcout << L"  StopSimulationRequest received. Simulation state=STOPPED" << std::endl;
    }
    else if (nomMsg->getName() == L"ATInfo"
        || nomMsg->getName() == L"DownlinkInfo_3501"
        || nomMsg->getName() == L"DownlinkInfo"
        || nomMsg->getName() == L"UplinkInfo_1501")
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
