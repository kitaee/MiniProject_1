#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
    initialize();
}

SimulationManager::~SimulationManager()
{
    release();
}

void SimulationManager::initialize()
{
    setUserName(L"SimulationManager");
    mec = new MECComponent;
    mec->setUser(this);
}

void SimulationManager::release()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
    registeredMsgMap.clear();
    discoveredMsgMap.clear();
}

std::shared_ptr<NOM> SimulationManager::registerMsg(std::wstring msgName)
{
    std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
    registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
    return nomMsg;
}

void SimulationManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void SimulationManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void SimulationManager::reflectMsg(std::shared_ptr<NOM>) {}
void SimulationManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
    mec->deleteMsg(nomMsg);
    registeredMsgMap.erase(nomMsg->getInstanceID());
}

void SimulationManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void SimulationManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void SimulationManager::recvMsg(std::shared_ptr<NOM>) {}
void SimulationManager::setUserName(std::wstring userName) { name = userName; }
tstring SimulationManager::getUserName() { return name; }
void SimulationManager::setData(void*) {}
bool SimulationManager::start() { return true; }
bool SimulationManager::stop() { return true; }
void SimulationManager::setMEBComponent(IMEBComponent* realMEB)
{
    meb = realMEB;
    mec->setMEB(meb);
}

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new SimulationManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }
