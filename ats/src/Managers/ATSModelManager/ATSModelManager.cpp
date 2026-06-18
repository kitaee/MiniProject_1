#include "ATSModelManager.h"

// 역할: ATS 물리/행동 모델
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

ATSModelManager::ATSModelManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"ATSModelManager");
}

ATSModelManager::~ATSModelManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> ATSModelManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void ATSModelManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void ATSModelManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void ATSModelManager::reflectMsg(std::shared_ptr<NOM>) {}
void ATSModelManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void ATSModelManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void ATSModelManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void ATSModelManager::recvMsg(std::shared_ptr<NOM>) {}
void ATSModelManager::setUserName(std::wstring userName) { name = userName; }
tstring ATSModelManager::getUserName() { return name; }
void ATSModelManager::setData(void*) {}
bool ATSModelManager::start() { return true; }
bool ATSModelManager::stop() { return true; }
void ATSModelManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new ATSModelManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }