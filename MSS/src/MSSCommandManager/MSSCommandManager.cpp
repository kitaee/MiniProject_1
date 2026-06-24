#pragma once
# include <nFramework/util/IniHandler.h>
# include "MSSCommandManager.h"
# include <map>

/**
* @ class: MSSCommandManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
MSSCommandManager::MSSCommandManager(void)
{
	initialize();
}

MSSCommandManager::~MSSCommandManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
MSSCommandManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("MSSCommandManager"));

	currentState = MSSState::Idle; // 상태 초기화 


	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
MSSCommandManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
MSSCommandManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
MSSCommandManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
MSSCommandManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
MSSCommandManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
MSSCommandManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
MSSCommandManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
MSSCommandManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
MSSCommandManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	if (nomMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager::recvMsg] nomMsg is nullptr") << std::endl;
		return;
	}

	const tstring msgName = nomMsg->getName();

	tcout << _T("[MSSCommandManager::recvMsg] ") << msgName << std::endl;

	if (!isMessageAllowedInCurrentState(msgName))
	{
		tcout << _T("[MSSCommandManager::recvMsg] Ignored by current state. message: ")
			<< msgName << std::endl;
		return;
	}

	if (msgName == _T("InnerSendScenario"))
	{
		recvInnerSendScenario(nomMsg);
	}
	else if (msgName == _T("InnerSendCompleteInitialize"))
	{
		recvInnerSendCompleteInitialize(nomMsg);
	}
	else if (msgName == _T("InnerStartSimulation"))
	{
		recvInnerStartSimulation(nomMsg);
	}
	else if (msgName == _T("InnerStopSimulation"))
	{
		recvInnerStopSimulation(nomMsg);
	}
	else if (msgName == _T("InnerLaunchMissile"))
	{
		recvInnerLaunchMissile(nomMsg);
	}
	else if (msgName == _T("InnerUplinkInfo"))
	{
		recvInnerUplinkInfo(nomMsg);
	}
	else if (msgName == _T("InnerDownlinkInfoFromModel"))
	{
		recvInnerDownlinkInfoFromModel(nomMsg);
	}
	else if (msgName == _T("InnerDetonationEvent"))
	{
		recvInnerDetonationEvent(nomMsg);
	}
	else
	{
		tcout << _T("[MSSCommandManager::recvMsg] Unknown message: ")
			<< msgName << std::endl;
	}
}

void
MSSCommandManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
MSSCommandManager::getUserName()
{
	return name;
}

void
MSSCommandManager::setData(void * data)
{
}

bool
MSSCommandManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("MSSCommandManager/MSSCommandManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
MSSCommandManager::stop()
{
	bool result = true;
	return result;
}

void
MSSCommandManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new MSSCommandManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}



/************************************************************************
	
************************************************************************/

bool
MSSCommandManager::isMessageAllowedInCurrentState(const tstring& msgName) const
{
	if (msgName == _T("InnerStopSimulation"))
	{
		return true;
	}

	switch (currentState)
	{
	case MSSState::Idle:
		return msgName == _T("InnerSendScenario");

	case MSSState::ScenarioLoading:
		return msgName == _T("InnerSendCompleteInitialize");

	case MSSState::Ready:
		return msgName == _T("InnerStartSimulation")
			|| msgName == _T("InnerSendScenario");

	case MSSState::Running:
		return msgName == _T("InnerLaunchMissile")
			|| msgName == _T("InnerUplinkInfo")
			|| msgName == _T("InnerDownlinkInfoFromModel")
			|| msgName == _T("InnerDetonationEvent");

	case MSSState::Engaged:
		return msgName == _T("InnerUplinkInfo")
			|| msgName == _T("InnerDownlinkInfoFromModel")
			|| msgName == _T("InnerDetonationEvent");

	case MSSState::Stopped:
		return msgName == _T("InnerSendScenario");

	default:
		return false;
	}
}

/************************************************************************
	분기 함수 구현
************************************************************************/

