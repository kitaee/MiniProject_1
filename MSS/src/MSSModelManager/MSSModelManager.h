#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include "Missile.h"
#include "IGuidanceModel.h"

using namespace nframework;
using namespace nom;

class BASEMGRDLL_API MSSModelManager : public BaseManager
{
public:
	MSSModelManager(void);
	~MSSModelManager(void);

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
	std::unique_ptr<Missile> missile;
	std::unique_ptr<IGuidanceModel> guidanceModel;


private:
	void recvInnerSendScenarioToModel(std::shared_ptr<NOM> nomMsg);
	void recvInnerStartSimulationToModel(std::shared_ptr<NOM> nomMsg);
	void recvInnerStopSimulationToModel(std::shared_ptr<NOM> nomMsg);
	void recvInnerLaunchMissileToModel(std::shared_ptr<NOM> nomMsg);
	void recvInnerUplinkInfoToModel(std::shared_ptr<NOM> nomMsg);
};

