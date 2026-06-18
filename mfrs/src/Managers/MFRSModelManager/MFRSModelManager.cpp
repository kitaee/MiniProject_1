#include "MFRSModelManager.h"

// 역할: MFRS 물리/행동 모델
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

MFRSModelManager::MFRSModelManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"MFRSModelManager");
}

MFRSModelManager::~MFRSModelManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> MFRSModelManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void MFRSModelManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void MFRSModelManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void MFRSModelManager::reflectMsg(std::shared_ptr<NOM>) {}
void MFRSModelManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void MFRSModelManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void MFRSModelManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void MFRSModelManager::recvMsg(std::shared_ptr<NOM>) {}
void MFRSModelManager::setUserName(std::wstring userName) { name = userName; }
tstring MFRSModelManager::getUserName() { return name; }
void MFRSModelManager::setData(void*) {}
bool MFRSModelManager::start() { return true; }
bool MFRSModelManager::stop() { return true; }
void MFRSModelManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new MFRSModelManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }