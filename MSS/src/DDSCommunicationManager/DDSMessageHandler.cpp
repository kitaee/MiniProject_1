#pragma once

#include "DDSMessageHandler.h"
//#include "DDSMessageTable.h"
#include <algorithm>
#include <filesystem>
#include <fstream>	// test
#include <nFramework/util/util.h>

using namespace std::filesystem;
/************************************************************************
	constructor / destructor
************************************************************************/
DDSMessageHandler::DDSMessageHandler(BaseManager* ddsSimNetManager) : user(ddsSimNetManager)
{
	initialize();
}


DDSMessageHandler::~DDSMessageHandler(void)
{
	release();
}


/************************************************************************
	initialize / release
************************************************************************/
void
DDSMessageHandler::initialize()
{
	path p(util::tstring2string(user->getUserName()).c_str());
	current_path(p);

	IniHandler iniHandler;
	iniHandler.readIni(_T("LinkInfo.ini"));
	domainId = iniHandler.readInteger(_T("DDS"), _T("DOMAIN_ID"));
	

	// Schema Registry Data 파싱
	tstring schRegFilePath = current_path().c_str();
	schRegFilePath += _T("\\..\\SchemaRegistryData.xml");
	nomParser = std::make_unique<NOMParser>();
	nomParser->setNOMFile(schRegFilePath);

	// 순서 중요!!
	nomParser->parseNote();
	auto noteMap = nomParser->getNoteMap();
	nomParser->parseDataType();
	auto dataTypeMap = nomParser->getDataTypeMap();
	
	// NOM 파싱
	tstring nomFilePath = current_path().c_str();
	nomFilePath += _T("\\");
	nomFilePath += user->getUserName();
	nomFilePath += _T(".xml");
	nomParser->setNOMFile(nomFilePath);
	if (nomParser->parse(dataTypeMap, noteMap))
	{
		msgMap = nomParser->getMessageMap();
	}

	dcps = new DDSServiceProvider;

	participant = dcps->createDomainParticipant(domainId/*, project*/);
	participant->ignore_participant(participant->get_instance_handle());

	publisher = dcps->createPublisher();
	subscriber = dcps->createSubscriber();

	registerNOMMsg();
	registerNOMMsgProcessor();
	createLITS_DDSTopic();

	path up("..");
	current_path(up);
}


void
DDSMessageHandler::release()
{
	dcps->deleteSubscriber(subscriber);
	dcps->deletePublisher(publisher);
	dcps->deleteDomainParticipant(participant);
	
	delete dcps;

	deleteNOMMsgProcessor();
	deleteLITS_DDSTopic();
}


/************************************************************************
	register or delete NOM and TOPIC messages
************************************************************************/
void
DDSMessageHandler::registerNOMMsg()
{
	for (auto nomMsgItr : msgMap)
	{
		NMessage* nMsg = nomMsgItr.second;
		if (nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISH ||
			nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISHSUBSCRIBE) 
		{
			std::shared_ptr<NOM> nomMsg;

			int atsSourceID = 11;
			if (nomMsgItr.first == _T("AirThreatInformation"))
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					nomMsg = user->registerMsg(nomMsgItr.first);
					topicList.try_emplace(1000 + atsSourceID + nCount, nomMsg);
				}
			}

			int mssSourceID = 21;
			if (nomMsgItr.first == _T("InterceptorInformation"))
			{
				for (int nCount = 0; nCount < 2; nCount++)
				{
					nomMsg = user->registerMsg(nomMsgItr.first);
					topicList.try_emplace(2000 + mssSourceID + nCount, nomMsg);
				}
			}

			if (nomMsgItr.first == _T("UplinkInformation"))
			{
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(3031, nomMsg);			// REGCC
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(3051, nomMsg);			// MFRS
			}

			int downLinkSourceID = 21;
			if (nomMsgItr.first == _T("DownlinkInformation"))
			{
				for (int nCount = 0; nCount < 2; nCount++)
				{
					nomMsg = user->registerMsg(nomMsgItr.first);
					topicList.try_emplace(4000 + downLinkSourceID + nCount, nomMsg);
				}
			}

			if (nomMsgItr.first == _T("TimeTickInformation"))
			{
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(5031, nomMsg);			// REGCC
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(5051, nomMsg);			// MFRS
			}

			if (nomMsgItr.first == _T("MFRAttitudeInformation"))
			{
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(6031, nomMsg);			// REGCC
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(6051, nomMsg);			// MFRS
			}

		}
	}
}


