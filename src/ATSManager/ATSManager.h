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

#include "AirThreat.h"
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

	// 기준 위도 경도
	std::pair<double, double> origin;

	// 위도 경도 파싱점
	std::vector<std::pair<double, double>> latlng;

	// 인코딩된 경로
	std::string encodedPathString;

	int step = 0;

	std::pair<double, double> lastVelocity = { 0.0, 0.0 };

	virtual void recvInnerStartSimulationToModel(std::shared_ptr<NOM>);
	virtual void recvInnerStopSimulationToModel(std::shared_ptr<NOM>);
	virtual void recvDetonation(std::shared_ptr<NOM>);
	virtual void sendATInfo();
	virtual void pointParser(std::shared_ptr<NOM>);
	virtual void interpolation(const std::vector<std::pair<double, double>>& keyPoints);
	virtual AirThreat* createAT();
	virtual void deleteAT();
	virtual void encodedLatLng(std::vector<std::pair<double, double>>);

	//void printFlightTimeTable(const std::map<double, std::pair<double, double>>& flightTimeTable) {
	//	// Check if the map is empty
	//	if (flightTimeTable.empty()) {
	//		std::cout << "The flight time table is empty." << std::endl;
	//		return;
	//	}

	//	std::cout << "--- Flight Time Table Contents ---" << std::endl;

	//	// Iterate through the map using a range-based for loop
	//	for (const auto& entry : flightTimeTable) {
	//		// 'entry.first' is the key (double)
	//		// 'entry.second' is the value (std::pair<double, double>)

	//		double key = entry.first;
	//		double first_pair_value = entry.second.first;
	//		double second_pair_value = entry.second.second;

	//		std::cout << "Key: " << key
	//			<< ": Value: (" << first_pair_value
	//			<< ", " << second_pair_value << ")" << std::endl;
	//	}
	//	std::cout << "--------------------------------" << std::endl;
	//}
};