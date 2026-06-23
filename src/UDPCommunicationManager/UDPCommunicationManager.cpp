#include "UDPCommunicationManager.h"

#include <cstring>
#include <filesystem>
#include <iomanip>

using namespace std::filesystem;

UDPCommunicationManager::UDPCommunicationManager(void)
{
	init();
}

UDPCommunicationManager::~UDPCommunicationManager(void)
{
	release();
}

void UDPCommunicationManager::init()
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("UDPCommunicationManager"));

	mec = new MECComponent;
	mec->setUser(this);

	commConfig = new CommunicationConfig;
	commConfig->setIni(_T("CommLinkInfo.ini"));

	tstring schemaRegistryPath = current_path().c_str();
	schemaRegistryPath += _T("\\..\\SchemaRegistryData.xml");
	nomParser = std::make_unique<NOMParser>();
	nomParser->setNOMFile(schemaRegistryPath);
	nomParser->parseNote();
	auto noteMap = nomParser->getNoteMap();
	nomParser->parseDataType();
	auto dataTypeMap = nomParser->getDataTypeMap();

	tstring nomFilePath = current_path().c_str();
	nomFilePath += _T("\\");
	nomFilePath += getUserName();
	nomFilePath += _T(".xml");
	nomParser->setNOMFile(nomFilePath);

	if (nomParser->parse(dataTypeMap, noteMap))
	{
		list<NMessage*> msgList = nomParser->getMessageList();
		for (auto* nMsg : msgList)
		{
			if (nMsg)
			{
				commMsgHandler.setIDNameTable(
					nMsg->getMessageID(), nMsg->getName());
			}
		}
	}

	funcMapInit();
}

void UDPCommunicationManager::release()
{
	if (commInterface)
		stop();

	delete commConfig;
	commConfig = nullptr;
	meb = nullptr;
	delete mec;
	mec = nullptr;
	funcMap.clear();
	registeredMsg.clear();
	discoveredMsg.clear();
	nomParser.reset();
}

shared_ptr<NOM> UDPCommunicationManager::registerMsg(tstring msgName)
{
	shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	if (nomMsg)
	{
		registeredMsg.insert({ nomMsg->getInstanceID(), nomMsg });
	}
	return nomMsg;
}

void UDPCommunicationManager::discoverMsg(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	discoveredMsg.insert({ nomMsg->getInstanceID(), nomMsg });
	if (commInterface)
		commInterface->registerCommMsg(nomMsg);
}

void UDPCommunicationManager::updateMsg(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	unsigned int oid = getObjectInstanceID(nomMsg);
	if (oid > 0)
	{
		nomMsg->setInstanceID(oid);
		mec->updateMsg(nomMsg);
	}
	else
	{
		printf("oid error:%u\n", oid);
	}
}

void UDPCommunicationManager::reflectMsg(shared_ptr<NOM> nomMsg)
{
	if (commInterface && nomMsg)
		commInterface->updateCommMsg(nomMsg);
}

void UDPCommunicationManager::deleteMsg(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void UDPCommunicationManager::removeMsg(shared_ptr<NOM> nomMsg)
{
	if (nomMsg)
		discoveredMsg.erase(nomMsg->getInstanceID());
}

void UDPCommunicationManager::sendMsg(shared_ptr<NOM> nomMsg)
{
	if (nomMsg)
		mec->sendMsg(nomMsg);
}

void UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	const auto iter = funcMap.find(nomMsg->getName());
	if (iter != funcMap.end())
		iter->second(nomMsg);
}

void UDPCommunicationManager::setUserName(tstring userName)
{
	name = userName;
}

tstring UDPCommunicationManager::getUserName()
{
	return name;
}

void UDPCommunicationManager::setData(void* data)
{
}