void
DDSMessageHandler::registerNOMMsgProcessor()
{
	std::function<void(std::shared_ptr<NOM>)> nomMsgProc;

	nomMsgProc = bind(&DDSMessageHandler::processAirThreatInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(_T("AirThreatInformation"), nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processInterceptorInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(_T("InterceptorInformation"), nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processUplinkInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(_T("UplinkInformation"), nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processDownlinkInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(_T("DownlinkInformation"), nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processTimeTickInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(_T("TimeTickInformation"), nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processMFRAttitudeInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(_T("MFRAttitudeInformation"), nomMsgProc);

	// test
	/*nomMsgProc = bind(&DDSMessageHandler::testDDSConnectSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(_T("TestDDSConnection"), nomMsgProc);*/

	// test
	/*
	nomMsgProc = bind(&DDSMessageHandler::processStop, this, std::placeholders::_1);
	nomProcessorMap.emplace(_T("StopSimulation"), nomMsgProc);
	*/
}


// test
/*
void
DDSMessageHandler::processStop(std::shared_ptr<NOM> nom)
{
	ofstream testFile("./testDDSFile.txt", std::ofstream::out | std::ofstream::trunc);
	testFile << "Time" << std::endl;
	for (auto itr : testQueue)
	{
		std::time_t testTime = std::chrono::system_clock::to_time_t(itr);
		struct tm T;
		localtime_s(&T, &testTime);

		auto timeSineEpoch = itr.time_since_epoch();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(timeSineEpoch).count();
		auto mills = std::chrono::duration_cast<std::chrono::milliseconds>(timeSineEpoch).count();

		testFile << T.tm_hour << "." << T.tm_min << "." << T.tm_sec << "." << mills - seconds * 1000 << std::endl;
	}
	testFile.close();
}
*/

void
DDSMessageHandler::deleteNOMMsgProcessor()
{
	nomProcessorMap.clear();
}


void
DDSMessageHandler::createLITS_DDSTopic()
{
	DDSProviderInterface* topic;

	// Topic_Instance::AirThreatInformation
	topic = new DDSTopicServicesTemplate<AirThreatInformationTypeSupport, AirThreatInformationDataWriter, AirThreatInformationDataReader, AirThreatInformationSeq, AirThreatInformation>(participant, publisher, subscriber, "AirThreatInformation");
	topicProcessorList.emplace(_T("AirThreatInformation"), topic);

	auto airThreatInfoTopic = static_cast<DDSTopicServicesTemplate<AirThreatInformationTypeSupport, AirThreatInformationDataWriter, AirThreatInformationDataReader, AirThreatInformationSeq, AirThreatInformation>*>(topic);
	std::function<void(byte*)> airThreatInfoProc = bind(&DDSMessageHandler::processAirThreatInformationReceived, this, std::placeholders::_1);
	airThreatInfoTopic->injectDDSMsgProcessor(airThreatInfoProc);
	
	// Topic_Instance::InterceptorInformation
	topic = new DDSTopicServicesTemplate<InterceptorInformationTypeSupport, InterceptorInformationDataWriter, InterceptorInformationDataReader, InterceptorInformationSeq, InterceptorInformation>(participant, publisher, subscriber, "InterceptorInformation");
	topicProcessorList.emplace(_T("InterceptorInformation"), topic);

	auto interceptorInfoTopic = static_cast<DDSTopicServicesTemplate<InterceptorInformationTypeSupport, InterceptorInformationDataWriter, InterceptorInformationDataReader, InterceptorInformationSeq, InterceptorInformation>*>(topic);
	std::function<void(byte*)> interceptorInfoProc = bind(&DDSMessageHandler::processInterceptorInformationReceived, this, std::placeholders::_1);
	interceptorInfoTopic->injectDDSMsgProcessor(interceptorInfoProc);

	// Topic_Instance::UplinkInformation
	topic = new DDSTopicServicesTemplate<UplinkInformationTypeSupport, UplinkInformationDataWriter, UplinkInformationDataReader, UplinkInformationSeq, UplinkInformation>(participant, publisher, subscriber, "UplinkInformation");
	topicProcessorList.emplace(_T("UplinkInformation"), topic);

	auto uplinkInfoTopic = static_cast<DDSTopicServicesTemplate<UplinkInformationTypeSupport, UplinkInformationDataWriter, UplinkInformationDataReader, UplinkInformationSeq, UplinkInformation>*>(topic);
	std::function<void(byte*)> uplinkInfoProc = bind(&DDSMessageHandler::processUplinkInformationReceived, this, std::placeholders::_1);
	uplinkInfoTopic->injectDDSMsgProcessor(uplinkInfoProc);

	// Topic_Instance::DownlinkInformation
	topic = new DDSTopicServicesTemplate<DownlinkInformationTypeSupport, DownlinkInformationDataWriter, DownlinkInformationDataReader, DownlinkInformationSeq, DownlinkInformation>(participant, publisher, subscriber, "DownlinkInformation");
	topicProcessorList.emplace(_T("DownlinkInformation"), topic);

	auto downlinkInfoTopic = static_cast<DDSTopicServicesTemplate<DownlinkInformationTypeSupport, DownlinkInformationDataWriter, DownlinkInformationDataReader, DownlinkInformationSeq, DownlinkInformation>*>(topic);
	std::function<void(byte*)> downlinkInfoProc = bind(&DDSMessageHandler::processDownlinkInformationReceived, this, std::placeholders::_1);
	downlinkInfoTopic->injectDDSMsgProcessor(downlinkInfoProc);

	// Topic_Instance::TimeTickInformation
	topic = new DDSTopicServicesTemplate<TimeTickInformationTypeSupport, TimeTickInformationDataWriter, TimeTickInformationDataReader, TimeTickInformationSeq, TimeTickInformation>(participant, publisher, subscriber, "TimeTickInformation");
	topicProcessorList.emplace(_T("TimeTickInformation"), topic);

	auto timeTickInfoTopic = static_cast<DDSTopicServicesTemplate<TimeTickInformationTypeSupport, TimeTickInformationDataWriter, TimeTickInformationDataReader, TimeTickInformationSeq, TimeTickInformation>*>(topic);
	std::function<void(byte*)> timeTickInfoProc = bind(&DDSMessageHandler::processTimeTickInformationReceived, this, std::placeholders::_1);
	timeTickInfoTopic->injectDDSMsgProcessor(timeTickInfoProc);

	// Topic_Instance::MFRAttitudeInformation
	topic = new DDSTopicServicesTemplate<MFRAttitudeInformationTypeSupport, MFRAttitudeInformationDataWriter, MFRAttitudeInformationDataReader, MFRAttitudeInformationSeq, MFRAttitudeInformation>(participant, publisher, subscriber, "MFRAttitudeInformation");
	topicProcessorList.emplace(_T("MFRAttitudeInformation"), topic);

	auto mfrAttitudeInformationTopic = static_cast<DDSTopicServicesTemplate<MFRAttitudeInformationTypeSupport, MFRAttitudeInformationDataWriter, MFRAttitudeInformationDataReader, MFRAttitudeInformationSeq, MFRAttitudeInformation>*>(topic);
	std::function<void(byte*)> mfrAttituedInfoProc = bind(&DDSMessageHandler::processMFRAttitudeInformationReceived, this, std::placeholders::_1);
	mfrAttitudeInformationTopic->injectDDSMsgProcessor(mfrAttituedInfoProc);

	// test 230921
	//<typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
	/*topic = new DDSTopicServicesTemplate<TestDDSConnectionTypeSupport, TestDDSConnectionDataWriter, TestDDSConnectionDataReader, TestDDSConnectionSeq, TestDDSConnection>(participant, publisher, subscriber, "TestDDSConnection");
	topicProcessorList.emplace(_T("TestDDSConnection"), topic));
	
	auto ddsConnectTopic = static_cast<DDSTopicServicesTemplate<TestDDSConnectionTypeSupport, TestDDSConnectionDataWriter, TestDDSConnectionDataReader, TestDDSConnectionSeq, TestDDSConnection>*>(topic);
	std::function<void(byte*)> ddsConnectProc = bind(&DDSMessageHandler::testDDSConnectReceived, this, std::placeholders::_1);
	ddsConnectTopic->injectDDSMsgProcessor(ddsConnectProc);*/


	// to access topic services
	for_each(topicProcessorList.begin(), topicProcessorList.end(), [this](auto elem) { elem.second->injectDDSProvider(dcps); elem.second->create(); });
}


void
DDSMessageHandler::deleteLITS_DDSTopic()
{
	for_each(topicProcessorList.begin(), topicProcessorList.end(), [](auto elem) { delete elem.second; });
	topicProcessorList.clear();
}


/************************************************************************
	methods between xxxHandler and xxxManager
************************************************************************/
void
DDSMessageHandler::injectMEB(IMEBComponent* meb)
{
	this->meb = meb;
}


void
DDSMessageHandler::processMessageSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = nomProcessorMap.find(nom->getName()); itr != nomProcessorMap.end())
	{ 
		itr->second(nom);
		//if (itr->first == L"AirThreatInformation")
		//{
		//	tstringstream pathPrefixStream;
		//	pathPrefixStream << _T("AirThreatMessage[") << 0 << _T("]");

		//	tstring pathPrefix;
		//	pathPrefixStream >> pathPrefix;
		//	tcout << nom->getValue(pathPrefix + _T(".AccelerationX"))->toShort();
		//	tcout << nom->getValue(pathPrefix + _T(".AccelerationY"))->toShort();
		//	tcout << nom->getValue(pathPrefix + _T(".AccelerationZ"))->toShort();
		//}
	}
	else
	{
		tcerr << _T("NOM does not exist.") << std::endl;
	}
}


/************************************************************************
	process NOM Messages
************************************************************************/

// test
//void
//DDSMessageHandler::testDDSConnectSent(std::shared_ptr<NOM> nom)
//{
//	tcout << _T("before test Start") << std::std::endl;
//	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
//	{	
//		auto topicInterface = static_cast<DDSTopicServicesTemplate<TestDDSConnectionTypeSupport, TestDDSConnectionDataWriter, TestDDSConnectionDataReader, TestDDSConnectionSeq, TestDDSConnection>*>(itr->second);
//		TestDDSConnection* instance = topicInterface->createTopic();
//		instance->TestParam = nom->getValue(_T("TestParam"))->toUShort();
//		tcout << _T("in Test DDS Connect Sent");
//		topicInterface->writeTopic(instance);
//	}
//	tcout << _T("after test Start") << std::std::endl;
//
//}

void
DDSMessageHandler::processAirThreatInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		inAirthreatCount++;
		if((inAirthreatCount % 50)==0)
		{ 
			ntcout << _T("in Airthreat") << std::endl;
			
			
		}
		auto topicInterface = static_cast<DDSTopicServicesTemplate<AirThreatInformationTypeSupport, AirThreatInformationDataWriter, AirThreatInformationDataReader, AirThreatInformationSeq, AirThreatInformation>*>(itr->second);
		AirThreatInformation* instance = topicInterface->createTopic();

		// MessageHeader
		instance->Header.TopicLabel = nom->getValue(_T("Header.TopicLabel"))->toUShort();
		instance->Header.TopicSize = nom->getValue(_T("Header.TopicSize"))->toUShort();
		instance->Header.SourceID = nom->getValue(_T("Header.SourceID"))->toByte();
		instance->Header.TopicClass = nom->getValue(_T("Header.TopicClass"))->toByte();
		instance->Header.TopicNumber = nom->getValue(_T("Header.TopicNumber"))->toUShort();
		instance->Header.SystemTime = nom->getValue(_T("Header.SystemTime"))->toUInt64();
		
		// AirThreatInformation
		instance->TimeTick = nom->getValue(_T("TimeTick"))->toUInt();
		instance->SimulationFlag = nom->getValue(_T("SimulationFlag"))->toUShort();
		auto objectCount = nom->getValue(_T("ObjectCount"))->toUShort();
		instance->ObjectCount = objectCount;
		instance->AirThreatInformation::AirThreatMessage.length(objectCount);
		

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << _T("AirThreatMessage[") << i << _T("]");

			tstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			instance->AirThreatInformation::AirThreatMessage[i].ObjectID = nom->getValue(pathPrefix + _T(".ObjectID"))->toUShort();
			instance->AirThreatInformation::AirThreatMessage[i].ObjectType = nom->getValue(pathPrefix + _T(".ObjectType"))->toByte();
			instance->AirThreatInformation::AirThreatMessage[i].DestructionFlag = nom->getValue(pathPrefix + _T(".DestructionFlag"))->toByte();
			instance->AirThreatInformation::AirThreatMessage[i].PositionX = nom->getValue(pathPrefix + _T(".PositionX"))->toInt();
			instance->AirThreatInformation::AirThreatMessage[i].PositionY = nom->getValue(pathPrefix + _T(".PositionY"))->toInt();
			instance->AirThreatInformation::AirThreatMessage[i].PositionZ = nom->getValue(pathPrefix + _T(".PositionZ"))->toInt();
			instance->AirThreatInformation::AirThreatMessage[i].VelocityX = nom->getValue(pathPrefix + _T(".VelocityX"))->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].VelocityY = nom->getValue(pathPrefix + _T(".VelocityY"))->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].VelocityZ = nom->getValue(pathPrefix + _T(".VelocityZ"))->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].AccelerationX = nom->getValue(pathPrefix + _T(".AccelerationX"))->toShort();
			// tcout << nom->getValue(pathPrefix + _T(".AccelerationX"))->toShort() << std::std::endl ;
			instance->AirThreatInformation::AirThreatMessage[i].AccelerationY = nom->getValue(pathPrefix + _T(".AccelerationY"))->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].AccelerationZ = nom->getValue(pathPrefix + _T(".AccelerationZ"))->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].MeanRCS = nom->getValue(pathPrefix + _T(".MeanRCS"))->toUShort();
			instance->AirThreatInformation::AirThreatMessage[i].Reserved = nom->getValue(pathPrefix + _T(".Reserved"))->toByte();
			instance->AirThreatInformation::AirThreatMessage[i].JammingType = nom->getValue(pathPrefix + _T(".JammingType"))->toByte();
			instance->AirThreatInformation::AirThreatMessage[i].JammingPower = nom->getValue(pathPrefix + _T(".JammingPower"))->toUShort();
			instance->AirThreatInformation::AirThreatMessage[i].JammingPullOff = nom->getValue(pathPrefix + _T(".JammingPullOff"))->toUShort();
		}

		topicInterface->writeTopic(instance);

		//testQueue.push_back(std::chrono::system_clock::now());	// test
	}
	else
	{
		tcerr << _T("NOM does not exist.") << std::endl;
	}
}


