#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <map>

#include "AirThreat.h"

using namespace nframework;
using namespace nom;
using namespace nlinestream;

class BASEMGRDLL_API ATSManager : public BaseManager
{
public:
	ATSManager(void);
	~ATSManager(void);

	/**
 * @brief 두 좌표 사이의 거리를 계산합니다.
 */
	double distance(const std::pair<double, double>& p1, const std::pair<double, double>& p2) {
		return std::sqrt(std::pow(p2.first - p1.first, 2) + std::pow(p2.second - p1.second, 2));
	}

	/**
	 * @brief Catmull-Rom 스플라인 보간 함수
	 * @param p0, p1, p2, p3: 제어점 (p1과 p2 사이를 보간)
	 * @param t: 보간 매개변수 (0.0에서 1.0 사이)
	 * @return 보간된 좌표
	 */
	std::pair<double, double> interpolate_catmull_rom(
		const std::pair<double, double>& p0,
		const std::pair<double, double>& p1,
		const std::pair<double, double>& p2,
		const std::pair<double, double>& p3,
		double t)
	{
		double t2 = t * t;
		double t3 = t2 * t;

		// Catmull-Rom 기저 함수 (Tension=0.0)
		double b1 = 0.5 * (-t3 + 2.0 * t2 - t);
		double b2 = 0.5 * (3.0 * t3 - 5.0 * t2 + 2.0);
		double b3 = 0.5 * (-3.0 * t3 + 4.0 * t2 + t);
		double b4 = 0.5 * (t3 - t2);

		std::pair<double, double> p;
		p.first = p0.first * b1 + p1.first * b2 + p2.first * b3 + p3.first * b4;
		p.second = p0.second * b1 + p1.second * b2 + p2.second * b3 + p3.second * b4;
		return p;
	}

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

	// 자체적으로 필요한거
	std::vector<std::pair<double, double>> points;
	virtual void pointParser(std::shared_ptr<NOM>);
	void interpolation(const std::vector<std::pair<double, double>>& keyPoints);
	virtual AirThreat* createAT();
	virtual void deleteAT();

	// 테스트 및 확인용
	const std::vector<std::map<double, std::pair<double, double>>>& getTimeTable() const {
		return timetable;
	}

	virtual void sendATInfo();
	virtual void recvDetonation();

	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> msgFuncMap;
	std::function<void(std::shared_ptr<NOM>)> msgProc;

	AirThreat* AirThreat_ptr;

private:
	void initialize();
	void release();

	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;

	NTimer* nTimer;
	int timerHandle;

	std::shared_ptr<NOM> atsNOM;

	NLineTstream ntcout{ Level::COUT };

	// 시간표: 경로별 시간-위치 데이터
	// std::vector<std::map<double(시간), std::pair<double, double>(x, y)>>
	std::vector<std::map<double, std::pair<double, double>>> timetable;

	// 경로를 파일로 저장 (full_path_for_plot.csv)
	void saveFullPath(const std::vector<std::pair<double, double>>& path) const {
		std::ofstream fullPathFile("full_path_for_plot.csv");
		if (!fullPathFile.is_open()) {
			std::cerr << "데이터 파일을 열 수 없습니다: full_path_for_plot.csv" << std::endl;
			return;
		}
		fullPathFile << std::fixed << std::setprecision(4);
		fullPathFile << "X,Y\n";
		for (const auto& p : path) {
			fullPathFile << p.first << "," << p.second << "\n";
		}
		fullPathFile.close();
		std::cout << "전체 항로 데이터 파일 저장 완료: full_path_for_plot.csv\n";
	}

};