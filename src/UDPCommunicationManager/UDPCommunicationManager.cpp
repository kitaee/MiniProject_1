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
	auto nomMockDeployScenario = meb->getNOMInstance(name, _T("DeployScenarioRequest"));
	nomMockDeployScenario->setValue(_T("LauncherXPos"), &(NFloat)37.7);
	nomMockDeployScenario->setValue(_T("LauncherYPos"), &(NFloat)127.7);
	deployScenario(nomMockDeployScenario);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	//// 모의 시작
	auto nomMockStartSimulation = meb->getNOMInstance(name, _T("StartSimulationRequest"));
	startSimulation(nomMockStartSimulation);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// 모의 중지
	auto nomMockStopSimulation = meb->getNOMInstance(name, _T("StopSimulationRequest"));
	stopSimulation(nomMockStopSimulation);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	auto nomMockFire = meb->getNOMInstance(name, _T("LaunchMissileRequest"));
	nomMockFire->setValue(_T("AirthreatID"), &(NUInteger)1);
	nomMockFire->setValue(_T("AirthreatxPos"), &(NFloat)37.7);
	nomMockFire->setValue(_T("AirthreatyPos"), &(NFloat)127.7);
	nomMockFire->setValue(_T("MissleID"), &(NUInteger)1);
	launchMissle(nomMockFire);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	auto nomMockFireAgain = meb->getNOMInstance(name, _T("LaunchMissileRequest"));
	nomMockFireAgain->setValue(_T("AirthreatID"), &(NUInteger)1);
	nomMockFireAgain->setValue(_T("AirthreatxPos"), &(NFloat)37.7);
	nomMockFireAgain->setValue(_T("AirthreatyPos"), &(NFloat)127.7);
	nomMockFireAgain->setValue(_T("MissleID"), &(NUInteger)2);
	launchMissle(nomMockFireAgain);
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

	// TCC로부터 받는 시나리오 배포 요청
	msgProc = bind(&UDPCommunicationManager::deployScenario, this, placeholders::_1);
	funcMap.insert({ _T("DeployScenarioRequest"), msgProc });

	// ModelManager로부터 받는 시나리오 ACK 요청
	msgProc = bind(&UDPCommunicationManager::sendScenarioAck, this, placeholders::_1);
	funcMap.insert({ _T("ScenarioACKInnerManager"), msgProc });

	// TCC로부터 받는 모의 시작
	msgProc = bind(&UDPCommunicationManager::startSimulation, this, placeholders::_1);
	funcMap.insert({ _T("StartSimulationRequest"), msgProc });

	// TCC로부터 받는 모의 중지
	msgProc = bind(&UDPCommunicationManager::stopSimulation, this, placeholders::_1);
	funcMap.insert({ _T("StopSimulationRequest"), msgProc });

	// TCC로부터 받는 발사 요청
	msgProc = bind(&UDPCommunicationManager::launchMissle, this, placeholders::_1);
	funcMap.insert({ _T("LaunchMissileRequest"), msgProc });

	// LaunchManager로부터 받는 발사 완료 응답
	msgProc = bind(&UDPCommunicationManager::recvLaunchMissleResponse, this, placeholders::_1);
	funcMap.insert({ _T("LaunchMissleResponseToUDP"), msgProc });
}

void UDPCommunicationManager::recvInnerRouteToComm(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("sendRouteAT"));
	routeString = nomMsg->getValue(_T("RouteAT"))->toString();
	NUShort msgID(0x43);;
	NString route(routeString);

	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
	nomMsg_new->setValue(_T("RouteAT"), &route);

	commInterface->sendCommMsg(nomMsg_new);
}