bool UDPCommunicationManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;

	commInterface = new NCommInterface(this);
	commInterface->setMEBComponent(meb);

	MessageProcessor msgProcessor = bind(
		&UDPCommunicationManager::processRecvMessage,
		this,
		placeholders::_1,
		placeholders::_2);
	commConfig->setMsgProcessor(msgProcessor);

	tcout << _T("[UDPCommunicationManager] local: ")
		<< commConfig->getLocalIPNumber()
		<< _T(":") << commConfig->getLocalPortNumber()
		<< _T(", remote: ") << commConfig->getRemoteIPNumber()
		<< _T(":") << commConfig->getRemotePortNumber()
		<< _T(", multicast: ") << commConfig->getMulticastIPNumber()
		<< _T(":") << commConfig->getMulticastPort()
		<< std::endl;

	const bool initialized = commInterface->initNetEnv(commConfig);
	if (!initialized)
	{
		tcerr << _T("[UDPCommunicationManager] initNetEnv failed.")
			<< std::endl;
		delete commInterface;
		commInterface = nullptr;
		return false;
	}

	tcout << _T("[UDPCommunicationManager] initNetEnv succeeded.")
		<< std::endl;

	list<NMessage*> msgList = nomParser->getObjectList();
	for (auto* nMsg : msgList)
	{
		if (!nMsg)
			continue;

		if (nMsg->getSharing() ==
				ESharing::ENUM_SHARING_PUBLISHSUBSCRIBE ||
			nMsg->getSharing() ==
				ESharing::ENUM_SHARING_PUBLISH)
		{
			registerMsg(nMsg->getName());
		}
	}

	//ProcessTestCode();

	return true;
}

