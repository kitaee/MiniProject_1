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
	if (auto itr = msgFuncMap.find(nomMsg->getName()); itr != msgFuncMap.end())
	{
		itr->second(nomMsg);
	}
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
	// recvMsg에서 호출될 메서드 등록
	std::function<void(std::shared_ptr<NOM>)> msgProcessor;

	msgProcessor = std::bind(&LCSModelManager::recvScenario, this, std::placeholders::_1);
	msgFuncMap.insert(make_pair(_T("DeployScenarioInnerManager"), msgProcessor));

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

/*
	Handler Method
*/

void
LCSModelManager::recvScenario(std::shared_ptr<NOM> nomMsg)
{
	float launcherLatitude = nomMsg->getValue(_T("LauncherPositionLatitude"))->toFloat();
	float launcherLongitude = nomMsg->getValue(_T("LauncherPositionLongitude"))->toFloat();

	// 발사대 모델 세팅
	launcherModel = std::make_shared<LCS_MODEL>();
	launcherModel->launcherPosition.x = launcherLatitude;
	launcherModel->launcherPosition.y = launcherLongitude;

	// ACK 송신
	auto InnerNOMInstance = meb->getNOMInstance(name, _T("ScenarioACKInnerManager"));

	// ACK 헤더 세팅
	InnerNOMInstance->setValue(_T("MessageHeader.MessageID"), &NUInteger(4101));
	
	std::cout << "발사대 모의기 LCSModelManager ACK 송신\n" << std::endl;
	this->sendMsg(InnerNOMInstance);
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