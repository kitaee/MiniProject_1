#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/comm/HLACommInterface.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <sstream>
#include <vector>
#include <iostream>
#include <atomic>
#include <future>
#include <thread>

using namespace nframework;
using namespace nom;
using namespace nicelink;
using namespace nlinestream;

class BASEMGRDLL_API RTICommunicationManager : public BaseManager
{
public:
	RTICommunicationManager(void);
	~RTICommunicationManager(void);

	// inherited from the BaseManager class
	virtual std::shared_ptr<NOM> registerMsg(tstring) override;
	virtual void discoverMsg(std::shared_ptr<NOM>) override;
	virtual void updateMsg(std::shared_ptr<NOM>) override;
	virtual void reflectMsg(std::shared_ptr<NOM>) override;
	virtual void deleteMsg(std::shared_ptr<NOM>) override;
	virtual void removeMsg(std::shared_ptr<NOM>) override;
	virtual void sendMsg(std::shared_ptr<NOM>) override;
	virtual void recvMsg(std::shared_ptr<NOM>) override;
	virtual void setUserName(tstring) override;
	virtual tstring getUserName() override;
	virtual void setData(void*) override;
	virtual bool start() override;
	virtual bool stop() override;
	virtual void setMEBComponent(IMEBComponent*) override;

private:
	void initialize();
	void release();
	void resignFed();
	void joinFed();

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsg;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsg;

	std::unique_ptr<CommunicationInterface> hlaCommunicator;
	CommunicationConfig* hlaCommConfig;

	std::mutex mut;

	std::shared_ptr<bool> isStarted = std::make_shared<bool>(false);

	std::atomic<bool> continueSimFlag;

	NLineTstream ntcout { Level::COUT };
	
};


