#include "LCSModelManager.h"

// 역할: LCS 물리/행동 모델
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

LCSModelManager::LCSModelManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"LCSModelManager");
}

LCSModelManager::~LCSModelManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> LCSModelManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void LCSModelManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void LCSModelManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void LCSModelManager::reflectMsg(std::shared_ptr<NOM>) {}
void LCSModelManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void LCSModelManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void LCSModelManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void LCSModelManager::recvMsg(std::shared_ptr<NOM>) {}
void LCSModelManager::setUserName(std::wstring userName) { name = userName; }
tstring LCSModelManager::getUserName() { return name; }
void LCSModelManager::setData(void*) {}
bool LCSModelManager::start() { return true; }
bool LCSModelManager::stop() { return true; }
void LCSModelManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new LCSModelManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }