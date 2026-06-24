#include "PurePursuitGuidanceModel.h"
#include <cmath>

MissileInfo
PurePursuitGuidanceModel::calculateNextState(
	const MissileInfo& currentMissile,
	const AirThreatInfo& airThreat)
{
	MissileInfo nextMissile = currentMissile;

	const float dx = airThreat.AirthreatXPos - currentMissile.missileXPos;
	const float dy = airThreat.AirthreatYPos - currentMissile.missileYPos;
	const float distance = std::sqrt((dx * dx) + (dy * dy));

	if (distance <= 0.0f)
	{
		nextMissile.currentDirectionX = 0.0f;
		nextMissile.currentDirectionY = 0.0f;
		return nextMissile;
	}

	nextMissile.currentDirectionX = dx / distance;
	nextMissile.currentDirectionY = dy / distance;
	nextMissile.missileXPos += nextMissile.currentDirectionX * nextMissile.missileVelocity;
	nextMissile.missileYPos += nextMissile.currentDirectionY * nextMissile.missileVelocity;

	return nextMissile;
}
