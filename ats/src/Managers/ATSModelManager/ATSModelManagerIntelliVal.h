#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:51

namespace nframework::intellival
{
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

}
