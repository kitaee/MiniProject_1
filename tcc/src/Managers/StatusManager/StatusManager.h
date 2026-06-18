#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>

using namespace nframework;
using namespace nom;

// 역할: 모의기 상태·트랙·Ack 집계

class BASEMGRDLL_API StatusManager : public BaseManager
{
public:
    StatusManager();
    ~StatusManager() override;

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
    IMEBComponent* meb{ nullptr };
    MECComponent* mec{ nullptr };
    tstring name;
};