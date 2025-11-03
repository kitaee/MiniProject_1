#pragma once
#include <nFramework/util/IniHandler.h>
#include "ATSManager.h"
#include <map>


/************************************************************************
	constructor / destructor
************************************************************************/
ATSManager::ATSManager(void)
{
	initialize();
}

ATSManager::~ATSManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
ATSManager::initialize(void)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;


	setUserName(_T("ATSManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);

	// 함수들 바인딩
	msgProc = std::bind(&ATSManager::pointParser, this, std::placeholders::_1);
	msgFuncMap.insert(std::make_pair(_T("SendScenario_ToATM"), msgProc));


    std::function <void(void*)> periodicFunc = std::bind(&ATSManager::sendATInfo, this);

    nTimer = &(NTimer::getInstance());
    timerHandle = nTimer->addPeriodicTask(500, periodicFunc);

}

void
ATSManager::release()
{
    nTimer->removeTask(timerHandle);
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
ATSManager::registerMsg(tstring msgName)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;


	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
ATSManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

}

void
ATSManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	mec->updateMsg(nomMsg);
}

void
ATSManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


}

void
ATSManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
ATSManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	discoveredMsgMap.erase(nomMsg->getInstanceID());

}

void
ATSManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	mec->sendMsg(nomMsg);
}

void
ATSManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;


	if (auto itr = msgFuncMap.find(nomMsg->getName()); itr != msgFuncMap.end()) {
		itr->second(nomMsg);
	}

}

void
ATSManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
ATSManager::getUserName()
{
	return name;
}

void
ATSManager::setData(void* data)
{

}

bool
ATSManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("ATSManager/ATSManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

    AirThreat_ptr = ATSManager::createAT();
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

	return true;
}

bool
ATSManager::stop()
{
	bool result = true;

    ATSManager::deleteAT();
	return result;
}

void
ATSManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void ATSManager::pointParser(std::shared_ptr<NOM> nomMsg)
{

}

/**
     * @brief Catmull-Rom 스플라인 보간을 사용하여 비행 경로를 계산하고,
     * 등속도 운동 시뮬레이션 결과를 timetable에 저장합니다.
     * @param keyPoints: 4개 이상의 키 포인트 (P0, P1, P2, ...)
     */
