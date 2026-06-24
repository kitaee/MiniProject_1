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

	funcMapInit();
}

void
SimulationManager::release(void)
{
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
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	auto iter = funcMap.find(nomMsg->getName());
	if (iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
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

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
SimulationManager::stop()
{
	bool result = true;
	return result;
}

void
SimulationManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void
SimulationManager::funcMapInit()
{
	std::function<void(std::shared_ptr<NOM>)> msgProc;

	msgProc = std::bind(&SimulationManager::recvDeployScenarioRequest, this, std::placeholders::_1);
	funcMap.insert({ _T("DeployScenarioRequest"), msgProc });

	msgProc = std::bind(&SimulationManager::recvStartSimulationRequest, this, std::placeholders::_1);
	funcMap.insert({ _T("StartSimulationRequest"), msgProc });

	msgProc = std::bind(&SimulationManager::recvStopSimulationRequest, this, std::placeholders::_1);
	funcMap.insert({ _T("StopSimulationRequest"), msgProc });

	msgProc = std::bind(&SimulationManager::recvDetonationInfo, this, std::placeholders::_1);
	funcMap.insert({ _T("DetonationInfo"), msgProc });
}

void
SimulationManager::recvDeployScenarioRequest(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("DeployScenarioToModel"));

	NUInteger msgID(2201);
	modelMsg->setValue(_T("MessageHeader.MessageID"), &msgID);

	auto airthreat = nomMsg->getDataTypeObject(_T("Airthreat"));
	if (!airthreat)
	{
		tcout << _T("[SimulationManager] DeployScenarioRequest has no Airthreat.") << std::endl;
		return;
	}

	if (!modelMsg->setDataTypeObjectByCopying(_T("Airthreat"), airthreat))
	{
		tcout << _T("[SimulationManager] failed to set Airthreat to DeployScenarioToModel.") << std::endl;
		return;
	}

	NUInteger msgLength(modelMsg->getLength());
	modelMsg->setValue(_T("MessageHeader.MessageLength"), &msgLength);

	forwardToModel(modelMsg);
	sendScenarioACK(nomMsg);
}

void
SimulationManager::recvStartSimulationRequest(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("StartSimulationToModel"));

	NUInteger msgID(2202);
	modelMsg->setValue(_T("MessageHeader.MessageID"), &msgID);
	NUInteger msgLength(modelMsg->getLength());
	modelMsg->setValue(_T("MessageHeader.MessageLength"), &msgLength);

	forwardToModel(modelMsg);
}

void
SimulationManager::recvStopSimulationRequest(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("StopSimulationToModel"));

	NUInteger msgID(2203);
	modelMsg->setValue(_T("MessageHeader.MessageID"), &msgID);
	NUInteger msgLength(modelMsg->getLength());
	modelMsg->setValue(_T("MessageHeader.MessageLength"), &msgLength);

	forwardToModel(modelMsg);
}

void
SimulationManager::recvDetonationInfo(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("DetonationInfoToModel"));

	NUInteger msgID(2204);
	modelMsg->setValue(_T("MessageHeader.MessageID"), &msgID);

	auto targetID = nomMsg->getValue(_T("TargetID"));
	if (!targetID)
	{
		tcout << _T("[SimulationManager] DetonationInfo has no TargetID.") << std::endl;
		return;
	}
	modelMsg->setValue(_T("TargetID"), targetID);

	NUInteger msgLength(modelMsg->getLength());
	modelMsg->setValue(_T("MessageHeader.MessageLength"), &msgLength);

	forwardToModel(modelMsg);
}

// 모델로 보내는 내부 연동 메시지 4개 이름 다르게 해서 추가해야 됨
void
SimulationManager::forwardToModel(std::shared_ptr<NOM> modelMsg)
{
	this->sendMsg(modelMsg);
}

void
SimulationManager::sendScenarioACK(std::shared_ptr<NOM> srcMsg)
{
	auto ackMsg = meb->getNOMInstance(name, _T("ScenarioACK"));

	if (!ackMsg.get())
	{
		tcout << _T("[SimulationManager] failed to create ScenarioACK.") << std::endl;
		return;
	}

	NUInteger msgID(2101);
	NUInteger msgLength(8);

	ackMsg->setValue(_T("MessageHeader.MessageID"), &msgID);
	ackMsg->setValue(_T("MessageHeader.MessageLength"), &msgLength);


	this->sendMsg(ackMsg);
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
