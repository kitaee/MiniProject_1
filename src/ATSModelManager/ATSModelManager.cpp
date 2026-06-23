#pragma once
# include <nFramework/util/IniHandler.h>
# include "ATSModelManager.h"
# include <map>
# include <cmath>

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
	stopSimulationLoop();

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
	stopSimulationLoop();
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

	resetAirthreatState();

	auto airthreatID = nomMsg->getValue(_T("Airthreat.AirthreatID"));
	auto airthreatVelocity = nomMsg->getValue(_T("Airthreat.AirthreatVelocity"));
	auto startXPos = nomMsg->getValue(_T("Airthreat.StartXPos"));
	auto startYPos = nomMsg->getValue(_T("Airthreat.StartYPos"));
	auto endXPos = nomMsg->getValue(_T("Airthreat.EndXPos"));
	auto endYPos = nomMsg->getValue(_T("Airthreat.EndYPos"));

	if (!airthreatID || !airthreatVelocity || !startXPos || !startYPos || !endXPos || !endYPos)
	{
		tcout << _T("[ATSModelManager] DeployScenarioToModel has invalid Airthreat fields.") << std::endl;
		return;
	}

	airthreatState.airthreatID = airthreatID->toUInt();
	airthreatState.airthreatVelocity = airthreatVelocity->toFloat();
	airthreatState.airthreatStartXPos = startXPos->toFloat();
	airthreatState.airthreatStartYPos = startYPos->toFloat();
	airthreatState.airthreatEndXPos = endXPos->toFloat();
	airthreatState.airthreatEndYPos = endYPos->toFloat();
	airthreatState.airthreatXPos = airthreatState.airthreatStartXPos;
	airthreatState.airthreatYPos = airthreatState.airthreatStartYPos;
	airthreatState.scenarioLoaded = true;
	airthreatState.airThreatDetonated = false;
}

void
ATSModelManager::recvStartSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	if (!airthreatState.scenarioLoaded)
	{
		tcout << _T("[ATSModelManager] cannot start simulation: scenario is not loaded.") << std::endl;
		return;
	}
	if (airthreatState.airThreatDetonated)
	{
		tcout << _T("[ATSModelManager] cannot start simulation: air threat is already detonated.") << std::endl;
		return;
	}

	airthreatState.simulationRunning = true;
	startSimulationLoop();
}

void
ATSModelManager::recvStopSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	stopSimulationLoop();
	resetAirthreatState();
}

void
ATSModelManager::recvDetonationInfoToModel(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	auto targetID = nomMsg->getValue(_T("TargetID"));
	if (!targetID)
	{
		tcout << _T("[ATSModelManager] DetonationInfoToModel has no TargetID.") << std::endl;
		return;
	}

	{
		std::lock_guard<std::mutex> lock(airthreatStateMutex);

		if (!airthreatState.scenarioLoaded)
		{
			tcout << _T("[ATSModelManager] cannot process detonation: scenario is not loaded.") << std::endl;
			return;
		}

		if (targetID->toUInt() != airthreatState.airthreatID)
		{
			tcout << _T("[ATSModelManager] DetonationInfoToModel TargetID does not match current air threat.") << std::endl;
			return;
		}

		airthreatState.simulationRunning = false;
		airthreatState.airThreatDetonated = true;
	}

	stopSimulationLoop();
	sendATInfo();
}

