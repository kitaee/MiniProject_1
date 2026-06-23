#include "UDPCommunicationManager.h"
#include <filesystem>
using namespace std::filesystem;

/************************************************************************
	Constructor / Destructor
************************************************************************/
UDPCommunicationManager::UDPCommunicationManager(void)
{
	init();
}

UDPCommunicationManager::~UDPCommunicationManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
UDPCommunicationManager::init()
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("UDPCommunicationManager"));

	// by contract
	mec = new MECComponent;
	mec->setUser(this);

	commConfig = new CommunicationConfig;
	commConfig->setIni(_T("CommLinkInfo.ini"));

	//socket issue
	//commInterface = new NCommInterface(this);

	//NOM 메시지 등록
	tstring schRegFilePath = current_path().c_str();
	schRegFilePath += _T("\\..\\SchemaRegistryData.xml");
	nomParser = std::make_unique<NOMParser>();
	nomParser->setNOMFile(schRegFilePath);

	nomParser->parseNote();
	auto noteMap = nomParser->getNoteMap();
	nomParser->parseDataType();
	auto dataTypeMap = nomParser->getDataTypeMap();

	//NOM 파싱 
	tstring nomFilePath = current_path().c_str();
	nomFilePath += _T("\\");
	nomFilePath += getUserName();
	nomFilePath += _T(".xml");
	nomParser->setNOMFile(nomFilePath);

	if (nomParser->parse(dataTypeMap, noteMap))
		//if (nomParser->parse())
	{
		list<NMessage*> msgList = nomParser->getMessageList();
		list<NMessage*>::iterator itr;
		for (itr = msgList.begin(); itr != msgList.end(); itr++)
		{
			NMessage* nMsg = *itr;
			commMsgHandler.setIDNameTable(nMsg->getMessageID(), nMsg->getName());
		}
	}

	funcMapInit();
}

void
UDPCommunicationManager::release()
{
	delete commConfig;

	//socket issue
	//delete commInterface;

	meb = nullptr;
	delete mec;
	mec = nullptr;

	funcMap.clear();
}

/************************************************************************
	Inherit Function
************************************************************************/
shared_ptr<NOM>
UDPCommunicationManager::registerMsg(tstring msgName)
{
	shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));

	return nomMsg;
}

void
UDPCommunicationManager::discoverMsg(shared_ptr<NOM> nomMsg)
{
	discoveredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));
	commInterface->registerCommMsg(nomMsg);
}

void
UDPCommunicationManager::updateMsg(shared_ptr<NOM> nomMsg)
{
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

void
UDPCommunicationManager::reflectMsg(shared_ptr<NOM> nomMsg)
{
	tcout << _T("UDPCommunicationManager::Message is reflected.") << endl;
	commInterface->updateCommMsg(nomMsg);
}

void
UDPCommunicationManager::deleteMsg(shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
UDPCommunicationManager::removeMsg(shared_ptr<NOM> nomMsg)
{
	map<unsigned int, shared_ptr<NOM>>::iterator itr;
	itr = discoveredMsg.find(nomMsg->getInstanceID());

	if(itr != discoveredMsg.end())
	{
		discoveredMsg.erase(nomMsg->getInstanceID());
	}
	else
	{
		tcerr << _T("UDPCommunicationManager::Message was removed.") << endl;
	}
}

void
UDPCommunicationManager::sendMsg(shared_ptr<NOM> nomMsg)
{
	//tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	mec->sendMsg(nomMsg);
}

void
UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}

	//commInterface->sendCommMsg(nomMsg);
}

void
UDPCommunicationManager::setUserName(tstring userName)
{
	name = userName; 
}

tstring
UDPCommunicationManager::getUserName()
{
	return name;
}

void
UDPCommunicationManager::setData(void* data)
{
	// if need be
}

