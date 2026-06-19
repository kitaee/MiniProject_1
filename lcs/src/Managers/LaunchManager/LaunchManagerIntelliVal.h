#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:47

namespace nframework::intellival
{
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

namespace LaunchMissileRequest
{
using v_MessageHeader_MessageID = nframework::nom::NUInteger;
using v_MessageHeader_MessageLength = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

}
