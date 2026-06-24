#pragma once

enum class ICD_MessageID
{
	// 모의기 간 ICD
	SendScenario = 0x01,
	SendScenarioAck,
	StartSimulation,
	StartSimulationAck,
	StopSimulation,
	StopSimulationAck,
	FireMissileToLCS,
	FireMissileAckToTCC,
	FireMissileToMSS,
	FireMissileAckToLCS = 0x0A,
	SimulatorState,
	SendMissileInfo,
	AirThreatInfo,
	MissileInfo,
	MissileDetonation,
	RadarDetectionInfo,
	UplinkInfo,
	AirThreatDetonation = 0x12,
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