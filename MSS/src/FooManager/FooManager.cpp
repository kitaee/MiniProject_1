#pragma once
#include <nFramework/util/IniHandler.h>
#include "FooManager.h"
#include <map>

/**
* @ class: FooManager
* @ author : 하재희
* @ version: 1.0
* @ see also: FooHandler
* @ description: MEC 객체를 사용하기 위해 BaseManager 인터페이스를 사용받아 구현한 클래스
* @ date: 2023.11.4
**/



/************************************************************************
	constructor / destructor
************************************************************************/
FooManager::FooManager(void)
{
	initialize();
}

FooManager::~FooManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
FooManager::initialize(void)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
	
	setUserName(_T("FooManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
FooManager::release()
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
FooManager::registerMsg(tstring msgName)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;
	
	
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
FooManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

}

void
FooManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->updateMsg(nomMsg);
}

void
FooManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
}

void
FooManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
FooManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	discoveredMsgMap.erase(nomMsg->getInstanceID());

}

void
FooManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	mec->sendMsg(nomMsg);
}

void
FooManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
}


void
FooManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
FooManager::getUserName()
{
	return name;
}

void
FooManager::setData(void* data)
{

}

bool
FooManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("FooManager/FooManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
	
	

	return true;
}

bool
FooManager::stop()
{
	bool result = true;

	return result;
}

void
FooManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager * createObject()
{
	return new FooManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager * userManager)
{
	delete userManager;
}
