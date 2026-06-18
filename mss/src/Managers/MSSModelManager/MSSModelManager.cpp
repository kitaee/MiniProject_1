#include "MSSModelManager.h"

// 역할: MSS 물리/행동 모델
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

MSSModelManager::MSSModelManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"MSSModelManager");
}

MSSModelManager::~MSSModelManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> MSSModelManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void MSSModelManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void MSSModelManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void MSSModelManager::reflectMsg(std::shared_ptr<NOM>) {}
void MSSModelManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void MSSModelManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void MSSModelManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void MSSModelManager::recvMsg(std::shared_ptr<NOM>) {}
void MSSModelManager::setUserName(std::wstring userName) { name = userName; }
tstring MSSModelManager::getUserName() { return name; }
void MSSModelManager::setData(void*) {}
bool MSSModelManager::start() { return true; }
bool MSSModelManager::stop() { return true; }
void MSSModelManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new MSSModelManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }