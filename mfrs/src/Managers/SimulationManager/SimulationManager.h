#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <atomic>
#include <map>
#include <mutex>
#include <thread>

using namespace nframework;
using namespace nom;
using namespace nlinestream;

class BASEMGRDLL_API SimulationManager : public BaseManager
{
public:
    SimulationManager();
    ~SimulationManager() override;

    std::shared_ptr<NOM> registerMsg(std::wstring) override;
    void discoverMsg(std::shared_ptr<NOM>) override;
    void updateMsg(std::shared_ptr<NOM>) override;
    void reflectMsg(std::shared_ptr<NOM>) override;
    void deleteMsg(std::shared_ptr<NOM>) override;
    void removeMsg(std::shared_ptr<NOM>) override;
    void sendMsg(std::shared_ptr<NOM>) override;
    void recvMsg(std::shared_ptr<NOM>) override;
    void setUserName(std::wstring) override;
    tstring getUserName() override;
    void setData(void*) override;
    bool start() override;
    bool stop() override;
    void setMEBComponent(IMEBComponent*) override;

private:
    struct ScenarioState
    {
        float radarLat{ 37.5500f };
        float radarLon{ 127.0500f };
        bool deployed{ false };
    };

    struct TargetState
    {
        uint32_t id{ 1 };
        float lat{ 37.5000f };
        float lon{ 127.0000f };
        float alt{ 10.0f };
        float velocity{ 300.0f };
        bool valid{ false };
        bool detected{ false };
    };

    struct MissileState
    {
        uint32_t id{ 1 };
        float lat{ 37.5200f };
        float lon{ 127.0200f };
        float alt{ 0.0f };
        float velocity{ 650.0f };
        bool valid{ false };
    };

    void initialize();
    void release();
    void sendScenarioAck();
    void handleDeployScenario(std::shared_ptr<NOM> nomMsg);
    void handleObjectUpdate(std::shared_ptr<NOM> nomMsg);
    void startSimulationLoop();
    void stopSimulationLoop();
    void simulationLoop();
    void publishRadarDetectionInfo(const TargetState& target);
    void publishUplinkInfo(const TargetState& target, const MissileState& missile);
    void publishDownlinkInfoToTcc(const MissileState& missile);
    std::shared_ptr<NOM> getRegisteredObject(const std::wstring& msgName);

    static uint32_t readUInt(std::shared_ptr<NOM> nomMsg, const std::wstring& fieldName, uint32_t fallback);
    static float readFloat(std::shared_ptr<NOM> nomMsg, const std::wstring& fieldName, float fallback);
    static double distance2d(float lat1, float lon1, float lat2, float lon2);
    static bool isInRadarSector(float radarLat, float radarLon, float targetLat, float targetLon);

    IMEBComponent* meb{ nullptr };
    MECComponent* mec{ nullptr };
    tstring name;
    std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
    std::map<std::wstring, std::shared_ptr<NOM>> registeredMsgByName;
    std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
    std::mutex stateMutex;
    std::atomic_bool simulationRunning{ false };
    std::thread simulationThread;
    ScenarioState scenario;
    TargetState target;
    MissileState missile;
    NLineTstream ntcout{ Level::COUT };
};
