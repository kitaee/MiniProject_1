#pragma once
#include <afxwin.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/BaseManager.h>
#include "UITrackHandler.h"
#include <nFramework/nLineStream/NLineStreamMain.h>

using namespace nframework;
using namespace nom;
using namespace nlinestream;

struct NOMInfo
{
	TCHAR MsgName[1024];
	unsigned int MsgID;
	unsigned int MsgInstanceID;
	int MsgLen;
};

class BASEMGRDLL_API NewRoleManager : public BaseManager
{
public:
	NewRoleManager(void);
	~NewRoleManager(void);

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
	tstring managerName;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsg;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsg;

	HWND winHandle;
	std::unique_ptr<UITrackHandler> uiTrackHandler;

	NLineTstream ntcout{ Level::COUT };

	// ※※※※ MEC가 가장 먼저 소멸되어야 함. ※※※※
	std::unique_ptr<MECComponent> mec;
};