bool
UDPCommunicationManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;

	//socket issue
	commInterface = new NCommInterface(this);
	
	commInterface->setMEBComponent(meb);
	MessageProcessor msgProcessor = bind(&UDPCommunicationManager::processRecvMessage, this, placeholders::_1, placeholders::_2);
	commConfig->setMsgProcessor(msgProcessor);
	commInterface->initNetEnv(commConfig);

	//메시지 등록
	list<NMessage*> msgList = nomParser->getObjectList();
	list<NMessage*>::iterator itr;
	for (itr = msgList.begin(); itr != msgList.end(); itr++)
	{
		NMessage* nMsg = *itr;
		if (nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISHSUBSCRIBE || nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISH)
		{
			this->registerMsg(nMsg->getName());
		}
	}

	/*
	* MockUp 테스트 코드 (MiniProject.ini 파일에서 UDPCOmmunicationManager 맨 밑으로 내려야함)
	*/
	//ProcessTestCode();

	return true;
}

void
UDPCommunicationManager::ProcessTestCode()
{
	//시나리오 배포
	//<NOM:parameter name = "RadarPositionLatitude" semantics = "RadarPositionLatitude" dataType = "float" / >
	//	<NOM:parameter name = "RadarPositionLongitude" semantics = "RadarPositionLongitude" dataType = "float" / >
	//	<NOM:parameter name = "LauncherPositionLatitude" semantics = "LauncherPositionLatitude" dataType = "float" / >
	//	<NOM:parameter name = "LauncherPositionLongitude" semantics = "LauncherPositionLongitude" dataType = "float" / >
	//	<NOM:parameter name = "MissileVelocity" semantics = "MissileVelocity" dataType = "float" / >
	auto nomMockDeployScenario = meb->getNOMInstance(name, _T("DeployScenarioRequest"));
	nomMockDeployScenario->setValue(_T("MessageHeader.MessageID"), &(NUInteger)1001);
	nomMockDeployScenario->setValue(_T("Airthreat.AirthreatID"), &(NUInteger)1);
	nomMockDeployScenario->setValue(_T("Airthreat.AirthreatVelocity"), &(NFloat)100);
	nomMockDeployScenario->setValue(_T("Airthreat.StartLatitude"), &(NFloat)37.7f);
	nomMockDeployScenario->setValue(_T("Airthreat.StartLongitude"), &(NFloat)127.7f);
	nomMockDeployScenario->setValue(_T("Airthreat.EndLatitude"), &(NFloat)41);
	nomMockDeployScenario->setValue(_T("Airthreat.EndLongitude"), &(NFloat)139);

	nomMockDeployScenario->setValue(_T("RadarPositionLatitude"), &(NFloat)37);
	nomMockDeployScenario->setValue(_T("RadarPositionLongitude"), &(NFloat)139);
	nomMockDeployScenario->setValue(_T("LauncherPositionLatitude"), &(NFloat)37);
	nomMockDeployScenario->setValue(_T("LauncherPositionLongitude"), &(NFloat)139);
	nomMockDeployScenario->setValue(_T("MissileVelocity"), &(NFloat)200);
	nomMockDeployScenario->setValue(_T("MessageHeader.MessageLength"), &(NUInteger)52);
	recvDeployScenarioRequest(nomMockDeployScenario);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	////// 모의 시작
	//auto nomMockStartSimulation = meb->getNOMInstance(name, _T("StartSimulationRequest"));
	//startSimulation(nomMockStartSimulation);

	//std::this_thread::sleep_for(std::chrono::milliseconds(500));

	//// 모의 중지
	//auto nomMockStopSimulation = meb->getNOMInstance(name, _T("StopSimulationRequest"));
	//stopSimulation(nomMockStopSimulation);

	//std::this_thread::sleep_for(std::chrono::milliseconds(500));

	//auto nomMockFire = meb->getNOMInstance(name, _T("LaunchMissileRequest"));
	//nomMockFire->setValue(_T("AirthreatID"), &(NUInteger)1);
	//nomMockFire->setValue(_T("AirthreatLatitude"), &(NFloat)37.7);
	//nomMockFire->setValue(_T("AirthreatLongitude"), &(NFloat)127.7);
	//nomMockFire->setValue(_T("MissleID"), &(NUInteger)1);
	//launchMissle(nomMockFire);
}

bool
UDPCommunicationManager::stop()
{
	commInterface->releaseNetEnv(commConfig);

	//socket issue
	delete commInterface;
	return true;
}