void
MSSCommandManager::recvInnerSendScenario(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSCommandManager::recvInnerSendScenario]") << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("InnerSendScenarioToModel"));
	if (modelMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager] Failed to create InnerSendScenarioToModel") << std::endl;
		return;
	}

	NUInteger airthreatID(nomMsg->getValue(_T("Airthreat.AirthreatID"))->toUInt());
	NFloat airthreatVelocity(nomMsg->getValue(_T("Airthreat.AirthreatVelocity"))->toFloat());
	NFloat startXPos(nomMsg->getValue(_T("Airthreat.StartXPos"))->toFloat());
	NFloat startYPos(nomMsg->getValue(_T("Airthreat.StartYPos"))->toFloat());
	NFloat endXPos(nomMsg->getValue(_T("Airthreat.EndXPos"))->toFloat());
	NFloat endYPos(nomMsg->getValue(_T("Airthreat.EndYPos"))->toFloat());

	NFloat radarXPos(nomMsg->getValue(_T("RadarXPos"))->toFloat());
	NFloat radarYPos(nomMsg->getValue(_T("RadarYPos"))->toFloat());
	NFloat launcherXPos(nomMsg->getValue(_T("LauncherXPos"))->toFloat());
	NFloat launcherYPos(nomMsg->getValue(_T("LauncherYPos"))->toFloat());
	NFloat missileVelocity(nomMsg->getValue(_T("MissileVelocity"))->toFloat());

	modelMsg->setValue(_T("Airthreat.AirthreatID"), &airthreatID);
	modelMsg->setValue(_T("Airthreat.AirthreatVelocity"), &airthreatVelocity);
	modelMsg->setValue(_T("Airthreat.StartXPos"), &startXPos);
	modelMsg->setValue(_T("Airthreat.StartYPos"), &startYPos);
	modelMsg->setValue(_T("Airthreat.EndXPos"), &endXPos);
	modelMsg->setValue(_T("Airthreat.EndYPos"), &endYPos);

	modelMsg->setValue(_T("RadarXPos"), &radarXPos);
	modelMsg->setValue(_T("RadarYPos"), &radarYPos);
	modelMsg->setValue(_T("LauncherXPos"), &launcherXPos);
	modelMsg->setValue(_T("LauncherYPos"), &launcherYPos);
	modelMsg->setValue(_T("MissileVelocity"), &missileVelocity);

	sendMsg(modelMsg);

	currentState = MSSState::ScenarioLoading;
}


void
MSSCommandManager::recvInnerSendCompleteInitialize(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSCommandManager::recvInnerSendCompleteInitialize]") << std::endl;

	auto ackMsg = meb->getNOMInstance(name, _T("InnerSendScenarioAck"));
	if (ackMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager] Failed to create InnerSendScenarioAck") << std::endl;
		return;
	}

	sendMsg(ackMsg);

	currentState = MSSState::Ready;
}

void
MSSCommandManager::recvInnerStartSimulation(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSCommandManager::recvInnerStartSimulation]") << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("InnerStartSimulationToModel"));
	if (modelMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager] Failed to create InnerStartSimulationToModel") << std::endl;
		return;
	}

	sendMsg(modelMsg);

	currentState = MSSState::Running;
}

void
MSSCommandManager::recvInnerStopSimulation(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSCommandManager::recvInnerStopSimulation]") << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("InnerStopSimulationToModel"));
	if (modelMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager] Failed to create InnerStopSimulationToModel") << std::endl;
		return;
	}

	sendMsg(modelMsg);

	currentState = MSSState::Stopped;
}

void
MSSCommandManager::recvInnerLaunchMissile(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSCommandManager::recvInnerLaunchMissile]") << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("InnerLaunchMissileToModel"));
	if (modelMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager] Failed to create InnerLaunchMissileToModel") << std::endl;
		return;
	}

	NUInteger airthreatID(nomMsg->getValue(_T("AirthreatID"))->toUInt());
	NFloat airthreatXPos(nomMsg->getValue(_T("AirthreatXPos"))->toFloat());
	NFloat airthreatYPos(nomMsg->getValue(_T("AirthreatYPos"))->toFloat());
	NUInteger missileID(nomMsg->getValue(_T("MissileID"))->toUInt());
	NFloat lcsXPos(nomMsg->getValue(_T("LCSXPos"))->toFloat());
	NFloat lcsYPos(nomMsg->getValue(_T("LCSYPos"))->toFloat());

	modelMsg->setValue(_T("AirthreatID"), &airthreatID);
	modelMsg->setValue(_T("AirthreatXPos"), &airthreatXPos);
	modelMsg->setValue(_T("AirthreatYPos"), &airthreatYPos);
	modelMsg->setValue(_T("MissileID"), &missileID);
	modelMsg->setValue(_T("LCSXPos"), &lcsXPos);
	modelMsg->setValue(_T("LCSYPos"), &lcsYPos);

	sendMsg(modelMsg);

	currentState = MSSState::Engaged;
}

