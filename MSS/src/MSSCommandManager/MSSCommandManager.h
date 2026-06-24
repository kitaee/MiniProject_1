#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>

using namespace nframework;
using namespace nom;

class BASEMGRDLL_API MSSCommandManager : public BaseManager
{
public:
	MSSCommandManager(void);
	~MSSCommandManager(void);

public:
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

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;

private:
	enum class MSSState
	{
		Idle,
		ScenarioLoading,
		Ready,
		Running,
		Engaged,
		Stopped
	};

	bool isMessageAllowedInCurrentState(const tstring& msgName) const;

	void recvInnerSendScenario(std::shared_ptr<NOM> nomMsg);
	void recvInnerSendCompleteInitialize(std::shared_ptr<NOM> nomMsg);
	void recvInnerStartSimulation(std::shared_ptr<NOM> nomMsg);
	void recvInnerStopSimulation(std::shared_ptr<NOM> nomMsg);
	void recvInnerLaunchMissile(std::shared_ptr<NOM> nomMsg);
	void recvInnerUplinkInfo(std::shared_ptr<NOM> nomMsg);
	void recvInnerDownlinkInfoFromModel(std::shared_ptr<NOM> nomMsg);
	void recvInnerDetonationEvent(std::shared_ptr<NOM> nomMsg);


	MSSState currentState;
};

