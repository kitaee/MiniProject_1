#pragma once
#include <nFramework/mec/MECComponent.h>
#include <nFramework/comm/NCommInterface.h>
#include "CommMessageHandler.h"
#include <nFramework/nom/NOMParser.h>
#include <nFramework/nLineStream/NLineStreamMain.h>

#include "MFRSHeader.h"

using namespace std;
using namespace nframework;
using namespace nom;
using namespace ncomm;

class BASEMGRDLL_API UDPCommunicationManager : public BaseManager
{
public:
	UDPCommunicationManager(void);
	~UDPCommunicationManager(void);

public:
	// inherited from the BaseManager class
	virtual shared_ptr<NOM> registerMsg(tstring) override;
	virtual void discoverMsg(shared_ptr<NOM>) override;
	virtual void updateMsg(shared_ptr<NOM>) override;
	virtual void reflectMsg(shared_ptr<NOM>) override;
	virtual void deleteMsg(shared_ptr<NOM>) override;
	virtual void removeMsg(shared_ptr<NOM>) override;
	virtual void sendMsg(shared_ptr<NOM>) override;
	virtual void recvMsg(shared_ptr<NOM>) override;
	virtual void setUserName(tstring) override;
	virtual tstring getUserName() override;
	virtual void setData(void*) override;
	virtual bool start() override;
	virtual bool stop() override;
	virtual void setMEBComponent(IMEBComponent*) override;
	
public:
	void processRecvMessage(unsigned char* data, int size);
	unsigned int getObjectInstanceID(shared_ptr<NOM> nomMsg);
	
private:
	void init();
	void release();
	void sendInnerMsg(shared_ptr<NOM> nomMsg); // <- 안 쓰는듯?
	void funcMapInit();

private:
	// 외부 연동(수신)
	void recvDeployScenarioRequest(shared_ptr<NOM> nomMsg);
	void recvStartSimulationRequest(shared_ptr<NOM> nomMsg);
	void recvStopSimulationRequest(shared_ptr<NOM> nomMsg);
	void recvDetonationInfo(shared_ptr<NOM> nomMsg);

	// 내부 연동(수신)
	void recvScenarioACK(shared_ptr<NOM> nomMsg);
	void recvATInfo(shared_ptr<NOM> nomMsg);
	
public:
	std::unique_ptr<NOMParser> nomParser;

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	map<unsigned int, shared_ptr<NOM>> registeredMsg;
	map<unsigned int, shared_ptr<NOM>> discoveredMsg;
	map<tstring, function<void(shared_ptr<NOM>)>> funcMap;

	CommunicationInterface* commInterface;
	CommunicationConfig* commConfig;
	CommMessageHandler commMsgHandler;
	tstring routeString;
};

