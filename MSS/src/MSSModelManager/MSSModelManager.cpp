#pragma once
# include <nFramework/util/IniHandler.h>
# include "MSSModelManager.h"
# include <map>
#include <memory>
#include "IGuidanceModel.h"
#include "Missile.h"
#include "PurePursuitGuidanceModel.h"

/**
* @ class: MSSModelManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
MSSModelManager::MSSModelManager(void)
{
	initialize();
}

MSSModelManager::~MSSModelManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
MSSModelManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("MSSModelManager"));

	missile = std::make_unique<Missile>(std::make_unique<PurePursuitGuidanceModel>()
	);


	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
MSSModelManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
MSSModelManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
MSSModelManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
MSSModelManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
MSSModelManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
MSSModelManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
MSSModelManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
MSSModelManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
MSSModelManager::recvMsg(std::shared_ptr < NOM > nomMsg)
{
	if (nomMsg == nullptr)
	{
		tcerr << _T("[MSSModelManager::recvMsg] nomMsg is nullptr") << std::endl;
		return;
	}

	const tstring msgName = nomMsg->getName();

	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	tcout << _T("[MSSModelManager::recvMsg] ") << msgName << std::endl;

	if (msgName == _T("InnerSendScenarioToModel"))
	{
		recvInnerSendScenarioToModel(nomMsg);
	}
	else if (msgName == _T("InnerStartSimulationToModel"))
	{
		recvInnerStartSimulationToModel(nomMsg);
	}
	else if (msgName == _T("InnerStopSimulationToModel"))
	{
		recvInnerStopSimulationToModel(nomMsg);
	}
	else if (msgName == _T("InnerLaunchMissileToModel"))
	{
		recvInnerLaunchMissileToModel(nomMsg);
	}
	else if (msgName == _T("InnerUplinkInfoToModel"))
	{
		recvInnerUplinkInfoToModel(nomMsg);
	}
	else
	{
		tcout << _T("[MSSModelManager::recvMsg] Unknown message: ")
			<< msgName << std::endl;
	}
}

void
MSSModelManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
MSSModelManager::getUserName()
{
	return name;
}

void
MSSModelManager::setData(void * data)
{
}

bool
MSSModelManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("MSSModelManager/MSSModelManager.ini")); // ?살＜???묒뾽?붾젆?곕━: Main.exe媛 ?덈뒗 寃쎈줈

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
MSSModelManager::stop()
{
	bool result = true;
	return result;
}

void
MSSModelManager::setMEBComponent(IMEBComponent * realMEB)
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
	return new MSSModelManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}



/************************************************************************
	
************************************************************************/
void
MSSModelManager::recvInnerSendScenarioToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSModelManager::recvInnerSendScenarioToModel]") << std::endl;

	if (nomMsg == nullptr)
	{
		tcerr << _T("[MSSModelManager::recvInnerSendScenarioToModel] nomMsg is nullptr") << std::endl;
		return;
	}

	if (missile == nullptr)
	{
		tcerr << _T("[MSSModelManager::recvInnerSendScenarioToModel] missile is nullptr") << std::endl;
		return;
	}

	NFloat missileVelocity(nomMsg->getValue(_T("MissileVelocity"))->toFloat());
	missile->setVelocity(0.00787f);

	auto completeMsg = meb->getNOMInstance(name, _T("InnerSendCompleteInitialize"));
	if (completeMsg == nullptr)
	{
		tcerr << _T("[MSSModelManager] Failed to create InnerSendCompleteInitialize") << std::endl;
		return;
	}

	sendMsg(completeMsg);
}

void
MSSModelManager::recvInnerStartSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSModelManager::recvInnerStartSimulationToModel]") << std::endl;
}

void
MSSModelManager::recvInnerStopSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSModelManager::recvInnerStopSimulationToModel]") << std::endl;

	if (missile == nullptr)
	{
		tcerr << _T("[MSSModelManager::recvInnerStopSimulationToModel] missile is nullptr") << std::endl;
		return;
	}

	missile->resetSimulation();
}


