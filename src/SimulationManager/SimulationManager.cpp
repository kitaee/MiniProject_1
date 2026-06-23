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
	msgFuncMap.clear();
	registeredMsgMap.clear();
	discoveredMsgMap.clear();

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
	if (!nomMsg)
		return;

	const auto iter = msgFuncMap.find(nomMsg->getName());
	if (iter == msgFuncMap.end())
		return;

	iter->second(nomMsg);
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

	msgFuncMap.clear();

	msgFuncMap.emplace(
		_T("DeployScenarioInnerManager"),
		std::bind(
			&SimulationManager::
			recvDeployScenarioInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("ScenarioACKInnerManager"),
		std::bind(
			&SimulationManager::
			recvScenarioACKInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("StartSimulationInnerManager"),
		std::bind(
			&SimulationManager::
			recvStartSimulationInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("StopSimulationInnerManager"),
		std::bind(
			&SimulationManager::
			recvStopSimulationInnerManager,
			this,
			std::placeholders::_1));

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
SimulationManager::stop()
{
	msgFuncMap.clear();
	return true;
}

void
SimulationManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void SimulationManager::
recvDeployScenarioInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("MFRSModelManager"));
}

void SimulationManager::
recvScenarioACKInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("MFRSCommManager"));
}

void SimulationManager::
recvStartSimulationInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	tcout << _T(
		"[SimulationManager] StartSimulationInnerManager received.")
		<< std::endl;

	mec->sendMsg(
		nomMsg,
		_T("MFRSModelManager"));
}

void SimulationManager::
recvStopSimulationInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	tcout << _T(
		"[SimulationManager] StopSimulationInnerManager received.")
		<< std::endl;

	mec->sendMsg(
		nomMsg,
		_T("MFRSModelManager"));
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
