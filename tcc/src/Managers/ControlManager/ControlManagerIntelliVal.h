#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:49

namespace nframework::intellival
{
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

}