void
ATSModelManager::sendATInfo()
{
	tcout << _T("[ATSModelManager::sendATInfo] ATInfo") << std::endl;

	auto atInfoMsg = meb->getNOMInstance(name, _T("ATInfo"));

	if (!atInfoMsg.get())
	{
		tcout << _T("[ATSModelManager] failed to create ATInfo.") << std::endl;
		return;
	}

	NUInteger messageID(2501);
	atInfoMsg->setValue(_T("MessageHeader.MessageID"), &messageID);

	NUInteger airthreatID(0);
	NUInteger airthreatStatus(0);
	NFloat airthreatXPos(0.0f);
	NFloat airthreatYPos(0.0f);
	NFloat airthreatVelocity(0.0f);
	unsigned int logAirthreatID = 0;
	unsigned int logAirthreatStatus = 0;
	float logAirthreatXPos = 0.0f;
	float logAirthreatYPos = 0.0f;
	float logAirthreatVelocity = 0.0f;

	{
		std::lock_guard<std::mutex> lock(airthreatStateMutex);

		logAirthreatID = airthreatState.airthreatID;
		if (airthreatState.airThreatDetonated)
		{
			logAirthreatStatus = 2;
		}
		else if (airthreatState.simulationRunning)
		{
			logAirthreatStatus = 1;
		}
		else
		{
			logAirthreatStatus = 0;
		}
		logAirthreatXPos = airthreatState.airthreatXPos;
		logAirthreatYPos = airthreatState.airthreatYPos;
		logAirthreatVelocity = airthreatState.airthreatVelocity;
	}

	airthreatID = logAirthreatID;
	airthreatStatus = logAirthreatStatus;
	airthreatXPos = logAirthreatXPos;
	airthreatYPos = logAirthreatYPos;
	airthreatVelocity = logAirthreatVelocity;

	atInfoMsg->setValue(_T("AirthreatID"), &airthreatID);
	atInfoMsg->setValue(_T("AirthreatStatus"), &airthreatStatus);
	atInfoMsg->setValue(_T("AirthreatXPos"), &airthreatXPos);
	atInfoMsg->setValue(_T("AirthreatYPos"), &airthreatYPos);
	atInfoMsg->setValue(_T("AirthreatVelocity"), &airthreatVelocity);

	NUInteger messageLength(atInfoMsg->getLength());
	atInfoMsg->setValue(_T("MessageHeader.MessageLength"), &messageLength);

	printf("[ATSModelManager::sendATInfo] AirthreatID: %u\n", logAirthreatID);
	printf("[ATSModelManager::sendATInfo] AirthreatStatus: %u\n", logAirthreatStatus);
	printf("[ATSModelManager::sendATInfo] AirthreatXPos, AirthreatYPos: %.6f, %.6f\n", logAirthreatXPos, logAirthreatYPos);
	printf("[ATSModelManager::sendATInfo] AirthreatVelocity: %.6f\n", logAirthreatVelocity);
	this->sendMsg(atInfoMsg);
}

// XPos stores longitude, YPos stores latitude.
double ATSModelManager::calculateDistanceMeter(float currentLatitude, float currentLongitude, float endLatitude, float endLongitude)
{
	constexpr double EarthRadiusMeter = 6371000.0;

	auto toRadian = [](double degree)
		{
			return degree * 3.14159265358979323846 / 180.0;
		};

	double lat1 = toRadian(currentLatitude);
	double lon1 = toRadian(currentLongitude);
	double lat2 = toRadian(endLatitude);
	double lon2 = toRadian(endLongitude);

	double dLat = lat2 - lat1;
	double dLon = lon2 - lon1;

	double sinHalfLat = std::sin(dLat / 2.0);
	double sinHalfLon = std::sin(dLon / 2.0);

	double a =
		(sinHalfLat * sinHalfLat) +
		(std::cos(lat1) * std::cos(lat2) * sinHalfLon * sinHalfLon);

	double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

	return EarthRadiusMeter * c;
}

void ATSModelManager::resetAirthreatState()
{
	airthreatState = AirthreatState();
}

void ATSModelManager::startSimulationLoop()
{
	if (simulationLoopRunning)
	{
		return;
	}

	simulationLoopRunning = true;
	simulationThread = std::thread(&ATSModelManager::simulationLoop, this);
}

void ATSModelManager::stopSimulationLoop()
{
	simulationLoopRunning = false;

	{
		std::lock_guard<std::mutex> lock(airthreatStateMutex);
		airthreatState.simulationRunning = false;
	}

	if (simulationThread.joinable())
	{
		simulationThread.join();
	}
}

void ATSModelManager::simulationLoop()
{
	while (simulationLoopRunning)
	{
		{
			std::lock_guard<std::mutex> lock(airthreatStateMutex);

			if (!airthreatState.simulationRunning)
			{
				break;
			}

			if (!airthreatState.airThreatDetonated)
			{
				double distanceMeter = calculateDistanceMeter(
					airthreatState.airthreatYPos,
					airthreatState.airthreatXPos,
					airthreatState.airthreatEndYPos,
					airthreatState.airthreatEndXPos);

				float moveDistanceMeter = airthreatState.airthreatVelocity;

				if (distanceMeter <= moveDistanceMeter || distanceMeter <= 0.0f)
				{
					airthreatState.airthreatXPos = airthreatState.airthreatEndXPos;
					airthreatState.airthreatYPos = airthreatState.airthreatEndYPos;
					airthreatState.simulationRunning = false;
				}
				else
				{
					double ratio = moveDistanceMeter / distanceMeter;

					double dLongitude = airthreatState.airthreatEndXPos - airthreatState.airthreatXPos;
					double dLatitude = airthreatState.airthreatEndYPos - airthreatState.airthreatYPos;

					airthreatState.airthreatXPos += static_cast<float>(dLongitude * ratio);
					airthreatState.airthreatYPos += static_cast<float>(dLatitude * ratio);
				}
			}

		}

		sendATInfo();

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	simulationLoopRunning = false;
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
