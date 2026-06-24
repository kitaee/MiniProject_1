#pragma once
#include "IGuidanceModel.h"
class PurePursuitGuidanceModel : public IGuidanceModel
{
public:
	MissileInfo calculateNextState(
		const MissileInfo& currentMissile,
		const AirThreatInfo& airThreat
	) override;
};
