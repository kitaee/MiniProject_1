#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <map>

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
    void initialize();
    void release();

    IMEBComponent* meb{ nullptr };
    MECComponent* mec{ nullptr };
    tstring name;
    std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
    std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
    NLineTstream ntcout{ Level::COUT };
};
