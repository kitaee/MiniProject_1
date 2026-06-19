#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:50

namespace nframework::intellival
{
namespace ScenarioACK
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
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

}
