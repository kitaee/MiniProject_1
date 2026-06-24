#pragma once
#include <iostream>
#include <map>
#include <utility>
#include <tuple>

class AirThreat
{
private:
    static AirThreat* instance;

    std::pair<double, double> pos;
    std::pair<double, double> vel;
    unsigned short state;

    AirThreat();

public:
    ~AirThreat();

    static AirThreat* getInstance();
    static void destroyInstance();

    virtual void setValue(std::pair<double, double> newPos, std::pair<double, double> newVel, unsigned short newState);

    virtual std::tuple<std::pair<double, double>, std::pair<double, double>, unsigned short> getValue();

    virtual void updateValue(const std::pair<double, double>& newPos, const std::pair<double, double>& newVel);
};