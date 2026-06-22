#pragma once
# include <nFramework/util/IniHandler.h>
# include "LCSModelManager.h"
# include <map>

/**
* @ class: LCSModelManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
LCSModelManager::LCSModelManager(void)
{
	initialize();
}

LCSModelManager::~LCSModelManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
LCSModelManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("LCSModelManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
LCSModelManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
LCSModelManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
LCSModelManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
LCSModelManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
LCSModelManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
LCSModelManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
LCSModelManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
LCSModelManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
LCSModelManager::recvMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
LCSModelManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
LCSModelManager::getUserName()
{
	return name;
}

void
LCSModelManager::setData(void * data)
{
}

bool
LCSModelManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("LCSModelManager/LCSModelManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
LCSModelManager::stop()
{
	bool result = true;
	return result;
}

void
LCSModelManager::setMEBComponent(IMEBComponent * realMEB)
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
	return new LCSModelManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}