#pragma once
# include <nFramework/util/IniHandler.h>
# include "DatalinkManager.h"
# include <map>

/**
* @ class: DatalinkManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
DatalinkManager::DatalinkManager(void)
{
	initialize();
}

DatalinkManager::~DatalinkManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
DatalinkManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("DatalinkManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
DatalinkManager::release(void)
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
DatalinkManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
DatalinkManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
DatalinkManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
DatalinkManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
DatalinkManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
DatalinkManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
DatalinkManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
DatalinkManager::recvMsg(std::shared_ptr < NOM > nomMsg)
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
DatalinkManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
DatalinkManager::getUserName()
{
	return name;
}

void
DatalinkManager::setData(void * data)
{
}

bool
DatalinkManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("DatalinkManager/DatalinkManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	msgFuncMap.clear();

	msgFuncMap.emplace(
		_T("UplinkInfoToDatalinkInnerManager"),
		std::bind(
			&DatalinkManager::recvUplinkInfoToDatalinkInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("DownlinkInfoToDatalinkInnerManager"),
		std::bind(
			&DatalinkManager::recvDownlinkInfoToDatalinkInnerManager,
			this,
			std::placeholders::_1));

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
DatalinkManager::stop()
{
	msgFuncMap.clear();
	return true;
}

void
DatalinkManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void DatalinkManager::recvUplinkInfoToDatalinkInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	auto uplinkInfo =
		meb->getNOMInstance(
			name,
			_T("UplinkInfoToUDPInnerManager"));
	if (!uplinkInfo)
		return;

	const auto airthreatID =
		nomMsg->getValue(_T("AirthreatID"));
	const auto airthreatXPos =
		nomMsg->getValue(_T("AirthreatXPos"));
	const auto airthreatYPos =
		nomMsg->getValue(_T("AirthreatYPos"));
	const auto missileID =
		nomMsg->getValue(_T("MissileID"));
	const auto airthreatVelocity =
		nomMsg->getValue(_T("AirthreatVelocity"));

	if (!airthreatID || !airthreatXPos || !airthreatYPos ||
		!missileID || !airthreatVelocity)
	{
		return;
	}

	NUInteger airthreatIDValue(airthreatID->toUInt());
	NFloat airthreatXValue(airthreatXPos->toFloat());
	NFloat airthreatYValue(airthreatYPos->toFloat());
	NUInteger missileIDValue(missileID->toUInt());
	NFloat airthreatVelocityValue(airthreatVelocity->toFloat());

	uplinkInfo->setValue(
		_T("AirthreatID"),
		&airthreatIDValue);
	uplinkInfo->setValue(
		_T("AirthreatXPos"),
		&airthreatXValue);
	uplinkInfo->setValue(
		_T("AirthreatYPos"),
		&airthreatYValue);
	uplinkInfo->setValue(
		_T("MissileID"),
		&missileIDValue);
	uplinkInfo->setValue(
		_T("AirthreatVelocity"),
		&airthreatVelocityValue);

	mec->sendMsg(
		uplinkInfo,
		_T("MFRSCommManager"));
}

void DatalinkManager::recvDownlinkInfoToDatalinkInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	auto downlinkInfo =
		meb->getNOMInstance(
			name,
			_T("DownlinkInfoToUDPInnerManager"));
	if (!downlinkInfo)
		return;

	const auto missileID =
		nomMsg->getValue(_T("MissileID"));
	const auto missileVelocity =
		nomMsg->getValue(_T("MissileVelocity"));
	const auto missileXPos =
		nomMsg->getValue(_T("MissileXPos"));
	const auto missileYPos =
		nomMsg->getValue(_T("MissileYPos"));

	if (!missileID || !missileVelocity ||
		!missileXPos || !missileYPos)
	{
		return;
	}

	NUInteger missileIDValue(missileID->toUInt());
	NFloat missileVelocityValue(missileVelocity->toFloat());
	NFloat missileXValue(missileXPos->toFloat());
	NFloat missileYValue(missileYPos->toFloat());

	downlinkInfo->setValue(
		_T("MissileID"),
		&missileIDValue);
	downlinkInfo->setValue(
		_T("MissileVelocity"),
		&missileVelocityValue);
	downlinkInfo->setValue(
		_T("MissileXPos"),
		&missileXValue);
	downlinkInfo->setValue(
		_T("MissileYPos"),
		&missileYValue);

	mec->sendMsg(
		downlinkInfo,
		_T("MFRSCommManager"));
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new DatalinkManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