void
UDPCommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void UDPCommunicationManager::funcMapInit()
{
	function<void(shared_ptr<NOM>)> msgProc;

	// 외부 연동(수신)
	msgProc = bind(&UDPCommunicationManager::recvDeployScenarioRequest, this, placeholders::_1);
	funcMap.insert({ _T("DeployScenarioRequest"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvStartSimulationRequest, this, placeholders::_1);
	funcMap.insert({ _T("StartSimulationRequest"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvStopSimulationRequest, this, placeholders::_1);
	funcMap.insert({ _T("StopSimulationRequest"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvDetonationInfo, this, placeholders::_1);
	funcMap.insert({ _T("DetonationInfo"), msgProc });

	// 내부 연동(수신)
	msgProc = bind(&UDPCommunicationManager::recvScenarioACK, this, placeholders::_1);
	funcMap.insert({ _T("ScenarioACK"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvATInfo, this, placeholders::_1);
	funcMap.insert({ _T("ATInfo"), msgProc });
}

void UDPCommunicationManager::recvDeployScenarioRequest(shared_ptr<NOM> nomMsg)
{
	this->sendMsg(nomMsg);
}

void UDPCommunicationManager::recvStartSimulationRequest(shared_ptr<NOM> nomMsg)
{
	this->sendMsg(nomMsg);
}

void UDPCommunicationManager::recvStopSimulationRequest(shared_ptr<NOM> nomMsg)
{
	this->sendMsg(nomMsg);
}

void UDPCommunicationManager::recvDetonationInfo(shared_ptr<NOM> nomMsg)
{
	this->sendMsg(nomMsg);
}

void UDPCommunicationManager::recvScenarioACK(shared_ptr<NOM> nomMsg)
{
	commInterface->sendCommMsg(nomMsg);
	printf("[UDP] ScenarioACK MessageID=%u\n", nomMsg->getMessageID());
}

void UDPCommunicationManager::recvATInfo(shared_ptr<NOM> nomMsg)
{
	commInterface->sendCommMsg(nomMsg);
}

void UDPCommunicationManager::sendInnerMsg(shared_ptr<NOM> nomMsg)
{
	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
}

void
UDPCommunicationManager::processRecvMessage(unsigned char* data, int size)
{
	//auto HeaderSize = commConfig->getHeaderSize();
	auto IDPos = commConfig->getHeaderIDPos();
	auto IDSize = commConfig->getHeaderIDSize();

	auto msgID = 0;

	// 수신 확인용 디버깅 코드
	tcout << _T("[UDP] msgID=") << msgID << std::endl;

	//ID 형식이 short 또는 int인 경우만 처리
	if (IDSize == 2)
	{
		unsigned short tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		//msgID = ntohs(tmpMsgID);
		msgID = tmpMsgID;
	}
	else if (IDSize == 4)
	{
		unsigned int tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		//msgID = ntohl(tmpMsgID);
		msgID = tmpMsgID;

	}
	else
	{
		return;
	}

	auto msgName = commMsgHandler.getMsgName(msgID); // 수신받은 msgID
	if (msgName.empty()) // 수신받은 msgID가 아니면 안 하기
	{
		return;
	}
	auto nomMsg = meb->getNOMInstance(name, commMsgHandler.getMsgName(msgID));

	if (nomMsg.get())
	{
		if (nomMsg->getType() == nframework::nom::ENOMType::NOM_TYPE_OBJECT)
		{
			nomMsg->deserialize(data, size);
			this->updateMsg(nomMsg);
		}
		else
		{
			auto nomMsgCP = nomMsg->clone();
			nomMsgCP->deserialize(data, size);
			nomMsgCP->setOwner(name);
			sendInnerMsg(nomMsgCP);
			//this->sendMsg(nomMsgCP);
		}
	}
	else
	{
		tcerr << _T("undefined message") << endl;
	}
}

unsigned int
UDPCommunicationManager::getObjectInstanceID(shared_ptr<NOM> nomMsg)
{
	unsigned int oid = 0;
	map<unsigned int, shared_ptr<NOM>>::iterator itr;
	for (itr = registeredMsg.begin(); itr != registeredMsg.end(); itr++)
	{
		unsigned int key = itr->first;
		shared_ptr<NOM> nom = itr->second;

		if (nom->getMessageID() == nomMsg->getMessageID())
		{
			printf("[TCPCommunicationManager]Found object instance id : %u\n", key);
			oid = key;
			break;
		}
	}

	return oid;
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new UDPCommunicationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}

