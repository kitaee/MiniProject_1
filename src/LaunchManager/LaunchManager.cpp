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
	if (auto itr = msgFuncMap.find(nomMsg->getName()); itr != msgFuncMap.end())
	{
		itr->second(nomMsg);
	}
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
	// 발사 요청
	msgFuncMap.insert(make_pair(
		_T("LaunchMissleInnerManager"),
		std::bind(&LaunchManager::launchMissle, this, std::placeholders::_1)
	));

	// 발사 완료 응답
	msgFuncMap.insert(make_pair(
		_T("LaunchMissleResponseInnerManager"),
		std::bind(&LaunchManager::recvLaunchMissleResponse, this, std::placeholders::_1)
	));

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

void
LaunchManager::launchMissle(std::shared_ptr<NOM> nomMsg)
{
	std::cout << "발사대 모의기 LaunchManager 발사 요청 송신\n" << std::endl;

	auto InnerNOMInstance = meb->getNOMInstance(name, _T("LaunchMissleInnerToModel"));

	// 내부 구조체 세팅
	InnerNOMInstance->setValue(_T("AirthreatID"), &(NUInteger)(nomMsg->getValue(_T("AirthreatID"))->toUInt()));
	InnerNOMInstance->setValue(_T("AirthreatXPos"), &(NFloat)(nomMsg->getValue(_T("AirthreatXPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("AirthreatYPos"), &(NFloat)(nomMsg->getValue(_T("AirthreatYPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("MissleID"), &(NUInteger)(nomMsg->getValue(_T("MissleID"))->toUInt()));

	this->sendMsg(InnerNOMInstance);
}

void
LaunchManager::recvLaunchMissleResponse(std::shared_ptr<NOM> nomMsg)
{
	std::cout << "발사대 모의기 LaunchManager 발사 완료 응답 수신\n" << std::endl;

	auto InnerNOMInstance = meb->getNOMInstance(name, _T("LaunchMissleResponseToUDP"));

	// 발사 응답 세팅
	InnerNOMInstance->setValue(_T("AirthreatID"), &(NUInteger)(nomMsg->getValue(_T("AirthreatID"))->toUInt()));
	InnerNOMInstance->setValue(_T("AirthreatXPos"), &(NFloat)(nomMsg->getValue(_T("AirthreatXPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("AirthreatYPos"), &(NFloat)(nomMsg->getValue(_T("AirthreatYPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("MissleID"), &(NUInteger)(nomMsg->getValue(_T("MissleID"))->toUInt()));
	InnerNOMInstance->setValue(_T("LCSXPos"), &(NFloat)(nomMsg->getValue(_T("LCSXPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("LCSYPos"), &(NFloat)(nomMsg->getValue(_T("LCSYPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("RemainMissleCount"), &(NUInteger)(nomMsg->getValue(_T("RemainMissleCount"))->toFloat()));

	this->sendMsg(InnerNOMInstance);
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