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

	return true;
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
}

void UDPCommunicationManager::recvATInfo(shared_ptr<NOM> nomMsg)
{
	commInterface->sendCommMsg(nomMsg);
}

//
//void UDPCommunicationManager::recvMissileDetonation(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerAirThreatDetonationToATM"));
//	mec->sendMsg(nomMsg_new);
//	//std::cout << "\n\n\n\nUDP에서 미사일 폭파 이벤트 수신\n\n\n" << std::endl;
//}
//
//void UDPCommunicationManager::recvInnerAirThreatInfo(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("AirThreatInfo"));
//	NUShort msgID(0x0d);;
//	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
//
//	NUShort objectID(nomMsg->getValue(_T("AirThreatInfo.ObjectID"))->toShort());
//	nomMsg_new->setValue(_T("AirThreatInfo.ObjectID"), &objectID);
//
//	NUShort objectState(nomMsg->getValue(_T("AirThreatInfo.ObjectState"))->toShort());
//	nomMsg_new->setValue(_T("AirThreatInfo.ObjectState"), &objectState);
//
//	NDouble posX(nomMsg->getValue(_T("AirThreatInfo.PositionX"))->toDouble());
//	nomMsg_new->setValue(_T("AirThreatInfo.PositionX"), &posX);
//
//	NDouble posY(nomMsg->getValue(_T("AirThreatInfo.PositionY"))->toDouble());
//	nomMsg_new->setValue(_T("AirThreatInfo.PositionY"), &posY);
//
//	NDouble velX(nomMsg->getValue(_T("AirThreatInfo.VelocityX"))->toDouble());
//	nomMsg_new->setValue(_T("AirThreatInfo.VelocityX"), &velX);
//
//	NDouble velY(nomMsg->getValue(_T("AirThreatInfo.VelocityY"))->toDouble());
//	nomMsg_new->setValue(_T("AirThreatInfo.VelocityY"), &velY);
//
//	//std::cout << "\n" << velX << ", " << velY << std::endl;
//
//	commInterface->sendCommMsg(nomMsg_new);
//}
//
//void UDPCommunicationManager::recvInnerRouteToComm(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("sendRouteAT"));
//	routeString = nomMsg->getValue(_T("RouteAT"))->toString();
//	NUShort msgID(0x43);;
//	NString route(routeString);
//
//	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
//	nomMsg_new->setValue(_T("RouteAT"), &route);
//
//	commInterface->sendCommMsg(nomMsg_new);
//}
//
//void UDPCommunicationManager::recvSendScenario(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerSendScenario"));
//
//	nomMsg_new->setValue(_T("Scenario.OriginLat"), &(NDouble)(nomMsg->getValue(_T("Scenario.OriginLat"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.OriginLng"), &(NDouble)(nomMsg->getValue(_T("Scenario.OriginLng"))->toDouble()));
//
//	nomMsg_new->setValue(_T("Scenario.WayPoint0_X"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint0_X"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint0_Y"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint0_Y"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint1_X"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint1_X"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint1_Y"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint1_Y"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint2_X"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint2_X"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint2_Y"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint2_Y"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint3_X"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint3_X"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint3_Y"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint3_Y"))->toDouble()));
//
//	nomMsg_new->setValue(_T("Scenario.WayPoint0_Lat"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint0_Lat"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint0_Lng"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint0_Lng"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint1_Lat"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint1_Lat"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint1_Lng"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint1_Lng"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint2_Lat"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint2_Lat"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint2_Lng"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint2_Lng"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint3_Lat"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint3_Lat"))->toDouble()));
//	nomMsg_new->setValue(_T("Scenario.WayPoint3_Lng"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint3_Lng"))->toDouble()));
//
//	this->sendMsg(nomMsg_new);
//}
//
//void UDPCommunicationManager::recvStartSimulation(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStartSimulation"));
//
//	this->sendMsg(nomMsg_new);
//}
//
//void UDPCommunicationManager::recvStopSimulation(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStopSimulation"));
//
//	this->sendMsg(nomMsg_new);
//}
//
//void UDPCommunicationManager::recvInnerSendScenarioAck(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("SendScenarioAck"));
//	NUShort msgID = NUShort((ushort)ICD_MessageID::SendScenarioAck);
//	NUShort simulatorID = nomMsg->getValue(_T("SimulatorID"))->toUShort();
//
//	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
//	nomMsg_new->setValue(_T("SimulatorID"), &simulatorID);
//
//	commInterface->sendCommMsg(nomMsg_new);
//}
//
//void UDPCommunicationManager::recvInnerStartSimulationAck(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("StartSimulationAck"));
//	NUShort msgID = NUShort((ushort)ICD_MessageID::StartSimulationAck);
//	NUShort simulatorID = nomMsg->getValue(_T("SimulatorID"))->toUShort();
//
//	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
//	nomMsg_new->setValue(_T("SimulatorID"), &simulatorID);
//
//	commInterface->sendCommMsg(nomMsg_new);
//}
//
//void UDPCommunicationManager::recvInnerStopSimulationAck(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("StopSimulationAck"));
//	NUShort msgID = NUShort((ushort)ICD_MessageID::StopSimulationAck);
//	NUShort simulatorID = nomMsg->getValue(_T("SimulatorID"))->toUShort();
//
//	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
//	nomMsg_new->setValue(_T("SimulatorID"), &simulatorID);
//
//	commInterface->sendCommMsg(nomMsg_new);
//}
//
//void UDPCommunicationManager::recvInnerSimulatorStateComm(shared_ptr<NOM> nomMsg)
//{
//	auto nomMsg_new = meb->getNOMInstance(name, _T("SimulatorState"));
//	NUShort msgID = NUShort((ushort)ICD_MessageID::SimulatorState);
//	NUShort simulatorID = nomMsg->getValue(_T("SimulatorID"))->toUShort();
//
//	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
//	nomMsg_new->setValue(_T("SimulatorID"), &simulatorID);
//
//	commInterface->sendCommMsg(nomMsg_new);
//}

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
		msgID = ntohs(tmpMsgID);
	}
	else if (IDSize == 4)
	{
		unsigned int tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		msgID = ntohl(tmpMsgID);
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
	msgID = 1001;

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