void ATSManager::interpolation(const std::vector<std::pair<double, double>>& keyPoints) {
    if (keyPoints.size() < 4) {
        std::cerr << "경로 보간을 위해 최소 4개의 키 포인트가 필요합니다." << std::endl;
        return;
    }

    const int segmentsPerInterval = 50;
    std::vector<std::pair<double, double>> path;
    size_t N = keyPoints.size();

    // 1. Catmull-Rom 스플라인을 이용한 경로 생성

    // P0 -> P1 구간 (시작점 처리)
    for (int i = 0; i <= segmentsPerInterval; ++i) {
        double t = (double)i / segmentsPerInterval;
        path.push_back(interpolate_catmull_rom(keyPoints[0], keyPoints[0], keyPoints[1], keyPoints[2], t));
    }

    // P1 -> P(N-2) 구간 (중간점 일반 처리)
    for (size_t i = 1; i < N - 2; ++i) {
        for (int j = 1; j <= segmentsPerInterval; ++j) {
            double t = (double)j / segmentsPerInterval;
            path.push_back(interpolate_catmull_rom(keyPoints[i - 1], keyPoints[i], keyPoints[i + 1], keyPoints[i + 2], t));
        }
    }

    // P(N-2) -> P(N-1) 구간 (끝점 처리)
    size_t i = N - 2;
    for (int j = 1; j <= segmentsPerInterval; ++j) {
        double t = (double)j / segmentsPerInterval;
        path.push_back(interpolate_catmull_rom(keyPoints[i - 1], keyPoints[i], keyPoints[i + 1], keyPoints[i + 1], t));
    }

    if (path.empty()) return;

    // 2. 전체 경로 길이 계산 및 누적 거리 계산
    std::vector<double> cumulativeDistances;
    cumulativeDistances.push_back(0.0);
    double totalDistance = 0.0;
    for (size_t k = 1; k < path.size(); ++k) {
        double dist = distance(path[k - 1], path[k]);
        totalDistance += dist;
        cumulativeDistances.push_back(totalDistance);
    }

    // 3. 등속도 운동 시뮬레이션 및 timetable 저장

    double totalFlightTime = 20.0;
    double speed = totalDistance / totalFlightTime;
    const double timeStep = 0.5;
    double currentTime = 0.0;
    std::map<double, std::pair<double, double>> currentFlightTimeTable;

    while (currentTime <= totalFlightTime + 1e-6) {
        double distanceTraveled = speed * currentTime;

        // 이동 거리에 해당하는 경로상의 위치 찾기
        auto it = std::lower_bound(cumulativeDistances.begin(), cumulativeDistances.end(), distanceTraveled);

        size_t nextIndex = std::distance(cumulativeDistances.begin(), it);
        size_t prevIndex = nextIndex > 0 ? nextIndex - 1 : 0;

        std::pair<double, double> currentPos;
        if (nextIndex >= cumulativeDistances.size()) {
            currentPos = path.back(); // 마지막 점에 도달
        }
        else {
            double distPrev = cumulativeDistances[prevIndex];
            double distNext = cumulativeDistances[nextIndex];
            double segmentDistance = distNext - distPrev;

            if (segmentDistance < 1e-6) {
                currentPos = path[prevIndex];
            }
            else {
                // 선형 보간을 통해 정확한 현재 좌표 계산
                double ratio = (distanceTraveled - distPrev) / segmentDistance;
                currentPos.first = path[prevIndex].first + ratio * (path[nextIndex].first - path[prevIndex].first);
                currentPos.second = path[prevIndex].second + ratio * (path[nextIndex].second - path[prevIndex].second);
            }
        }

        // timetable에 저장: map<시간, (X, Y)>
        currentFlightTimeTable[currentTime] = currentPos;

        currentTime += timeStep;
    }

    // 결과 TimeMap을 ATSManager의 timetable 멤버에 추가
    timetable.push_back(currentFlightTimeTable);
    std::cout << "시뮬레이션 결과가 ATSManager::timetable에 저장되었습니다 (총 이동 거리: "
        << std::fixed << std::setprecision(2) << totalDistance << ", 예상 비행 시간: " << totalFlightTime << "초)\n";

    // 4. 전체 경로점 데이터 파일 저장 유지
    saveFullPath(path);

    // 5. key_points.csv 파일 저장
    std::ofstream keyPointsFile("key_points.csv");
    if (keyPointsFile.is_open()) {
        keyPointsFile << "X,Y\n";
        for (const auto& p : keyPoints) {
            keyPointsFile << p.first << "," << p.second << "\n";
        }
        keyPointsFile.close();
        std::cout << "키 포인트 데이터 파일 저장 완료: key_points.csv\n";
    }
}

AirThreat* ATSManager::createAT()
{
	std::cout << "\n--- AirThreatManager::createAT() 호출 ---" << std::endl;
	return AirThreat::getInstance();
}

// AirThreatManager::deleteAT() 함수: AirThreat::destroyInstance() 호출을 통해 객체를 삭제
void ATSManager::deleteAT()
{
	std::cout << "\n--- AirThreatManager::deleteAT() 호출 ---" << std::endl;
	AirThreat::destroyInstance();
}

void ATSManager::sendATInfo()
{
    atsNOM = meb->getNOMInstance(name, _T("AirThreatInfo_ToComm"));
    unsigned short msgID = 0x41;
    NUShort value(msgID);
    atsNOM->setValue(_T("Header.MessageID"), &value);

    sendMsg(atsNOM);
}

void ATSManager::recvDetonation()
{

}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new ATSManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
