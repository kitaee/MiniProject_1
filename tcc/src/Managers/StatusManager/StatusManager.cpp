#include "StatusManager.h"

// 역할: 모의기 상태·트랙·Ack 집계
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

StatusManager::StatusManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"StatusManager");
}

StatusManager::~StatusManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> StatusManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void StatusManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void StatusManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void StatusManager::reflectMsg(std::shared_ptr<NOM>) {}
void StatusManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void StatusManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void StatusManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void StatusManager::recvMsg(std::shared_ptr<NOM>) {}
void StatusManager::setUserName(std::wstring userName) { name = userName; }
tstring StatusManager::getUserName() { return name; }
void StatusManager::setData(void*) {}
bool StatusManager::start() { return true; }
bool StatusManager::stop() { return true; }
void StatusManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new StatusManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }