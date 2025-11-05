#pragma once
#define _USE_MATH_DEFINES
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

#include "AirThreat.h"
#include "polylineencoder.h"

using namespace nframework;
using namespace nom;
using namespace nlinestream;
using namespace gepaf;

// WGS84 타원체 상수
const double WGS84_A = 6378137.0;        // 적도 반경 (meter)
const double WGS84_F = 1.0 / 298.257223563; // 역편평률
const double WGS84_E2 = 2.0 * WGS84_F - WGS84_F * WGS84_F; // 이심률 제곱

// 각도 <-> 라디안 변환 상수
const double DEG_TO_RAD = M_PI / 180.0;
const double RAD_TO_DEG = 180.0 / M_PI;

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

	AirThreat* AirThreat_ptr = nullptr;

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

	std::shared_ptr<NOM> atsNOM;

	NLineTstream ntcout{ Level::COUT };

	// 시간표: 경로별 시간-위치 데이터
	// std::map<double(시간), std::pair<double, double>(x, y)>
	std::map<double, std::pair<double, double>> flightTimeTable;

	// 파싱한 4개의 점이 저장될 위치
	std::vector<std::pair<double, double>> points;

	// 인코딩된 경로
	std::string encodedPathString;

	// 기준 위도 경도
	std::pair<double, double> origin;

	//
	std::vector<std::pair<double, double>> transformedPath;



	virtual void recvInnerStartSimulationToModel(std::shared_ptr<NOM>);
	virtual void recvInnerStopSimulationToModel(std::shared_ptr<NOM>);
	virtual void recvDetonation(std::shared_ptr<NOM>);
	virtual void sendATInfo();
	virtual void pointParser(std::shared_ptr<NOM>);
	virtual void interpolation(const std::vector<std::pair<double, double>>& keyPoints);
	virtual AirThreat* createAT();
	virtual void deleteAT();
};