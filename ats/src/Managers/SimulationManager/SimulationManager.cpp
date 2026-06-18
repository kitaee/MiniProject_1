#include "SimulationManager.h"

// 역할: 시뮬레이션 상태·시나리오·Ack
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

SimulationManager::SimulationManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"SimulationManager");
}

SimulationManager::~SimulationManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> SimulationManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void SimulationManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void SimulationManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void SimulationManager::reflectMsg(std::shared_ptr<NOM>) {}
void SimulationManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void SimulationManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void SimulationManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void SimulationManager::recvMsg(std::shared_ptr<NOM>) {}
void SimulationManager::setUserName(std::wstring userName) { name = userName; }
tstring SimulationManager::getUserName() { return name; }
void SimulationManager::setData(void*) {}
bool SimulationManager::start() { return true; }
bool SimulationManager::stop() { return true; }
void SimulationManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new SimulationManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }