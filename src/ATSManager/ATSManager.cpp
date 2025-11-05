#pragma once
#include <nFramework/util/IniHandler.h>
#include "ATSManager.h"
#include <nFramework/util/util.h>
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
    ntcout << "ATS_Initialized" << std::endl;

	mec = new MECComponent;
	mec->setUser(this);

    funcMapInit();

}

void
ATSManager::release()
{
    
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
	iniHandler.readIni(_T("ATSManager/ATSManager.ini"));

	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

	return true;
}

bool
ATSManager::stop()
{
	bool result = true;
    nTimer->removeTask(timerHandle);
    deleteAT();
    delete mec;
    mec = nullptr;
    meb = nullptr;
    
    initialize();
	return result;
}

void
ATSManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void ATSManager::funcMapInit()
{
    std::function<void(std::shared_ptr<NOM>)> msgProc;

    msgProc = bind(&ATSManager::pointParser, this, std::placeholders::_1);
    msgFuncMap.insert({ _T("InnerSendScenarioToModel"), msgProc });

    msgProc = bind(&ATSManager::recvInnerStartSimulationToModel, this, std::placeholders::_1);
    msgFuncMap.insert({ _T("InnerStartSimulationToModel"), msgProc });

    msgProc = bind(&ATSManager::recvInnerStopSimulationToModel, this, std::placeholders::_1);
    msgFuncMap.insert({ _T("InnerStopSimulationToModel"), msgProc });

    msgProc = bind(&ATSManager::recvDetonation, this, std::placeholders::_1);
    msgFuncMap.insert({ _T("InnerAirThreatDetonationToATM"), msgProc });
}

void ATSManager::pointParser(std::shared_ptr<NOM> nomMsg)
{
    // 초기화 프로세스
    flightTimeTable.clear();
    encodedPathString.clear();
    deleteAT();
    points.clear();
    latlng.clear();
    step = 0;
    currentSimTime = 0.0;
    lastVelocity = { 0.0, 0.0 };

    // 기준 위도 경도 수신
    origin.first = nomMsg->getValue(_T("Scenario.OriginLat"))->toDouble();
    origin.second = nomMsg->getValue(_T("Scenario.OriginLng"))->toDouble();

    // WayPoint 0 추가
    double x0 = nomMsg->getValue(_T("Scenario.WayPoint0_X"))->toDouble();
    double y0 = nomMsg->getValue(_T("Scenario.WayPoint0_Y"))->toDouble();
    points.emplace_back(x0, y0);

    // WayPoint 1 추가
    double x1 = nomMsg->getValue(_T("Scenario.WayPoint1_X"))->toDouble();
    double y1 = nomMsg->getValue(_T("Scenario.WayPoint1_Y"))->toDouble();
    points.emplace_back(x1, y1);

    // WayPoint 2 추가
    double x2 = nomMsg->getValue(_T("Scenario.WayPoint2_X"))->toDouble();
    double y2 = nomMsg->getValue(_T("Scenario.WayPoint2_Y"))->toDouble();
    points.emplace_back(x2, y2);

    // WayPoint 3 추가
    double x3 = nomMsg->getValue(_T("Scenario.WayPoint3_X"))->toDouble();
    double y3 = nomMsg->getValue(_T("Scenario.WayPoint3_Y"))->toDouble();
    points.emplace_back(x3, y3);

    // WayPoint 0 위경도 추가
    double lat0 = nomMsg->getValue(_T("Scenario.WayPoint0_Lat"))->toDouble();
    double lng0 = nomMsg->getValue(_T("Scenario.WayPoint0_Lng"))->toDouble();
    latlng.emplace_back(lat0, lng0);

    // WayPoint 1 위경도 추가
    double lat1 = nomMsg->getValue(_T("Scenario.WayPoint1_Lat"))->toDouble();
    double lng1 = nomMsg->getValue(_T("Scenario.WayPoint1_Lng"))->toDouble();
    latlng.emplace_back(lat1, lng1);

    // WayPoint 2 위경도 추가
    double lat2 = nomMsg->getValue(_T("Scenario.WayPoint2_Lat"))->toDouble();
    double lng2 = nomMsg->getValue(_T("Scenario.WayPoint2_Lng"))->toDouble();
    latlng.emplace_back(lat2, lng2);

    // WayPoint 3 위경도 추가
    double lat3 = nomMsg->getValue(_T("Scenario.WayPoint3_Lat"))->toDouble();
    double lng3 = nomMsg->getValue(_T("Scenario.WayPoint3_Lng"))->toDouble();
    latlng.emplace_back(lat3, lng3);

    interpolation(latlng);
    step = 1;
    flightTimeTable.clear();
    interpolation(points);
}

double distance(const std::pair<double, double>& p1, const std::pair<double, double>& p2) {
		return std::sqrt(std::pow(p2.first - p1.first, 2) + std::pow(p2.second - p1.second, 2));
}

std::pair<double, double> interpolate_catmull_rom(const std::pair<double, double>& p0, const std::pair<double, double>& p1, const std::pair<double, double>& p2, const std::pair<double, double>& p3, double t)
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

void ATSManager::interpolation(const std::vector<std::pair<double, double>>& keyPoints) {

    // 기존 데이터 초기화
    const int segmentsPerInterval = 50;
    std::vector<std::pair<double, double>> path;
    size_t N = keyPoints.size();

    // 1. Catmull-Rom 스플라인을 이용한 상대 좌표 경로 생성 (기존 로직 유지)

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

    if (path.empty()) return ;

    if (step == 0) {
        encodedLatLng(path);
        return;
    }

    // 2. 전체 경로 길이 계산 및 누적 거리 계산 (path를 사용하여 거리 계산)
    std::vector<double> cumulativeDistances;
    cumulativeDistances.push_back(0.0);
    double totalDistance = 0.0;
    for (size_t k = 1; k < path.size(); ++k) {
        double dist = distance(path[k - 1], path[k]);
        totalDistance += dist;
        cumulativeDistances.push_back(totalDistance);
    }

    // 3. 등속력 운동 시뮬레이션 및 flightTimeTable 저장 (X, Y 상대좌표를 저장)
    double totalFlightTime = 60.0;
    double speed = totalDistance / totalFlightTime;
    const double timeStep = 0.5;
    double currentTime = 0.0;

    while (currentTime <= totalFlightTime + 1e-6) {
        double distanceTraveled = speed * currentTime;

        // 이동 거리에 해당하는 경로상의 위치 찾기
        auto it = std::lower_bound(cumulativeDistances.begin(), cumulativeDistances.end(), distanceTraveled);

        size_t nextIndex = std::distance(cumulativeDistances.begin(), it);
        size_t prevIndex = nextIndex > 0 ? nextIndex - 1 : 0;

        std::pair<double, double> currentPos; // (X, Y) 상대 좌표
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
                // 선형 보간을 통해 정확한 현재 좌표 (X, Y) 계산
                double ratio = (distanceTraveled - distPrev) / segmentDistance;
                currentPos.first = path[prevIndex].first + ratio * (path[nextIndex].first - path[prevIndex].first);
                currentPos.second = path[prevIndex].second + ratio * (path[nextIndex].second - path[prevIndex].second);
            }
        }

        // flightTimeTable 멤버 변수에 직접 저장: map<시간, (X, Y)>
        flightTimeTable[currentTime] = currentPos;

        currentTime += timeStep;

        
    }

    std::cout << "시뮬레이션 결과가 ATSManager::flightTimeTable에 저장되었습니다 (총 이동 거리: "
        << std::fixed << std::setprecision(2) << totalDistance << ", 예상 비행 시간: " << totalFlightTime << "초)\n";
}

void ATSManager::encodedLatLng(std::vector<std::pair<double, double>> path)
{
    using Encoder = PolylineEncoder<5>; // 기본 정밀도 5 사용

    auto getLat = [](const std::pair<double, double>& p) { return p.first; };  // p.first = Lat
    auto getLon = [](const std::pair<double, double>& p) { return p.second; }; // p.second = Lon

    encodedPathString = Encoder::encode(
        path.cbegin(),
        path.cend(),
        getLat,
        getLon
    );

    std::cout << "\n\nPolyLine Encoded Path:\n" << encodedPathString << std::endl;

    atsNOM = meb->getNOMInstance(name, _T("InnerRouteToComm"));
    NString route(util::string2tstring(encodedPathString));
    atsNOM->setValue(_T("RouteAT"), &route);
    mec->sendMsg(atsNOM);
}

AirThreat* ATSManager::createAT()
{
	std::cout << "\n--- AirThreatManager::createAT() 호출 ---" << std::endl;
	return AirThreat::getInstance();
}

void ATSManager::deleteAT()
{
	std::cout << "\n--- AirThreatManager::deleteAT() 호출 ---" << std::endl;
	AirThreat::destroyInstance();
}

