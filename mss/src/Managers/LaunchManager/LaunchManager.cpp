#include "LaunchManager.h"

// 역할: 발사 제어
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

LaunchManager::LaunchManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"LaunchManager");
}

LaunchManager::~LaunchManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> LaunchManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void LaunchManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void LaunchManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void LaunchManager::reflectMsg(std::shared_ptr<NOM>) {}
void LaunchManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void LaunchManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void LaunchManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void LaunchManager::recvMsg(std::shared_ptr<NOM>) {}
void LaunchManager::setUserName(std::wstring userName) { name = userName; }
tstring LaunchManager::getUserName() { return name; }
void LaunchManager::setData(void*) {}
bool LaunchManager::start() { return true; }
bool LaunchManager::stop() { return true; }
void LaunchManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new LaunchManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }