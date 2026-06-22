#pragma once

#include <cstdint>

enum class ICD_MessageID : std::uint32_t
{
	DeployScenarioRequest = 1001,
	StartSimulationRequest = 1002,
	StopSimulationRequest = 1003,
	LaunchMissileRequest = 1401,
	UplinkInfo_TCC_MFRS = 1501,

	ScenarioACK_ATS = 2101,
	ATInfo = 2501,

	ScenarioACK_MSS = 3101,
	DetonationInfo = 3201,
	DownlinkInfo_MSS_MFRS = 3501,

	ScenarioACK_LCS = 4101,
	MissileQuantityInfo = 4102,
	LaunchMissile = 4301,

	ScenarioACK = 5101,
	RadarDetectionInfo = 5102,
	DownlinkInfo_MFRS_TCC = 5103,
	UplinkInfo_MFRS_MSS = 5301
};

enum class InnerICD_MessageID
{
	// 공용 ICD 내부 메시지
	InnerSimulatorStateToComm = 0x20,
	InnerSendScenario,
	InnerSendScenarioAck,
	InnerSendScenarioToModel,
	InnerStartSimulation,
	InnerStartSimulationAck,
	InnerStartSimulationToModel,
	InnerStopSimulation,
	InnerStopSimulationAck,
	InnerStopSimulationToModel = 0x29,

	// ATS ICD 내부 메시지
	InnerAirThreatDetonationToATM = 0x40,
	InnerAirThreatInfoToComm,

	// LCS ICD 내부 메시지
	InnerFireMissileAckToLCS = 0x50,
	InnerFireMissileToMSS,
	InnerSendMissileInfoToComm,

	// MSS ICD 내부 메시지
	InnerMissileInfoToComm = 0x60,
	InnerMissileInfoToDeto,
	InnerUplinkInfoToMiss,
	InnerUplinkInfoToDeto,
	InnerMissileDetonationToMiss,
	InnerMissileDetonationToComm,
	InnerFireMissileToMiss,
	
	// MFRS ICD 내부 메시지
	InnerAirThreatInfo = 0x70,
	InnerMissileInfo,
	InnerRadarDetectionInfo,
	InnerAirThreatDetonation,
};

enum class SimulatorID
{
	TCC = 100,
	LCS,
	ATS,
	MSS,
	MFRS,
};

enum class TrackState
{
	// ATS
	ATS_Flight = 0,
	ATS_Detonation,

	// MSS
	MSS_Flight = 10,
	MSS_Detonation,
	MSS_EmergencyDetonation,
};