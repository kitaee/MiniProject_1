#include "UDPCommunicationManager.h"

#include <cstring>
#include <filesystem>

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

	tcout << _T("[UDPCommunicationManager] local=")
		<< commConfig->getLocalIPNumber()
		<< _T(":") << commConfig->getLocalPortNumber()
		<< _T(", remote=") << commConfig->getRemoteIPNumber()
		<< _T(":") << commConfig->getRemotePortNumber()
		<< _T(", multicast=") << commConfig->getMulticastIPNumber()
		<< _T(":") << commConfig->getMulticastPort()
		<< _T(", role=") << commConfig->getServerRole()
		<< _T(", cast=") << commConfig->getCastType()
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

	ProcessTestCode();

	return true;
}

void
UDPCommunicationManager::ProcessTestCode()
{
	//시나리오 배포
	auto nomMockDeployScenario = meb->getNOMInstance(name, _T("DeployScenarioRequest"));
	nomMockDeployScenario->setValue(_T("RadarPositionLatitude"), &(NFloat)37.7);
	nomMockDeployScenario->setValue(_T("RadarPositionLongitude"), &(NFloat)127.7);
	deployScenario(nomMockDeployScenario);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	//// 모의 시작
	auto nomMockStartSimulation = meb->getNOMInstance(name, _T("StartSimulationRequest"));
	startSimulation(nomMockStartSimulation);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// 모의 중지
	auto nomMockStopSimulation = meb->getNOMInstance(name, _T("StopSimulationRequest"));
	stopSimulation(nomMockStopSimulation);
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
}

void UDPCommunicationManager::deployScenario(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg || !meb)
		return;

	auto innerNOMInstance = meb->getNOMInstance(
		name, _T("DeployScenarioInnerManager"));
	if (!innerNOMInstance)
		return;

	const auto latitude = nomMsg->getValue(_T("RadarPositionLatitude"));
	const auto longitude = nomMsg->getValue(_T("RadarPositionLongitude"));
	if (!latitude || !longitude)
		return;

	float radarLatitudeValue = latitude->toFloat();
	float radarLongitudeValue = longitude->toFloat();

	tcout << _T("[UDPCommunicationManager] RadarPositionLatitude=")
		<< radarLatitudeValue
		<< _T(", RadarPositionLongitude=")
		<< radarLongitudeValue
		<< std::endl;

	NFloat radarLatitude(radarLatitudeValue);
	NFloat radarLongitude(radarLongitudeValue);
	innerNOMInstance->setValue(
		_T("RadarPositionLatitude"), &radarLatitude);
	innerNOMInstance->setValue(
		_T("RadarPositionLongitude"), &radarLongitude);

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
	printf("[UDP CALLBACK] datagram received. size=%d\n", size);

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

	printf("[UDP CALLBACK] messageID=%d\n", messageID);

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
