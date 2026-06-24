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
	void ProcessTestCode();
	virtual bool stop() override;
	virtual void setMEBComponent(IMEBComponent*) override;
	
public:
	void processRecvMessage(unsigned char* data, int size);
	unsigned int getObjectInstanceID(shared_ptr<NOM> nomMsg);
	
private:
	void init();
	void release();
	void sendInnerMsg(shared_ptr<NOM> nomMsg);
	void funcMapInit();

private:
	//void recvSendScenario(shared_ptr<NOM> nomMsg);
	void deployScenario(shared_ptr<NOM> nomMsg);
	void sendScenarioAck(shared_ptr<NOM> nomMsg);
	void startSimulation(shared_ptr<NOM> nomMsg);
	void stopSimulation(shared_ptr<NOM> nomMsg);
	void launchMissle(shared_ptr<NOM> nomMsg);
	void recvLaunchMissleResponse(shared_ptr<NOM> nomMsg);
	void sendMissleFireResult(shared_ptr<NOM> nomMsg);
	void sendMissleFireRequestToMissle(shared_ptr<NOM> nomMsg);
	/*void recvStartSimulation(shared_ptr<NOM> nomMsg);
	void recvStopSimulation(shared_ptr<NOM> nomMsg);
	void recvInnerSendScenarioAck(shared_ptr<NOM> nomMsg);
	void recvInnerStartSimulationAck(shared_ptr<NOM> nomMsg);
	void recvInnerStopSimulationAck(shared_ptr<NOM> nomMsg);
	void recvInnerSimulatorStateComm(shared_ptr<NOM> nomMsg);
	void recvInnerAirThreatInfo(shared_ptr<NOM> nomMsg);
	void recvMissileDetonation(shared_ptr<NOM> nomMsg);*/
	void recvInnerRouteToComm(shared_ptr<NOM> nomMsg);
	
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

