#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <functional>
#include <map>

using namespace nframework;
using namespace nom;

class BASEMGRDLL_API ATSModelManager : public BaseManager
{
public:
	ATSModelManager(void);
	~ATSModelManager(void);

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
	void recvDeployScenarioToModel(std::shared_ptr<NOM> nomMsg);
	void recvStartSimulationToModel(std::shared_ptr<NOM> nomMsg);
	void recvStopSimulationToModel(std::shared_ptr<NOM> nomMsg);
	void recvDetonationInfoToModel(std::shared_ptr<NOM> nomMsg);
	void sendATInfo();

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> funcMap;

private:
	bool scenarioLoaded = false;
	bool simulationRunning = false;
	bool airThreatDetonated = false;
};

