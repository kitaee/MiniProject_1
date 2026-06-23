#pragma once
#define _USE_MATH_DEFINES
# include <nFramework/util/IniHandler.h>
# include "MFRSModelManager.h"
# include <map>
#include <iomanip>
#include <math.h>

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

	msgFuncMap.emplace(
		_T("StartSimulationInnerManager"),
		std::bind(
			&MFRSModelManager::recvStartSimulation,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("StopSimulationInnerManager"),
		std::bind(
			&MFRSModelManager::recvStopSimulation,
			this,
			std::placeholders::_1));

	msgFuncMap.emplace(
		_T("TargetInfoInnerManager"),
		std::bind(
			&MFRSModelManager::recvTargetInfo,
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

	if (!nomMsg->getValue(_T("RadarXPos")) ||
		!nomMsg->getValue(_T("RadarYPos")))
	{
		return;
	}

	float radarX =
		nomMsg->getValue(_T("RadarXPos"))->toFloat();
	float radarY =
		nomMsg->getValue(_T("RadarYPos"))->toFloat();

	tcout << std::fixed << std::setprecision(2) 
		<< _T("[MFRSModelManager] RadarXPos=")
		<< radarX
		<< _T(", RadarYPos=")
		<< radarY
		<< std::endl;

	MFRSModel =
		std::make_shared<MFRS_MODEL>();

	MFRSModel->position.x =
		radarX;

	MFRSModel->position.y =
		radarY;

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

void MFRSModelManager::recvStartSimulation(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	isSimulationRunning = true;

	tcout << _T(
		"[MFRSModelManager] StartSimulationInnerManager received.")
		<< std::endl;
	tcout << _T(
		"[MFRSModelManager] Current simulation state: START.")
		<< std::endl;
}

void MFRSModelManager::recvStopSimulation(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	isSimulationRunning = false;

	tcout << _T(
		"[MFRSModelManager] StopSimulationInnerManager received.")
		<< std::endl;
	tcout << _T(
		"[MFRSModelManager] Current simulation state: STOPPED.")
		<< std::endl;
}

void MFRSModelManager::recvTargetInfo(
	std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	const auto targetID =
		nomMsg->getValue(_T("TargetID"));
	const auto targetStatus =
		nomMsg->getValue(_T("TargetStatus"));
	const auto targetXPos =
		nomMsg->getValue(_T("TargetXPos"));
	const auto targetYPos =
		nomMsg->getValue(_T("TargetYPos"));
	const auto targetVelocity =
		nomMsg->getValue(_T("TargetVelocity"));

	if (!targetID || !targetStatus ||
		!targetXPos || !targetYPos ||
		!targetVelocity)
	{
		return;
	}

	if (!MFRSModel)
	{
		tcerr << _T(
			"[MFRSModelManager] MFRSModel is not initialized. Ignore TargetInfoInnerManager.")
			<< std::endl;
		return;
	}

	const unsigned int targetIDValue =
		targetID->toUInt();
	const unsigned int targetStatusValue =
		targetStatus->toUInt();
	const float targetXPosValue =
		targetXPos->toFloat();
	const float targetYPosValue =
		targetYPos->toFloat();
	const float targetVelocityValue =
		targetVelocity->toFloat();
	

	// my detection
	/*float dx = targetXPosValue - (MFRSModel->position.x);
	float dy = targetYPosValue - (MFRSModel->position.y);
	float dist_m = std::sqrt(dx * dx + dy * dy) / 1000.0F;
	double az_rad = std::atan2(dx, dy);
	double azimuth = std::fmod(az_rad * (180.0 / M_PI) + 540.0, 360.0) - 180.0;
	*/
	
	float dist_m = 0.0f;
	float azimuth = 0.0f;

	// Haversine 공식의 a 값
	double a =
		std::sin(((double)targetYPosValue - (double)MFRSModel->position.y) * M_PI / 180.0 / 2.0)
		* std::sin(((double)targetYPosValue - (double)MFRSModel->position.y) * M_PI / 180.0 / 2.0)

		+ std::cos((double)MFRSModel->position.y * M_PI / 180.0)
		* std::cos((double)targetYPosValue * M_PI / 180.0)

		* std::sin(((double)targetXPosValue - (double)MFRSModel->position.x) * M_PI / 180.0 / 2.0)
		* std::sin(((double)targetXPosValue - (double)MFRSModel->position.x) * M_PI / 180.0 / 2.0);

	// 부동소수점 오차로 a가 1보다 살짝 커지거나 0보다 작아지는 것 방지
	a = std::clamp(a, 0.0, 1.0);

	// 거리 계산, 단위 meter
	dist_m = (float)(
		6371008.8 * 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a))
		);

	// 방위각 계산, 정북 기준 -180 ~ 180도
	azimuth = (float)(
		std::atan2(
			std::sin(((double)targetXPosValue - (double)MFRSModel->position.x) * M_PI / 180.0)
			* std::cos((double)targetYPosValue * M_PI / 180.0),

			std::cos((double)MFRSModel->position.y * M_PI / 180.0)
			* std::sin((double)targetYPosValue * M_PI / 180.0)

			- std::sin((double)MFRSModel->position.y * M_PI / 180.0)
			* std::cos((double)targetYPosValue * M_PI / 180.0)
			* std::cos(((double)targetXPosValue - (double)MFRSModel->position.x) * M_PI / 180.0)
		)
		* 180.0 / M_PI
		);

	int detectedflag = (dist_m <= MFRSModel->maxDetectionRangeKm*1000) &&
		(azimuth >= MFRSModel->minDetectionAzimuthDeg) &&
		(azimuth <= MFRSModel->maxDetectionAzimuthDeg);

	if (targetStatusValue == 2) detectedflag = 2;

	tcout << _T("[MFRSModelManager] Radar X: ")
		<< MFRSModel->position.x
		<< _T(", Radar Y: ")
		<< MFRSModel->position.y
		<< _T(", dist_m: ")
		<< dist_m
		<< _T(" m, azimuth: ")
		<< azimuth
		<< std::endl;

	auto radarDetectionInfo =
		meb->getNOMInstance(
			name,
			_T("RadarDetectionInfoInnerManager"));

	if (!radarDetectionInfo)
		return;

	NUInteger radarTargetID(targetIDValue);
	NFloat radarTargetXPos(targetXPosValue);
	NFloat radarTargetYPos(targetYPosValue);
	NUInteger radarDetectedFlag(detectedflag);
	NFloat radarTargetVelocity(targetVelocityValue);

	radarDetectionInfo->setValue(
		_T("TargetID"),
		&radarTargetID);
	radarDetectionInfo->setValue(
		_T("TargetXPos"),
		&radarTargetXPos);
	radarDetectionInfo->setValue(
		_T("TargetYPos"),
		&radarTargetYPos);
	radarDetectionInfo->setValue(
		_T("DetectedFlag"),
		&radarDetectedFlag);
	radarDetectionInfo->setValue(
		_T("TargetVelocity"),
		&radarTargetVelocity);

	mec->sendMsg(
		radarDetectionInfo,
		_T("DetectManager"));
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