void
DDSMessageHandler::processInterceptorInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<InterceptorInformationTypeSupport, InterceptorInformationDataWriter, InterceptorInformationDataReader, InterceptorInformationSeq, InterceptorInformation>*>(itr->second);
		InterceptorInformation* instance = topicInterface->createTopic();

		// MessageHeader
		instance->Header.TopicLabel = nom->getValue(_T("Header.TopicLabel"))->toUShort();
		instance->Header.TopicSize = nom->getValue(_T("Header.TopicSize"))->toUShort();
		instance->Header.SourceID = nom->getValue(_T("Header.SourceID"))->toByte();
		instance->Header.TopicClass = nom->getValue(_T("Header.TopicClass"))->toByte();
		instance->Header.TopicNumber = nom->getValue(_T("Header.TopicNumber"))->toUShort();
		instance->Header.SystemTime = nom->getValue(_T("Header.SystemTime"))->toUInt64();

		instance->TimeTick = nom->getValue(_T("TimeTick"))->toUInt();
		instance->SimulationFlag = nom->getValue(_T("SimulationFlag"))->toUShort();
		auto objectCount = nom->getValue(_T("ObjectCount"))->toUShort();
		instance->ObjectCount = objectCount;
		instance->InterceptorInformation::InterceptorMessage.length(objectCount);

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << _T("InterceptorMessage[") << i << _T("]");

			tstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			instance->InterceptorInformation::InterceptorMessage[i].ObjectID = nom->getValue(pathPrefix + _T(".ObjectID"))->toUShort();	// [2021.12.06] ysk
			instance->InterceptorInformation::InterceptorMessage[i].MissileType = nom->getValue(pathPrefix + _T(".MissileType"))->toByte();
			instance->InterceptorInformation::InterceptorMessage[i].DestructionFlag = nom->getValue(pathPrefix + _T(".DestructionFlag"))->toByte();
			instance->InterceptorInformation::InterceptorMessage[i].PositionX = nom->getValue(pathPrefix + _T(".PositionX"))->toInt();
			instance->InterceptorInformation::InterceptorMessage[i].PositionY = nom->getValue(pathPrefix + _T(".PositionY"))->toInt();
			instance->InterceptorInformation::InterceptorMessage[i].PositionZ = nom->getValue(pathPrefix + _T(".PositionZ"))->toInt();
			instance->InterceptorInformation::InterceptorMessage[i].VelocityX = nom->getValue(pathPrefix + _T(".VelocityX"))->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].VelocityY = nom->getValue(pathPrefix + _T(".VelocityY"))->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].VelocityZ = nom->getValue(pathPrefix + _T(".VelocityZ"))->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].AccelerationX = nom->getValue(pathPrefix + _T(".AccelerationX"))->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].AccelerationY = nom->getValue(pathPrefix + _T(".AccelerationY"))->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].AccelerationZ = nom->getValue(pathPrefix + _T(".AccelerationZ"))->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].MeanRCS = nom->getValue(pathPrefix + _T(".MeanRCS"))->toUShort();		// [22.09.06] ksy
			instance->InterceptorInformation::InterceptorMessage[i].Reserved = nom->getValue(pathPrefix + _T(".Reserved"))->toUShort();		// [22.09.06] ksy
			instance->InterceptorInformation::InterceptorMessage[i].SignalPower = nom->getValue(pathPrefix + _T(".SignalPower"))->toUShort();
			instance->InterceptorInformation::InterceptorMessage[i].SeekerPhase = nom->getValue(pathPrefix + _T(".SeekerPhase"))->toByte();	// [22.09.06] ksy
			instance->InterceptorInformation::InterceptorMessage[i].AddressKey = nom->getValue(pathPrefix + _T(".AddressKey"))->toByte();	// [22.05.24] ksy
		}

		topicInterface->writeTopic(instance);
	}
	else
	{
		tcerr << _T("NOM does not exist.") << std::endl;
	}
}


