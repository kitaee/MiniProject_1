#pragma once
# include <nFramework/util/IniHandler.h>
# include "LaunchManager.h"
# include <map>

/**
* @ class: LaunchManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
LaunchManager::LaunchManager(void)
{
	initialize();
}

LaunchManager::~LaunchManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
LaunchManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("LaunchManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
LaunchManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
LaunchManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
LaunchManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
LaunchManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
LaunchManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
LaunchManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
LaunchManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
LaunchManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
LaunchManager::recvMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
LaunchManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
LaunchManager::getUserName()
{
	return name;
}

void
LaunchManager::setData(void * data)
{
}

bool
LaunchManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("LaunchManager/LaunchManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
LaunchManager::stop()
{
	bool result = true;
	return result;
}

void
LaunchManager::setMEBComponent(IMEBComponent * realMEB)
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
	return new LaunchManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}