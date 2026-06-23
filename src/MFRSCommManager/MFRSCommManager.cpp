#pragma once
# include <nFramework/util/IniHandler.h>
# include "MFRSCommManager.h"
# include <map>
# include <functional>

/**
* @ class: MFRSCommManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
MFRSCommManager::MFRSCommManager(void)
{
	initialize();
}

MFRSCommManager::~MFRSCommManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
MFRSCommManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("MFRSCommManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
MFRSCommManager::release(void)
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
MFRSCommManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
MFRSCommManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
MFRSCommManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
MFRSCommManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
MFRSCommManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
MFRSCommManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
MFRSCommManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
MFRSCommManager::recvMsg(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	const auto iter =
		msgFuncMap.find(nomMsg->getName());

	if (iter == msgFuncMap.end())
		return;

	iter->second(nomMsg);
}

void
MFRSCommManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
MFRSCommManager::getUserName()
{
	return name;
}

void
MFRSCommManager::setData(void * data)
{
}

bool
MFRSCommManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(
		_T("MFRSCommManager/MFRSCommManager.ini"));

	msgFuncMap.clear();

	msgFuncMap.emplace(
		_T("DeployScenarioInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvDeployScenarioInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("ScenarioACKInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvScenarioACKInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("StartSimulationInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvStartSimulationInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("StopSimulationInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvStopSimulationInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("ATInfoInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvATInfoInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("RadarDetectionInfoInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvRadarDetectionInfoInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("UplinkInfoToDatalinkInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvUplinkInfoToDatalinkInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("UplinkInfoToUDPInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvUplinkInfoToUDPInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("DownlinkInfoToDatalinkInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvDownlinkInfoToDatalinkInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("DownlinkInfoToUDPInnerManager"),
		std::bind(
			&MFRSCommManager::
			recvDownlinkInfoToUDPInnerManager,
			this,
			std::placeholders::_1));

	return true;
}

bool
MFRSCommManager::stop()
{
	msgFuncMap.clear();
	return true;
}

void
MFRSCommManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}
void MFRSCommManager::
recvDeployScenarioInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("SimulationManager"));
}

void MFRSCommManager::
recvScenarioACKInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("UDPCommunicationManager"));
}

void MFRSCommManager::
recvStartSimulationInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	tcout << _T(
		"[MFRSCommManager] StartSimulationInnerManager received.")
		<< std::endl;

	mec->sendMsg(
		nomMsg,
		_T("SimulationManager"));
}

void MFRSCommManager::
recvStopSimulationInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	tcout << _T(
		"[MFRSCommManager] StopSimulationInnerManager received.")
		<< std::endl;

	mec->sendMsg(
		nomMsg,
		_T("SimulationManager"));
}

void MFRSCommManager::
recvATInfoInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("DetectManager"));
}

void MFRSCommManager::
recvRadarDetectionInfoInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("UDPCommunicationManager"));
}

void MFRSCommManager::
recvUplinkInfoToDatalinkInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("DatalinkManager"));
}

void MFRSCommManager::
recvUplinkInfoToUDPInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("UDPCommunicationManager"));
}

void MFRSCommManager::
recvDownlinkInfoToDatalinkInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("DatalinkManager"));
}

void MFRSCommManager::
recvDownlinkInfoToUDPInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("UDPCommunicationManager"));
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new MFRSCommManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
