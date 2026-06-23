#pragma once
# include <nFramework/util/IniHandler.h>
# include "ControlManager.h"
# include <nFramework/nom/NUInteger.h>
# include <map>

/**
* @ class: ControlManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
ControlManager::ControlManager(void)
{
	initialize();
}

ControlManager::~ControlManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
ControlManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("ControlManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
ControlManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
ControlManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
ControlManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
ControlManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
ControlManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
ControlManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
ControlManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
ControlManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
ControlManager::recvMsg(std::shared_ptr < NOM > nomMsg)
{
	if (nomMsg == nullptr)
		return;

	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	const auto msgName = nomMsg->getName();
	if (msgName == _T("StartSimulationCommand"))
	{
		sendSimulationRequest(_T("StartSimulationRequest"), 1002);
	}
	else if (msgName == _T("StopSimulationCommand"))
	{
		sendSimulationRequest(_T("StopSimulationRequest"), 1003);
	}
}

void
ControlManager::sendSimulationRequest(const tstring& requestName, uint32_t messageId)
{
	if (meb == nullptr)
		return;

	auto requestTemplate = meb->getNOMInstance(name, requestName);
	if (!requestTemplate)
	{
		tcerr << _T("[ControlManager] undefined message: ") << requestName << std::endl;
		return;
	}

	auto requestMsg = requestTemplate->clone();
	requestMsg->setOwner(name);
	requestMsg->setValue(_T("MessageHeader.MessageID"), new NUInteger(messageId));
	requestMsg->setValue(_T("MessageHeader.MessageLength"), new NUInteger(8));

	sendMsg(requestMsg);
}

void
ControlManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
ControlManager::getUserName()
{
	return name;
}

void
ControlManager::setData(void * data)
{
}

bool
ControlManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("ControlManager/ControlManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
ControlManager::stop()
{
	bool result = true;
	return result;
}

void
ControlManager::setMEBComponent(IMEBComponent * realMEB)
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
	return new ControlManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
