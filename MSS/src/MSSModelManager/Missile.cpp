#include "Missile.h"
#include "IGuidanceModel.h"
#include <cmath>

Missile::Missile(std::unique_ptr<IGuidanceModel> guidanceModel)
	: missileState{ 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	  airThreatState{ 0, 0.0f, 0.0f, 0.0f },
	  guidanceModel(std::move(guidanceModel))
{
}

void
Missile::setVelocity(float velocity)
{
	missileState.missileVelocity = velocity;
}

void
Missile::resetSimulation()
{
	const float velocity = missileState.missileVelocity;

	missileState = {
		0,
		0.0f,
		0.0f,
		velocity,
		0.0f,
		0.0f
	};

	airThreatState = {
		0,
		0.0f,
		0.0f,
		0.0f
	};
}

const MissileInfo&
Missile::getMissileInfo() const
{
	return missileState;
}

void
Missile::launch(uint32_t missileID, float missileXPos, float missileYPos, const AirThreatInfo& airThreat)
{
	missileState.missileID = missileID;
	missileState.missileXPos = missileXPos;
	missileState.missileYPos = missileYPos;
	airThreatState = airThreat;

	const float dx = airThreatState.AirthreatXPos - missileState.missileXPos;
	const float dy = airThreatState.AirthreatYPos - missileState.missileYPos;
	const float distance = std::sqrt((dx * dx) + (dy * dy));

	if (distance > 0.0f)
	{
		missileState.currentDirectionX = dx / distance;
		missileState.currentDirectionY = dy / distance;
	}
	else
	{
		missileState.currentDirectionX = 0.0f;
		missileState.currentDirectionY = 0.0f;
	}
}

void
Missile::updatePosition(const AirThreatInfo& airThreat)
{
	airThreatState = airThreat;

	if (guidanceModel)
	{
		missileState = guidanceModel->calculateNextState(missileState, airThreatState);
	}
}

bool
Missile::isDetonated()
{
	return checkDistance() < 0.0045f;
}

float
Missile::checkDistance()
{
	const float dx = missileState.missileXPos - airThreatState.AirthreatXPos;
	const float dy = missileState.missileYPos - airThreatState.AirthreatYPos;

	return std::sqrt((dx * dx) + (dy * dy));
}
