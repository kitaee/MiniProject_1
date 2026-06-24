#pragma once
#include <cstdint>
#include <memory>

class IGuidanceModel;

enum class MissileState
{
	Uninitialized,
	Ready,
	Launched,
	Detonated
};


struct AirThreatInfo
{
	uint32_t airthreatID;
	float AirthreatXPos;
	float AirthreatYPos;
	float Airthreatvelocity;
};

struct MissileInfo
{
	uint32_t missileID;
	float missileXPos;
	float missileYPos;
	float missileVelocity;
	float currentDirectionX;
	float currentDirectionY;
};

class Missile
{
private:
	MissileInfo missileState;
	AirThreatInfo airThreatState;
	
	std::unique_ptr<IGuidanceModel> guidanceModel;
public:
	explicit Missile(std::unique_ptr<IGuidanceModel> guidanceModel);
	void setVelocity(float velocity);
	void resetSimulation();
	void launch(uint32_t missileID, float missileXPos, float missileYPos,
		const AirThreatInfo& airThreat);
	const MissileInfo& getMissileInfo() const;
public:
	void updatePosition(const AirThreatInfo& airThreat);
	bool isDetonated();


private:
	float checkDistance();
};