void
MSSModelManager::recvInnerLaunchMissileToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSModelManager::recvInnerLaunchMissileToModel]") << std::endl;

	if (nomMsg == nullptr)
	{
		tcerr << _T("[MSSModelManager::recvInnerLaunchMissileToModel] nomMsg is nullptr") << std::endl;
		return;
	}

	if (missile == nullptr)
	{
		tcerr << _T("[MSSModelManager::recvInnerLaunchMissileToModel] missile is nullptr") << std::endl;
		return;
	}

	const uint32_t airthreatID = nomMsg->getValue(_T("AirthreatID"))->toUInt();
	const float airthreatXPos = nomMsg->getValue(_T("AirthreatXPos"))->toFloat();
	const float airthreatYPos = nomMsg->getValue(_T("AirthreatYPos"))->toFloat();
	const uint32_t missileID = nomMsg->getValue(_T("MissileID"))->toUInt();
	const float lcsXPos = nomMsg->getValue(_T("LCSXPos"))->toFloat();
	const float lcsYPos = nomMsg->getValue(_T("LCSYPos"))->toFloat();

	AirThreatInfo airThreatInfo{
		airthreatID,
		airthreatXPos,
		airthreatYPos,
		0.0f
	};

	missile->launch(missileID, lcsXPos, lcsYPos, airThreatInfo);
}

void
MSSModelManager::recvInnerUplinkInfoToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[MSSModelManager::recvInnerUplinkInfoToModel]") << std::endl;

	if (nomMsg == nullptr)
	{
		tcerr << _T("[MSSModelManager::recvInnerUplinkInfoToModel] nomMsg is nullptr") << std::endl;
		return;
	}

	if (missile == nullptr)
	{
		tcerr << _T("[MSSModelManager::recvInnerUplinkInfoToModel] missile is nullptr") << std::endl;
		return;
	}

	AirThreatInfo airThreatInfo{
		nomMsg->getValue(_T("UplinkInfo.AirthreatID"))->toUInt(),
		nomMsg->getValue(_T("UplinkInfo.AirthreatXPos"))->toFloat(),
		nomMsg->getValue(_T("UplinkInfo.AirthreatYPos"))->toFloat(),
		nomMsg->getValue(_T("UplinkInfo.AirthreatVelocity"))->toFloat()
	};

	missile->updatePosition(airThreatInfo);

	if (missile->isDetonated())
	{
		auto detonationMsg = meb->getNOMInstance(name, _T("InnerDetonationEvent"));
		if (detonationMsg == nullptr)
		{
			tcerr << _T("[MSSModelManager] Failed to create InnerDetonationEvent") << std::endl;
			return;
		}

		NUInteger missileID(nomMsg->getValue(_T("UplinkInfo.MissileID"))->toUInt());
		NUInteger targetID(airThreatInfo.airthreatID);

		detonationMsg->setValue(_T("MissileID"), &missileID);
		detonationMsg->setValue(_T("TargetID"), &targetID);

		sendMsg(detonationMsg);
		missile->resetSimulation();
		return;
	}

	const MissileInfo& missileInfo = missile->getMissileInfo();
	auto downlinkMsg = meb->getNOMInstance(name, _T("InnerDownlinkInfoFromModel"));
	if (downlinkMsg == nullptr)
	{
		tcerr << _T("[MSSModelManager] Failed to create InnerDownlinkInfoFromModel") << std::endl;
		return;
	}

	NUInteger missileID(missileInfo.missileID);
	NFloat missileVelocity(missileInfo.missileVelocity);
	NFloat missileXPos(missileInfo.missileXPos);
	NFloat missileYPos(missileInfo.missileYPos);

	downlinkMsg->setValue(_T("DownlinkInfo.MissileID"), &missileID);
	downlinkMsg->setValue(_T("DownlinkInfo.MissileVelocity"), &missileVelocity);
	downlinkMsg->setValue(_T("DownlinkInfo.MissileXPos"), &missileXPos);
	downlinkMsg->setValue(_T("DownlinkInfo.MissileYPos"), &missileYPos);

	sendMsg(downlinkMsg);
	//로깅
	printf(
		"[DownlinkInfo] MissileID=%u, MissileVelocity=%.3f, MissileXPos=%.3f, MissileYPos=%.3f\n",
		missileInfo.missileID,
		missileInfo.missileVelocity,
		missileInfo.missileXPos,
		missileInfo.missileYPos
	);


}