void
DDSMessageHandler::processUplinkInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<UplinkInformationTypeSupport, UplinkInformationDataWriter, UplinkInformationDataReader, UplinkInformationSeq, UplinkInformation>*>(itr->second);
		UplinkInformation* instance = topicInterface->createTopic();

		// MessageHeader
		instance->Header.TopicLabel = nom->getValue(_T("Header.TopicLabel"))->toUShort();
		instance->Header.TopicSize = nom->getValue(_T("Header.TopicSize"))->toUShort();
		instance->Header.SourceID = nom->getValue(_T("Header.SourceID"))->toByte();
		instance->Header.TopicClass = nom->getValue(_T("Header.TopicClass"))->toByte();
		instance->Header.TopicNumber = nom->getValue(_T("Header.TopicNumber"))->toUShort();
		instance->Header.SystemTime = nom->getValue(_T("Header.SystemTime"))->toUInt64();

		instance->TimeTick = nom->getValue(_T("TimeTick"))->toUInt();
	
		// [21.11.10] ysk, [22.05.24] ksy
		instance->UplinkMessage.AddressKey = nom->getValue(_T("UplinkMessage.AddressKey"))->toUInt();
		instance->UplinkMessage.MissileType = nom->getValue(_T("UplinkMessage.MissileType"))->toUInt();

		for (auto i = 0; i < 26; i++)
		{
			instance->UplinkMessage.Data[i] = nom->getValue(_T("UplinkMessage.Data"), i)->toUShort();
		}

		topicInterface->writeTopic(instance);
	}
	else
	{
		tcerr << _T("NOM does not exist.") << std::endl;
	}
}