void
UDPCommunicationManager::ProcessTestCode()
{
	//시나리오 배포
	auto nomMockDeployScenario = meb->getNOMInstance(name, _T("DeployScenarioRequest"));
	NFloat radarXPos(127.0F);
	NFloat radarYPos(35.0F);
	nomMockDeployScenario->setValue(_T("RadarXPos"), &radarXPos);
	nomMockDeployScenario->setValue(_T("RadarYPos"), &radarYPos);
	deployScenario(nomMockDeployScenario);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	//// 모의 시작
	auto nomMockStartSimulation = meb->getNOMInstance(name, _T("StartSimulationRequest"));
	startSimulation(nomMockStartSimulation);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// 모의 중지
	/*auto nomMockStopSimulation = meb->getNOMInstance(name, _T("StopSimulationRequest"));
	stopSimulation(nomMockStopSimulation);*/

	tcout << _T("========== [ProcessTestCode] ATInfo Path Test Begin ==========")
		<< std::endl;

	for (int index = 0; index < 2; ++index)
	{
		auto nomMockATInfo =
			meb->getNOMInstance(name, _T("ATInfo"));
		if (!nomMockATInfo)
			continue;

		NUInteger airthreatID(1001);
		NUInteger airthreatStatus(index == 0 ? 1 : 2);
		NFloat airthreatXPos(127.0F);
		NFloat airthreatYPos(36.0F);
		NFloat airthreatVelocity(250.0F + (10.0F * index));

		nomMockATInfo->setValue(_T("AirthreatID"), &airthreatID);
		nomMockATInfo->setValue(_T("AirthreatStatus"), &airthreatStatus);
		nomMockATInfo->setValue(_T("AirthreatXPos"), &airthreatXPos);
		nomMockATInfo->setValue(_T("AirthreatYPos"), &airthreatYPos);
		nomMockATInfo->setValue(_T("AirthreatVelocity"), &airthreatVelocity);

		tcout << _T("---- [ProcessTestCode] Inject mock ATInfo #")
			<< (index + 1)
			<< _T(" / Status=")
			<< airthreatStatus.toUInt()
			<< _T(" ----")
			<< std::endl;

		recvATInfo(nomMockATInfo);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	tcout << _T("=========== [ProcessTestCode] ATInfo Path Test End ===========")
		<< std::endl;

}

bool UDPCommunicationManager::stop()
{
	if (!commInterface)
		return true;

	commInterface->releaseNetEnv(commConfig);
	delete commInterface;
	commInterface = nullptr;
	return true;
}

void UDPCommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void UDPCommunicationManager::funcMapInit()
{
	funcMap.clear();
	function<void(shared_ptr<NOM>)> msgProcessor;

	msgProcessor = bind(
		&UDPCommunicationManager::deployScenario,
		this,
		placeholders::_1);
	funcMap.insert({ _T("DeployScenarioRequest"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::sendScenarioAck,
		this,
		placeholders::_1);
	funcMap.insert({ _T("ScenarioACKInnerManager"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::startSimulation,
		this,
		placeholders::_1);
	funcMap.insert({ _T("StartSimulationRequest"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::stopSimulation,
		this,
		placeholders::_1);
	funcMap.insert({ _T("StopSimulationRequest"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::recvATInfo,
		this,
		placeholders::_1);
	funcMap.insert({ _T("ATInfo"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::sendRadarDetectionInfo,
		this,
		placeholders::_1);
	funcMap.insert({ _T("RadarDetectionInfoInnerManager"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::recvUplinkInfoToMFRS,
		this,
		placeholders::_1);
	funcMap.insert({ _T("UplinkInfo"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::sendUplinkInfoToMSS,
		this,
		placeholders::_1);
	funcMap.insert({ _T("UplinkInfoToUDPInnerManager"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::recvDownlinkInfoToMFRS,
		this,
		placeholders::_1);
	funcMap.insert({ _T("DownlinkInfoFromMSS"), msgProcessor });

	msgProcessor = bind(
		&UDPCommunicationManager::sendDownlinkInfoToTCC,
		this,
		placeholders::_1);
	funcMap.insert({ _T("DownlinkInfoToUDPInnerManager"), msgProcessor });
}

void UDPCommunicationManager::deployScenario(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb)
		return;

	auto innerNOMInstance = meb->getNOMInstance(
		name, _T("DeployScenarioInnerManager"));
	if (!innerNOMInstance)
		return;

	const auto radarX = nomMsg->getValue(_T("RadarXPos"));
	const auto radarY = nomMsg->getValue(_T("RadarYPos"));
	if (!radarX || !radarY)
		return;

	float radarXValue = radarX->toFloat();
	float radarYValue = radarY->toFloat();

	NFloat radarXPos(radarXValue);
	NFloat radarYPos(radarYValue);
	innerNOMInstance->setValue(
		_T("RadarXPos"), &radarXPos);
	innerNOMInstance->setValue(
		_T("RadarYPos"), &radarYPos);

	tcout << _T(
		"[UDPCommunicationManager] DeployScenarioRequest received.")
		<< std::endl;
	mec->sendMsg(innerNOMInstance, _T("MFRSCommManager"));
}

void UDPCommunicationManager::sendScenarioAck(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !commInterface)
		return;

	auto outerNOMInstance = meb->getNOMInstance(
		name, _T("ScenarioACK"));
	if (!outerNOMInstance)
		return;

	NUInteger messageID(5101);
	NUInteger messageLength(8);
	outerNOMInstance->setValue(
		_T("MessageHeader.MessageID"), &messageID);
	outerNOMInstance->setValue(
		_T("MessageHeader.MessageLength"), &messageLength);

	tcout << _T(
		"[UDPCommunicationManager] ScenarioACK send to TCCS.")
		<< std::endl;
	commInterface->sendCommMsg(outerNOMInstance);
}

void UDPCommunicationManager::sendRadarDetectionInfo(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !commInterface)
		return;

	const auto targetID =
		nomMsg->getValue(_T("TargetID"));
	const auto targetXPos =
		nomMsg->getValue(_T("TargetXPos"));
	const auto targetYPos =
		nomMsg->getValue(_T("TargetYPos"));
	const auto detectedFlag =
		nomMsg->getValue(_T("DetectedFlag"));
	const auto targetVelocity =
		nomMsg->getValue(_T("TargetVelocity"));

	if (!targetID || !targetXPos || !targetYPos ||
		!detectedFlag || !targetVelocity)
	{
		return;
	}

	auto outerNOMInstance =
		meb->getNOMInstance(
			name,
			_T("RadarDetectionInfo"));

	if (!outerNOMInstance)
		return;

	NUInteger messageID(5102);
	NUInteger messageLength(28);
	NUInteger targetIDValue(targetID->toUInt());
	NFloat targetXValue(targetXPos->toFloat());
	NFloat targetYValue(targetYPos->toFloat());
	NUInteger detectedFlagValue(detectedFlag->toUInt());
	NFloat targetVelocityValue(targetVelocity->toFloat());

	outerNOMInstance->setValue(
		_T("MessageHeader.MessageID"),
		&messageID);
	outerNOMInstance->setValue(
		_T("MessageHeader.MessageLength"),
		&messageLength);
	outerNOMInstance->setValue(
		_T("RadarDetection.TargetID"),
		&targetIDValue);
	outerNOMInstance->setValue(
		_T("RadarDetection.TargetXPos"),
		&targetXValue);
	outerNOMInstance->setValue(
		_T("RadarDetection.TargetYPos"),
		&targetYValue);
	outerNOMInstance->setValue(
		_T("RadarDetection.DetectedFlag"),
		&detectedFlagValue);
	outerNOMInstance->setValue(
		_T("RadarDetection.TargetVelocity"),
		&targetVelocityValue);

	tcout << std::fixed << std::setprecision(2)
		<< _T("[UDPCommunicationManager] TCC RadarDetectionInfo SEND.")
		<< std::endl;

	commInterface->sendCommMsg(outerNOMInstance);
}

void UDPCommunicationManager::recvUplinkInfoToMFRS(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	auto innerNOMInstance =
		meb->getNOMInstance(
			name,
			_T("UplinkInfoToDatalinkInnerManager"));
	if (!innerNOMInstance)
		return;

	const auto airthreatID =
		nomMsg->getValue(_T("UplinkInfo.AirthreatID"));
	const auto airthreatXPos =
		nomMsg->getValue(_T("UplinkInfo.AirthreatXPos"));
	const auto airthreatYPos =
		nomMsg->getValue(_T("UplinkInfo.AirthreatYPos"));
	const auto missileID =
		nomMsg->getValue(_T("UplinkInfo.MissileID"));
	const auto airthreatVelocity =
		nomMsg->getValue(_T("UplinkInfo.AirthreatVelocity"));

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

	innerNOMInstance->setValue(
		_T("AirthreatID"),
		&airthreatIDValue);
	innerNOMInstance->setValue(
		_T("AirthreatXPos"),
		&airthreatXValue);
	innerNOMInstance->setValue(
		_T("AirthreatYPos"),
		&airthreatYValue);
	innerNOMInstance->setValue(
		_T("MissileID"),
		&missileIDValue);
	innerNOMInstance->setValue(
		_T("AirthreatVelocity"),
		&airthreatVelocityValue);

	tcout << std::fixed << std::setprecision(2)
		<< _T("---- [UDPCommunicationManager] TCC UplinkInfo received. ----")
		<< std::endl
		<< _T("AirthreatID=")
		<< airthreatIDValue.toUInt()
		<< _T(", AirthreatX=")
		<< airthreatXValue.toFloat()
		<< _T(", AirthreatY=")
		<< airthreatYValue.toFloat()
		<< _T(", MissileID=")
		<< missileIDValue.toUInt()
		<< _T(", AirthreatVelocity=")
		<< airthreatVelocityValue.toFloat()
		<< std::endl;

	mec->sendMsg(
		innerNOMInstance,
		_T("MFRSCommManager"));
}

void UDPCommunicationManager::sendUplinkInfoToMSS(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !commInterface)
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

	auto outerNOMInstance =
		meb->getNOMInstance(
			name,
			_T("UplinkInfoToMSS"));
	if (!outerNOMInstance)
		return;

	NUInteger messageID(5301);
	NUInteger messageLength(28);
	NUInteger airthreatIDValue(airthreatID->toUInt());
	NFloat airthreatXValue(airthreatXPos->toFloat());
	NFloat airthreatYValue(airthreatYPos->toFloat());
	NUInteger missileIDValue(missileID->toUInt());
	NFloat airthreatVelocityValue(airthreatVelocity->toFloat());

	outerNOMInstance->setValue(
		_T("MessageHeader.MessageID"),
		&messageID);
	outerNOMInstance->setValue(
		_T("MessageHeader.MessageLength"),
		&messageLength);
	outerNOMInstance->setValue(
		_T("UplinkInfo.AirthreatID"),
		&airthreatIDValue);
	outerNOMInstance->setValue(
		_T("UplinkInfo.AirthreatXPos"),
		&airthreatXValue);
	outerNOMInstance->setValue(
		_T("UplinkInfo.AirthreatYPos"),
		&airthreatYValue);
	outerNOMInstance->setValue(
		_T("UplinkInfo.MissileID"),
		&missileIDValue);
	outerNOMInstance->setValue(
		_T("UplinkInfo.AirthreatVelocity"),
		&airthreatVelocityValue);

	tcout << std::fixed << std::setprecision(2)
		<< _T("---- [UDPCommunicationManager] MSS UplinkInfo send. ----")
		<< std::endl
		<< _T("AirthreatID=")
		<< airthreatIDValue.toUInt()
		<< _T(", AirthreatX=")
		<< airthreatXValue.toFloat()
		<< _T(", AirthreatY=")
		<< airthreatYValue.toFloat()
		<< _T(", MissileID=")
		<< missileIDValue.toUInt()
		<< _T(", AirthreatVelocity=")
		<< airthreatVelocityValue.toFloat()
		<< std::endl;

	commInterface->sendCommMsg(outerNOMInstance);
}

void UDPCommunicationManager::recvDownlinkInfoToMFRS(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	auto innerNOMInstance =
		meb->getNOMInstance(
			name,
			_T("DownlinkInfoToDatalinkInnerManager"));
	if (!innerNOMInstance)
		return;

	const auto missileID =
		nomMsg->getValue(_T("DownlinkInfo.MissileID"));
	const auto missileVelocity =
		nomMsg->getValue(_T("DownlinkInfo.MissileVelocity"));
	const auto missileXPos =
		nomMsg->getValue(_T("DownlinkInfo.MissileXPos"));
	const auto missileYPos =
		nomMsg->getValue(_T("DownlinkInfo.MissileYPos"));

	if (!missileID || !missileVelocity ||
		!missileXPos || !missileYPos)
	{
		return;
	}

	NUInteger missileIDValue(missileID->toUInt());
	NFloat missileVelocityValue(missileVelocity->toFloat());
	NFloat missileXValue(missileXPos->toFloat());
	NFloat missileYValue(missileYPos->toFloat());

	innerNOMInstance->setValue(
		_T("MissileID"),
		&missileIDValue);
	innerNOMInstance->setValue(
		_T("MissileVelocity"),
		&missileVelocityValue);
	innerNOMInstance->setValue(
		_T("MissileXPos"),
		&missileXValue);
	innerNOMInstance->setValue(
		_T("MissileYPos"),
		&missileYValue);

	tcout << std::fixed << std::setprecision(2)
		<< _T("---- [UDPCommunicationManager] MSS DownlinkInfo received. ----")
		<< std::endl
		<< _T("MissileID=")
		<< missileIDValue.toUInt()
		<< _T(", MissileVelocity=")
		<< missileVelocityValue.toFloat()
		<< _T(", MissileX=")
		<< missileXValue.toFloat()
		<< _T(", MissileY=")
		<< missileYValue.toFloat()
		<< std::endl;

	mec->sendMsg(
		innerNOMInstance,
		_T("MFRSCommManager"));
}

void UDPCommunicationManager::sendDownlinkInfoToTCC(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !commInterface)
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

	auto outerNOMInstance =
		meb->getNOMInstance(
			name,
			_T("DownlinkInfo"));
	if (!outerNOMInstance)
		return;

	NUInteger messageID(5103);
	NUInteger messageLength(24);
	NUInteger missileIDValue(missileID->toUInt());
	NFloat missileVelocityValue(missileVelocity->toFloat());
	NFloat missileXValue(missileXPos->toFloat());
	NFloat missileYValue(missileYPos->toFloat());

	outerNOMInstance->setValue(
		_T("MessageHeader.MessageID"),
		&messageID);
	outerNOMInstance->setValue(
		_T("MessageHeader.MessageLength"),
		&messageLength);
	outerNOMInstance->setValue(
		_T("DownlinkInfo.MissileID"),
		&missileIDValue);
	outerNOMInstance->setValue(
		_T("DownlinkInfo.MissileVelocity"),
		&missileVelocityValue);
	outerNOMInstance->setValue(
		_T("DownlinkInfo.MissileXPos"),
		&missileXValue);
	outerNOMInstance->setValue(
		_T("DownlinkInfo.MissileYPos"),
		&missileYValue);

	tcout << std::fixed << std::setprecision(2)
		<< _T("---- [UDPCommunicationManager] TCC DownlinkInfo send. ----")
		<< std::endl
		<< _T("MissileID=")
		<< missileIDValue.toUInt()
		<< _T(", MissileVelocity=")
		<< missileVelocityValue.toFloat()
		<< _T(", MissileX=")
		<< missileXValue.toFloat()
		<< _T(", MissileY=")
		<< missileYValue.toFloat()
		<< std::endl;

	commInterface->sendCommMsg(outerNOMInstance);
}

void UDPCommunicationManager::startSimulation(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	auto innerNOMInstance = meb->getNOMInstance(
		name, _T("StartSimulationInnerManager"));
	if (!innerNOMInstance)
		return;

	tcout << _T(
		"[UDPCommunicationManager] StartSimulationRequest received.")
		<< std::endl;

	mec->sendMsg(innerNOMInstance, _T("MFRSCommManager"));
}

void UDPCommunicationManager::stopSimulation(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	auto innerNOMInstance = meb->getNOMInstance(
		name, _T("StopSimulationInnerManager"));
	if (!innerNOMInstance)
		return;

	tcout << _T(
		"[UDPCommunicationManager] StopSimulationRequest received.")
		<< std::endl;

	mec->sendMsg(innerNOMInstance, _T("MFRSCommManager"));
}

void UDPCommunicationManager::recvATInfo(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb || !mec)
		return;

	auto innerNOMInstance = meb->getNOMInstance(
		name, _T("ATInfoInnerManager"));
	if (!innerNOMInstance)
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

	NUInteger idValue(airthreatID->toUInt());
	NUInteger statusValue(airthreatStatus->toUInt());
	NFloat xValue(airthreatXPos->toFloat());
	NFloat yValue(airthreatYPos->toFloat());
	NFloat velocityValue(airthreatVelocity->toFloat());

	innerNOMInstance->setValue(_T("AirthreatID"), &idValue);
	innerNOMInstance->setValue(_T("AirthreatStatus"), &statusValue);
	innerNOMInstance->setValue(_T("AirthreatXPos"), &xValue);
	innerNOMInstance->setValue(_T("AirthreatYPos"), &yValue);
	innerNOMInstance->setValue(_T("AirthreatVelocity"), &velocityValue);

	tcout << std::fixed << std::setprecision(2)
		<< _T("[UDPCommunicationManager] ATS ATInfo received. ")
		<< _T("(AirthreatID: ")
		<< idValue.toUInt()
		<< _T(", Status: ")
		<< statusValue.toUInt()
		<< _T(", X: ")
		<< xValue.toFloat()
		<< _T(", Y: ")
		<< yValue.toFloat()
		<< _T(", Velocity: ")
		<< velocityValue.toFloat()
		<< _T(")\n");

	mec->sendMsg(innerNOMInstance, _T("MFRSCommManager"));
}

void UDPCommunicationManager::sendInnerMsg(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return;

	const auto iter = funcMap.find(nomMsg->getName());
	if (iter != funcMap.end())
		iter->second(nomMsg);
}

void UDPCommunicationManager::processRecvMessage(
	unsigned char* data,
	int size)
{
	if (!data || !commConfig || !meb)
		return;

	const int idPosition = commConfig->getHeaderIDPos();
	const int idSize = commConfig->getHeaderIDSize();
	if (idSize != sizeof(std::uint32_t) ||
		size < idPosition + idSize)
	{
		return;
	}

	std::uint32_t messageID = 0;
	std::memcpy(
		&messageID,
		data + idPosition,
		sizeof(messageID));

	const int messageDestination = (messageID / 100) % 10;
	if (messageDestination != 0 && messageDestination != 5)
		return;

	auto nomMsg = meb->getNOMInstance(
		name,
		commMsgHandler.getMsgName(messageID));
	if (!nomMsg)
	{
		tcerr << _T("undefined message") << std::endl;
		return;
	}

	if (nomMsg->getType() ==
		nframework::nom::ENOMType::NOM_TYPE_OBJECT)
	{
		if (nomMsg->deserialize(data, size))
			updateMsg(nomMsg);
		return;
	}

	auto copiedMsg = nomMsg->clone();
	if (!copiedMsg)
		return;

	if (!copiedMsg->deserialize(data, size))
	{
		tcerr << _T("message deserialize failed") << std::endl;
		return;
	}

	copiedMsg->setOwner(name);
	sendInnerMsg(copiedMsg);
}

unsigned int UDPCommunicationManager::getObjectInstanceID(
	shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return 0;

	for (const auto& item : registeredMsg)
	{
		if (item.second &&
			item.second->getMessageID() == nomMsg->getMessageID())
		{
			return item.first;
		}
	}
	return 0;
}

extern "C" BASEMGRDLL_API BaseManager* createObject()
{
	return new UDPCommunicationManager;
}

extern "C" BASEMGRDLL_API void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
