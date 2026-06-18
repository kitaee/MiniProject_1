#include "ControlManager.h"

// 역할: 시뮬레이션 제어·발사 명령
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

ControlManager::ControlManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"ControlManager");
}

ControlManager::~ControlManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> ControlManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void ControlManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void ControlManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void ControlManager::reflectMsg(std::shared_ptr<NOM>) {}
void ControlManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void ControlManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void ControlManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void ControlManager::recvMsg(std::shared_ptr<NOM>) {}
void ControlManager::setUserName(std::wstring userName) { name = userName; }
tstring ControlManager::getUserName() { return name; }
void ControlManager::setData(void*) {}
bool ControlManager::start() { return true; }
bool ControlManager::stop() { return true; }
void ControlManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new ControlManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }