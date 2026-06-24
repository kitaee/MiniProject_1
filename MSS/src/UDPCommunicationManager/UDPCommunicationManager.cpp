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

	//?ㅽ듃?뚰겕 愿??
	commConfig = new CommunicationConfig;
	commConfig->setIni(_T("CommLinkInfo.ini"));

	//socket issue
	//commInterface = new NCommInterface(this);

	//NOM 硫붿떆吏 ?깅줉
	tstring schRegFilePath = current_path().c_str();
	schRegFilePath += _T("\\..\\SchemaRegistryData.xml"); //怨듭슜 援ъ“泥?
	nomParser = std::make_unique<NOMParser>();
	nomParser->setNOMFile(schRegFilePath);

	nomParser->parseNote();
	auto noteMap = nomParser->getNoteMap();
	nomParser->parseDataType();
	auto dataTypeMap = nomParser->getDataTypeMap();

	//NOM ?뚯떛 
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

//?대? 硫붿떆吏 ?섏떊 ??funcMap???깅줉???몃뱾???몄텧
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

	//硫붿떆吏 ?깅줉
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
	///*?뚯뒪??*/
	//auto nomMsg_new = meb->getNOMInstance(name, _T("DeployScenarioRequest"));

	////NUInteger msgID(static_cast<uint32_t>(ICD_MessageID::DeployScenarioRequest));
	//nomMsg_new->setValue(_T("MessageHeader.MessageID"), &NUInteger(1001));
	//NUInteger msgLength(52);

	////nomMsg_new->setValue(_T("MessageHeader.MessageID"), &msgID);
	//nomMsg_new->setValue(_T("MessageHeader.MessageLength"), &msgLength);

	//commInterface->sendCommMsg(nomMsg_new); //?몃?濡??꾨떖


	///*?뚯뒪??*/
	/*auto nomMsg_new = meb->getNOMInstance(name, _T("DeployScenarioRequest"));
	nomMsg_new->setValue(_T("MessageHeader.MessageID"), &NUInteger(1001));
	nomMsg_new->setValue(_T("RadarPositionLatitude"), &NFloat(37.7));

	commInterface->sendCommMsg(nomMsg_new); */
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
	
	msgProc = bind(&UDPCommunicationManager::recvDeployScenarioRequest, this, placeholders::_1);
	funcMap.insert({ _T("DeployScenarioRequest"), msgProc }); 


	msgProc = bind(&UDPCommunicationManager::recvStartSimulationRequest, this, placeholders::_1);
	funcMap.insert({ _T("StartSimulationRequest"), msgProc});

	msgProc = bind(&UDPCommunicationManager::recvStopSimulationRequest, this, placeholders::_1);
	funcMap.insert({ _T("StopSimulationRequest"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvLaunchMissile, this, placeholders::_1);
	funcMap.insert({ _T("LaunchMissile"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvUplinkInfo, this, placeholders::_1);
	funcMap.insert({ _T("UplinkInfoToMSS"), msgProc });

	//?대? ?섏떊 泥섎━->?몃?濡?硫붿떆吏 ?꾨떖
	msgProc = bind(&UDPCommunicationManager::recvSendScenarioAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerSendScenarioAck"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvDownlinkInfo, this, placeholders::_1);
	funcMap.insert({ _T("InnerDownlinkInfo"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvDetonationInfo, this, placeholders::_1);
	funcMap.insert({ _T("InnerDetonationInfo"), msgProc });
}
/*************************************************************************************************************/

// ?쒕굹由ъ삤 諛고룷 ?섏떊 泥섎━
void UDPCommunicationManager::recvDeployScenarioRequest(shared_ptr<NOM> nomMsg)
{
    auto innerMsg = meb->getNOMInstance(name, _T("InnerSendScenario"));

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

    innerMsg->setValue(_T("Airthreat.AirthreatID"), &airthreatID);
    innerMsg->setValue(_T("Airthreat.AirthreatVelocity"), &airthreatVelocity);
    innerMsg->setValue(_T("Airthreat.StartXPos"), &startXPos);
    innerMsg->setValue(_T("Airthreat.StartYPos"), &startYPos);
    innerMsg->setValue(_T("Airthreat.EndXPos"), &endXPos);
    innerMsg->setValue(_T("Airthreat.EndYPos"), &endYPos);
    innerMsg->setValue(_T("RadarXPos"), &radarXPos);
    innerMsg->setValue(_T("RadarYPos"), &radarYPos);
    innerMsg->setValue(_T("LauncherXPos"), &launcherXPos);
    innerMsg->setValue(_T("LauncherYPos"), &launcherYPos);
    innerMsg->setValue(_T("MissileVelocity"), &missileVelocity);

    this->sendMsg(innerMsg);
}
void UDPCommunicationManager::recvStartSimulationRequest(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStartSimulation")); 

	this->sendMsg(nomMsg_new); 


	/*TEST*/
	printf("[recieve Start Simulation Command]");
}
//紐⑥쓽 以묒? 紐낅졊 ?섏떊 泥섎━
void UDPCommunicationManager::recvStopSimulationRequest(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStopSimulation")); 

	this->sendMsg(nomMsg_new); //?대?濡??꾨떖
}
//諛쒖궗 紐낅졊 ?섏떊 泥섎━ - 諛쒖궗 紐낅졊 CommandManager ?꾨떖
void UDPCommunicationManager::recvLaunchMissile(shared_ptr<NOM> nomMsg)
{
    auto innerMsg = meb->getNOMInstance(name, _T("InnerLaunchMissile"));

    NUInteger airthreatID(nomMsg->getValue(_T("AirthreatID"))->toUInt());
    NFloat airthreatXPos(nomMsg->getValue(_T("AirthreatXPos"))->toFloat());
    NFloat airthreatYPos(nomMsg->getValue(_T("AirthreatYPos"))->toFloat());
    NUInteger missileID(nomMsg->getValue(_T("MissileID"))->toUInt());
    NFloat lcsXPos(nomMsg->getValue(_T("LCSXPos"))->toFloat());
    NFloat lcsYPos(nomMsg->getValue(_T("LCSYPos"))->toFloat());

    innerMsg->setValue(_T("AirthreatID"), &airthreatID);
    innerMsg->setValue(_T("AirthreatXPos"), &airthreatXPos);
    innerMsg->setValue(_T("AirthreatYPos"), &airthreatYPos);
    innerMsg->setValue(_T("MissileID"), &missileID);
    innerMsg->setValue(_T("LCSXPos"), &lcsXPos);
    innerMsg->setValue(_T("LCSYPos"), &lcsYPos);

    this->sendMsg(innerMsg);
}
void UDPCommunicationManager::recvUplinkInfo(shared_ptr<NOM> nomMsg)
{
    auto innerMsg = meb->getNOMInstance(name, _T("InnerUplinkInfo"));

    NUInteger airthreatID(nomMsg->getValue(_T("UplinkInfo.AirthreatID"))->toUInt());
    NFloat airthreatXPos(nomMsg->getValue(_T("UplinkInfo.AirthreatXPos"))->toFloat());
    NFloat airthreatYPos(nomMsg->getValue(_T("UplinkInfo.AirthreatYPos"))->toFloat());
    NUInteger missileID(nomMsg->getValue(_T("UplinkInfo.MissileID"))->toUInt());
    NFloat airthreatVelocity(nomMsg->getValue(_T("UplinkInfo.AirthreatVelocity"))->toFloat());

    innerMsg->setValue(_T("UplinkInfo.AirthreatID"), &airthreatID);
    innerMsg->setValue(_T("UplinkInfo.AirthreatXPos"), &airthreatXPos);
    innerMsg->setValue(_T("UplinkInfo.AirthreatYPos"), &airthreatYPos);
    innerMsg->setValue(_T("UplinkInfo.MissileID"), &missileID);
    innerMsg->setValue(_T("UplinkInfo.AirthreatVelocity"), &airthreatVelocity);

    this->sendMsg(innerMsg);
}
void UDPCommunicationManager::recvSendScenarioAck(shared_ptr<NOM> nomMsg)
{
    auto ackMsg = meb->getNOMInstance(name, _T("ScenarioACK"));

    NUInteger msgID(static_cast<uint32_t>(ICD_MessageID::ScenarioACK));
    NUInteger msgLength(8);

    ackMsg->setValue(_T("MessageHeader.MessageID"), &msgID);
    ackMsg->setValue(_T("MessageHeader.MessageLength"), &msgLength);

    commInterface->sendCommMsg(ackMsg);
    printf("[Send ScenarioACK Complete]");
}
void UDPCommunicationManager::recvDownlinkInfo(shared_ptr<NOM> nomMsg)
{
	auto outMsg = meb->getNOMInstance(name, _T("DownlinkInfoFromMSS"));

	NUInteger msgID(static_cast<uint32_t>(ICD_MessageID::DownlinkInfo));
	NUInteger msgLength(24); // MessageHeader 8 + DownlinkInfo 16

	NUInteger missileID(nomMsg->getValue(_T("DownlinkInfo.MissileID"))->toUInt());
	NFloat missileVelocity(nomMsg->getValue(_T("DownlinkInfo.MissileVelocity"))->toFloat());
	NFloat missileXPos(nomMsg->getValue(_T("DownlinkInfo.MissileXPos"))->toFloat());
	NFloat missileYPos(nomMsg->getValue(_T("DownlinkInfo.MissileYPos"))->toFloat());

	outMsg->setValue(_T("MessageHeader.MessageID"), &msgID);
	outMsg->setValue(_T("MessageHeader.MessageLength"), &msgLength);
	outMsg->setValue(_T("DownlinkInfo.MissileID"), &missileID);
	outMsg->setValue(_T("DownlinkInfo.MissileVelocity"), &missileVelocity);
	outMsg->setValue(_T("DownlinkInfo.MissileXPos"), &missileXPos);
	outMsg->setValue(_T("DownlinkInfo.MissileYPos"), &missileYPos);

	commInterface->sendCommMsg(outMsg);
}

void UDPCommunicationManager::recvDetonationInfo(shared_ptr<NOM> nomMsg)
{
	
		auto outMsg = meb->getNOMInstance(name, _T("DetonationInfo"));

		NUInteger msgID(static_cast<uint32_t>(ICD_MessageID::DetonationInfo));
		NUInteger msgLength(16); // MessageHeader(8) + MissileID(4) + TargetID(4)

		NUInteger missileID(nomMsg->getValue(_T("MissileID"))->toUInt());
		NUInteger targetID(nomMsg->getValue(_T("TargetID"))->toUInt());

		outMsg->setValue(_T("MessageHeader.MessageID"), &msgID);
		outMsg->setValue(_T("MessageHeader.MessageLength"), &msgLength);
		outMsg->setValue(_T("MissileID"), &missileID);
		outMsg->setValue(_T("TargetID"), &targetID);

		commInterface->sendCommMsg(outMsg);

		printf(
			"[Send DetonationInfo] MissileID=%u, TargetID=%u\n",
			missileID.toUInt(),
			targetID.toUInt()
		);
	
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
	
	auto IDPos = commConfig->getHeaderIDPos(); //4
	auto IDSize = commConfig->getHeaderIDSize();

	auto msgID = 0;

	
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

	//unsigned short tmpMsgID = 0;
	//memcpy(&tmpMsgID, data + IDPos, IDPos);
	//auto msgID = ntohs(tmpMsgID);

	
	auto msgName = commMsgHandler.getMsgName(msgID);

	if (msgName.empty())
	{
		return;
	}

	printf("[processRecvMessage] msgID(decimal) = %u\n", msgID);

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
			sendInnerMsg(nomMsgCP); // ?섏떊???몃? 硫붿떆吏?????id瑜?異붿텧?섍퀬 NOM?쇰줈 蹂??> funcMap???깅줉???몃뱾???몄텧->媛??몃뱾?ъ뿉?쒕뒗 ?대? 硫붿떆吏 ?앹꽦 ???꾨젅?꾩썙?щ줈 ?꾨떖??
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


