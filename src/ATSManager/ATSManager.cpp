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
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << "ATS_Initialized" << std::endl;
	// design by contract
	mec = new MECComponent;
	mec->setUser(this);

    funcMapInit();
}

void
ATSManager::release()
{
    nTimer->removeTask(timerHandle);
    deleteAT();
    currentSimTime = 0.0;
    AirThreat_ptr = nullptr;
	delete mec;
	mec = nullptr;
	meb = nullptr;
    initialize();
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

	return true;
}

bool
ATSManager::stop()
{
	bool result = true;

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
    points.clear();
    latlng.clear();
    step = 0;

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
    double totalFlightTime = 20.0;
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
    // 5. 폴리라인 인코딩 (transformedPath 사용)
    using Encoder = PolylineEncoder<5>; // 기본 정밀도 5 사용

    auto getLat = [](const std::pair<double, double>& p) { return p.first; };  // p.first = Lat
    auto getLon = [](const std::pair<double, double>& p) { return p.second; }; // p.second = Lon

    encodedPathString = Encoder::encode(
        path.cbegin(),
        path.cend(),
        getLat,
        getLon
    );

    std::cout << "\n\n\n\n" << encodedPathString << "\n\n\n\n" << std::endl;

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

// AirThreatManager::deleteAT() 함수: AirThreat::destroyInstance() 호출을 통해 객체를 삭제
void ATSManager::deleteAT()
{
	std::cout << "\n--- AirThreatManager::deleteAT() 호출 ---" << std::endl;
	AirThreat::destroyInstance();
}

void ATSManager::sendATInfo()
{
    // 1. 공중 위협 객체 업데이트
    if (AirThreat_ptr != nullptr && !flightTimeTable.empty()) { // <--- map이 비어있지 않은지 확인
        // 시간표 flightTimeTable를 직접 사용
        auto it = flightTimeTable.find(currentSimTime);

        if (it != flightTimeTable.end()) {
            // 현재 위치 (curPos)
            const auto& curPos = it->second;

            // 현재 속도 (curVel)를 계산
            std::pair<double, double> curVel = { 0.0, 0.0 };
            double nextTime = currentSimTime + 0.5;

            // flightTimeTable에서 바로 find
            auto nextIt = flightTimeTable.find(nextTime);

            if (nextIt != flightTimeTable.end()) {
                const auto& nextPos = nextIt->second;

                curVel.first = (nextPos.first - curPos.first) / 0.5;
                curVel.second = (nextPos.second - curPos.second) / 0.5;
            }

            AirThreat_ptr->updateValue(curPos, curVel);
            currentSimTime += 0.5;
        }
        else {
            // currentSimTime이 시간표의 끝을 초과한 경우
            // 객체는 최종 위치에 머무르며, 타이머를 해제하고 시뮬레이션을 종료할 수 있습니다.

            //ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << _T("경로 끝 도달. 타이머 해제.") << std::endl;
            // release();
        }
    }


    // 2. NOM 메시지 생성 및 전송
    atsNOM = meb->getNOMInstance(name, _T("InnerAirThreatInfoToComm"));

    // AirThreat 객체에서 현재 값(업데이트된 값)을 가져옵니다.
    auto [pos_pair, vel_pair, curState] = AirThreat_ptr->getValue();

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
    // 만약 상태가 격추라면 release (BaseManager의 stop, 타이머 해제 등 포함)
    if (curState == 1) {
        release();
    }
}

void ATSManager::recvDetonation(std::shared_ptr<NOM> nomMsg)
{
    auto [pos_pair, vel_pair, curState] = AirThreat_ptr->getValue();
    AirThreat_ptr->setValue(pos_pair, vel_pair, 1);
}
void ATSManager::recvInnerStartSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
    // 시뮬레이션 시작 시 시간 초기화
    currentSimTime = 0.0;

    AirThreat_ptr = ATSManager::createAT();
    sendATInfo_Periodic = std::bind(&ATSManager::sendATInfo, this);
    nTimer = &(NTimer::getInstance());

    printFlightTimeTable(flightTimeTable);

    // 500ms(0.5초) 주기로 sendATInfo 호출 시작
    timerHandle = nTimer->addPeriodicTask(500, sendATInfo_Periodic);
}
void ATSManager::recvInnerStopSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
    std::cout << "\n\n\n시뮬레이션 종료됨\n\n\n\n" << std::endl;
    release();
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
