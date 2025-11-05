#include "AirThreat.h"

// 정적 멤버 변수 초기화
AirThreat* AirThreat::instance ;

// private 생성자 구현
AirThreat::AirThreat() : pos({ 0.0, 0.0 }), vel({ 0.0, 0.0 }), state(0)
{
    std::cout << "[생성] AirThreat 객체가 생성되었습니다." << std::endl;
}

// public 소멸자 구현
AirThreat::~AirThreat()
{
    std::cout << "[소멸] AirThreat 객체가 소멸되었습니다." << std::endl;
}

// 유일한 인스턴스를 반환하는 정적 메서드 구현
AirThreat* AirThreat::getInstance()
{
    if (instance == nullptr) {
        // 포인터가 nullptr이면 (아직 없거나, 삭제되었다면) 새로 생성
        instance = new AirThreat();
    }
    return instance;
}

// 명시적으로 인스턴스를 삭제하고 포인터를 nullptr로 초기화하는 함수
void AirThreat::destroyInstance()
{
    if (instance != nullptr) {
        std::cout << "[해제] AirThreat 인스턴스를 삭제합니다." << std::endl;
        delete instance;
        instance = nullptr; // 이 부분이 재생성을 허용하는 핵심입니다.
        std::cout << "[상태] AirThreat 인스턴스가 nullptr로 초기화되어 재생성이 가능합니다." << std::endl;
    }
}

void AirThreat::setValue(std::pair<double, double> newPos, std::pair<double, double> newVel, unsigned short newState)
{
    this->pos = newPos;
    this->vel = newVel;
    this->state = newState;
}

std::tuple<std::pair<double, double>, std::pair<double, double>, unsigned short> AirThreat::getValue()
{
    // { {pos.x, pos.y}, {vel, state} } 형태의 중첩된 pair를 반환
    return { this->pos, this->vel, this->state };
}

void AirThreat::updateValue(const std::pair<double, double>& newPos, const std::pair<double, double>& newVel)
{
    this->pos = newPos;
    this->vel = newVel;
}