void ATSManager::sendATInfo()
{
    std::pair<double, double> p_pair;
    std::pair<double, double> v_pair;
    double cState;
    if (AirThreat_ptr != nullptr) {
        std::tie(p_pair, v_pair, cState) = AirThreat_ptr->getValue();
    }
    // 발사대로부터 3000Km 이상 벗어나면
    if (p_pair.first >= -3000000 &&  p_pair.first <= 3000000 && p_pair.second >= -3000000 && p_pair.second <= 3000000 && cState != 1) {
        // 1. 공중 위협 객체 업데이트
        if (AirThreat_ptr != nullptr && !flightTimeTable.empty()) {

            // 1.1 시간표 탐색 및 현재 위치/속도 계산
            std::pair<double, double> curPos = { 0.0, 0.0 };
            std::pair<double, double> curVel = { 0.0, 0.0 };
            //bool isTableTraversed = false; // 이 플래그 대신 시간표 탐색 성공 여부로 판단

            auto it = flightTimeTable.find(currentSimTime);
            const double timeStep = 0.5; // 시간 간격

            if (it != flightTimeTable.end()) {
                // **A. 시간표 탐색 성공 (경로 이동 중)**

                // 현재 위치 (curPos)는 시간표에서 가져옴
                curPos = it->second;

                // 다음 시간 계산 및 탐색
                double nextTime = currentSimTime + timeStep;
                auto nextIt = flightTimeTable.find(nextTime);

                if (nextIt != flightTimeTable.end()) {
                    // 다음 위치가 시간표에 있을 경우: 속도 계산
                    const auto& nextPos = nextIt->second;

                    curVel.first = (nextPos.first - curPos.first) / timeStep;
                    curVel.second = (nextPos.second - curPos.second) / timeStep;

                    // 마지막 속도 저장 (경로가 끝난 후 직진에 사용)
                    lastVelocity = curVel;

                }
                else {
                    // 현재 시간이 시간표의 마지막 엔트리일 경우: 마지막 속도를 사용
                    curVel = lastVelocity;
                }

                // 시뮬레이션 시간 증가
                currentSimTime += timeStep;
            }
            else {
                // **B. 시간표 탐색 실패 (경로 이동 완료, 직진 운동 시작/유지)**

                // 직전 프레임의 위치와 마지막 계산된 속도(lastVelocity)를 이용
                curVel = lastVelocity; // 마지막 속도를 유지

                // 새 위치 = 이전 위치 + (마지막 속도 * 시간 간격)
                std::pair<double, double> pos_pair;
                std::pair<double, double> vel_pair;
                double curState;
                if (AirThreat_ptr != nullptr) {
                    std::tie(pos_pair, vel_pair, curState) = AirThreat_ptr->getValue();
                }
                curPos = pos_pair; // 직전 업데이트 위치를 가져옴
                curPos.first += curVel.first * timeStep;
                curPos.second += curVel.second * timeStep;

                // 시뮬레이션 시간도 계속 증가
                currentSimTime += timeStep;
            }

            // 1.2 AirThreat 객체 업데이트
            AirThreat_ptr->updateValue(curPos, curVel);
        }
    }
    
    // 2. NOM 메시지 생성 및 전송
    atsNOM = meb->getNOMInstance(name, _T("InnerAirThreatInfoToComm"));

    // AirThreat 객체에서 현재 값(업데이트된 값)을 가져옵니다.
    std::pair<double, double> pos_pair;
    std::pair<double, double> vel_pair;
    double curState;
    if (AirThreat_ptr != nullptr) {
        std::tie(pos_pair, vel_pair, curState) = AirThreat_ptr->getValue();
    }

    // ObjectID는 예시로 1을 사용하거나, AirThreat 객체 내부에 ID가 있다면 사용
    NUShort objectID(10200);
    atsNOM->setValue(_T("AirThreatInfo.ObjectID"), &objectID);

    // ObjectState 설정
    NUShort stateValue(curState);
    atsNOM->setValue(_T("AirThreatInfo.ObjectState"), &stateValue);

    // Position X, Y 설정
    NDouble posXValue(pos_pair.first);
    atsNOM->setValue(_T("AirThreatInfo.PositionX"), &posXValue);

    NDouble posYValue(pos_pair.second);
    atsNOM->setValue(_T("AirThreatInfo.PositionY"), &posYValue);

    // Velocity X, Y 설정
    NDouble velXValue(vel_pair.first);
    atsNOM->setValue(_T("AirThreatInfo.VelocityX"), &velXValue);

    NDouble velYValue(vel_pair.second);
    atsNOM->setValue(_T("AirThreatInfo.VelocityY"), &velYValue);

    mec->sendMsg(atsNOM);

    // 3. 상태 확인 및 종료
    if (curState == 1) {
        deleteAT();
        nTimer->removeTask(timerHandle);
    }
}

void ATSManager::recvDetonation(std::shared_ptr<NOM> nomMsg)
{
    std::pair<double, double> p_pair;
    std::pair<double, double> v_pair;
    double cState;
    if (AirThreat_ptr != nullptr) {
        std::tie(p_pair, v_pair, cState) = AirThreat_ptr->getValue();
        AirThreat_ptr->setValue(p_pair, v_pair, 1);
    }
    //std::cout << "\n\n\n\n격추됨\n\n\n\n" << std::endl;
}

void ATSManager::recvInnerStartSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
    nTimer = &(NTimer::getInstance());
    // 시뮬레이션 시작 시 시간 초기화
    currentSimTime = 0.0;

    AirThreat_ptr = ATSManager::createAT();
    sendATInfo_Periodic = std::bind(&ATSManager::sendATInfo, this);

    /*printFlightTimeTable(flightTimeTable);*/

    // 500ms(0.5초) 주기로 sendATInfo 호출 시작
    timerHandle = nTimer->addPeriodicTask(500, sendATInfo_Periodic);
}

void ATSManager::recvInnerStopSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
    std::cout << "\n\n\n시뮬레이션 종료됨\n\n\n\n" << std::endl;
    deleteAT();
    nTimer->removeTask(timerHandle);
    flightTimeTable.clear();
    encodedPathString.clear();
    points.clear();
    latlng.clear();
    step = 0;
    currentSimTime = 0.0;
    lastVelocity = { 0.0, 0.0 };
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
