#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <sstream>
#include <chrono>


using namespace nframework;
using namespace nom;
using namespace nlinestream;


class BASEMGRDLL_API CommandManager : public BaseManager
{
public:
	CommandManager(void);
	~CommandManager(void);

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
	void init();
	void release();

	void testSend();
	void testSendArgs(wchar_t*);

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsg;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsg;

	std::shared_ptr<NOM> testObjNOM;
	NTimer* nTimer;

	std::vector<tstring> weapons;

	NLineTstream ntcout { Level::COUT };
	NLineTstream ntcerr{ Level::CERR };
	
};

