#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>

#include <functional>
#include <map>
#include <memory>

#include "MFRS_STRUCT.h"

using namespace nframework;
using namespace nom;

class BASEMGRDLL_API MFRSModelManager : public BaseManager
{
public:
	MFRSModelManager(void);
	~MFRSModelManager(void);

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

	void recvScenario(std::shared_ptr<NOM> nomMsg);

private:
	std::map<
		tstring,
		std::function<void(std::shared_ptr<NOM>)>
	> msgFuncMap;

	std::shared_ptr<MFRS_MODEL> MFRSModel;

private:
	IMEBComponent* meb = nullptr;
	MECComponent* mec = nullptr;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
};