void
DDSMessageHandler::processDownlinkInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<DownlinkInformationTypeSupport, DownlinkInformationDataWriter, DownlinkInformationDataReader, DownlinkInformationSeq, DownlinkInformation>*>(itr->second);
		DownlinkInformation* instance = topicInterface->createTopic();

		// MessageHeader
		instance->Header.TopicLabel = nom->getValue(_T("Header.TopicLabel"))->toUShort();
		instance->Header.TopicSize = nom->getValue(_T("Header.TopicSize"))->toUShort();
		instance->Header.SourceID = nom->getValue(_T("Header.SourceID"))->toByte();
		instance->Header.TopicClass = nom->getValue(_T("Header.TopicClass"))->toByte();
		instance->Header.TopicNumber = nom->getValue(_T("Header.TopicNumber"))->toUShort();
		instance->Header.SystemTime = nom->getValue(_T("Header.SystemTime"))->toUInt64();

		instance->TimeTick = nom->getValue(_T("TimeTick"))->toUInt();
		auto objectCount = nom->getValue(_T("ObjectCount"))->toUInt();
		instance->ObjectCount = objectCount;
		instance->DownlinkInformation::DownlinkMessage.length(objectCount);

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << _T("DownlinkMessage[") << i << _T("]");

			tstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			instance->DownlinkInformation::DownlinkMessage[i].AddressKey = nom->getValue(pathPrefix + _T(".AddressKey"))->toUShort();
			instance->DownlinkInformation::DownlinkMessage[i].CRC = nom->getValue(pathPrefix + _T(".CRC"))->toUShort();

			for (auto j = 0; j < 24; j++)
			{
				instance->DownlinkInformation::DownlinkMessage[i].Data[j] = nom->getValue(pathPrefix + _T(".Data"), j)->toUShort();
			}
		}

		topicInterface->writeTopic(instance);
	}
	else
	{
		tcerr << _T("NOM does not exist.") << std::endl;
	}
}


void
DDSMessageHandler::processTimeTickInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<TimeTickInformationTypeSupport, TimeTickInformationDataWriter, TimeTickInformationDataReader, TimeTickInformationSeq, TimeTickInformation>*>(itr->second);
		TimeTickInformation* instance = topicInterface->createTopic();

		instance->Header.TopicLabel = nom->getValue(_T("Header.TopicLabel"))->toUShort();
		instance->Header.TopicSize = nom->getValue(_T("Header.TopicSize"))->toUShort();
		instance->Header.SourceID = nom->getValue(_T("Header.SourceID"))->toByte();
		instance->Header.TopicClass = nom->getValue(_T("Header.TopicClass"))->toByte();
		instance->Header.TopicNumber = nom->getValue(_T("Header.TopicNumber"))->toUShort();
		instance->Header.SystemTime = nom->getValue(_T("Header.SystemTime"))->toUInt64();
		instance->TimeTickMessage.SyncCycle = nom->getValue(_T("TimeTickMessage.SyncCycle"))->toUInt();
		instance->TimeTickMessage.TimeTick = nom->getValue(_T("TimeTickMessage.TimeTick"))->toUInt();
		topicInterface->writeTopic(instance);
}
	else
	{
		tcerr << _T("NOM does not exist.") << std::endl;
	}
}


void
DDSMessageHandler::processMFRAttitudeInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<MFRAttitudeInformationTypeSupport, MFRAttitudeInformationDataWriter, MFRAttitudeInformationDataReader, MFRAttitudeInformationSeq, MFRAttitudeInformation>*>(itr->second);
		MFRAttitudeInformation* instance = topicInterface->createTopic();

		instance->Header.TopicLabel = nom->getValue(_T("Header.TopicLabel"))->toUShort();
		instance->Header.TopicSize = nom->getValue(_T("Header.TopicSize"))->toUShort();
		instance->Header.SourceID = nom->getValue(_T("Header.SourceID"))->toByte();
		instance->Header.TopicClass = nom->getValue(_T("Header.TopicClass"))->toByte();
		instance->Header.TopicNumber = nom->getValue(_T("Header.TopicNumber"))->toUShort();
		instance->Header.SystemTime = nom->getValue(_T("Header.SystemTime"))->toUInt64();
		instance->MFRAttitudeMessage.MFRAntennaRoll = nom->getValue(_T("MFRAttitudeMessage.MFRAntennaRoll"))->toFloat();
		instance->MFRAttitudeMessage.MFRAntennaPitch = nom->getValue(_T("MFRAttitudeMessage.MFRAntennaPitch"))->toFloat();
		instance->MFRAttitudeMessage.MFRAntennaHeading = nom->getValue(_T("MFRAttitudeMessage.MFRAntennaHeading"))->toFloat();
		topicInterface->writeTopic(instance);
	}
	else
	{
		tcerr << _T("NOM does not exist.") << std::endl;
	}
}

/************************************************************************
	process Topic Messages
************************************************************************/
void
DDSMessageHandler::processAirThreatInformationReceived(byte* instance)
{
	// if need be, write your code
	// converting topic instance to nom instance should be implemented.
	// [22.05.25] ksy
	AirThreatInformation* topic = nullptr;
	topic = reinterpret_cast<AirThreatInformation*>(instance);

		// [2021.11.12] ysk
	int topicKey = 1000 + topic->Header.SourceID;
	//tcout << topic->Header.SourceID << std::endl;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(_T("Header.TopicLabel"), &NUShort(topic->Header.TopicLabel));
		nom->setValue(_T("Header.TopicSize"), &NUShort(topic->Header.TopicSize));
		nom->setValue(_T("Header.SourceID"), &NByte(topic->Header.SourceID));
		nom->setValue(_T("Header.TopicClass"), &NByte(topic->Header.TopicClass));
		nom->setValue(_T("Header.TopicNumber"), &NUShort(topic->Header.TopicNumber));
		nom->setValue(_T("Header.SystemTime"), &NUInteger64((uint64)(topic->Header.SystemTime)));

		// body
		nom->setValue(_T("TimeTick"), &NUInteger(topic->TimeTick));
		nom->setValue(_T("SimulationFlag"), &NUShort(topic->SimulationFlag));
		auto objectCount = topic->ObjectCount;
		nom->setValue(_T("ObjectCount"), &NUShort(objectCount));

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << _T("AirThreatMessage[") << i << _T("]");

			tstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			nom->setValue(pathPrefix + _T(".ObjectID"), &NUShort(topic->AirThreatMessage[i].ObjectID));
			nom->setValue(pathPrefix + _T(".ObjectType"), &NByte(topic->AirThreatMessage[i].ObjectType));
			nom->setValue(pathPrefix + _T(".DestructionFlag"), &NByte(topic->AirThreatMessage[i].DestructionFlag));
			nom->setValue(pathPrefix + _T(".PositionX"), &NInteger(topic->AirThreatMessage[i].PositionX));
			nom->setValue(pathPrefix + _T(".PositionY"), &NInteger(topic->AirThreatMessage[i].PositionY));
			nom->setValue(pathPrefix + _T(".PositionZ"), &NInteger(topic->AirThreatMessage[i].PositionZ));
			nom->setValue(pathPrefix + _T(".VelocityX"), &NShort(topic->AirThreatMessage[i].VelocityX));
			nom->setValue(pathPrefix + _T(".VelocityY"), &NShort(topic->AirThreatMessage[i].VelocityY));
			nom->setValue(pathPrefix + _T(".VelocityZ"), &NShort(topic->AirThreatMessage[i].VelocityZ));
			nom->setValue(pathPrefix + _T(".AccelerationX"), &NShort(topic->AirThreatMessage[i].AccelerationX));
			nom->setValue(pathPrefix + _T(".AccelerationY"), &NShort(topic->AirThreatMessage[i].AccelerationY));
			nom->setValue(pathPrefix + _T(".AccelerationZ"), &NShort(topic->AirThreatMessage[i].AccelerationZ));
			nom->setValue(pathPrefix + _T(".MeanRCS"), &NUShort(topic->AirThreatMessage[i].MeanRCS));
			nom->setValue(pathPrefix + _T(".Reserved"), &NByte(topic->AirThreatMessage[i].Reserved));
			nom->setValue(pathPrefix + _T(".JammingType"), &NByte(topic->AirThreatMessage[i].JammingType));
			nom->setValue(pathPrefix + _T(".JammingPower"), &NUShort(topic->AirThreatMessage[i].JammingPower));
			nom->setValue(pathPrefix + _T(".JammingPullOff"), &NUShort(topic->AirThreatMessage[i].JammingPullOff));
		}

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processInterceptorInformationReceived(byte* instance)
{
	// if need be, write your code
	// getting the nom instance must be implemented.
	// [22.05.25] ksy
	InterceptorInformation* topic = nullptr;
	topic = reinterpret_cast<InterceptorInformation*>(instance);

	// [2021.11.12] ysk
	int topicKey = 2000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(_T("Header.TopicLabel"), &NUShort(topic->Header.TopicLabel));
		nom->setValue(_T("Header.TopicSize"), &NUShort(topic->Header.TopicSize));
		nom->setValue(_T("Header.SourceID"), &NByte(topic->Header.SourceID));
		nom->setValue(_T("Header.TopicClass"), &NByte(topic->Header.TopicClass));
		nom->setValue(_T("Header.TopicNumber"), &NUShort(topic->Header.TopicNumber));
		nom->setValue(_T("Header.SystemTime"), &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(_T("TimeTick"), &NUInteger(topic->TimeTick));
		nom->setValue(_T("SimulationFlag"), &NUShort(topic->SimulationFlag));
		auto objectCount = topic->ObjectCount;
		nom->setValue(_T("ObjectCount"), &NUShort(objectCount));

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << _T("InterceptorMessage[") << i << _T("]");

			tstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			nom->setValue(pathPrefix + _T(".ObjectID"), &NUShort(topic->InterceptorMessage[i].ObjectID));
			nom->setValue(pathPrefix + _T(".MissileType"), &NByte(topic->InterceptorMessage[i].MissileType));
			nom->setValue(pathPrefix + _T(".DestructionFlag"), &NByte(topic->InterceptorMessage[i].DestructionFlag));
			nom->setValue(pathPrefix + _T(".PositionX"), &NInteger(topic->InterceptorMessage[i].PositionX));
			nom->setValue(pathPrefix + _T(".PositionY"), &NInteger(topic->InterceptorMessage[i].PositionY));
			nom->setValue(pathPrefix + _T(".PositionZ"), &NInteger(topic->InterceptorMessage[i].PositionZ));
			nom->setValue(pathPrefix + _T(".VelocityX"), &NShort(topic->InterceptorMessage[i].VelocityX));
			nom->setValue(pathPrefix + _T(".VelocityY"), &NShort(topic->InterceptorMessage[i].VelocityY));
			nom->setValue(pathPrefix + _T(".VelocityZ"), &NShort(topic->InterceptorMessage[i].VelocityZ));
			nom->setValue(pathPrefix + _T(".AccelerationX"), &NShort(topic->InterceptorMessage[i].AccelerationX));
			nom->setValue(pathPrefix + _T(".AccelerationY"), &NShort(topic->InterceptorMessage[i].AccelerationY));
			nom->setValue(pathPrefix + _T(".AccelerationZ"), &NShort(topic->InterceptorMessage[i].AccelerationZ));
			nom->setValue(pathPrefix + _T(".MeanRCS"), &NUShort(topic->InterceptorMessage[i].MeanRCS));
			nom->setValue(pathPrefix + _T(".Reserved"), &NUShort(topic->InterceptorMessage[i].Reserved));
			nom->setValue(pathPrefix + _T(".SignalPower"), &NUShort(topic->InterceptorMessage[i].SignalPower));
			nom->setValue(pathPrefix + _T(".SeekerPhase"), &NByte(topic->InterceptorMessage[i].SeekerPhase));
			nom->setValue(pathPrefix + _T(".AddressKey"), &NByte(topic->InterceptorMessage[i].AddressKey));	// [22.05.24] ksy
		}

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processUplinkInformationReceived(byte* instance)
{
	// [22.05.25] ksy
	UplinkInformation* topic = nullptr;
	topic = reinterpret_cast<UplinkInformation*>(instance);

	// [2021.11.12] ysk
	int topicKey = 3000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(_T("Header.TopicLabel"), &NUShort(topic->Header.TopicLabel));
		nom->setValue(_T("Header.TopicSize"), &NUShort(topic->Header.TopicSize));
		nom->setValue(_T("Header.SourceID"), &NByte(topic->Header.SourceID));
		nom->setValue(_T("Header.TopicClass"), &NByte(topic->Header.TopicClass));
		nom->setValue(_T("Header.TopicNumber"), &NUShort(topic->Header.TopicNumber));
		nom->setValue(_T("Header.SystemTime"), &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(_T("TimeTick"), &NUInteger(topic->TimeTick));
		nom->setValue(_T("UplinkMessage.AddressKey"), &NUShort(topic->UplinkMessage.AddressKey));
		nom->setValue(_T("UplinkMessage.MissileType"), &NUShort(topic->UplinkMessage.MissileType));

		for (auto i = 0; i < 26; i++)
		{
			nom->setValue(_T("UplinkMessage.Data"), &NUShort(topic->UplinkMessage.Data[i]), i);
		}

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processDownlinkInformationReceived(byte* instance)
{
	// [22.05.25] ksy
	DownlinkInformation* topic = nullptr;
	topic = reinterpret_cast<DownlinkInformation*>(instance);

	// [2021.11.12] ysk
	int topicKey = 4000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(_T("Header.TopicLabel"), &NUShort(topic->Header.TopicLabel));
		nom->setValue(_T("Header.TopicSize"), &NUShort(topic->Header.TopicSize));
		nom->setValue(_T("Header.SourceID"), &NByte(topic->Header.SourceID));
		nom->setValue(_T("Header.TopicClass"), &NByte(topic->Header.TopicClass));
		nom->setValue(_T("Header.TopicNumber"), &NUShort(topic->Header.TopicNumber));
		nom->setValue(_T("Header.SystemTime"), &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(_T("TimeTick"), &NUInteger(topic->TimeTick));
		uint objectCount = topic->ObjectCount;
		nom->setValue(_T("ObjectCount"), &NUInteger(objectCount));

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << _T("DownlinkMessage[") << i << _T("]");

			tstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			nom->setValue(pathPrefix + _T(".AddressKey"), &NUShort(topic->DownlinkMessage[i].AddressKey));
			nom->setValue(pathPrefix + _T(".CRC"), &NUShort(topic->DownlinkMessage[i].CRC));

			for (auto j = 0; j < 24; j++)
			{
				nom->setValue(pathPrefix + _T(".Data"), &NUShort(topic->DownlinkMessage[i].Data[j]), j);
			}
		}

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processTimeTickInformationReceived(byte* instance)
{
	// if need be, write your code
	// getting the nom instance must be implemented.
	// [22.05.25] ksy
	TimeTickInformation* topic = nullptr;
	topic = reinterpret_cast<TimeTickInformation*>(instance);

	// [2021.11.12] ysk
	int topicKey = 5000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(_T("Header.TopicLabel"), &NUShort(topic->Header.TopicLabel));
		nom->setValue(_T("Header.TopicSize"), &NUShort(topic->Header.TopicSize));
		nom->setValue(_T("Header.SourceID"), &NByte(topic->Header.SourceID));
		nom->setValue(_T("Header.TopicClass"), &NByte(topic->Header.TopicClass));
		nom->setValue(_T("Header.TopicNumber"), &NUShort(topic->Header.TopicNumber));
		nom->setValue(_T("Header.SystemTime"), &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(_T("TimeTickMessage.SyncCycle"), &NUInteger(topic->TimeTickMessage.SyncCycle));
		nom->setValue(_T("TimeTickMessage.TimeTick"), &NUInteger(topic->TimeTickMessage.TimeTick));

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processMFRAttitudeInformationReceived(byte* instance)
{
	// [2022.05.24] ksy
	MFRAttitudeInformation* topic = nullptr;
	topic = reinterpret_cast<MFRAttitudeInformation*>(instance);

	int topicKey = 6000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(_T("Header.TopicLabel"), &NUShort(topic->Header.TopicLabel));
		nom->setValue(_T("Header.TopicSize"), &NUShort(topic->Header.TopicSize));
		nom->setValue(_T("Header.SourceID"), &NByte(topic->Header.SourceID));
		nom->setValue(_T("Header.TopicClass"), &NByte(topic->Header.TopicClass));
		nom->setValue(_T("Header.TopicNumber"), &NUShort(topic->Header.TopicNumber));
		nom->setValue(_T("Header.SystemTime"), &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(_T("MFRAttitudeMessage.MFRAntennaRoll"), &NFloat(topic->MFRAttitudeMessage.MFRAntennaRoll));
		nom->setValue(_T("MFRAttitudeMessage.MFRAntennaPitch"), &NFloat(topic->MFRAttitudeMessage.MFRAntennaPitch));
		nom->setValue(_T("MFRAttitudeMessage.MFRAntennaHeading"), &NFloat(topic->MFRAttitudeMessage.MFRAntennaHeading));

		user->updateMsg(nom);
	}
}


// test
//void
//DDSMessageHandler::testDDSConnectReceived(byte* instance)
//{
//	// [2022.05.24] ksy
//	TestDDSConnection* topic = nullptr;
//	topic = reinterpret_cast<TestDDSConnection*>(instance);
//	std::shared_ptr<NOM> nomMsg;
//
//	nomMsg = user->registerMsg(_T("TestDDSConnection"));
//	
//	nomMsg->setValue(_T("TestParam"), &NUShort(topic->TestParam));
//	tcout << _T("DDS Received Message!"); // [23.10.25] 받는 부분 코드 수정 - hs
//
//	user->updateMsg(nomMsg);
//}