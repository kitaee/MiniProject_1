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
        uint32_t airthreatId{ 1 };
        float startLat{ 37.5000f };
        float startLon{ 127.0000f };
        float endLat{ 37.6000f };
        float endLon{ 127.1000f };
        float velocity{ 300.0f };
        double progress{ 0.0 };
        bool deployed{ false };
        bool detonated{ false };
    };

    void initialize();
    void release();
    void sendScenarioAck();
    void handleDeployScenario(std::shared_ptr<NOM> nomMsg);
    void handleDetonation(std::shared_ptr<NOM> nomMsg);
    void startSimulationLoop();
    void stopSimulationLoop();
    void simulationLoop();
    void publishAirthreatInfo();
    std::shared_ptr<NOM> getRegisteredObject(const std::wstring& msgName);

    static uint32_t readUInt(std::shared_ptr<NOM> nomMsg, const std::wstring& fieldName, uint32_t fallback);
    static float readFloat(std::shared_ptr<NOM> nomMsg, const std::wstring& fieldName, float fallback);

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
    NLineTstream ntcout{ Level::COUT };
};
