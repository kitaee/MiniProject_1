#pragma once
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/BaseManager.h>
#include <nFramework\nTimer\NTimer.h>

using namespace nframework;
using namespace nom;

class UITrackHandler
{
public:
	UITrackHandler(BaseManager*);
	~UITrackHandler();

	void addTime(void *arg);
	std::shared_ptr<NOM> discoverUITrack(std::shared_ptr<NOM>);
	std::shared_ptr<NOM> reflectUITrack(std::shared_ptr<NOM>);
	std::shared_ptr<NOM> removeUITrack(std::shared_ptr<NOM>);
	void startTimer();
	void stopTimer();

private:
	void initialize();
	void release();

	BaseManager* userMgr;
	NTimer* timer = nullptr;
	unsigned int time = 0;
	int taskHandler;

	std::map<unsigned int, std::shared_ptr<NOM>> registeredUIMsg;
};