#include "DataLinkManager.h"

// 역할: 데이터링크
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

DataLinkManager::DataLinkManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"DataLinkManager");
}

DataLinkManager::~DataLinkManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> DataLinkManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void DataLinkManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void DataLinkManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void DataLinkManager::reflectMsg(std::shared_ptr<NOM>) {}
void DataLinkManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void DataLinkManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void DataLinkManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void DataLinkManager::recvMsg(std::shared_ptr<NOM>) {}
void DataLinkManager::setUserName(std::wstring userName) { name = userName; }
tstring DataLinkManager::getUserName() { return name; }
void DataLinkManager::setData(void*) {}
bool DataLinkManager::start() { return true; }
bool DataLinkManager::stop() { return true; }
void DataLinkManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new DataLinkManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }