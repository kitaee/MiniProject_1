#pragma once
#include <nFramework/mec/MECComponent.h>
#include <nFramework/comm/NCommInterface.h>
#include "CommMessageHandler.h"
#include <nFramework/nom/NOMParser.h>
#include <nFramework/Log4nF/Loggable.h>
using namespace std;
using namespace nframework;
using namespace nom;
using namespace ncomm;
using namespace log4nf;

class BASEMGRDLL_API UDPCommunicationManager : public BaseManager
{
public:
	UDPCommunicationManager(void);
	~UDPCommunicationManager(void);

public:
	// inherited from the BaseManager class
	shared_ptr<NOM> registerMsg(std::wstring) override;
	void discoverMsg(shared_ptr<NOM>) override;
	void updateMsg(shared_ptr<NOM>) override;
	void reflectMsg(shared_ptr<NOM>) override;
	void deleteMsg(shared_ptr<NOM>) override;
	void removeMsg(shared_ptr<NOM>) override;
	void sendMsg(shared_ptr<NOM>) override;
	void recvMsg(shared_ptr<NOM>) override;
	void setUserName(std::wstring) override;
	tstring getUserName() override;
	void setData(void*) override;
	bool start() override;
	bool stop() override;
	void setMEBComponent(IMEBComponent*) override;
	
public:
	void processRecvMessage(unsigned char* data, int size);
	unsigned int getObjectInstanceID(shared_ptr<NOM> nomMsg);
	
private:
	void init();
	void release();
	
public:
	std::unique_ptr<NOMParser> nomParser;

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	map<unsigned int, shared_ptr<NOM>> registeredMsg;
	map<unsigned int, shared_ptr<NOM>> discoveredMsg;

	CommunicationInterface* commInterface;
	CommunicationConfig* commConfig;
	CommMessageHandler commMsgHandler;

	static inline Loggable l{ L"UDPCommunicationManager" };
};