void UDPCommunicationManager::deployScenario(shared_ptr<NOM> nomMsg)
{
	auto InnerNOMInstance = meb->getNOMInstance(name, _T("DeployScenarioInnerManager"));

	// 내부 구조체 세팅
	InnerNOMInstance->setValue(_T("LCSXPos"), &(NFloat)(nomMsg->getValue(_T("LauncherXPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("LCSYPos"), &(NFloat)(nomMsg->getValue(_T("LauncherYPos"))->toFloat()));
	
	std::cout << "발사대 모의기 UDPCommunicationManager 시나리오 배포 수신\n" << std::endl;
	this->sendMsg(InnerNOMInstance);
}

void UDPCommunicationManager::sendScenarioAck(shared_ptr<NOM> nomMsg)
{
	auto outerNOMInstance = meb->getNOMInstance(name, _T("ScenarioACK"));

	// 내부 구조체 세팅
	outerNOMInstance->setValue(_T("MessageHeader.MessageID"), &NUInteger(4101));
	outerNOMInstance->setValue(_T("MessageHeader.MessageLength"), &NUInteger(8));

	std::cout << "발사대 모의기 UDPCommunicationManager 시나리오 ACK 송신\n" << std::endl;
		
	commInterface->sendCommMsg(outerNOMInstance);
}

void UDPCommunicationManager::startSimulation(shared_ptr<NOM> nomMsg)
{
	std::cout << "발사대 모의기 UDPCommunicationManager 모의 시작\n" << std::endl;
}

void UDPCommunicationManager::stopSimulation(shared_ptr<NOM> nomMsg)
{
	auto InnerNOMInstance = meb->getNOMInstance(name, _T("StopSimulationRequestInnerManager"));
	std::cout << "발사대 모의기 UDPCommunicationManager 모의 중지 수신\n" << std::endl;
	this->sendMsg(InnerNOMInstance);
}

void UDPCommunicationManager::launchMissle(shared_ptr<NOM> nomMsg)
{
	std::cout << "발사대 모의기 UDPCommunicationManager 발사 요청 송신\n" << std::endl;

	auto InnerNOMInstance = meb->getNOMInstance(name, _T("LaunchMissleInnerManager"));

	// 내부 구조체 세팅
	InnerNOMInstance->setValue(_T("AirthreatID"), &(NUInteger)(nomMsg->getValue(_T("AirthreatID"))->toUInt()));
	InnerNOMInstance->setValue(_T("AirthreatXPos"), &(NFloat)(nomMsg->getValue(_T("AirthreatxPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("AirthreatYPos"), &(NFloat)(nomMsg->getValue(_T("AirthreatyPos"))->toFloat()));
	InnerNOMInstance->setValue(_T("MissleID"), &(NUInteger)(nomMsg->getValue(_T("MissleID"))->toUInt()));

	this->sendMsg(InnerNOMInstance);
}

void UDPCommunicationManager::recvLaunchMissleResponse(shared_ptr<NOM> nomMsg)
{
	// TCC한테 발사 응답 송신
	sendMissleFireResult(nomMsg);

	// Missle한테 발사 요청 송신
	sendMissleFireRequestToMissle(nomMsg);
}

void UDPCommunicationManager::sendMissleFireResult(shared_ptr<NOM> nomMsg)
{
	auto outerNOMInstance = meb->getNOMInstance(name, _T("MissileQuantityInfo"));

	outerNOMInstance->setValue(_T("MessageHeader.MessageID"), &NUInteger(4102));

	auto remainMissleCount = nomMsg->getValue(_T("RemainMissleCount"))->toUInt();

	// 임시로 재고탄 3발 (추후 수정 예정)
	outerNOMInstance->setValue(_T("MissileQuantity"), &NUInteger(remainMissleCount));

	commInterface->sendCommMsg(outerNOMInstance);
}

void UDPCommunicationManager::sendMissleFireRequestToMissle(shared_ptr<NOM> nomMsg)
{
	auto outerNOMInstance = meb->getNOMInstance(name, _T("LaunchMissile"));

	outerNOMInstance->setValue(_T("MessageHeader.MessageID"), &NUInteger(4301));
	outerNOMInstance->setValue(_T("AirthreatID"), &(NUInteger)(nomMsg->getValue(_T("AirthreatID"))->toUInt()));
	outerNOMInstance->setValue(_T("AirthreatXPos"), &(NFloat)(nomMsg->getValue(_T("AirthreatXPos"))->toFloat()));
	outerNOMInstance->setValue(_T("AirthreatYPos"), &(NFloat)(nomMsg->getValue(_T("AirthreatYPos"))->toFloat()));
	outerNOMInstance->setValue(_T("MissileID"), &(NUInteger)(nomMsg->getValue(_T("MissleID"))->toUInt()));
	outerNOMInstance->setValue(_T("LCSXPos"), &(NFloat)(nomMsg->getValue(_T("LCSXPos"))->toFloat()));
	outerNOMInstance->setValue(_T("LCSYPos"), &(NFloat)(nomMsg->getValue(_T("LCSYPos"))->toFloat()));

	commInterface->sendCommMsg(outerNOMInstance);
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
	// 외부통신 진입점
	auto IDPos = commConfig->getHeaderIDPos();
	auto IDSize = commConfig->getHeaderIDSize();

	auto msgID = 0;

	//ID 형식이 short 또는 int인 경우만 처리
	if (IDSize == 4)
	{
		uint32_t tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, sizeof(uint32_t));
		msgID = tmpMsgID;
	}
	else
	{
		return;
	}

	int messageDestination = (msgID / 100) % 10;

	// 발사대 모의기로 온 메세지가 아니면 방어 로직 추가
	if (messageDestination != 0 && messageDestination != 4)
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

