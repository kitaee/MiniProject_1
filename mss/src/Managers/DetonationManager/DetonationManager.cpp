#include "DetonationManager.h"

// 역할: 요격·폭발 결과
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

DetonationManager::DetonationManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"DetonationManager");
}

DetonationManager::~DetonationManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> DetonationManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void DetonationManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void DetonationManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void DetonationManager::reflectMsg(std::shared_ptr<NOM>) {}
void DetonationManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void DetonationManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void DetonationManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void DetonationManager::recvMsg(std::shared_ptr<NOM>) {}
void DetonationManager::setUserName(std::wstring userName) { name = userName; }
tstring DetonationManager::getUserName() { return name; }
void DetonationManager::setData(void*) {}
bool DetonationManager::start() { return true; }
bool DetonationManager::stop() { return true; }
void DetonationManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new DetonationManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }