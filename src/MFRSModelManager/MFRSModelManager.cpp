#pragma once
# include <nFramework/util/IniHandler.h>
# include "MFRSModelManager.h"
# include <map>

/**
* @ class: MFRSModelManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
MFRSModelManager::MFRSModelManager(void)
{
	initialize();
}

MFRSModelManager::~MFRSModelManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
MFRSModelManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("MFRSModelManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);

	MFRSModel.reset();
	msgFuncMap.clear();
	registeredMsgMap.clear();
	discoveredMsgMap.clear();
}

void
MFRSModelManager::release(void)
{
	MFRSModel.reset();
	msgFuncMap.clear();

	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
MFRSModelManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
MFRSModelManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
MFRSModelManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
MFRSModelManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
MFRSModelManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
MFRSModelManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
MFRSModelManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
MFRSModelManager::recvMsg(std::shared_ptr<NOM> nomMsg)
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
MFRSModelManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
MFRSModelManager::getUserName()
{
	return name;
}

void
MFRSModelManager::setData(void * data)
{
}

bool
MFRSModelManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(
		_T("MFRSModelManager/MFRSModelManager.ini"));

	msgFuncMap.clear();

	msgFuncMap.emplace(
		_T("DeployScenarioInnerManager"),
		std::bind(
			&MFRSModelManager::recvScenario,
			this,
			std::placeholders::_1));

	return true;
}

bool
MFRSModelManager::stop()
{
	msgFuncMap.clear();
	return true;
}

void
MFRSModelManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void MFRSModelManager::recvScenario(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb)
		return;

	const auto latitudeValue =
		nomMsg->getValue(_T("RadarPositionLatitude"));
	const auto longitudeValue =
		nomMsg->getValue(_T("RadarPositionLongitude"));

	if (!latitudeValue || !longitudeValue)
		return;

	const float latitude = latitudeValue->toFloat();
	const float longitude = longitudeValue->toFloat();

	MFRSModel =
		std::make_shared<MFRS_MODEL>();

	MFRSModel->position.latitude =
		latitude;

	MFRSModel->position.longitude =
		longitude;

	MFRSModel->position.altitude =
		0.0F;

	auto ackMsg =
		meb->getNOMInstance(
			name,
			_T("ScenarioACKInnerManager"));

	if (!ackMsg)
		return;

	NUInteger messageID(5101);
	NUInteger messageLength(8);

	ackMsg->setValue(
		_T("MessageHeader.MessageID"),
		&messageID);

	ackMsg->setValue(
		_T("MessageHeader.MessageLength"),
		&messageLength);

	mec->sendMsg(
		ackMsg,
		_T("SimulationManager"));
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new MFRSModelManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
