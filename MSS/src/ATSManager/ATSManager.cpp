// ATSManager.cpp
// 역할: 공중위협(Air Threat) 시뮬레이션 매니저.
//       시나리오(웨이포인트)를 수신하고, 시뮬레이션 시작 시 공중위협의
//       비행 경로를 보간하여 주기적으로 위치 정보를 송신한다.

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
    - initialize: MEC 생성, 이름 설정, 메시지-함수 바인딩 초기화
    - release   : 자원 해제 (MEC, MEB, 타이머, AirThreat 인스턴스)
************************************************************************/

void ATSManager::initialize(void)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

    // 이 매니저의 이름 설정 (MEB에서 메시지를 가져올 때 식별자로 사용)
    setUserName(_T("ATSManager"));

    // MEC(MECComponent) 생성 — nFramework에서 메시지 송수신을 담당하는 객체.
    // setUser(this): 이 ATSManager가 MEC의 사용자임을 등록.
    mec = new MECComponent;
    mec->setUser(this);

    // 수신 메시지 이름과 처리 함수를 바인딩한다.
    funcMapInit();
}

void ATSManager::release()
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

    // 실행 중인 타이머 정지
    stopSequence();

    delete mec;
    mec = nullptr;
    meb = nullptr;
}

/************************************************************************
    funcMapInit
    수신 메시지 이름 → 처리 함수를 msgFuncMap에 등록한다.
    recvMsg()에서 메시지 이름으로 이 맵을 조회하여 적절한 함수를 호출한다.
************************************************************************/

void ATSManager::funcMapInit()
{
    std::function<void(std::shared_ptr<NOM>)> msgProc;

    // InnerSendScenarioToModel: SimulationManager가 시나리오를 포워딩해준 메시지.
    // 웨이포인트(위도/경도)를 파싱하고 비행 경로를 생성한다.
    msgProc = std::bind(&ATSManager::pointParser, this, std::placeholders::_1);
    msgFuncMap.insert({ _T("InnerSendScenarioToModel"), msgProc });

    // InnerStartSimulationToModel: 시뮬레이션 시작 명령.
    // 타이머를 등록하여 sendATInfo()를 주기적으로 호출한다.
    msgProc = std::bind(&ATSManager::recvInnerStartSimulationToModel, this, std::placeholders::_1);
    msgFuncMap.insert({ _T("InnerStartSimulationToModel"), msgProc });

    // InnerStopSimulationToModel: 시뮬레이션 정지 명령.
    msgProc = std::bind(&ATSManager::recvInnerStopSimulationToModel, this, std::placeholders::_1);
    msgFuncMap.insert({ _T("InnerStopSimulationToModel"), msgProc });

    // InnerAirThreatDetonationToATM: 격추(Detonation) 이벤트.
    msgProc = std::bind(&ATSManager::recvDetonation, this, std::placeholders::_1);
    msgFuncMap.insert({ _T("InnerAirThreatDetonationToATM"), msgProc });
}

/************************************************************************
    BaseManager 인터페이스 구현
    nFramework가 호출하는 표준 메서드들이다.
    FooManager.cpp 패턴을 따른다.
************************************************************************/

std::shared_ptr<NOM>
ATSManager::registerMsg(tstring msgName)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;

    // mec를 통해 NOM 인스턴스를 등록하고 registeredMsgMap에 저장한다.
    std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
    registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
    return nomMsg;
}

void ATSManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
    discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void ATSManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
    mec->updateMsg(nomMsg);
}

void ATSManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
}

void ATSManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
    mec->deleteMsg(nomMsg);
    registeredMsgMap.erase(nomMsg->getInstanceID());
}

void ATSManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
    discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void ATSManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
    mec->sendMsg(nomMsg);
}

void ATSManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;

    // msgFuncMap에서 메시지 이름으로 핸들러를 찾아 호출한다.
    auto iter = msgFuncMap.find(nomMsg->getName());
    if (iter != msgFuncMap.end())
    {
        iter->second(nomMsg);
    }
}

void ATSManager::setUserName(tstring userName)
{
    name = userName;
}

tstring ATSManager::getUserName()
{
    return name;
}

void ATSManager::setData(void* data)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
}

