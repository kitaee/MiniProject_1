#pragma once
#include "Missile.h"


class IGuidanceModel
{
public:
	virtual ~IGuidanceModel() = default;

	virtual MissileInfo calculateNextState(
		const MissileInfo& currentMissile,
		const AirThreatInfo& airThreat
	) = 0;
};