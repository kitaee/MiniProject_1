#include "ScenarioManager.h"

// 역할: 시나리오 저장·배포
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

ScenarioManager::ScenarioManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"ScenarioManager");
}

ScenarioManager::~ScenarioManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> ScenarioManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void ScenarioManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void ScenarioManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void ScenarioManager::reflectMsg(std::shared_ptr<NOM>) {}
void ScenarioManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void ScenarioManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void ScenarioManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void ScenarioManager::recvMsg(std::shared_ptr<NOM>) {}
void ScenarioManager::setUserName(std::wstring userName) { name = userName; }
tstring ScenarioManager::getUserName() { return name; }
void ScenarioManager::setData(void*) {}
bool ScenarioManager::start() { return true; }
bool ScenarioManager::stop() { return true; }
void ScenarioManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new ScenarioManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }