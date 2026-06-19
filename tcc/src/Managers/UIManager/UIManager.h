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

class BASEMGRDLL_API UIManager : public BaseManager
{
public:
	UIManager(void);
	~UIManager(void) override;

	std::shared_ptr<NOM> registerMsg(tstring) override;
	void discoverMsg(std::shared_ptr<NOM>) override;
	void updateMsg(std::shared_ptr<NOM>) override;
	void reflectMsg(std::shared_ptr<NOM>) override;
	void deleteMsg(std::shared_ptr<NOM>) override;
	void removeMsg(std::shared_ptr<NOM>) override;
	void sendMsg(std::shared_ptr<NOM>) override;
	void recvMsg(std::shared_ptr<NOM>) override;
	void setUserName(tstring) override;
	tstring getUserName() override;
	void setData(void*) override;
	bool start() override;
	bool stop() override;
	void setMEBComponent(IMEBComponent*) override;

private:
	void initialize();
	void release();

	IMEBComponent* meb{ nullptr };
	tstring managerName;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsg;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsg;

	HWND winHandle{ nullptr };
	std::unique_ptr<UITrackHandler> uiTrackHandler;

	NLineTstream ntcout{ Level::COUT };

	std::unique_ptr<MECComponent> mec;
};
