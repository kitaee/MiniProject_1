#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:45

namespace nframework::intellival
{
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

}
