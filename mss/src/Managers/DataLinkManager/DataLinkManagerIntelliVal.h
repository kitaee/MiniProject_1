#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:48

namespace nframework::intellival
{
namespace DownlinkInfo
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

namespace UplinkInfo
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

}
