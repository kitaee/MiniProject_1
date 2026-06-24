#pragma once

#include <nFramework/util/IniHandler.h>

#include "DetectManager.h"

DetectManager::DetectManager(void)
{
	initialize();
}

DetectManager::~DetectManager(void)
{
	release();
}

void DetectManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("DetectManager"));

	mec = new MECComponent;
	mec->setUser(this);
}

void DetectManager::release(void)
{
	msgFuncMap.clear();
	registeredMsgMap.clear();
	discoveredMsgMap.clear();

	delete mec;
	mec = nullptr;
	meb = nullptr;
}

std::shared_ptr<NOM> DetectManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void DetectManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName()
		<< std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void DetectManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName()
		<< std::endl;
	mec->updateMsg(nomMsg);
}

void DetectManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName()
		<< std::endl;
}

void DetectManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName()
		<< std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void DetectManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName()
		<< std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void DetectManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName()
		<< std::endl;
	mec->sendMsg(nomMsg);
}

void DetectManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	const auto iter = msgFuncMap.find(nomMsg->getName());
	if (iter == msgFuncMap.end())
		return;

	iter->second(nomMsg);
}

void DetectManager::setUserName(tstring userName)
{
	name = userName;
}

tstring DetectManager::getUserName()
{
	return name;
}

void DetectManager::setData(void* data)
{
}

bool DetectManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("DetectManager/DetectManager.ini"));

	msgFuncMap.clear();
	msgFuncMap.emplace(
		_T("ATInfoInnerManager"),
		std::bind(
			&DetectManager::recvATInfoInnerManager,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("RadarDetectionInfoInnerManager"),
		std::bind(
			&DetectManager::recvRadarDetectionInfoInnerManager,
			this,
			std::placeholders::_1));

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool DetectManager::stop()
{
	msgFuncMap.clear();
	return true;
}

void DetectManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void DetectManager::recvATInfoInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	auto targetInfo = meb->getNOMInstance(
		name, _T("TargetInfoInnerManager"));
	if (!targetInfo)
		return;

	const auto airthreatID =
		nomMsg->getValue(_T("AirthreatID"));
	const auto airthreatStatus =
		nomMsg->getValue(_T("AirthreatStatus"));
	const auto airthreatXPos =
		nomMsg->getValue(_T("AirthreatXPos"));
	const auto airthreatYPos =
		nomMsg->getValue(_T("AirthreatYPos"));
	const auto airthreatVelocity =
		nomMsg->getValue(_T("AirthreatVelocity"));

	if (!airthreatID || !airthreatStatus ||
		!airthreatXPos || !airthreatYPos ||
		!airthreatVelocity)
	{
		return;
	}

	NUInteger targetID(airthreatID->toUInt());
	NUInteger targetStatus(airthreatStatus->toUInt());
	NFloat targetXPos(airthreatXPos->toFloat());
	NFloat targetYPos(airthreatYPos->toFloat());
	NFloat targetVelocity(airthreatVelocity->toFloat());

	targetInfo->setValue(_T("TargetID"), &targetID);
	targetInfo->setValue(_T("TargetStatus"), &targetStatus);
	targetInfo->setValue(_T("TargetXPos"), &targetXPos);
	targetInfo->setValue(_T("TargetYPos"), &targetYPos);
	targetInfo->setValue(_T("TargetVelocity"), &targetVelocity);

	mec->sendMsg(
		targetInfo,
		_T("MFRSModelManager"));
}

void DetectManager::recvRadarDetectionInfoInnerManager(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !mec)
		return;

	mec->sendMsg(
		nomMsg,
		_T("MFRSCommManager"));
}

extern "C" BASEMGRDLL_API BaseManager* createObject()
{
	return new DetectManager;
}

extern "C" BASEMGRDLL_API void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
