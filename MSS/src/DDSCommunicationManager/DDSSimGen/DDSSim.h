#pragma once

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from DDSSim.idl
using RTI Code Generator (rtiddsgen) version 3.1.2.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef DDSSim_744907754_h
#define DDSSim_744907754_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#include "rti/xcdr/Interpreter.hpp"
#else
#include "ndds_standalone_type.h"
#endif

extern "C" {

    extern const char *MessageHeaderTYPENAME;

}

struct MessageHeaderSeq;
#ifndef NDDS_STANDALONE_TYPE
class MessageHeaderTypeSupport;
class MessageHeaderDataWriter;
class MessageHeaderDataReader;
#endif
class MessageHeader 
{
  public:
    typedef struct MessageHeaderSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef MessageHeaderTypeSupport TypeSupport;
    typedef MessageHeaderDataWriter DataWriter;
    typedef MessageHeaderDataReader DataReader;
    #endif

    DDS_UnsignedShort   TopicLabel ;
    DDS_UnsignedShort   TopicSize ;
    DDS_Octet   SourceID ;
    DDS_Octet   TopicClass ;
    DDS_UnsignedShort   TopicNumber ;
    DDS_UnsignedLongLong   SystemTime ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * MessageHeader_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *MessageHeader_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *MessageHeader_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *MessageHeader_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(MessageHeaderSeq, MessageHeader);

NDDSUSERDllExport
RTIBool MessageHeader_initialize(
    MessageHeader* self);

NDDSUSERDllExport
RTIBool MessageHeader_initialize_ex(
    MessageHeader* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool MessageHeader_initialize_w_params(
    MessageHeader* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool MessageHeader_finalize_w_return(
    MessageHeader* self);

NDDSUSERDllExport
void MessageHeader_finalize(
    MessageHeader* self);

NDDSUSERDllExport
void MessageHeader_finalize_ex(
    MessageHeader* self,RTIBool deletePointers);

NDDSUSERDllExport
void MessageHeader_finalize_w_params(
    MessageHeader* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void MessageHeader_finalize_optional_members(
    MessageHeader* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool MessageHeader_copy(
    MessageHeader* dst,
    const MessageHeader* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *AirThreatStructTYPENAME;

}

struct AirThreatStructSeq;
#ifndef NDDS_STANDALONE_TYPE
class AirThreatStructTypeSupport;
class AirThreatStructDataWriter;
class AirThreatStructDataReader;
#endif
class AirThreatStruct 
{
  public:
    typedef struct AirThreatStructSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef AirThreatStructTypeSupport TypeSupport;
    typedef AirThreatStructDataWriter DataWriter;
    typedef AirThreatStructDataReader DataReader;
    #endif

    DDS_UnsignedShort   ObjectID ;
    DDS_Octet   ObjectType ;
    DDS_Octet   DestructionFlag ;
    DDS_Long   PositionX ;
    DDS_Long   PositionY ;
    DDS_Long   PositionZ ;
    DDS_Short   VelocityX ;
    DDS_Short   VelocityY ;
    DDS_Short   VelocityZ ;
    DDS_Short   AccelerationX ;
    DDS_Short   AccelerationY ;
    DDS_Short   AccelerationZ ;
    DDS_UnsignedShort   MeanRCS ;
    DDS_Octet   Reserved ;
    DDS_Octet   JammingType ;
    DDS_UnsignedShort   JammingPower ;
    DDS_UnsignedShort   JammingPullOff ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * AirThreatStruct_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *AirThreatStruct_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *AirThreatStruct_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *AirThreatStruct_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(AirThreatStructSeq, AirThreatStruct);

NDDSUSERDllExport
RTIBool AirThreatStruct_initialize(
    AirThreatStruct* self);

NDDSUSERDllExport
RTIBool AirThreatStruct_initialize_ex(
    AirThreatStruct* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool AirThreatStruct_initialize_w_params(
    AirThreatStruct* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool AirThreatStruct_finalize_w_return(
    AirThreatStruct* self);

NDDSUSERDllExport
void AirThreatStruct_finalize(
    AirThreatStruct* self);

NDDSUSERDllExport
void AirThreatStruct_finalize_ex(
    AirThreatStruct* self,RTIBool deletePointers);

NDDSUSERDllExport
void AirThreatStruct_finalize_w_params(
    AirThreatStruct* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void AirThreatStruct_finalize_optional_members(
    AirThreatStruct* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool AirThreatStruct_copy(
    AirThreatStruct* dst,
    const AirThreatStruct* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *AirThreatInformationTYPENAME;

}

struct AirThreatInformationSeq;
#ifndef NDDS_STANDALONE_TYPE
class AirThreatInformationTypeSupport;
class AirThreatInformationDataWriter;
class AirThreatInformationDataReader;
#endif
class AirThreatInformation 
{
  public:
    typedef struct AirThreatInformationSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef AirThreatInformationTypeSupport TypeSupport;
    typedef AirThreatInformationDataWriter DataWriter;
    typedef AirThreatInformationDataReader DataReader;
    #endif

    MessageHeader   Header ;
    DDS_UnsignedLong   TimeTick ;
    DDS_UnsignedShort   SimulationFlag ;
    DDS_UnsignedShort   ObjectCount ;
    AirThreatStructSeq  AirThreatMessage ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * AirThreatInformation_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *AirThreatInformation_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *AirThreatInformation_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *AirThreatInformation_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(AirThreatInformationSeq, AirThreatInformation);

NDDSUSERDllExport
RTIBool AirThreatInformation_initialize(
    AirThreatInformation* self);

NDDSUSERDllExport
RTIBool AirThreatInformation_initialize_ex(
    AirThreatInformation* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool AirThreatInformation_initialize_w_params(
    AirThreatInformation* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool AirThreatInformation_finalize_w_return(
    AirThreatInformation* self);

NDDSUSERDllExport
void AirThreatInformation_finalize(
    AirThreatInformation* self);

NDDSUSERDllExport
void AirThreatInformation_finalize_ex(
    AirThreatInformation* self,RTIBool deletePointers);

NDDSUSERDllExport
void AirThreatInformation_finalize_w_params(
    AirThreatInformation* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void AirThreatInformation_finalize_optional_members(
    AirThreatInformation* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool AirThreatInformation_copy(
    AirThreatInformation* dst,
    const AirThreatInformation* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *InterceptorStructTYPENAME;

}

struct InterceptorStructSeq;
#ifndef NDDS_STANDALONE_TYPE
class InterceptorStructTypeSupport;
class InterceptorStructDataWriter;
class InterceptorStructDataReader;
#endif
class InterceptorStruct 
{
  public:
    typedef struct InterceptorStructSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef InterceptorStructTypeSupport TypeSupport;
    typedef InterceptorStructDataWriter DataWriter;
    typedef InterceptorStructDataReader DataReader;
    #endif

    DDS_UnsignedShort   ObjectID ;
    DDS_Octet   MissileType ;
    DDS_Octet   DestructionFlag ;
    DDS_Long   PositionX ;
    DDS_Long   PositionY ;
    DDS_Long   PositionZ ;
    DDS_Short   VelocityX ;
    DDS_Short   VelocityY ;
    DDS_Short   VelocityZ ;
    DDS_Short   AccelerationX ;
    DDS_Short   AccelerationY ;
    DDS_Short   AccelerationZ ;
    DDS_UnsignedShort   MeanRCS ;
    DDS_UnsignedShort   Reserved ;
    DDS_UnsignedShort   SignalPower ;
    DDS_Octet   SeekerPhase ;
    DDS_Octet   AddressKey ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * InterceptorStruct_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *InterceptorStruct_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *InterceptorStruct_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *InterceptorStruct_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(InterceptorStructSeq, InterceptorStruct);

NDDSUSERDllExport
RTIBool InterceptorStruct_initialize(
    InterceptorStruct* self);

NDDSUSERDllExport
RTIBool InterceptorStruct_initialize_ex(
    InterceptorStruct* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool InterceptorStruct_initialize_w_params(
    InterceptorStruct* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool InterceptorStruct_finalize_w_return(
    InterceptorStruct* self);

NDDSUSERDllExport
void InterceptorStruct_finalize(
    InterceptorStruct* self);

NDDSUSERDllExport
void InterceptorStruct_finalize_ex(
    InterceptorStruct* self,RTIBool deletePointers);

NDDSUSERDllExport
void InterceptorStruct_finalize_w_params(
    InterceptorStruct* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void InterceptorStruct_finalize_optional_members(
    InterceptorStruct* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool InterceptorStruct_copy(
    InterceptorStruct* dst,
    const InterceptorStruct* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *InterceptorInformationTYPENAME;

}

struct InterceptorInformationSeq;
#ifndef NDDS_STANDALONE_TYPE
class InterceptorInformationTypeSupport;
class InterceptorInformationDataWriter;
class InterceptorInformationDataReader;
#endif
class InterceptorInformation 
{
  public:
    typedef struct InterceptorInformationSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef InterceptorInformationTypeSupport TypeSupport;
    typedef InterceptorInformationDataWriter DataWriter;
    typedef InterceptorInformationDataReader DataReader;
    #endif

    MessageHeader   Header ;
    DDS_UnsignedLong   TimeTick ;
    DDS_UnsignedShort   SimulationFlag ;
    DDS_UnsignedShort   ObjectCount ;
    InterceptorStructSeq  InterceptorMessage ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * InterceptorInformation_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *InterceptorInformation_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *InterceptorInformation_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *InterceptorInformation_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(InterceptorInformationSeq, InterceptorInformation);

NDDSUSERDllExport
RTIBool InterceptorInformation_initialize(
    InterceptorInformation* self);

NDDSUSERDllExport
RTIBool InterceptorInformation_initialize_ex(
    InterceptorInformation* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool InterceptorInformation_initialize_w_params(
    InterceptorInformation* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool InterceptorInformation_finalize_w_return(
    InterceptorInformation* self);

NDDSUSERDllExport
void InterceptorInformation_finalize(
    InterceptorInformation* self);

NDDSUSERDllExport
void InterceptorInformation_finalize_ex(
    InterceptorInformation* self,RTIBool deletePointers);

NDDSUSERDllExport
void InterceptorInformation_finalize_w_params(
    InterceptorInformation* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void InterceptorInformation_finalize_optional_members(
    InterceptorInformation* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool InterceptorInformation_copy(
    InterceptorInformation* dst,
    const InterceptorInformation* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *UplinkStructTYPENAME;

}

struct UplinkStructSeq;
#ifndef NDDS_STANDALONE_TYPE
class UplinkStructTypeSupport;
class UplinkStructDataWriter;
class UplinkStructDataReader;
#endif
class UplinkStruct 
{
  public:
    typedef struct UplinkStructSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef UplinkStructTypeSupport TypeSupport;
    typedef UplinkStructDataWriter DataWriter;
    typedef UplinkStructDataReader DataReader;
    #endif

    DDS_UnsignedShort   AddressKey ;
    DDS_UnsignedShort   MissileType ;
    DDS_UnsignedShort   Data [26L];

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * UplinkStruct_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *UplinkStruct_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *UplinkStruct_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *UplinkStruct_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(UplinkStructSeq, UplinkStruct);

NDDSUSERDllExport
RTIBool UplinkStruct_initialize(
    UplinkStruct* self);

NDDSUSERDllExport
RTIBool UplinkStruct_initialize_ex(
    UplinkStruct* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool UplinkStruct_initialize_w_params(
    UplinkStruct* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool UplinkStruct_finalize_w_return(
    UplinkStruct* self);

NDDSUSERDllExport
void UplinkStruct_finalize(
    UplinkStruct* self);

NDDSUSERDllExport
void UplinkStruct_finalize_ex(
    UplinkStruct* self,RTIBool deletePointers);

NDDSUSERDllExport
void UplinkStruct_finalize_w_params(
    UplinkStruct* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void UplinkStruct_finalize_optional_members(
    UplinkStruct* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool UplinkStruct_copy(
    UplinkStruct* dst,
    const UplinkStruct* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *UplinkInformationTYPENAME;

}

struct UplinkInformationSeq;
#ifndef NDDS_STANDALONE_TYPE
class UplinkInformationTypeSupport;
class UplinkInformationDataWriter;
class UplinkInformationDataReader;
#endif
class UplinkInformation 
{
  public:
    typedef struct UplinkInformationSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef UplinkInformationTypeSupport TypeSupport;
    typedef UplinkInformationDataWriter DataWriter;
    typedef UplinkInformationDataReader DataReader;
    #endif

    MessageHeader   Header ;
    DDS_UnsignedLong   TimeTick ;
    UplinkStruct   UplinkMessage ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * UplinkInformation_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *UplinkInformation_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *UplinkInformation_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *UplinkInformation_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(UplinkInformationSeq, UplinkInformation);

NDDSUSERDllExport
RTIBool UplinkInformation_initialize(
    UplinkInformation* self);

NDDSUSERDllExport
RTIBool UplinkInformation_initialize_ex(
    UplinkInformation* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool UplinkInformation_initialize_w_params(
    UplinkInformation* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool UplinkInformation_finalize_w_return(
    UplinkInformation* self);

NDDSUSERDllExport
void UplinkInformation_finalize(
    UplinkInformation* self);

NDDSUSERDllExport
void UplinkInformation_finalize_ex(
    UplinkInformation* self,RTIBool deletePointers);

NDDSUSERDllExport
void UplinkInformation_finalize_w_params(
    UplinkInformation* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void UplinkInformation_finalize_optional_members(
    UplinkInformation* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool UplinkInformation_copy(
    UplinkInformation* dst,
    const UplinkInformation* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *DownlinkStructTYPENAME;

}

struct DownlinkStructSeq;
#ifndef NDDS_STANDALONE_TYPE
class DownlinkStructTypeSupport;
class DownlinkStructDataWriter;
class DownlinkStructDataReader;
#endif
class DownlinkStruct 
{
  public:
    typedef struct DownlinkStructSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef DownlinkStructTypeSupport TypeSupport;
    typedef DownlinkStructDataWriter DataWriter;
    typedef DownlinkStructDataReader DataReader;
    #endif

    DDS_UnsignedShort   AddressKey ;
    DDS_UnsignedShort   CRC ;
    DDS_UnsignedShort   Data [24L];

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * DownlinkStruct_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *DownlinkStruct_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *DownlinkStruct_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *DownlinkStruct_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(DownlinkStructSeq, DownlinkStruct);

NDDSUSERDllExport
RTIBool DownlinkStruct_initialize(
    DownlinkStruct* self);

NDDSUSERDllExport
RTIBool DownlinkStruct_initialize_ex(
    DownlinkStruct* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool DownlinkStruct_initialize_w_params(
    DownlinkStruct* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool DownlinkStruct_finalize_w_return(
    DownlinkStruct* self);

NDDSUSERDllExport
void DownlinkStruct_finalize(
    DownlinkStruct* self);

NDDSUSERDllExport
void DownlinkStruct_finalize_ex(
    DownlinkStruct* self,RTIBool deletePointers);

NDDSUSERDllExport
void DownlinkStruct_finalize_w_params(
    DownlinkStruct* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void DownlinkStruct_finalize_optional_members(
    DownlinkStruct* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool DownlinkStruct_copy(
    DownlinkStruct* dst,
    const DownlinkStruct* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *DownlinkInformationTYPENAME;

}

struct DownlinkInformationSeq;
#ifndef NDDS_STANDALONE_TYPE
class DownlinkInformationTypeSupport;
class DownlinkInformationDataWriter;
class DownlinkInformationDataReader;
#endif
class DownlinkInformation 
{
  public:
    typedef struct DownlinkInformationSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef DownlinkInformationTypeSupport TypeSupport;
    typedef DownlinkInformationDataWriter DataWriter;
    typedef DownlinkInformationDataReader DataReader;
    #endif

    MessageHeader   Header ;
    DDS_UnsignedLong   TimeTick ;
    DDS_UnsignedLong   ObjectCount ;
    DownlinkStructSeq  DownlinkMessage ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * DownlinkInformation_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *DownlinkInformation_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *DownlinkInformation_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *DownlinkInformation_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(DownlinkInformationSeq, DownlinkInformation);

NDDSUSERDllExport
RTIBool DownlinkInformation_initialize(
    DownlinkInformation* self);

NDDSUSERDllExport
RTIBool DownlinkInformation_initialize_ex(
    DownlinkInformation* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool DownlinkInformation_initialize_w_params(
    DownlinkInformation* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool DownlinkInformation_finalize_w_return(
    DownlinkInformation* self);

NDDSUSERDllExport
void DownlinkInformation_finalize(
    DownlinkInformation* self);

NDDSUSERDllExport
void DownlinkInformation_finalize_ex(
    DownlinkInformation* self,RTIBool deletePointers);

NDDSUSERDllExport
void DownlinkInformation_finalize_w_params(
    DownlinkInformation* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void DownlinkInformation_finalize_optional_members(
    DownlinkInformation* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool DownlinkInformation_copy(
    DownlinkInformation* dst,
    const DownlinkInformation* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *TimeTickStructTYPENAME;

}

struct TimeTickStructSeq;
#ifndef NDDS_STANDALONE_TYPE
class TimeTickStructTypeSupport;
class TimeTickStructDataWriter;
class TimeTickStructDataReader;
#endif
class TimeTickStruct 
{
  public:
    typedef struct TimeTickStructSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef TimeTickStructTypeSupport TypeSupport;
    typedef TimeTickStructDataWriter DataWriter;
    typedef TimeTickStructDataReader DataReader;
    #endif

    DDS_UnsignedLong   SyncCycle ;
    DDS_UnsignedLong   TimeTick ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * TimeTickStruct_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *TimeTickStruct_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *TimeTickStruct_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *TimeTickStruct_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(TimeTickStructSeq, TimeTickStruct);

NDDSUSERDllExport
RTIBool TimeTickStruct_initialize(
    TimeTickStruct* self);

NDDSUSERDllExport
RTIBool TimeTickStruct_initialize_ex(
    TimeTickStruct* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool TimeTickStruct_initialize_w_params(
    TimeTickStruct* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool TimeTickStruct_finalize_w_return(
    TimeTickStruct* self);

NDDSUSERDllExport
void TimeTickStruct_finalize(
    TimeTickStruct* self);

NDDSUSERDllExport
void TimeTickStruct_finalize_ex(
    TimeTickStruct* self,RTIBool deletePointers);

NDDSUSERDllExport
void TimeTickStruct_finalize_w_params(
    TimeTickStruct* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void TimeTickStruct_finalize_optional_members(
    TimeTickStruct* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool TimeTickStruct_copy(
    TimeTickStruct* dst,
    const TimeTickStruct* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *TimeTickInformationTYPENAME;

}

struct TimeTickInformationSeq;
#ifndef NDDS_STANDALONE_TYPE
class TimeTickInformationTypeSupport;
class TimeTickInformationDataWriter;
class TimeTickInformationDataReader;
#endif
class TimeTickInformation 
{
  public:
    typedef struct TimeTickInformationSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef TimeTickInformationTypeSupport TypeSupport;
    typedef TimeTickInformationDataWriter DataWriter;
    typedef TimeTickInformationDataReader DataReader;
    #endif

    MessageHeader   Header ;
    TimeTickStruct   TimeTickMessage ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * TimeTickInformation_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *TimeTickInformation_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *TimeTickInformation_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *TimeTickInformation_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(TimeTickInformationSeq, TimeTickInformation);

NDDSUSERDllExport
RTIBool TimeTickInformation_initialize(
    TimeTickInformation* self);

NDDSUSERDllExport
RTIBool TimeTickInformation_initialize_ex(
    TimeTickInformation* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool TimeTickInformation_initialize_w_params(
    TimeTickInformation* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool TimeTickInformation_finalize_w_return(
    TimeTickInformation* self);

NDDSUSERDllExport
void TimeTickInformation_finalize(
    TimeTickInformation* self);

NDDSUSERDllExport
void TimeTickInformation_finalize_ex(
    TimeTickInformation* self,RTIBool deletePointers);

NDDSUSERDllExport
void TimeTickInformation_finalize_w_params(
    TimeTickInformation* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void TimeTickInformation_finalize_optional_members(
    TimeTickInformation* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool TimeTickInformation_copy(
    TimeTickInformation* dst,
    const TimeTickInformation* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *MFRAttitudeStructTYPENAME;

}

struct MFRAttitudeStructSeq;
#ifndef NDDS_STANDALONE_TYPE
class MFRAttitudeStructTypeSupport;
class MFRAttitudeStructDataWriter;
class MFRAttitudeStructDataReader;
#endif
class MFRAttitudeStruct 
{
  public:
    typedef struct MFRAttitudeStructSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef MFRAttitudeStructTypeSupport TypeSupport;
    typedef MFRAttitudeStructDataWriter DataWriter;
    typedef MFRAttitudeStructDataReader DataReader;
    #endif

    DDS_Float   MFRAntennaRoll ;
    DDS_Float   MFRAntennaPitch ;
    DDS_Float   MFRAntennaHeading ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * MFRAttitudeStruct_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *MFRAttitudeStruct_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *MFRAttitudeStruct_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *MFRAttitudeStruct_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(MFRAttitudeStructSeq, MFRAttitudeStruct);

NDDSUSERDllExport
RTIBool MFRAttitudeStruct_initialize(
    MFRAttitudeStruct* self);

NDDSUSERDllExport
RTIBool MFRAttitudeStruct_initialize_ex(
    MFRAttitudeStruct* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool MFRAttitudeStruct_initialize_w_params(
    MFRAttitudeStruct* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool MFRAttitudeStruct_finalize_w_return(
    MFRAttitudeStruct* self);

NDDSUSERDllExport
void MFRAttitudeStruct_finalize(
    MFRAttitudeStruct* self);

NDDSUSERDllExport
void MFRAttitudeStruct_finalize_ex(
    MFRAttitudeStruct* self,RTIBool deletePointers);

NDDSUSERDllExport
void MFRAttitudeStruct_finalize_w_params(
    MFRAttitudeStruct* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void MFRAttitudeStruct_finalize_optional_members(
    MFRAttitudeStruct* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool MFRAttitudeStruct_copy(
    MFRAttitudeStruct* dst,
    const MFRAttitudeStruct* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *MFRAttitudeInformationTYPENAME;

}

struct MFRAttitudeInformationSeq;
#ifndef NDDS_STANDALONE_TYPE
class MFRAttitudeInformationTypeSupport;
class MFRAttitudeInformationDataWriter;
class MFRAttitudeInformationDataReader;
#endif
class MFRAttitudeInformation 
{
  public:
    typedef struct MFRAttitudeInformationSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef MFRAttitudeInformationTypeSupport TypeSupport;
    typedef MFRAttitudeInformationDataWriter DataWriter;
    typedef MFRAttitudeInformationDataReader DataReader;
    #endif

    MessageHeader   Header ;
    MFRAttitudeStruct   MFRAttitudeMessage ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * MFRAttitudeInformation_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *MFRAttitudeInformation_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *MFRAttitudeInformation_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *MFRAttitudeInformation_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(MFRAttitudeInformationSeq, MFRAttitudeInformation);

NDDSUSERDllExport
RTIBool MFRAttitudeInformation_initialize(
    MFRAttitudeInformation* self);

NDDSUSERDllExport
RTIBool MFRAttitudeInformation_initialize_ex(
    MFRAttitudeInformation* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool MFRAttitudeInformation_initialize_w_params(
    MFRAttitudeInformation* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool MFRAttitudeInformation_finalize_w_return(
    MFRAttitudeInformation* self);

NDDSUSERDllExport
void MFRAttitudeInformation_finalize(
    MFRAttitudeInformation* self);

NDDSUSERDllExport
void MFRAttitudeInformation_finalize_ex(
    MFRAttitudeInformation* self,RTIBool deletePointers);

NDDSUSERDllExport
void MFRAttitudeInformation_finalize_w_params(
    MFRAttitudeInformation* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void MFRAttitudeInformation_finalize_optional_members(
    MFRAttitudeInformation* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool MFRAttitudeInformation_copy(
    MFRAttitudeInformation* dst,
    const MFRAttitudeInformation* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *TestDDSConnectionTYPENAME;

}

struct TestDDSConnectionSeq;
#ifndef NDDS_STANDALONE_TYPE
class TestDDSConnectionTypeSupport;
class TestDDSConnectionDataWriter;
class TestDDSConnectionDataReader;
#endif
class TestDDSConnection 
{
  public:
    typedef struct TestDDSConnectionSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef TestDDSConnectionTypeSupport TypeSupport;
    typedef TestDDSConnectionDataWriter DataWriter;
    typedef TestDDSConnectionDataReader DataReader;
    #endif

    DDS_UnsignedShort   TestParam ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode * TestDDSConnection_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *TestDDSConnection_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *TestDDSConnection_get_sample_access_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *TestDDSConnection_get_sample_seq_access_info(void);
#endif

DDS_SEQUENCE(TestDDSConnectionSeq, TestDDSConnection);

NDDSUSERDllExport
RTIBool TestDDSConnection_initialize(
    TestDDSConnection* self);

NDDSUSERDllExport
RTIBool TestDDSConnection_initialize_ex(
    TestDDSConnection* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool TestDDSConnection_initialize_w_params(
    TestDDSConnection* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool TestDDSConnection_finalize_w_return(
    TestDDSConnection* self);

NDDSUSERDllExport
void TestDDSConnection_finalize(
    TestDDSConnection* self);

NDDSUSERDllExport
void TestDDSConnection_finalize_ex(
    TestDDSConnection* self,RTIBool deletePointers);

NDDSUSERDllExport
void TestDDSConnection_finalize_w_params(
    TestDDSConnection* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void TestDDSConnection_finalize_optional_members(
    TestDDSConnection* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool TestDDSConnection_copy(
    TestDDSConnection* dst,
    const TestDDSConnection* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#ifndef NDDS_STANDALONE_TYPE
namespace rti { 
    namespace xcdr {
        template <>
        struct type_code<MessageHeader> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<AirThreatStruct> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<AirThreatInformation> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<InterceptorStruct> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<InterceptorInformation> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<UplinkStruct> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<UplinkInformation> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<DownlinkStruct> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<DownlinkInformation> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<TimeTickStruct> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<TimeTickInformation> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<MFRAttitudeStruct> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<MFRAttitudeInformation> {
            static const RTIXCdrTypeCode * get();
        };

        template <>
        struct type_code<TestDDSConnection> {
            static const RTIXCdrTypeCode * get();
        };

    } 
}

#endif

#endif /* DDSSim */

