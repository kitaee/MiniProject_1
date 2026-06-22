#pragma once
# include <nFramework/util/IniHandler.h>
# include "SimulationManager.h"
# include <map>

/**
* @ class: SimulationManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
SimulationManager::SimulationManager(void)
{
	initialize();
}

SimulationManager::~SimulationManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
SimulationManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("SimulationManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
SimulationManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
SimulationManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
SimulationManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
SimulationManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
SimulationManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
SimulationManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
SimulationManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
SimulationManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
SimulationManager::recvMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
SimulationManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
SimulationManager::getUserName()
{
	return name;
}

void
SimulationManager::setData(void * data)
{
}

bool
SimulationManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("SimulationManager/SimulationManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
SimulationManager::stop()
{
	bool result = true;
	return result;
}

void
SimulationManager::setMEBComponent(IMEBComponent * realMEB)
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
	return new SimulationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}