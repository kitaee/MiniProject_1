#pragma once
#include <iostream>
#include <map>
#include <utility> 

class AirThreat
{
private:
    // 1. 유일한 인스턴스를 저장할 정적 포인터
    static AirThreat* instance;

    std::pair<double, double> pos;
    double vel;
    unsigned short state;

    // 2. private 생성자: 외부에서의 직접 생성을 방지
    AirThreat();

public:
    ~AirThreat();

    // 3. 유일한 인스턴스를 얻는 정적 메서드 (생성 역할)
    static AirThreat* getInstance();

    // 4. 인스턴스를 삭제하고, 재생성을 가능하게 하는 정적 메서드
    static void destroyInstance();

    virtual void setValue(std::pair<double, double> newPos, double newVel, unsigned short newState);
    virtual std::pair<std::pair<double, double>, std::pair<double, unsigned short>> getValue();
    virtual void updateValue();
};