#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

#include "polylineencoder.h"

using namespace nframework;
using namespace nom;
using namespace nlinestream;
using namespace gepaf;

class BASEMGRDLL_API ATSManager : public BaseManager
{
public:
	ATSManager(void);
	~ATSManager(void);

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

	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> msgFuncMap;
	std::function<void(std::shared_ptr<NOM>)> msgProc;


private:
	void initialize();
	void release();
	void funcMapInit();

	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;  
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;

	// 시뮬레이션 현재 시간 (초)
	double currentSimTime = 0.0;

	NTimer* nTimer;
	int timerHandle;
	std::function <void(void*)> sendATInfo_Periodic; 

	std::shared_ptr<NOM> atsNOM; // 주기적으로 공중위협 정보를 넘길 메시지 

	NLineTstream ntcout{ Level::COUT };

	// 아래 자료형은 참고만하기. 팀별 설계한 내용으로 재구현 요망 

	// std::map<double(시간), std::pair<double, double>(x, y)>
	std::map<double, std::pair<double, double>> flightTimeTable;

	// 파싱한 4개의 점이 저장될 위치
	std::vector<std::pair<double, double>> points;

	// 기준 위도 경도
	std::pair<double, double> origin;

	// 위도 경도 파싱점
	std::vector<std::pair<double, double>> latlng;

	int step = 0;

	std::pair<double, double> lastVelocity = { 0.0, 0.0 };

	virtual void recvInnerStartSimulationToModel(std::shared_ptr<NOM>);
	virtual void recvInnerStopSimulationToModel(std::shared_ptr<NOM>);
	virtual void recvDetonation(std::shared_ptr<NOM>);
	virtual void sendATInfo();
	virtual void pointParser(std::shared_ptr<NOM>);
	virtual void stopSequence();


};