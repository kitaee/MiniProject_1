#pragma once
# include <nFramework/util/IniHandler.h>
# include "ATSModelManager.h"
# include <map>

/**
* @ class: ATSModelManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
ATSModelManager::ATSModelManager(void)
{
	initialize();
}

ATSModelManager::~ATSModelManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
ATSModelManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("ATSModelManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);

	funcMapInit();
}

void
ATSModelManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
ATSModelManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
ATSModelManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
ATSModelManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
ATSModelManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
ATSModelManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
ATSModelManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
ATSModelManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
ATSModelManager::recvMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	auto iter = funcMap.find(nomMsg->getName());
	if (iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
}

void
ATSModelManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
ATSModelManager::getUserName()
{
	return name;
}

void
ATSModelManager::setData(void * data)
{
}

bool
ATSModelManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("ATSModelManager/ATSModelManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
ATSModelManager::stop()
{
	bool result = true;
	return result;
}

void
ATSModelManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void
ATSModelManager::funcMapInit()
{
	std::function<void(std::shared_ptr<NOM>)> msgProc;

	msgProc = std::bind(&ATSModelManager::recvDeployScenarioToModel, this, std::placeholders::_1);
	funcMap.insert({ _T("DeployScenarioToModel"), msgProc });

	msgProc = std::bind(&ATSModelManager::recvStartSimulationToModel, this, std::placeholders::_1);
	funcMap.insert({ _T("StartSimulationToModel"), msgProc });

	msgProc = std::bind(&ATSModelManager::recvStopSimulationToModel, this, std::placeholders::_1);
	funcMap.insert({ _T("StopSimulationToModel"), msgProc });

	msgProc = std::bind(&ATSModelManager::recvDetonationInfoToModel, this, std::placeholders::_1);
	funcMap.insert({ _T("DetonationInfoToModel"), msgProc });
}

void
ATSModelManager::recvDeployScenarioToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

}

void
ATSModelManager::recvStartSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	simulationRunning = true;
}

void
ATSModelManager::recvStopSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	simulationRunning = false;
}

void
ATSModelManager::recvDetonationInfoToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	simulationRunning = false;
}

void
ATSModelManager::sendATInfo()
{
	auto atInfoMsg = meb->getNOMInstance(name, _T("ATInfo"));

	if (!atInfoMsg.get())
	{
		tcout << _T("[ATSModelManager] failed to create ATInfo.") << std::endl;
		return;
	}

	// TODO: MessageHeader, AirThreat 상태/좌표/속도 설정
	this->sendMsg(atInfoMsg);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new ATSModelManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}