#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:49

namespace nframework::intellival
{
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