bool ATSManager::start()
{
    IniHandler iniHandler;
    iniHandler.readIni(_T("ATSManager/ATSManager.ini"));

    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
    return true;
}

bool ATSManager::stop()
{
    stopSequence();
    return true;
}

void ATSManager::setMEBComponent(IMEBComponent* realMEB)
{
    meb = realMEB;
    mec->setMEB(meb);
}

/************************************************************************
    ATSManager 전용 메서드 구현
************************************************************************/

// pointParser: InnerSendScenarioToModel 수신 핸들러.
// 사전 설계된 시나리오 메시지에서 필요한 정보를 파싱하여 가져오는 예시  
void ATSManager::pointParser(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;

    // 기준 좌표(원점) 파싱 — NOM 필드 접근 방식: "구조체명.필드명"
    origin.first  = nomMsg->getValue(_T("Scenario.OriginLat"))->toDouble();
    origin.second = nomMsg->getValue(_T("Scenario.OriginLng"))->toDouble();

    ntcout << _T("[ATSManager] 원점 위도=") << origin.first
           << _T(", 경도=") << origin.second << std::endl;
    
    /* 코드는 단순 미완성 예시 일뿐, 팀별로 설계한대로 구현하기 */

}




// recvInnerStartSimulationToModel: 시뮬레이션 시작 명령 처리.
// AirThreat 인스턴스를 생성하고 NTimer를 통해 실질적으로 공중 위협 표적 좌표를 보내는 함수 sendATInfo()를 주기적으로 호출한다.
// *  코드는 단순 예시일뿐, 각 팀 별로 설계한대로 구현하기 
void ATSManager::recvInnerStartSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

    if (flightTimeTable.empty())
    {
        ntcout << _T("[ATSManager] 경고: 시나리오 배포 없이 시작 명령 수신. 무시합니다.") << std::endl;
        return;
    }

 
    // NTimer 싱글톤 획득 후 콜백 등록
    // sendATInfo_Periodic: void(void*) 형식의 타이머 콜백.
    // sendATInfo()는 인수가 없으므로 람다로 감싸서 형식 맞춤.
    nTimer = &(NTimer::getInstance());
    sendATInfo_Periodic = [this](void*) { this->sendATInfo(); };

    // addTimer(콜백, 주기_ms, 인수) → 타이머 핸들 반환
    // 100ms(10Hz)마다 sendATInfo() 호출
    timerHandle = nTimer->addPeriodicTask(500, sendATInfo_Periodic);
    ntcout << _T("[ATSManager] 시뮬레이션 시작 - 타이머 핸들: ") << timerHandle << std::endl;
}

// recvInnerStopSimulationToModel: 시뮬레이션 정지 명령 처리.
void ATSManager::recvInnerStopSimulationToModel(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
    stopSequence();
}

// recvDetonation: 격추(Detonation) 이벤트 처리.
// 미사일이 공중위협을 격추하면 nFramework가 이 이벤트를 전달한다.
void ATSManager::recvDetonation(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[") << _T(__FUNCTION__) << _T("] 공중위협 격추됨") << std::endl;
    stopSequence();
}

// sendATInfo: NTimer에 의해 주기적으로 호출된다.
// 현재 시뮬레이션 시간에 해당하는 공중위협의 위치/속도를 계산하여
// InnerAirThreatInfoToComm 메시지로 송신한다.
void ATSManager::sendATInfo()
{
    ntcout << _T("[ATSManager] 팀별 설계한 공중 위협 표적의 위치 좌표를 송신하는 로직 구현하기") << std::endl;

}

// stopSequence: 시뮬레이션 공통 정지 처리.
// 타이머 해제 및 AirThreat 인스턴스 삭제.
void ATSManager::stopSequence()
{
    ntcout << _T("[ATSManager] 시뮬레이션 정지") << std::endl;

    if (nTimer != nullptr && timerHandle != -1)
    {
        nTimer->removeTask(timerHandle);
        timerHandle = -1;
    }

    currentSimTime = 0.0;
    step = 0;
}


/************************************************************************
    DLL 진입점 (Export Function)
    nFramework가 DLL을 동적 로드할 때 이 함수들을 호출한다.
    createObject()  → ATSManager 인스턴스 생성
    deleteObject()  → ATSManager 인스턴스 소멸
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
