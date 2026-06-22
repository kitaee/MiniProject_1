#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <functional>
#include <map>

using namespace nframework;
using namespace nom;

class BASEMGRDLL_API SimulationManager : public BaseManager
{
public:
	SimulationManager(void);
	~SimulationManager(void);

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
	void funcMapInit();

private:
	// 내부 연동(수신 후 모델로 보냄)
	void recvDeployScenarioRequest(std::shared_ptr<NOM> nomMsg);
	void recvStartSimulationRequest(std::shared_ptr<NOM> nomMsg);
	void recvStopSimulationRequest(std::shared_ptr<NOM> nomMsg);
	void recvDetonationInfo(std::shared_ptr<NOM> nomMsg);

	// 내부 연동(송신 - UDP로 보냄)
	void sendScenarioACK(std::shared_ptr<NOM> srcMsg); // srcMsg로 함
	void forwardToModel(tstring msgName, std::shared_ptr<NOM> srcMsg);

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;

	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> funcMap;
};

