#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:51

namespace nframework::intellival
{
namespace UplinkInfo_1501
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_UplinkInfo_AirthreatID = nframework::nom::NUInteger;
using v_UplinkInfo_AirthreatXpos = nframework::nom::NFloat;
using v_UplinkInfo_AirthreatYPos = nframework::nom::NFloat;
using v_UplinkInfo_AirthreatZPos = nframework::nom::NFloat;
using v_UplinkInfo_MissileID = nframework::nom::NUInteger;
using v_UplinkInfo_AirthreatVelocity = nframework::nom::NFloat;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_UplinkInfo_AirthreatID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_UplinkInfo_AirthreatXpos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_UplinkInfo_AirthreatYPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_UplinkInfo_AirthreatZPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_UplinkInfo_MissileID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_UplinkInfo_AirthreatVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace ATInfo
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_AirthreatID = nframework::nom::NUInteger;
using v_AirthreatXPos = nframework::nom::NFloat;
using v_AirthreatYPos = nframework::nom::NFloat;
using v_AirthreatZPos = nframework::nom::NFloat;
using v_AirthreatVelocity = nframework::nom::NFloat;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AirthreatID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AirthreatXPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AirthreatYPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AirthreatZPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AirthreatVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace DownlinkInfo_3501
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_DownlinkInfo_MissleID = nframework::nom::NUInteger;
using v_DownlinkInfo_MissileVelocity = nframework::nom::NFloat;
using v_DownlinkInfo_MissleXPos = nframework::nom::NFloat;
using v_DownlinkInfo_MissleYPos = nframework::nom::NFloat;
using v_DownlinkInfo_MissleZPos = nframework::nom::NFloat;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_DownlinkInfo_MissleID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_DownlinkInfo_MissileVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_DownlinkInfo_MissleXPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_DownlinkInfo_MissleYPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_DownlinkInfo_MissleZPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace RadarDetectionInfo
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_RadarDetection_TargetID = nframework::nom::NUInteger;
using v_RadarDetection_TargetXPos = nframework::nom::NFloat;
using v_RadarDetection_TargetYPos = nframework::nom::NFloat;
using v_RadarDetection_TargetZPos = nframework::nom::NFloat;
using v_RadarDetection_DetectedFlag = nframework::nom::NUInteger;
using v_RadarDetection_TargetVelocity = nframework::nom::NFloat;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_RadarDetection_TargetID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_RadarDetection_TargetXPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_RadarDetection_TargetYPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_RadarDetection_TargetZPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_RadarDetection_DetectedFlag = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_RadarDetection_TargetVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace DownlinkInfo_5103
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_DownlinkInfo_MissleID = nframework::nom::NUInteger;
using v_DownlinkInfo_MissileVelocity = nframework::nom::NFloat;
using v_DownlinkInfo_MissleXPos = nframework::nom::NFloat;
using v_DownlinkInfo_MissleYPos = nframework::nom::NFloat;
using v_DownlinkInfo_MissleZPos = nframework::nom::NFloat;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_DownlinkInfo_MissleID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_DownlinkInfo_MissileVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_DownlinkInfo_MissleXPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_DownlinkInfo_MissleYPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_DownlinkInfo_MissleZPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace UplinkInfo_5301
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_UplinkInfo_AirthreatID = nframework::nom::NUInteger;
using v_UplinkInfo_AirthreatXpos = nframework::nom::NFloat;
using v_UplinkInfo_AirthreatYPos = nframework::nom::NFloat;
using v_UplinkInfo_AirthreatZPos = nframework::nom::NFloat;
using v_UplinkInfo_MissileID = nframework::nom::NUInteger;
using v_UplinkInfo_AirthreatVelocity = nframework::nom::NFloat;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_UplinkInfo_AirthreatID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_UplinkInfo_AirthreatXpos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_UplinkInfo_AirthreatYPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_UplinkInfo_AirthreatZPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_UplinkInfo_MissileID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_UplinkInfo_AirthreatVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace DeployScenarioRequest
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_Airthreat_AirthreatID = nframework::nom::NUInteger;
using v_Airthreat_StartLatitude = nframework::nom::NFloat;
using v_Airthreat_StartLongitude = nframework::nom::NFloat;
using v_Airthreat_EndLatitude = nframework::nom::NFloat;
using v_Airthreat_EndLongitude = nframework::nom::NFloat;
using v_RadarPositionLatitude = nframework::nom::NFloat;
using v_RadarPositionLongitude = nframework::nom::NFloat;
using v_LauncherPositionLatitude = nframework::nom::NFloat;
using v_LauncherPositionLongitude = nframework::nom::NFloat;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_Airthreat_AirthreatID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_Airthreat_StartLatitude = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Airthreat_StartLongitude = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Airthreat_EndLatitude = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Airthreat_EndLongitude = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_RadarPositionLatitude = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_RadarPositionLongitude = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_LauncherPositionLatitude = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_LauncherPositionLongitude = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace StartSimulationRequest
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace StopSimulationRequest
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace LaunchMissileRequest
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace ScenarioACK_2101
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace ScenarioACK_3101
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace DetonationInfo
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_MissleID = nframework::nom::NUInteger;
using v_TargetID = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MissleID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_TargetID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace ScenarioACK_4101
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace MissileQuantityInfo
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_MissileQuantity = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MissileQuantity = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace LaunchMissile
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
using v_AirthreatID = nframework::nom::NUInteger;
using v_AirthreatXpos = nframework::nom::NFloat;
using v_AirthreatYPos = nframework::nom::NFloat;
using v_AirthreatZPos = nframework::nom::NFloat;
using v_MissleID = nframework::nom::NUInteger;
using v_LCSXpos = nframework::nom::NFloat;
using v_LCSYPos = nframework::nom::NFloat;
using v_LCSZPos = nframework::nom::NFloat;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AirthreatID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AirthreatXpos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AirthreatYPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AirthreatZPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_MissleID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_LCSXpos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_LCSYPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_LCSZPos = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace ScenarioACK_5101
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

}