void
MSSCommandManager::recvInnerUplinkInfo(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSCommandManager::recvInnerUplinkInfo]") << std::endl;

	auto modelMsg = meb->getNOMInstance(name, _T("InnerUplinkInfoToModel"));
	if (modelMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager] Failed to create InnerUplinkInfoToModel") << std::endl;
		return;
	}

	NUInteger airthreatID(nomMsg->getValue(_T("UplinkInfo.AirthreatID"))->toUInt());
	NFloat airthreatXPos(nomMsg->getValue(_T("UplinkInfo.AirthreatXPos"))->toFloat());
	NFloat airthreatYPos(nomMsg->getValue(_T("UplinkInfo.AirthreatYPos"))->toFloat());
	NUInteger missileID(nomMsg->getValue(_T("UplinkInfo.MissileID"))->toUInt());
	NFloat airthreatVelocity(nomMsg->getValue(_T("UplinkInfo.AirthreatVelocity"))->toFloat());

	modelMsg->setValue(_T("UplinkInfo.AirthreatID"), &airthreatID);
	modelMsg->setValue(_T("UplinkInfo.AirthreatXPos"), &airthreatXPos);
	modelMsg->setValue(_T("UplinkInfo.AirthreatYPos"), &airthreatYPos);
	modelMsg->setValue(_T("UplinkInfo.MissileID"), &missileID);
	modelMsg->setValue(_T("UplinkInfo.AirthreatVelocity"), &airthreatVelocity);

	sendMsg(modelMsg);
}

void
MSSCommandManager::recvInnerDownlinkInfoFromModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSCommandManager::recvInnerDownlinkInfoFromModel]") << std::endl;

	auto udpMsg = meb->getNOMInstance(name, _T("InnerDownlinkInfo"));
	if (udpMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager] Failed to create InnerDownlinkInfo") << std::endl;
		return;
	}

	NUInteger missileID(nomMsg->getValue(_T("DownlinkInfo.MissileID"))->toUInt());
	NFloat missileVelocity(nomMsg->getValue(_T("DownlinkInfo.MissileVelocity"))->toFloat());
	NFloat missileXPos(nomMsg->getValue(_T("DownlinkInfo.MissileXPos"))->toFloat());
	NFloat missileYPos(nomMsg->getValue(_T("DownlinkInfo.MissileYPos"))->toFloat());

	udpMsg->setValue(_T("DownlinkInfo.MissileID"), &missileID);
	udpMsg->setValue(_T("DownlinkInfo.MissileVelocity"), &missileVelocity);
	udpMsg->setValue(_T("DownlinkInfo.MissileXPos"), &missileXPos);
	udpMsg->setValue(_T("DownlinkInfo.MissileYPos"), &missileYPos);

	sendMsg(udpMsg);
}

void
MSSCommandManager::recvInnerDetonationEvent(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSCommandManager::recvInnerDetonationEvent]") << std::endl;

	auto udpMsg = meb->getNOMInstance(name, _T("InnerDetonationInfo"));
	if (udpMsg == nullptr)
	{
		tcerr << _T("[MSSCommandManager] Failed to create InnerDetonationInfo") << std::endl;
		return;
	}

	NUInteger missileID(nomMsg->getValue(_T("MissileID"))->toUInt());
	NUInteger targetID(nomMsg->getValue(_T("TargetID"))->toUInt());

	udpMsg->setValue(_T("MissileID"), &missileID);
	udpMsg->setValue(_T("TargetID"), &targetID);

	sendMsg(udpMsg);

	currentState = MSSState::Stopped;
}