#pragma once

#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/util/IniHandler.h>
#include <sstream>
#include <windows.h>

#include "MFRSHeader.h"

using namespace nframework;
using namespace nlinestream;
using namespace nom;
using namespace std;

class BASEMGRDLL_API SimulationManager : public BaseManager
{
public:
	SimulationManager();
	~SimulationManager();

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
	void recvInnerSendScenario(std::shared_ptr<NOM>);
	void recvInnerStartSimulation(std::shared_ptr<NOM>);
	void recvInnerStopSimulation(std::shared_ptr<NOM>);

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
	map<tstring, function<void(shared_ptr<NOM>)>> funcMap;

	std::shared_ptr<NOM> testObjNOM;

	NLineTstream ntcout{ Level::COUT };
};