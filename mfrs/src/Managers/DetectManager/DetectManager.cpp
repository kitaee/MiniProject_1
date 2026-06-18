#include "DetectManager.h"

// 역할: 레이더 탐지
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

DetectManager::DetectManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"DetectManager");
}

DetectManager::~DetectManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> DetectManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void DetectManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void DetectManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void DetectManager::reflectMsg(std::shared_ptr<NOM>) {}
void DetectManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void DetectManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void DetectManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void DetectManager::recvMsg(std::shared_ptr<NOM>) {}
void DetectManager::setUserName(std::wstring userName) { name = userName; }
tstring DetectManager::getUserName() { return name; }
void DetectManager::setData(void*) {}
bool DetectManager::start() { return true; }
bool DetectManager::stop() { return true; }
void DetectManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new DetectManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }