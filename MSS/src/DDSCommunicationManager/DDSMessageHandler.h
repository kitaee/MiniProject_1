#pragma once
#include "DDSTopicServicesTemplate.hpp"
#include <nFramework/BaseManager.h>
#include <nFramework/util/IniHandler.h>
#include <nFramework/nom/NOMParser.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <sstream>

using namespace nframework;
using namespace nlinestream;
//class DDSMessageTable;

class DDSMessageHandler
{
public:
	DDSMessageHandler(BaseManager* ddsSimNetManager);
	~DDSMessageHandler(void);

public:
	void processAirThreatInformationReceived(byte* instance);
	void processInterceptorInformationReceived(byte* instance);
	void processUplinkInformationReceived(byte* instance);
	void processDownlinkInformationReceived(byte* instance);
	void processTimeTickInformationReceived(byte* instance);
	void processMFRAttitudeInformationReceived(byte* instance);
	void testDDSConnectReceived(byte* instance); //test 

public:
	void injectMEB(IMEBComponent* meb);
	void processMessageSent(std::shared_ptr<NOM> nom);

private:
	void processAirThreatInformationSent(std::shared_ptr<NOM> nom);
	void processInterceptorInformationSent(std::shared_ptr<NOM> nom);
	void processUplinkInformationSent(std::shared_ptr<NOM> nom);
	void processDownlinkInformationSent(std::shared_ptr<NOM> nom);
	void processTimeTickInformationSent(std::shared_ptr<NOM> nom);
	void processMFRAttitudeInformationSent(std::shared_ptr<NOM> nom);
	// void testDDSConnectSent(std::shared_ptr<NOM> nom); //test 

private:
	void initialize();
	void release();
	void registerNOMMsg();
	void registerNOMMsgProcessor();
	void deleteNOMMsgProcessor();
	void createLITS_DDSTopic();
	void deleteLITS_DDSTopic();
	// void processStop(std::shared_ptr<NOM> nom);	// test

private:
	BaseManager* user;
	IMEBComponent* meb;

	DDSServiceProvider* dcps;
	DDSDomainParticipant* participant;
	DDSPublisher* publisher;
	DDSSubscriber* subscriber;
	int domainId;
	// string project;
	//DDSMessageTable* ddsMsgTable;
	std::map<tstring, DDSProviderInterface*> topicProcessorList;
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> nomProcessorMap;
	std::unique_ptr<NOMParser> nomParser;
	std::map<tstring, NMessage*> msgMap;

	std::map<int, std::shared_ptr<NOM>> topicList;	// key : source id

	// temp
	int inAirthreatCount{ 0 };

	// list<std::chrono::system_clock::time_point> testQueue;	// test
	NLineTstream ntcout{ Level::COUT };
	
};
