#pragma once
#include <nFramework/util/IniHandler.h>
#include "StateManager.h"
#include <map>


/************************************************************************
	constructor / destructor
************************************************************************/
StateManager::StateManager(void)
{
	initialize();
}

StateManager::~StateManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
StateManager::initialize(void)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;


	setUserName(_T("StateManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);

	periodicFunc = std::bind(&StateManager::sendSimulatorState, this);

	nTimer = &(NTimer::getInstance());
	timerHandle = nTimer->addPeriodicTask(1000, periodicFunc);
}

void
StateManager::release()
{
	nTimer->removeTask(timerHandle);
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

void StateManager::sendSimulatorState()
{
	stateNOM = meb->getNOMInstance(name, _T("SimulatorStateToComm"));

	//// TODO : 각 모의기 ID 입력
	unsigned short simulatorID = 102;
	NUShort value(simulatorID);
	stateNOM->setValue(_T("SimulatorID"), &value);
	////
	
	sendMsg(stateNOM);
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
StateManager::registerMsg(tstring msgName)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;


	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
StateManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

}

void
StateManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	mec->updateMsg(nomMsg);
}

void
StateManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


}

void
StateManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
StateManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	discoveredMsgMap.erase(nomMsg->getInstanceID());

}

void
StateManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	// ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	mec->sendMsg(nomMsg);
}

void
StateManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
}


void
StateManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
StateManager::getUserName()
{
	return name;
}

void
StateManager::setData(void* data)
{

}

bool
StateManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("StateManager/StateManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

	return true;
}

bool
StateManager::stop()
{
	bool result = true;

	return result;
}

void
StateManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new StateManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
