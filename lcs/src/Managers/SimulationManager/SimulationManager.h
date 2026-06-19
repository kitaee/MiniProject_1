#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <map>
#include <mutex>

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
        uint32_t nextMissileId{ 1 };
        uint32_t missileQuantity{ 4 };
        float targetLat{ 37.6000f };
        float targetLon{ 127.1000f };
        float targetAlt{ 10.0f };
        float launcherLat{ 37.5200f };
        float launcherLon{ 127.0200f };
        float launcherAlt{ 0.0f };
        bool deployed{ false };
    };

    void initialize();
    void release();
    void sendScenarioAck();
    void sendLaunchMissile();
    void sendMissileQuantityInfo();
    void handleDeployScenario(std::shared_ptr<NOM> nomMsg);

    static uint32_t readUInt(std::shared_ptr<NOM> nomMsg, const std::wstring& fieldName, uint32_t fallback);
    static float readFloat(std::shared_ptr<NOM> nomMsg, const std::wstring& fieldName, float fallback);

    IMEBComponent* meb{ nullptr };
    MECComponent* mec{ nullptr };
    tstring name;
    std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
    std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
    std::mutex stateMutex;
    ScenarioState scenario;
    NLineTstream ntcout{ Level::COUT };
};
