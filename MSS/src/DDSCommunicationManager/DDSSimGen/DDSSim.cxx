

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from DDSSim.idl 
using RTI Code Generator (rtiddsgen) version 3.1.2.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif 
#ifndef dds_c_log_infrastructure_h                      
#include "dds_c/dds_c_infrastructure_impl.h"       
#endif 

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#ifndef osapi_heap_h
#include "osapi/osapi_heap.h" 
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "DDSSim.h"

#ifndef NDDS_STANDALONE_TYPE
#include "DDSSimPlugin.h"
#endif

#include <new>

/* ========================================================================= */
const char *MessageHeaderTYPENAME = "MessageHeader";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * MessageHeader_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member MessageHeader_g_tc_members[6]=
    {

        {
            (char *)"TopicLabel",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TopicSize",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"SourceID",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TopicClass",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TopicNumber",/* Member name */
            {
                4,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"SystemTime",/* Member name */
            {
                5,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode MessageHeader_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"MessageHeader", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            6, /* Number of members */
            MessageHeader_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for MessageHeader*/

    if (is_initialized) {
        return &MessageHeader_g_tc;
    }

    MessageHeader_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    MessageHeader_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    MessageHeader_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    MessageHeader_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    MessageHeader_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    MessageHeader_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    MessageHeader_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulonglong_w_new;

    /* Initialize the values for member annotations. */
    MessageHeader_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
    MessageHeader_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    MessageHeader_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    MessageHeader_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
    MessageHeader_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    MessageHeader_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    MessageHeader_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    MessageHeader_g_tc_members[2]._annotations._defaultValue._u.octet_value = 0;
    MessageHeader_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    MessageHeader_g_tc_members[2]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    MessageHeader_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    MessageHeader_g_tc_members[2]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    MessageHeader_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    MessageHeader_g_tc_members[3]._annotations._defaultValue._u.octet_value = 0;
    MessageHeader_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    MessageHeader_g_tc_members[3]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    MessageHeader_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    MessageHeader_g_tc_members[3]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    MessageHeader_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[4]._annotations._defaultValue._u.ushort_value = 0;
    MessageHeader_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[4]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    MessageHeader_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    MessageHeader_g_tc_members[4]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    MessageHeader_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
    MessageHeader_g_tc_members[5]._annotations._defaultValue._u.ulong_long_value = 0ull;
    MessageHeader_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
    MessageHeader_g_tc_members[5]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
    MessageHeader_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
    MessageHeader_g_tc_members[5]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;

    MessageHeader_g_tc._data._sampleAccessInfo =
    MessageHeader_get_sample_access_info();
    MessageHeader_g_tc._data._typePlugin =
    MessageHeader_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &MessageHeader_g_tc;
}

#define TSeq MessageHeaderSeq
#define T MessageHeader
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *MessageHeader_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo MessageHeader_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(MessageHeaderSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        MessageHeaderSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &MessageHeader_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *MessageHeader_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    MessageHeader *sample;

    static RTIXCdrMemberAccessInfo MessageHeader_g_memberAccessInfos[6] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo MessageHeader_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &MessageHeader_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        MessageHeader);
    if (sample == NULL) {
        return NULL;
    }

    MessageHeader_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TopicLabel - (char *)sample);

    MessageHeader_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TopicSize - (char *)sample);

    MessageHeader_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->SourceID - (char *)sample);

    MessageHeader_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TopicClass - (char *)sample);

    MessageHeader_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TopicNumber - (char *)sample);

    MessageHeader_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->SystemTime - (char *)sample);

    MessageHeader_g_sampleAccessInfo.memberAccessInfos = 
    MessageHeader_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(MessageHeader);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            MessageHeader_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            MessageHeader_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    MessageHeader_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    MessageHeader_g_sampleAccessInfo.getMemberValuePointerFcn = 
    MessageHeader_get_member_value_pointer;

    MessageHeader_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &MessageHeader_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *MessageHeader_get_type_plugin_info()
{
    static RTIXCdrTypePlugin MessageHeader_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        MessageHeader_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        MessageHeader_finalize_w_return,
        NULL
    };

    return &MessageHeader_g_typePlugin;
}
#endif

RTIBool MessageHeader_initialize(
    MessageHeader* sample) {
    return MessageHeader_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool MessageHeader_initialize_ex(
    MessageHeader* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return MessageHeader_initialize_w_params(
        sample,&allocParams);

}

RTIBool MessageHeader_initialize_w_params(
    MessageHeader* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->TopicLabel = 0;

    sample->TopicSize = 0;

    sample->SourceID = 0;

    sample->TopicClass = 0;

    sample->TopicNumber = 0;

    sample->SystemTime = 0ull;

    return RTI_TRUE;
}

RTIBool MessageHeader_finalize_w_return(
    MessageHeader* sample)
{
    MessageHeader_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void MessageHeader_finalize(
    MessageHeader* sample)
{

    MessageHeader_finalize_ex(sample,RTI_TRUE);
}

void MessageHeader_finalize_ex(
    MessageHeader* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    MessageHeader_finalize_w_params(
        sample,&deallocParams);
}

void MessageHeader_finalize_w_params(
    MessageHeader* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void MessageHeader_finalize_optional_members(
    MessageHeader* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool MessageHeader_copy(
    MessageHeader* dst,
    const MessageHeader* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyUnsignedShort (
            &dst->TopicLabel, &src->TopicLabel)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->TopicSize, &src->TopicSize)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->SourceID, &src->SourceID)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->TopicClass, &src->TopicClass)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->TopicNumber, &src->TopicNumber)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedLongLong (
            &dst->SystemTime, &src->SystemTime)) { 
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'MessageHeader' sequence class.
*/
#define T MessageHeader
#define TSeq MessageHeaderSeq

#define T_initialize_w_params MessageHeader_initialize_w_params

#define T_finalize_w_params   MessageHeader_finalize_w_params
#define T_copy       MessageHeader_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *AirThreatStructTYPENAME = "AirThreatStruct";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * AirThreatStruct_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member AirThreatStruct_g_tc_members[17]=
    {

        {
            (char *)"ObjectID",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"ObjectType",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"DestructionFlag",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"PositionX",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"PositionY",/* Member name */
            {
                4,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"PositionZ",/* Member name */
            {
                5,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"VelocityX",/* Member name */
            {
                6,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"VelocityY",/* Member name */
            {
                7,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"VelocityZ",/* Member name */
            {
                8,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"AccelerationX",/* Member name */
            {
                9,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"AccelerationY",/* Member name */
            {
                10,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"AccelerationZ",/* Member name */
            {
                11,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"MeanRCS",/* Member name */
            {
                12,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Reserved",/* Member name */
            {
                13,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"JammingType",/* Member name */
            {
                14,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"JammingPower",/* Member name */
            {
                15,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"JammingPullOff",/* Member name */
            {
                16,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode AirThreatStruct_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"AirThreatStruct", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            17, /* Number of members */
            AirThreatStruct_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for AirThreatStruct*/

    if (is_initialized) {
        return &AirThreatStruct_g_tc;
    }

    AirThreatStruct_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    AirThreatStruct_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    AirThreatStruct_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    AirThreatStruct_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    AirThreatStruct_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long_w_new;
    AirThreatStruct_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long_w_new;
    AirThreatStruct_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long_w_new;
    AirThreatStruct_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    AirThreatStruct_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    AirThreatStruct_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    AirThreatStruct_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    AirThreatStruct_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    AirThreatStruct_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    AirThreatStruct_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    AirThreatStruct_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    AirThreatStruct_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    AirThreatStruct_g_tc_members[15]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    AirThreatStruct_g_tc_members[16]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;

    /* Initialize the values for member annotations. */
    AirThreatStruct_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
    AirThreatStruct_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    AirThreatStruct_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    AirThreatStruct_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[1]._annotations._defaultValue._u.octet_value = 0;
    AirThreatStruct_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[1]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    AirThreatStruct_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[1]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    AirThreatStruct_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[2]._annotations._defaultValue._u.octet_value = 0;
    AirThreatStruct_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[2]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    AirThreatStruct_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[2]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    AirThreatStruct_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[3]._annotations._defaultValue._u.long_value = 0;
    AirThreatStruct_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[3]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    AirThreatStruct_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[3]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    AirThreatStruct_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[4]._annotations._defaultValue._u.long_value = 0;
    AirThreatStruct_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[4]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    AirThreatStruct_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[4]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    AirThreatStruct_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[5]._annotations._defaultValue._u.long_value = 0;
    AirThreatStruct_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[5]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    AirThreatStruct_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    AirThreatStruct_g_tc_members[5]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    AirThreatStruct_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[6]._annotations._defaultValue._u.short_value = 0;
    AirThreatStruct_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[6]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    AirThreatStruct_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[6]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    AirThreatStruct_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[7]._annotations._defaultValue._u.short_value = 0;
    AirThreatStruct_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[7]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    AirThreatStruct_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[7]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    AirThreatStruct_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[8]._annotations._defaultValue._u.short_value = 0;
    AirThreatStruct_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[8]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    AirThreatStruct_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[8]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    AirThreatStruct_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[9]._annotations._defaultValue._u.short_value = 0;
    AirThreatStruct_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[9]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    AirThreatStruct_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[9]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    AirThreatStruct_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[10]._annotations._defaultValue._u.short_value = 0;
    AirThreatStruct_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[10]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    AirThreatStruct_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[10]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    AirThreatStruct_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[11]._annotations._defaultValue._u.short_value = 0;
    AirThreatStruct_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[11]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    AirThreatStruct_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    AirThreatStruct_g_tc_members[11]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    AirThreatStruct_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[12]._annotations._defaultValue._u.ushort_value = 0;
    AirThreatStruct_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[12]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    AirThreatStruct_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[12]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    AirThreatStruct_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[13]._annotations._defaultValue._u.octet_value = 0;
    AirThreatStruct_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[13]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    AirThreatStruct_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[13]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    AirThreatStruct_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[14]._annotations._defaultValue._u.octet_value = 0;
    AirThreatStruct_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[14]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    AirThreatStruct_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    AirThreatStruct_g_tc_members[14]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    AirThreatStruct_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[15]._annotations._defaultValue._u.ushort_value = 0;
    AirThreatStruct_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[15]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    AirThreatStruct_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[15]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    AirThreatStruct_g_tc_members[16]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[16]._annotations._defaultValue._u.ushort_value = 0;
    AirThreatStruct_g_tc_members[16]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[16]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    AirThreatStruct_g_tc_members[16]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    AirThreatStruct_g_tc_members[16]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    AirThreatStruct_g_tc._data._sampleAccessInfo =
    AirThreatStruct_get_sample_access_info();
    AirThreatStruct_g_tc._data._typePlugin =
    AirThreatStruct_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &AirThreatStruct_g_tc;
}

#define TSeq AirThreatStructSeq
#define T AirThreatStruct
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *AirThreatStruct_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo AirThreatStruct_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(AirThreatStructSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        AirThreatStructSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &AirThreatStruct_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *AirThreatStruct_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    AirThreatStruct *sample;

    static RTIXCdrMemberAccessInfo AirThreatStruct_g_memberAccessInfos[17] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo AirThreatStruct_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &AirThreatStruct_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        AirThreatStruct);
    if (sample == NULL) {
        return NULL;
    }

    AirThreatStruct_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->ObjectID - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->ObjectType - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->DestructionFlag - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->PositionX - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->PositionY - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->PositionZ - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->VelocityX - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->VelocityY - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->VelocityZ - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AccelerationX - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AccelerationY - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AccelerationZ - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->MeanRCS - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Reserved - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->JammingType - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[15].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->JammingPower - (char *)sample);

    AirThreatStruct_g_memberAccessInfos[16].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->JammingPullOff - (char *)sample);

    AirThreatStruct_g_sampleAccessInfo.memberAccessInfos = 
    AirThreatStruct_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(AirThreatStruct);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            AirThreatStruct_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            AirThreatStruct_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    AirThreatStruct_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    AirThreatStruct_g_sampleAccessInfo.getMemberValuePointerFcn = 
    AirThreatStruct_get_member_value_pointer;

    AirThreatStruct_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &AirThreatStruct_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *AirThreatStruct_get_type_plugin_info()
{
    static RTIXCdrTypePlugin AirThreatStruct_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        AirThreatStruct_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        AirThreatStruct_finalize_w_return,
        NULL
    };

    return &AirThreatStruct_g_typePlugin;
}
#endif

RTIBool AirThreatStruct_initialize(
    AirThreatStruct* sample) {
    return AirThreatStruct_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool AirThreatStruct_initialize_ex(
    AirThreatStruct* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return AirThreatStruct_initialize_w_params(
        sample,&allocParams);

}

RTIBool AirThreatStruct_initialize_w_params(
    AirThreatStruct* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->ObjectID = 0;

    sample->ObjectType = 0;

    sample->DestructionFlag = 0;

    sample->PositionX = 0;

    sample->PositionY = 0;

    sample->PositionZ = 0;

    sample->VelocityX = 0;

    sample->VelocityY = 0;

    sample->VelocityZ = 0;

    sample->AccelerationX = 0;

    sample->AccelerationY = 0;

    sample->AccelerationZ = 0;

    sample->MeanRCS = 0;

    sample->Reserved = 0;

    sample->JammingType = 0;

    sample->JammingPower = 0;

    sample->JammingPullOff = 0;

    return RTI_TRUE;
}

RTIBool AirThreatStruct_finalize_w_return(
    AirThreatStruct* sample)
{
    AirThreatStruct_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void AirThreatStruct_finalize(
    AirThreatStruct* sample)
{

    AirThreatStruct_finalize_ex(sample,RTI_TRUE);
}

void AirThreatStruct_finalize_ex(
    AirThreatStruct* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    AirThreatStruct_finalize_w_params(
        sample,&deallocParams);
}

void AirThreatStruct_finalize_w_params(
    AirThreatStruct* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void AirThreatStruct_finalize_optional_members(
    AirThreatStruct* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool AirThreatStruct_copy(
    AirThreatStruct* dst,
    const AirThreatStruct* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyUnsignedShort (
            &dst->ObjectID, &src->ObjectID)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->ObjectType, &src->ObjectType)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->DestructionFlag, &src->DestructionFlag)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyLong (
            &dst->PositionX, &src->PositionX)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyLong (
            &dst->PositionY, &src->PositionY)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyLong (
            &dst->PositionZ, &src->PositionZ)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->VelocityX, &src->VelocityX)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->VelocityY, &src->VelocityY)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->VelocityZ, &src->VelocityZ)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->AccelerationX, &src->AccelerationX)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->AccelerationY, &src->AccelerationY)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->AccelerationZ, &src->AccelerationZ)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->MeanRCS, &src->MeanRCS)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->Reserved, &src->Reserved)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->JammingType, &src->JammingType)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->JammingPower, &src->JammingPower)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->JammingPullOff, &src->JammingPullOff)) { 
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'AirThreatStruct' sequence class.
*/
#define T AirThreatStruct
#define TSeq AirThreatStructSeq

#define T_initialize_w_params AirThreatStruct_initialize_w_params

#define T_finalize_w_params   AirThreatStruct_finalize_w_params
#define T_copy       AirThreatStruct_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *AirThreatInformationTYPENAME = "AirThreatInformation";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * AirThreatInformation_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode AirThreatInformation_g_tc_AirThreatMessage_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((150L),NULL);

    static DDS_TypeCode_Member AirThreatInformation_g_tc_members[5]=
    {

        {
            (char *)"Header",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TimeTick",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"SimulationFlag",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"ObjectCount",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"AirThreatMessage",/* Member name */
            {
                4,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode AirThreatInformation_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"AirThreatInformation", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            AirThreatInformation_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for AirThreatInformation*/

    if (is_initialized) {
        return &AirThreatInformation_g_tc;
    }

    AirThreatInformation_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    AirThreatInformation_g_tc_AirThreatMessage_sequence._data._typeCode = (RTICdrTypeCode *)AirThreatStruct_get_typecode();
    AirThreatInformation_g_tc_AirThreatMessage_sequence._data._sampleAccessInfo = AirThreatStruct_get_sample_seq_access_info();
    AirThreatInformation_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)MessageHeader_get_typecode();
    AirThreatInformation_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong_w_new;
    AirThreatInformation_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    AirThreatInformation_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    AirThreatInformation_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)& AirThreatInformation_g_tc_AirThreatMessage_sequence;

    /* Initialize the values for member annotations. */

    AirThreatInformation_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    AirThreatInformation_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    AirThreatInformation_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    AirThreatInformation_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    AirThreatInformation_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    AirThreatInformation_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    AirThreatInformation_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    AirThreatInformation_g_tc_members[2]._annotations._defaultValue._u.ushort_value = 0;
    AirThreatInformation_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    AirThreatInformation_g_tc_members[2]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    AirThreatInformation_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    AirThreatInformation_g_tc_members[2]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    AirThreatInformation_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    AirThreatInformation_g_tc_members[3]._annotations._defaultValue._u.ushort_value = 0;
    AirThreatInformation_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    AirThreatInformation_g_tc_members[3]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    AirThreatInformation_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    AirThreatInformation_g_tc_members[3]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    AirThreatInformation_g_tc._data._sampleAccessInfo =
    AirThreatInformation_get_sample_access_info();
    AirThreatInformation_g_tc._data._typePlugin =
    AirThreatInformation_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &AirThreatInformation_g_tc;
}

#define TSeq AirThreatInformationSeq
#define T AirThreatInformation
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *AirThreatInformation_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo AirThreatInformation_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(AirThreatInformationSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        AirThreatInformationSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &AirThreatInformation_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *AirThreatInformation_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    AirThreatInformation *sample;

    static RTIXCdrMemberAccessInfo AirThreatInformation_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo AirThreatInformation_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &AirThreatInformation_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        AirThreatInformation);
    if (sample == NULL) {
        return NULL;
    }

    AirThreatInformation_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

    AirThreatInformation_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TimeTick - (char *)sample);

    AirThreatInformation_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->SimulationFlag - (char *)sample);

    AirThreatInformation_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->ObjectCount - (char *)sample);

    AirThreatInformation_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AirThreatMessage - (char *)sample);

    AirThreatInformation_g_sampleAccessInfo.memberAccessInfos = 
    AirThreatInformation_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(AirThreatInformation);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            AirThreatInformation_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            AirThreatInformation_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    AirThreatInformation_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    AirThreatInformation_g_sampleAccessInfo.getMemberValuePointerFcn = 
    AirThreatInformation_get_member_value_pointer;

    AirThreatInformation_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &AirThreatInformation_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *AirThreatInformation_get_type_plugin_info()
{
    static RTIXCdrTypePlugin AirThreatInformation_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        AirThreatInformation_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        AirThreatInformation_finalize_w_return,
        NULL
    };

    return &AirThreatInformation_g_typePlugin;
}
#endif

RTIBool AirThreatInformation_initialize(
    AirThreatInformation* sample) {
    return AirThreatInformation_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool AirThreatInformation_initialize_ex(
    AirThreatInformation* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return AirThreatInformation_initialize_w_params(
        sample,&allocParams);

}

RTIBool AirThreatInformation_initialize_w_params(
    AirThreatInformation* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!MessageHeader_initialize_w_params(&sample->Header,
    allocParams)) {
        return RTI_FALSE;
    }
    sample->TimeTick = 0u;

    sample->SimulationFlag = 0;

    sample->ObjectCount = 0;

    if (allocParams->allocate_memory) {
        if(!AirThreatStructSeq_initialize(&sample->AirThreatMessage )){
            return RTI_FALSE;
        };
        if(!AirThreatStructSeq_set_element_allocation_params(&sample->AirThreatMessage ,allocParams)){
            return RTI_FALSE;
        };
        if(!AirThreatStructSeq_set_absolute_maximum(&sample->AirThreatMessage , (150L))){
            return RTI_FALSE;
        }
        if (!AirThreatStructSeq_set_maximum(&sample->AirThreatMessage, (150L))) {
            return RTI_FALSE;
        }
    } else { 
        if(!AirThreatStructSeq_set_length(&sample->AirThreatMessage, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool AirThreatInformation_finalize_w_return(
    AirThreatInformation* sample)
{
    AirThreatInformation_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void AirThreatInformation_finalize(
    AirThreatInformation* sample)
{

    AirThreatInformation_finalize_ex(sample,RTI_TRUE);
}

void AirThreatInformation_finalize_ex(
    AirThreatInformation* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    AirThreatInformation_finalize_w_params(
        sample,&deallocParams);
}

void AirThreatInformation_finalize_w_params(
    AirThreatInformation* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    MessageHeader_finalize_w_params(&sample->Header,deallocParams);

    if(!AirThreatStructSeq_set_element_deallocation_params(
        &sample->AirThreatMessage,deallocParams)){
        return; 
    }
    if(!AirThreatStructSeq_finalize(&sample->AirThreatMessage)){
        return;
    }

}

void AirThreatInformation_finalize_optional_members(
    AirThreatInformation* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool AirThreatInformation_copy(
    AirThreatInformation* dst,
    const AirThreatInformation* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!MessageHeader_copy(
            &dst->Header,(const MessageHeader*)&src->Header)) {
            return RTI_FALSE;
        } 
        if (!RTICdrType_copyUnsignedLong (
            &dst->TimeTick, &src->TimeTick)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->SimulationFlag, &src->SimulationFlag)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->ObjectCount, &src->ObjectCount)) { 
            return RTI_FALSE;
        }
        if (!AirThreatStructSeq_copy(&dst->AirThreatMessage ,
        &src->AirThreatMessage )) {
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'AirThreatInformation' sequence class.
*/
#define T AirThreatInformation
#define TSeq AirThreatInformationSeq

#define T_initialize_w_params AirThreatInformation_initialize_w_params

#define T_finalize_w_params   AirThreatInformation_finalize_w_params
#define T_copy       AirThreatInformation_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *InterceptorStructTYPENAME = "InterceptorStruct";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * InterceptorStruct_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member InterceptorStruct_g_tc_members[17]=
    {

        {
            (char *)"ObjectID",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"MissileType",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"DestructionFlag",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"PositionX",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"PositionY",/* Member name */
            {
                4,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"PositionZ",/* Member name */
            {
                5,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"VelocityX",/* Member name */
            {
                6,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"VelocityY",/* Member name */
            {
                7,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"VelocityZ",/* Member name */
            {
                8,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"AccelerationX",/* Member name */
            {
                9,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"AccelerationY",/* Member name */
            {
                10,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"AccelerationZ",/* Member name */
            {
                11,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"MeanRCS",/* Member name */
            {
                12,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Reserved",/* Member name */
            {
                13,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"SignalPower",/* Member name */
            {
                14,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"SeekerPhase",/* Member name */
            {
                15,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"AddressKey",/* Member name */
            {
                16,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode InterceptorStruct_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"InterceptorStruct", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            17, /* Number of members */
            InterceptorStruct_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for InterceptorStruct*/

    if (is_initialized) {
        return &InterceptorStruct_g_tc;
    }

    InterceptorStruct_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    InterceptorStruct_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    InterceptorStruct_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    InterceptorStruct_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    InterceptorStruct_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long_w_new;
    InterceptorStruct_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long_w_new;
    InterceptorStruct_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long_w_new;
    InterceptorStruct_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    InterceptorStruct_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    InterceptorStruct_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    InterceptorStruct_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    InterceptorStruct_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    InterceptorStruct_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short_w_new;
    InterceptorStruct_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    InterceptorStruct_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    InterceptorStruct_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    InterceptorStruct_g_tc_members[15]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;
    InterceptorStruct_g_tc_members[16]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;

    /* Initialize the values for member annotations. */
    InterceptorStruct_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
    InterceptorStruct_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    InterceptorStruct_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    InterceptorStruct_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[1]._annotations._defaultValue._u.octet_value = 0;
    InterceptorStruct_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[1]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    InterceptorStruct_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[1]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    InterceptorStruct_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[2]._annotations._defaultValue._u.octet_value = 0;
    InterceptorStruct_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[2]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    InterceptorStruct_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[2]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    InterceptorStruct_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[3]._annotations._defaultValue._u.long_value = 0;
    InterceptorStruct_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[3]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    InterceptorStruct_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[3]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    InterceptorStruct_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[4]._annotations._defaultValue._u.long_value = 0;
    InterceptorStruct_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[4]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    InterceptorStruct_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[4]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    InterceptorStruct_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[5]._annotations._defaultValue._u.long_value = 0;
    InterceptorStruct_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[5]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    InterceptorStruct_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    InterceptorStruct_g_tc_members[5]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    InterceptorStruct_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[6]._annotations._defaultValue._u.short_value = 0;
    InterceptorStruct_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[6]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    InterceptorStruct_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[6]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    InterceptorStruct_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[7]._annotations._defaultValue._u.short_value = 0;
    InterceptorStruct_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[7]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    InterceptorStruct_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[7]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    InterceptorStruct_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[8]._annotations._defaultValue._u.short_value = 0;
    InterceptorStruct_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[8]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    InterceptorStruct_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[8]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    InterceptorStruct_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[9]._annotations._defaultValue._u.short_value = 0;
    InterceptorStruct_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[9]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    InterceptorStruct_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[9]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    InterceptorStruct_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[10]._annotations._defaultValue._u.short_value = 0;
    InterceptorStruct_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[10]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    InterceptorStruct_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[10]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    InterceptorStruct_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[11]._annotations._defaultValue._u.short_value = 0;
    InterceptorStruct_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[11]._annotations._minValue._u.short_value = RTIXCdrShort_MIN;
    InterceptorStruct_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_SHORT;
    InterceptorStruct_g_tc_members[11]._annotations._maxValue._u.short_value = RTIXCdrShort_MAX;

    InterceptorStruct_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[12]._annotations._defaultValue._u.ushort_value = 0;
    InterceptorStruct_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[12]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    InterceptorStruct_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[12]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    InterceptorStruct_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[13]._annotations._defaultValue._u.ushort_value = 0;
    InterceptorStruct_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[13]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    InterceptorStruct_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[13]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    InterceptorStruct_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[14]._annotations._defaultValue._u.ushort_value = 0;
    InterceptorStruct_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[14]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    InterceptorStruct_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    InterceptorStruct_g_tc_members[14]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    InterceptorStruct_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[15]._annotations._defaultValue._u.octet_value = 0;
    InterceptorStruct_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[15]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    InterceptorStruct_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[15]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    InterceptorStruct_g_tc_members[16]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[16]._annotations._defaultValue._u.octet_value = 0;
    InterceptorStruct_g_tc_members[16]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[16]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
    InterceptorStruct_g_tc_members[16]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
    InterceptorStruct_g_tc_members[16]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

    InterceptorStruct_g_tc._data._sampleAccessInfo =
    InterceptorStruct_get_sample_access_info();
    InterceptorStruct_g_tc._data._typePlugin =
    InterceptorStruct_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &InterceptorStruct_g_tc;
}

#define TSeq InterceptorStructSeq
#define T InterceptorStruct
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *InterceptorStruct_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo InterceptorStruct_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(InterceptorStructSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        InterceptorStructSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &InterceptorStruct_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *InterceptorStruct_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    InterceptorStruct *sample;

    static RTIXCdrMemberAccessInfo InterceptorStruct_g_memberAccessInfos[17] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo InterceptorStruct_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &InterceptorStruct_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        InterceptorStruct);
    if (sample == NULL) {
        return NULL;
    }

    InterceptorStruct_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->ObjectID - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->MissileType - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->DestructionFlag - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->PositionX - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->PositionY - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->PositionZ - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->VelocityX - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->VelocityY - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->VelocityZ - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AccelerationX - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AccelerationY - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AccelerationZ - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->MeanRCS - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Reserved - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->SignalPower - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[15].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->SeekerPhase - (char *)sample);

    InterceptorStruct_g_memberAccessInfos[16].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AddressKey - (char *)sample);

    InterceptorStruct_g_sampleAccessInfo.memberAccessInfos = 
    InterceptorStruct_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(InterceptorStruct);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            InterceptorStruct_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            InterceptorStruct_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    InterceptorStruct_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    InterceptorStruct_g_sampleAccessInfo.getMemberValuePointerFcn = 
    InterceptorStruct_get_member_value_pointer;

    InterceptorStruct_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &InterceptorStruct_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *InterceptorStruct_get_type_plugin_info()
{
    static RTIXCdrTypePlugin InterceptorStruct_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        InterceptorStruct_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        InterceptorStruct_finalize_w_return,
        NULL
    };

    return &InterceptorStruct_g_typePlugin;
}
#endif

RTIBool InterceptorStruct_initialize(
    InterceptorStruct* sample) {
    return InterceptorStruct_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool InterceptorStruct_initialize_ex(
    InterceptorStruct* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return InterceptorStruct_initialize_w_params(
        sample,&allocParams);

}

RTIBool InterceptorStruct_initialize_w_params(
    InterceptorStruct* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->ObjectID = 0;

    sample->MissileType = 0;

    sample->DestructionFlag = 0;

    sample->PositionX = 0;

    sample->PositionY = 0;

    sample->PositionZ = 0;

    sample->VelocityX = 0;

    sample->VelocityY = 0;

    sample->VelocityZ = 0;

    sample->AccelerationX = 0;

    sample->AccelerationY = 0;

    sample->AccelerationZ = 0;

    sample->MeanRCS = 0;

    sample->Reserved = 0;

    sample->SignalPower = 0;

    sample->SeekerPhase = 0;

    sample->AddressKey = 0;

    return RTI_TRUE;
}

RTIBool InterceptorStruct_finalize_w_return(
    InterceptorStruct* sample)
{
    InterceptorStruct_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void InterceptorStruct_finalize(
    InterceptorStruct* sample)
{

    InterceptorStruct_finalize_ex(sample,RTI_TRUE);
}

void InterceptorStruct_finalize_ex(
    InterceptorStruct* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    InterceptorStruct_finalize_w_params(
        sample,&deallocParams);
}

void InterceptorStruct_finalize_w_params(
    InterceptorStruct* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void InterceptorStruct_finalize_optional_members(
    InterceptorStruct* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool InterceptorStruct_copy(
    InterceptorStruct* dst,
    const InterceptorStruct* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyUnsignedShort (
            &dst->ObjectID, &src->ObjectID)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->MissileType, &src->MissileType)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->DestructionFlag, &src->DestructionFlag)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyLong (
            &dst->PositionX, &src->PositionX)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyLong (
            &dst->PositionY, &src->PositionY)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyLong (
            &dst->PositionZ, &src->PositionZ)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->VelocityX, &src->VelocityX)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->VelocityY, &src->VelocityY)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->VelocityZ, &src->VelocityZ)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->AccelerationX, &src->AccelerationX)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->AccelerationY, &src->AccelerationY)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyShort (
            &dst->AccelerationZ, &src->AccelerationZ)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->MeanRCS, &src->MeanRCS)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->Reserved, &src->Reserved)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->SignalPower, &src->SignalPower)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->SeekerPhase, &src->SeekerPhase)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyOctet (
            &dst->AddressKey, &src->AddressKey)) { 
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'InterceptorStruct' sequence class.
*/
#define T InterceptorStruct
#define TSeq InterceptorStructSeq

#define T_initialize_w_params InterceptorStruct_initialize_w_params

#define T_finalize_w_params   InterceptorStruct_finalize_w_params
#define T_copy       InterceptorStruct_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *InterceptorInformationTYPENAME = "InterceptorInformation";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * InterceptorInformation_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode InterceptorInformation_g_tc_InterceptorMessage_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((30L),NULL);

    static DDS_TypeCode_Member InterceptorInformation_g_tc_members[5]=
    {

        {
            (char *)"Header",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TimeTick",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"SimulationFlag",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"ObjectCount",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"InterceptorMessage",/* Member name */
            {
                4,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode InterceptorInformation_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"InterceptorInformation", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            5, /* Number of members */
            InterceptorInformation_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for InterceptorInformation*/

    if (is_initialized) {
        return &InterceptorInformation_g_tc;
    }

    InterceptorInformation_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    InterceptorInformation_g_tc_InterceptorMessage_sequence._data._typeCode = (RTICdrTypeCode *)InterceptorStruct_get_typecode();
    InterceptorInformation_g_tc_InterceptorMessage_sequence._data._sampleAccessInfo = InterceptorStruct_get_sample_seq_access_info();
    InterceptorInformation_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)MessageHeader_get_typecode();
    InterceptorInformation_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong_w_new;
    InterceptorInformation_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    InterceptorInformation_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    InterceptorInformation_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)& InterceptorInformation_g_tc_InterceptorMessage_sequence;

    /* Initialize the values for member annotations. */

    InterceptorInformation_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    InterceptorInformation_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    InterceptorInformation_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    InterceptorInformation_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    InterceptorInformation_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    InterceptorInformation_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    InterceptorInformation_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    InterceptorInformation_g_tc_members[2]._annotations._defaultValue._u.ushort_value = 0;
    InterceptorInformation_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    InterceptorInformation_g_tc_members[2]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    InterceptorInformation_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    InterceptorInformation_g_tc_members[2]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    InterceptorInformation_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    InterceptorInformation_g_tc_members[3]._annotations._defaultValue._u.ushort_value = 0;
    InterceptorInformation_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    InterceptorInformation_g_tc_members[3]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    InterceptorInformation_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    InterceptorInformation_g_tc_members[3]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    InterceptorInformation_g_tc._data._sampleAccessInfo =
    InterceptorInformation_get_sample_access_info();
    InterceptorInformation_g_tc._data._typePlugin =
    InterceptorInformation_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &InterceptorInformation_g_tc;
}

#define TSeq InterceptorInformationSeq
#define T InterceptorInformation
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *InterceptorInformation_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo InterceptorInformation_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(InterceptorInformationSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        InterceptorInformationSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &InterceptorInformation_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *InterceptorInformation_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    InterceptorInformation *sample;

    static RTIXCdrMemberAccessInfo InterceptorInformation_g_memberAccessInfos[5] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo InterceptorInformation_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &InterceptorInformation_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        InterceptorInformation);
    if (sample == NULL) {
        return NULL;
    }

    InterceptorInformation_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

    InterceptorInformation_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TimeTick - (char *)sample);

    InterceptorInformation_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->SimulationFlag - (char *)sample);

    InterceptorInformation_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->ObjectCount - (char *)sample);

    InterceptorInformation_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->InterceptorMessage - (char *)sample);

    InterceptorInformation_g_sampleAccessInfo.memberAccessInfos = 
    InterceptorInformation_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(InterceptorInformation);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            InterceptorInformation_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            InterceptorInformation_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    InterceptorInformation_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    InterceptorInformation_g_sampleAccessInfo.getMemberValuePointerFcn = 
    InterceptorInformation_get_member_value_pointer;

    InterceptorInformation_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &InterceptorInformation_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *InterceptorInformation_get_type_plugin_info()
{
    static RTIXCdrTypePlugin InterceptorInformation_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        InterceptorInformation_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        InterceptorInformation_finalize_w_return,
        NULL
    };

    return &InterceptorInformation_g_typePlugin;
}
#endif

RTIBool InterceptorInformation_initialize(
    InterceptorInformation* sample) {
    return InterceptorInformation_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool InterceptorInformation_initialize_ex(
    InterceptorInformation* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return InterceptorInformation_initialize_w_params(
        sample,&allocParams);

}

RTIBool InterceptorInformation_initialize_w_params(
    InterceptorInformation* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!MessageHeader_initialize_w_params(&sample->Header,
    allocParams)) {
        return RTI_FALSE;
    }
    sample->TimeTick = 0u;

    sample->SimulationFlag = 0;

    sample->ObjectCount = 0;

    if (allocParams->allocate_memory) {
        if(!InterceptorStructSeq_initialize(&sample->InterceptorMessage )){
            return RTI_FALSE;
        };
        if(!InterceptorStructSeq_set_element_allocation_params(&sample->InterceptorMessage ,allocParams)){
            return RTI_FALSE;
        };
        if(!InterceptorStructSeq_set_absolute_maximum(&sample->InterceptorMessage , (30L))){
            return RTI_FALSE;
        }
        if (!InterceptorStructSeq_set_maximum(&sample->InterceptorMessage, (30L))) {
            return RTI_FALSE;
        }
    } else { 
        if(!InterceptorStructSeq_set_length(&sample->InterceptorMessage, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool InterceptorInformation_finalize_w_return(
    InterceptorInformation* sample)
{
    InterceptorInformation_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void InterceptorInformation_finalize(
    InterceptorInformation* sample)
{

    InterceptorInformation_finalize_ex(sample,RTI_TRUE);
}

void InterceptorInformation_finalize_ex(
    InterceptorInformation* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    InterceptorInformation_finalize_w_params(
        sample,&deallocParams);
}

void InterceptorInformation_finalize_w_params(
    InterceptorInformation* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    MessageHeader_finalize_w_params(&sample->Header,deallocParams);

    if(!InterceptorStructSeq_set_element_deallocation_params(
        &sample->InterceptorMessage,deallocParams)){
        return; 
    }
    if(!InterceptorStructSeq_finalize(&sample->InterceptorMessage)){
        return;
    }

}

void InterceptorInformation_finalize_optional_members(
    InterceptorInformation* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool InterceptorInformation_copy(
    InterceptorInformation* dst,
    const InterceptorInformation* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!MessageHeader_copy(
            &dst->Header,(const MessageHeader*)&src->Header)) {
            return RTI_FALSE;
        } 
        if (!RTICdrType_copyUnsignedLong (
            &dst->TimeTick, &src->TimeTick)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->SimulationFlag, &src->SimulationFlag)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->ObjectCount, &src->ObjectCount)) { 
            return RTI_FALSE;
        }
        if (!InterceptorStructSeq_copy(&dst->InterceptorMessage ,
        &src->InterceptorMessage )) {
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'InterceptorInformation' sequence class.
*/
#define T InterceptorInformation
#define TSeq InterceptorInformationSeq

#define T_initialize_w_params InterceptorInformation_initialize_w_params

#define T_finalize_w_params   InterceptorInformation_finalize_w_params
#define T_copy       InterceptorInformation_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *UplinkStructTYPENAME = "UplinkStruct";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * UplinkStruct_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode UplinkStruct_g_tc_Data_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,26L, NULL,NULL);

    static DDS_TypeCode_Member UplinkStruct_g_tc_members[3]=
    {

        {
            (char *)"AddressKey",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"MissileType",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Data",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode UplinkStruct_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"UplinkStruct", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            UplinkStruct_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for UplinkStruct*/

    if (is_initialized) {
        return &UplinkStruct_g_tc;
    }

    UplinkStruct_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    UplinkStruct_g_tc_Data_array._data._typeCode =(RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    UplinkStruct_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    UplinkStruct_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    UplinkStruct_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)& UplinkStruct_g_tc_Data_array;

    /* Initialize the values for member annotations. */
    UplinkStruct_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    UplinkStruct_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
    UplinkStruct_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    UplinkStruct_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    UplinkStruct_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    UplinkStruct_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    UplinkStruct_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    UplinkStruct_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
    UplinkStruct_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    UplinkStruct_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    UplinkStruct_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    UplinkStruct_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    UplinkStruct_g_tc._data._sampleAccessInfo =
    UplinkStruct_get_sample_access_info();
    UplinkStruct_g_tc._data._typePlugin =
    UplinkStruct_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &UplinkStruct_g_tc;
}

#define TSeq UplinkStructSeq
#define T UplinkStruct
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *UplinkStruct_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo UplinkStruct_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(UplinkStructSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        UplinkStructSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &UplinkStruct_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *UplinkStruct_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    UplinkStruct *sample;

    static RTIXCdrMemberAccessInfo UplinkStruct_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo UplinkStruct_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &UplinkStruct_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        UplinkStruct);
    if (sample == NULL) {
        return NULL;
    }

    UplinkStruct_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AddressKey - (char *)sample);

    UplinkStruct_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->MissileType - (char *)sample);

    UplinkStruct_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Data - (char *)sample);

    UplinkStruct_g_sampleAccessInfo.memberAccessInfos = 
    UplinkStruct_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(UplinkStruct);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            UplinkStruct_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            UplinkStruct_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    UplinkStruct_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    UplinkStruct_g_sampleAccessInfo.getMemberValuePointerFcn = 
    UplinkStruct_get_member_value_pointer;

    UplinkStruct_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &UplinkStruct_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *UplinkStruct_get_type_plugin_info()
{
    static RTIXCdrTypePlugin UplinkStruct_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        UplinkStruct_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        UplinkStruct_finalize_w_return,
        NULL
    };

    return &UplinkStruct_g_typePlugin;
}
#endif

RTIBool UplinkStruct_initialize(
    UplinkStruct* sample) {
    return UplinkStruct_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool UplinkStruct_initialize_ex(
    UplinkStruct* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return UplinkStruct_initialize_w_params(
        sample,&allocParams);

}

RTIBool UplinkStruct_initialize_w_params(
    UplinkStruct* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->AddressKey = 0;

    sample->MissileType = 0;

    RTICdrType_initArrayUnsafe(sample->Data,
    (26L),
    RTI_CDR_UNSIGNED_SHORT_SIZE);
    return RTI_TRUE;
}

RTIBool UplinkStruct_finalize_w_return(
    UplinkStruct* sample)
{
    UplinkStruct_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void UplinkStruct_finalize(
    UplinkStruct* sample)
{

    UplinkStruct_finalize_ex(sample,RTI_TRUE);
}

void UplinkStruct_finalize_ex(
    UplinkStruct* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    UplinkStruct_finalize_w_params(
        sample,&deallocParams);
}

void UplinkStruct_finalize_w_params(
    UplinkStruct* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void UplinkStruct_finalize_optional_members(
    UplinkStruct* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool UplinkStruct_copy(
    UplinkStruct* dst,
    const UplinkStruct* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyUnsignedShort (
            &dst->AddressKey, &src->AddressKey)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->MissileType, &src->MissileType)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyArray(
            dst->Data ,src->Data,(26L), RTI_CDR_UNSIGNED_SHORT_SIZE)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'UplinkStruct' sequence class.
*/
#define T UplinkStruct
#define TSeq UplinkStructSeq

#define T_initialize_w_params UplinkStruct_initialize_w_params

#define T_finalize_w_params   UplinkStruct_finalize_w_params
#define T_copy       UplinkStruct_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *UplinkInformationTYPENAME = "UplinkInformation";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * UplinkInformation_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member UplinkInformation_g_tc_members[3]=
    {

        {
            (char *)"Header",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TimeTick",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"UplinkMessage",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode UplinkInformation_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"UplinkInformation", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            UplinkInformation_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for UplinkInformation*/

    if (is_initialized) {
        return &UplinkInformation_g_tc;
    }

    UplinkInformation_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    UplinkInformation_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)MessageHeader_get_typecode();
    UplinkInformation_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong_w_new;
    UplinkInformation_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)UplinkStruct_get_typecode();

    /* Initialize the values for member annotations. */

    UplinkInformation_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    UplinkInformation_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    UplinkInformation_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    UplinkInformation_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    UplinkInformation_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    UplinkInformation_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    UplinkInformation_g_tc._data._sampleAccessInfo =
    UplinkInformation_get_sample_access_info();
    UplinkInformation_g_tc._data._typePlugin =
    UplinkInformation_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &UplinkInformation_g_tc;
}

#define TSeq UplinkInformationSeq
#define T UplinkInformation
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *UplinkInformation_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo UplinkInformation_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(UplinkInformationSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        UplinkInformationSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &UplinkInformation_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *UplinkInformation_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    UplinkInformation *sample;

    static RTIXCdrMemberAccessInfo UplinkInformation_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo UplinkInformation_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &UplinkInformation_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        UplinkInformation);
    if (sample == NULL) {
        return NULL;
    }

    UplinkInformation_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

    UplinkInformation_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TimeTick - (char *)sample);

    UplinkInformation_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->UplinkMessage - (char *)sample);

    UplinkInformation_g_sampleAccessInfo.memberAccessInfos = 
    UplinkInformation_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(UplinkInformation);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            UplinkInformation_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            UplinkInformation_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    UplinkInformation_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    UplinkInformation_g_sampleAccessInfo.getMemberValuePointerFcn = 
    UplinkInformation_get_member_value_pointer;

    UplinkInformation_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &UplinkInformation_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *UplinkInformation_get_type_plugin_info()
{
    static RTIXCdrTypePlugin UplinkInformation_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        UplinkInformation_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        UplinkInformation_finalize_w_return,
        NULL
    };

    return &UplinkInformation_g_typePlugin;
}
#endif

RTIBool UplinkInformation_initialize(
    UplinkInformation* sample) {
    return UplinkInformation_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool UplinkInformation_initialize_ex(
    UplinkInformation* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return UplinkInformation_initialize_w_params(
        sample,&allocParams);

}

RTIBool UplinkInformation_initialize_w_params(
    UplinkInformation* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!MessageHeader_initialize_w_params(&sample->Header,
    allocParams)) {
        return RTI_FALSE;
    }
    sample->TimeTick = 0u;

    if (!UplinkStruct_initialize_w_params(&sample->UplinkMessage,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool UplinkInformation_finalize_w_return(
    UplinkInformation* sample)
{
    UplinkInformation_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void UplinkInformation_finalize(
    UplinkInformation* sample)
{

    UplinkInformation_finalize_ex(sample,RTI_TRUE);
}

void UplinkInformation_finalize_ex(
    UplinkInformation* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    UplinkInformation_finalize_w_params(
        sample,&deallocParams);
}

void UplinkInformation_finalize_w_params(
    UplinkInformation* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    MessageHeader_finalize_w_params(&sample->Header,deallocParams);

    UplinkStruct_finalize_w_params(&sample->UplinkMessage,deallocParams);

}

void UplinkInformation_finalize_optional_members(
    UplinkInformation* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool UplinkInformation_copy(
    UplinkInformation* dst,
    const UplinkInformation* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!MessageHeader_copy(
            &dst->Header,(const MessageHeader*)&src->Header)) {
            return RTI_FALSE;
        } 
        if (!RTICdrType_copyUnsignedLong (
            &dst->TimeTick, &src->TimeTick)) { 
            return RTI_FALSE;
        }
        if (!UplinkStruct_copy(
            &dst->UplinkMessage,(const UplinkStruct*)&src->UplinkMessage)) {
            return RTI_FALSE;
        } 

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'UplinkInformation' sequence class.
*/
#define T UplinkInformation
#define TSeq UplinkInformationSeq

#define T_initialize_w_params UplinkInformation_initialize_w_params

#define T_finalize_w_params   UplinkInformation_finalize_w_params
#define T_copy       UplinkInformation_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *DownlinkStructTYPENAME = "DownlinkStruct";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * DownlinkStruct_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode DownlinkStruct_g_tc_Data_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,24L, NULL,NULL);

    static DDS_TypeCode_Member DownlinkStruct_g_tc_members[3]=
    {

        {
            (char *)"AddressKey",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"CRC",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Data",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode DownlinkStruct_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"DownlinkStruct", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            DownlinkStruct_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for DownlinkStruct*/

    if (is_initialized) {
        return &DownlinkStruct_g_tc;
    }

    DownlinkStruct_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    DownlinkStruct_g_tc_Data_array._data._typeCode =(RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    DownlinkStruct_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    DownlinkStruct_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;
    DownlinkStruct_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)& DownlinkStruct_g_tc_Data_array;

    /* Initialize the values for member annotations. */
    DownlinkStruct_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    DownlinkStruct_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
    DownlinkStruct_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    DownlinkStruct_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    DownlinkStruct_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    DownlinkStruct_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    DownlinkStruct_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    DownlinkStruct_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
    DownlinkStruct_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    DownlinkStruct_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    DownlinkStruct_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    DownlinkStruct_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    DownlinkStruct_g_tc._data._sampleAccessInfo =
    DownlinkStruct_get_sample_access_info();
    DownlinkStruct_g_tc._data._typePlugin =
    DownlinkStruct_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &DownlinkStruct_g_tc;
}

#define TSeq DownlinkStructSeq
#define T DownlinkStruct
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *DownlinkStruct_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo DownlinkStruct_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(DownlinkStructSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        DownlinkStructSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &DownlinkStruct_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *DownlinkStruct_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    DownlinkStruct *sample;

    static RTIXCdrMemberAccessInfo DownlinkStruct_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo DownlinkStruct_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &DownlinkStruct_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        DownlinkStruct);
    if (sample == NULL) {
        return NULL;
    }

    DownlinkStruct_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->AddressKey - (char *)sample);

    DownlinkStruct_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->CRC - (char *)sample);

    DownlinkStruct_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Data - (char *)sample);

    DownlinkStruct_g_sampleAccessInfo.memberAccessInfos = 
    DownlinkStruct_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(DownlinkStruct);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            DownlinkStruct_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            DownlinkStruct_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    DownlinkStruct_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    DownlinkStruct_g_sampleAccessInfo.getMemberValuePointerFcn = 
    DownlinkStruct_get_member_value_pointer;

    DownlinkStruct_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &DownlinkStruct_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *DownlinkStruct_get_type_plugin_info()
{
    static RTIXCdrTypePlugin DownlinkStruct_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        DownlinkStruct_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        DownlinkStruct_finalize_w_return,
        NULL
    };

    return &DownlinkStruct_g_typePlugin;
}
#endif

RTIBool DownlinkStruct_initialize(
    DownlinkStruct* sample) {
    return DownlinkStruct_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool DownlinkStruct_initialize_ex(
    DownlinkStruct* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return DownlinkStruct_initialize_w_params(
        sample,&allocParams);

}

RTIBool DownlinkStruct_initialize_w_params(
    DownlinkStruct* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->AddressKey = 0;

    sample->CRC = 0;

    RTICdrType_initArrayUnsafe(sample->Data,
    (24L),
    RTI_CDR_UNSIGNED_SHORT_SIZE);
    return RTI_TRUE;
}

RTIBool DownlinkStruct_finalize_w_return(
    DownlinkStruct* sample)
{
    DownlinkStruct_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void DownlinkStruct_finalize(
    DownlinkStruct* sample)
{

    DownlinkStruct_finalize_ex(sample,RTI_TRUE);
}

void DownlinkStruct_finalize_ex(
    DownlinkStruct* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    DownlinkStruct_finalize_w_params(
        sample,&deallocParams);
}

void DownlinkStruct_finalize_w_params(
    DownlinkStruct* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void DownlinkStruct_finalize_optional_members(
    DownlinkStruct* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool DownlinkStruct_copy(
    DownlinkStruct* dst,
    const DownlinkStruct* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyUnsignedShort (
            &dst->AddressKey, &src->AddressKey)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedShort (
            &dst->CRC, &src->CRC)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyArray(
            dst->Data ,src->Data,(24L), RTI_CDR_UNSIGNED_SHORT_SIZE)) {
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'DownlinkStruct' sequence class.
*/
#define T DownlinkStruct
#define TSeq DownlinkStructSeq

#define T_initialize_w_params DownlinkStruct_initialize_w_params

#define T_finalize_w_params   DownlinkStruct_finalize_w_params
#define T_copy       DownlinkStruct_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *DownlinkInformationTYPENAME = "DownlinkInformation";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * DownlinkInformation_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode DownlinkInformation_g_tc_DownlinkMessage_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((30L),NULL);

    static DDS_TypeCode_Member DownlinkInformation_g_tc_members[4]=
    {

        {
            (char *)"Header",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TimeTick",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"ObjectCount",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"DownlinkMessage",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode DownlinkInformation_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"DownlinkInformation", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            4, /* Number of members */
            DownlinkInformation_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for DownlinkInformation*/

    if (is_initialized) {
        return &DownlinkInformation_g_tc;
    }

    DownlinkInformation_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    DownlinkInformation_g_tc_DownlinkMessage_sequence._data._typeCode = (RTICdrTypeCode *)DownlinkStruct_get_typecode();
    DownlinkInformation_g_tc_DownlinkMessage_sequence._data._sampleAccessInfo = DownlinkStruct_get_sample_seq_access_info();
    DownlinkInformation_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)MessageHeader_get_typecode();
    DownlinkInformation_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong_w_new;
    DownlinkInformation_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong_w_new;
    DownlinkInformation_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)& DownlinkInformation_g_tc_DownlinkMessage_sequence;

    /* Initialize the values for member annotations. */

    DownlinkInformation_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    DownlinkInformation_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    DownlinkInformation_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    DownlinkInformation_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    DownlinkInformation_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    DownlinkInformation_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    DownlinkInformation_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    DownlinkInformation_g_tc_members[2]._annotations._defaultValue._u.ulong_value = 0u;
    DownlinkInformation_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    DownlinkInformation_g_tc_members[2]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    DownlinkInformation_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    DownlinkInformation_g_tc_members[2]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    DownlinkInformation_g_tc._data._sampleAccessInfo =
    DownlinkInformation_get_sample_access_info();
    DownlinkInformation_g_tc._data._typePlugin =
    DownlinkInformation_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &DownlinkInformation_g_tc;
}

#define TSeq DownlinkInformationSeq
#define T DownlinkInformation
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *DownlinkInformation_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo DownlinkInformation_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(DownlinkInformationSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        DownlinkInformationSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &DownlinkInformation_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *DownlinkInformation_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    DownlinkInformation *sample;

    static RTIXCdrMemberAccessInfo DownlinkInformation_g_memberAccessInfos[4] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo DownlinkInformation_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &DownlinkInformation_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        DownlinkInformation);
    if (sample == NULL) {
        return NULL;
    }

    DownlinkInformation_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

    DownlinkInformation_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TimeTick - (char *)sample);

    DownlinkInformation_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->ObjectCount - (char *)sample);

    DownlinkInformation_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->DownlinkMessage - (char *)sample);

    DownlinkInformation_g_sampleAccessInfo.memberAccessInfos = 
    DownlinkInformation_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(DownlinkInformation);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            DownlinkInformation_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            DownlinkInformation_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    DownlinkInformation_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    DownlinkInformation_g_sampleAccessInfo.getMemberValuePointerFcn = 
    DownlinkInformation_get_member_value_pointer;

    DownlinkInformation_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &DownlinkInformation_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *DownlinkInformation_get_type_plugin_info()
{
    static RTIXCdrTypePlugin DownlinkInformation_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        DownlinkInformation_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        DownlinkInformation_finalize_w_return,
        NULL
    };

    return &DownlinkInformation_g_typePlugin;
}
#endif

RTIBool DownlinkInformation_initialize(
    DownlinkInformation* sample) {
    return DownlinkInformation_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool DownlinkInformation_initialize_ex(
    DownlinkInformation* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return DownlinkInformation_initialize_w_params(
        sample,&allocParams);

}

RTIBool DownlinkInformation_initialize_w_params(
    DownlinkInformation* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!MessageHeader_initialize_w_params(&sample->Header,
    allocParams)) {
        return RTI_FALSE;
    }
    sample->TimeTick = 0u;

    sample->ObjectCount = 0u;

    if (allocParams->allocate_memory) {
        if(!DownlinkStructSeq_initialize(&sample->DownlinkMessage )){
            return RTI_FALSE;
        };
        if(!DownlinkStructSeq_set_element_allocation_params(&sample->DownlinkMessage ,allocParams)){
            return RTI_FALSE;
        };
        if(!DownlinkStructSeq_set_absolute_maximum(&sample->DownlinkMessage , (30L))){
            return RTI_FALSE;
        }
        if (!DownlinkStructSeq_set_maximum(&sample->DownlinkMessage, (30L))) {
            return RTI_FALSE;
        }
    } else { 
        if(!DownlinkStructSeq_set_length(&sample->DownlinkMessage, 0)){
            return RTI_FALSE;
        }    
    }
    return RTI_TRUE;
}

RTIBool DownlinkInformation_finalize_w_return(
    DownlinkInformation* sample)
{
    DownlinkInformation_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void DownlinkInformation_finalize(
    DownlinkInformation* sample)
{

    DownlinkInformation_finalize_ex(sample,RTI_TRUE);
}

void DownlinkInformation_finalize_ex(
    DownlinkInformation* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    DownlinkInformation_finalize_w_params(
        sample,&deallocParams);
}

void DownlinkInformation_finalize_w_params(
    DownlinkInformation* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    MessageHeader_finalize_w_params(&sample->Header,deallocParams);

    if(!DownlinkStructSeq_set_element_deallocation_params(
        &sample->DownlinkMessage,deallocParams)){
        return; 
    }
    if(!DownlinkStructSeq_finalize(&sample->DownlinkMessage)){
        return;
    }

}

void DownlinkInformation_finalize_optional_members(
    DownlinkInformation* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool DownlinkInformation_copy(
    DownlinkInformation* dst,
    const DownlinkInformation* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!MessageHeader_copy(
            &dst->Header,(const MessageHeader*)&src->Header)) {
            return RTI_FALSE;
        } 
        if (!RTICdrType_copyUnsignedLong (
            &dst->TimeTick, &src->TimeTick)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedLong (
            &dst->ObjectCount, &src->ObjectCount)) { 
            return RTI_FALSE;
        }
        if (!DownlinkStructSeq_copy(&dst->DownlinkMessage ,
        &src->DownlinkMessage )) {
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'DownlinkInformation' sequence class.
*/
#define T DownlinkInformation
#define TSeq DownlinkInformationSeq

#define T_initialize_w_params DownlinkInformation_initialize_w_params

#define T_finalize_w_params   DownlinkInformation_finalize_w_params
#define T_copy       DownlinkInformation_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *TimeTickStructTYPENAME = "TimeTickStruct";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * TimeTickStruct_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member TimeTickStruct_g_tc_members[2]=
    {

        {
            (char *)"SyncCycle",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TimeTick",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode TimeTickStruct_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"TimeTickStruct", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            TimeTickStruct_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for TimeTickStruct*/

    if (is_initialized) {
        return &TimeTickStruct_g_tc;
    }

    TimeTickStruct_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    TimeTickStruct_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong_w_new;
    TimeTickStruct_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong_w_new;

    /* Initialize the values for member annotations. */
    TimeTickStruct_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    TimeTickStruct_g_tc_members[0]._annotations._defaultValue._u.ulong_value = 0u;
    TimeTickStruct_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    TimeTickStruct_g_tc_members[0]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    TimeTickStruct_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    TimeTickStruct_g_tc_members[0]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    TimeTickStruct_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_ULONG;
    TimeTickStruct_g_tc_members[1]._annotations._defaultValue._u.ulong_value = 0u;
    TimeTickStruct_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_ULONG;
    TimeTickStruct_g_tc_members[1]._annotations._minValue._u.ulong_value = RTIXCdrUnsignedLong_MIN;
    TimeTickStruct_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_ULONG;
    TimeTickStruct_g_tc_members[1]._annotations._maxValue._u.ulong_value = RTIXCdrUnsignedLong_MAX;

    TimeTickStruct_g_tc._data._sampleAccessInfo =
    TimeTickStruct_get_sample_access_info();
    TimeTickStruct_g_tc._data._typePlugin =
    TimeTickStruct_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &TimeTickStruct_g_tc;
}

#define TSeq TimeTickStructSeq
#define T TimeTickStruct
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *TimeTickStruct_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo TimeTickStruct_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(TimeTickStructSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        TimeTickStructSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &TimeTickStruct_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *TimeTickStruct_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    TimeTickStruct *sample;

    static RTIXCdrMemberAccessInfo TimeTickStruct_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo TimeTickStruct_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &TimeTickStruct_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        TimeTickStruct);
    if (sample == NULL) {
        return NULL;
    }

    TimeTickStruct_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->SyncCycle - (char *)sample);

    TimeTickStruct_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TimeTick - (char *)sample);

    TimeTickStruct_g_sampleAccessInfo.memberAccessInfos = 
    TimeTickStruct_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(TimeTickStruct);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            TimeTickStruct_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            TimeTickStruct_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    TimeTickStruct_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    TimeTickStruct_g_sampleAccessInfo.getMemberValuePointerFcn = 
    TimeTickStruct_get_member_value_pointer;

    TimeTickStruct_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &TimeTickStruct_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *TimeTickStruct_get_type_plugin_info()
{
    static RTIXCdrTypePlugin TimeTickStruct_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        TimeTickStruct_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        TimeTickStruct_finalize_w_return,
        NULL
    };

    return &TimeTickStruct_g_typePlugin;
}
#endif

RTIBool TimeTickStruct_initialize(
    TimeTickStruct* sample) {
    return TimeTickStruct_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool TimeTickStruct_initialize_ex(
    TimeTickStruct* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return TimeTickStruct_initialize_w_params(
        sample,&allocParams);

}

RTIBool TimeTickStruct_initialize_w_params(
    TimeTickStruct* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->SyncCycle = 0u;

    sample->TimeTick = 0u;

    return RTI_TRUE;
}

RTIBool TimeTickStruct_finalize_w_return(
    TimeTickStruct* sample)
{
    TimeTickStruct_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void TimeTickStruct_finalize(
    TimeTickStruct* sample)
{

    TimeTickStruct_finalize_ex(sample,RTI_TRUE);
}

void TimeTickStruct_finalize_ex(
    TimeTickStruct* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    TimeTickStruct_finalize_w_params(
        sample,&deallocParams);
}

void TimeTickStruct_finalize_w_params(
    TimeTickStruct* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void TimeTickStruct_finalize_optional_members(
    TimeTickStruct* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool TimeTickStruct_copy(
    TimeTickStruct* dst,
    const TimeTickStruct* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyUnsignedLong (
            &dst->SyncCycle, &src->SyncCycle)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyUnsignedLong (
            &dst->TimeTick, &src->TimeTick)) { 
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'TimeTickStruct' sequence class.
*/
#define T TimeTickStruct
#define TSeq TimeTickStructSeq

#define T_initialize_w_params TimeTickStruct_initialize_w_params

#define T_finalize_w_params   TimeTickStruct_finalize_w_params
#define T_copy       TimeTickStruct_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *TimeTickInformationTYPENAME = "TimeTickInformation";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * TimeTickInformation_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member TimeTickInformation_g_tc_members[2]=
    {

        {
            (char *)"Header",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TimeTickMessage",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode TimeTickInformation_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"TimeTickInformation", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            TimeTickInformation_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for TimeTickInformation*/

    if (is_initialized) {
        return &TimeTickInformation_g_tc;
    }

    TimeTickInformation_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    TimeTickInformation_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)MessageHeader_get_typecode();
    TimeTickInformation_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)TimeTickStruct_get_typecode();

    /* Initialize the values for member annotations. */

    TimeTickInformation_g_tc._data._sampleAccessInfo =
    TimeTickInformation_get_sample_access_info();
    TimeTickInformation_g_tc._data._typePlugin =
    TimeTickInformation_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &TimeTickInformation_g_tc;
}

#define TSeq TimeTickInformationSeq
#define T TimeTickInformation
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *TimeTickInformation_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo TimeTickInformation_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(TimeTickInformationSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        TimeTickInformationSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &TimeTickInformation_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *TimeTickInformation_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    TimeTickInformation *sample;

    static RTIXCdrMemberAccessInfo TimeTickInformation_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo TimeTickInformation_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &TimeTickInformation_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        TimeTickInformation);
    if (sample == NULL) {
        return NULL;
    }

    TimeTickInformation_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

    TimeTickInformation_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TimeTickMessage - (char *)sample);

    TimeTickInformation_g_sampleAccessInfo.memberAccessInfos = 
    TimeTickInformation_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(TimeTickInformation);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            TimeTickInformation_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            TimeTickInformation_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    TimeTickInformation_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    TimeTickInformation_g_sampleAccessInfo.getMemberValuePointerFcn = 
    TimeTickInformation_get_member_value_pointer;

    TimeTickInformation_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &TimeTickInformation_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *TimeTickInformation_get_type_plugin_info()
{
    static RTIXCdrTypePlugin TimeTickInformation_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        TimeTickInformation_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        TimeTickInformation_finalize_w_return,
        NULL
    };

    return &TimeTickInformation_g_typePlugin;
}
#endif

RTIBool TimeTickInformation_initialize(
    TimeTickInformation* sample) {
    return TimeTickInformation_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool TimeTickInformation_initialize_ex(
    TimeTickInformation* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return TimeTickInformation_initialize_w_params(
        sample,&allocParams);

}

RTIBool TimeTickInformation_initialize_w_params(
    TimeTickInformation* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!MessageHeader_initialize_w_params(&sample->Header,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!TimeTickStruct_initialize_w_params(&sample->TimeTickMessage,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool TimeTickInformation_finalize_w_return(
    TimeTickInformation* sample)
{
    TimeTickInformation_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void TimeTickInformation_finalize(
    TimeTickInformation* sample)
{

    TimeTickInformation_finalize_ex(sample,RTI_TRUE);
}

void TimeTickInformation_finalize_ex(
    TimeTickInformation* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    TimeTickInformation_finalize_w_params(
        sample,&deallocParams);
}

void TimeTickInformation_finalize_w_params(
    TimeTickInformation* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    MessageHeader_finalize_w_params(&sample->Header,deallocParams);

    TimeTickStruct_finalize_w_params(&sample->TimeTickMessage,deallocParams);

}

void TimeTickInformation_finalize_optional_members(
    TimeTickInformation* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool TimeTickInformation_copy(
    TimeTickInformation* dst,
    const TimeTickInformation* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!MessageHeader_copy(
            &dst->Header,(const MessageHeader*)&src->Header)) {
            return RTI_FALSE;
        } 
        if (!TimeTickStruct_copy(
            &dst->TimeTickMessage,(const TimeTickStruct*)&src->TimeTickMessage)) {
            return RTI_FALSE;
        } 

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'TimeTickInformation' sequence class.
*/
#define T TimeTickInformation
#define TSeq TimeTickInformationSeq

#define T_initialize_w_params TimeTickInformation_initialize_w_params

#define T_finalize_w_params   TimeTickInformation_finalize_w_params
#define T_copy       TimeTickInformation_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *MFRAttitudeStructTYPENAME = "MFRAttitudeStruct";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * MFRAttitudeStruct_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member MFRAttitudeStruct_g_tc_members[3]=
    {

        {
            (char *)"MFRAntennaRoll",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"MFRAntennaPitch",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"MFRAntennaHeading",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode MFRAttitudeStruct_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"MFRAttitudeStruct", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            MFRAttitudeStruct_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for MFRAttitudeStruct*/

    if (is_initialized) {
        return &MFRAttitudeStruct_g_tc;
    }

    MFRAttitudeStruct_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    MFRAttitudeStruct_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
    MFRAttitudeStruct_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
    MFRAttitudeStruct_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float_w_new;

    /* Initialize the values for member annotations. */
    MFRAttitudeStruct_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[0]._annotations._defaultValue._u.float_value = 0.0f;
    MFRAttitudeStruct_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[0]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    MFRAttitudeStruct_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[0]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    MFRAttitudeStruct_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    MFRAttitudeStruct_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    MFRAttitudeStruct_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    MFRAttitudeStruct_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[2]._annotations._defaultValue._u.float_value = 0.0f;
    MFRAttitudeStruct_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[2]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    MFRAttitudeStruct_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    MFRAttitudeStruct_g_tc_members[2]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    MFRAttitudeStruct_g_tc._data._sampleAccessInfo =
    MFRAttitudeStruct_get_sample_access_info();
    MFRAttitudeStruct_g_tc._data._typePlugin =
    MFRAttitudeStruct_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &MFRAttitudeStruct_g_tc;
}

#define TSeq MFRAttitudeStructSeq
#define T MFRAttitudeStruct
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *MFRAttitudeStruct_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo MFRAttitudeStruct_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(MFRAttitudeStructSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        MFRAttitudeStructSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &MFRAttitudeStruct_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *MFRAttitudeStruct_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    MFRAttitudeStruct *sample;

    static RTIXCdrMemberAccessInfo MFRAttitudeStruct_g_memberAccessInfos[3] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo MFRAttitudeStruct_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &MFRAttitudeStruct_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        MFRAttitudeStruct);
    if (sample == NULL) {
        return NULL;
    }

    MFRAttitudeStruct_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->MFRAntennaRoll - (char *)sample);

    MFRAttitudeStruct_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->MFRAntennaPitch - (char *)sample);

    MFRAttitudeStruct_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->MFRAntennaHeading - (char *)sample);

    MFRAttitudeStruct_g_sampleAccessInfo.memberAccessInfos = 
    MFRAttitudeStruct_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(MFRAttitudeStruct);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            MFRAttitudeStruct_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            MFRAttitudeStruct_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    MFRAttitudeStruct_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    MFRAttitudeStruct_g_sampleAccessInfo.getMemberValuePointerFcn = 
    MFRAttitudeStruct_get_member_value_pointer;

    MFRAttitudeStruct_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &MFRAttitudeStruct_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *MFRAttitudeStruct_get_type_plugin_info()
{
    static RTIXCdrTypePlugin MFRAttitudeStruct_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        MFRAttitudeStruct_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        MFRAttitudeStruct_finalize_w_return,
        NULL
    };

    return &MFRAttitudeStruct_g_typePlugin;
}
#endif

RTIBool MFRAttitudeStruct_initialize(
    MFRAttitudeStruct* sample) {
    return MFRAttitudeStruct_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool MFRAttitudeStruct_initialize_ex(
    MFRAttitudeStruct* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return MFRAttitudeStruct_initialize_w_params(
        sample,&allocParams);

}

RTIBool MFRAttitudeStruct_initialize_w_params(
    MFRAttitudeStruct* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->MFRAntennaRoll = 0.0f;

    sample->MFRAntennaPitch = 0.0f;

    sample->MFRAntennaHeading = 0.0f;

    return RTI_TRUE;
}

RTIBool MFRAttitudeStruct_finalize_w_return(
    MFRAttitudeStruct* sample)
{
    MFRAttitudeStruct_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void MFRAttitudeStruct_finalize(
    MFRAttitudeStruct* sample)
{

    MFRAttitudeStruct_finalize_ex(sample,RTI_TRUE);
}

void MFRAttitudeStruct_finalize_ex(
    MFRAttitudeStruct* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    MFRAttitudeStruct_finalize_w_params(
        sample,&deallocParams);
}

void MFRAttitudeStruct_finalize_w_params(
    MFRAttitudeStruct* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void MFRAttitudeStruct_finalize_optional_members(
    MFRAttitudeStruct* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool MFRAttitudeStruct_copy(
    MFRAttitudeStruct* dst,
    const MFRAttitudeStruct* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyFloat (
            &dst->MFRAntennaRoll, &src->MFRAntennaRoll)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyFloat (
            &dst->MFRAntennaPitch, &src->MFRAntennaPitch)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyFloat (
            &dst->MFRAntennaHeading, &src->MFRAntennaHeading)) { 
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'MFRAttitudeStruct' sequence class.
*/
#define T MFRAttitudeStruct
#define TSeq MFRAttitudeStructSeq

#define T_initialize_w_params MFRAttitudeStruct_initialize_w_params

#define T_finalize_w_params   MFRAttitudeStruct_finalize_w_params
#define T_copy       MFRAttitudeStruct_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *MFRAttitudeInformationTYPENAME = "MFRAttitudeInformation";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * MFRAttitudeInformation_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member MFRAttitudeInformation_g_tc_members[2]=
    {

        {
            (char *)"Header",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"MFRAttitudeMessage",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode MFRAttitudeInformation_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"MFRAttitudeInformation", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            MFRAttitudeInformation_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for MFRAttitudeInformation*/

    if (is_initialized) {
        return &MFRAttitudeInformation_g_tc;
    }

    MFRAttitudeInformation_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    MFRAttitudeInformation_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)MessageHeader_get_typecode();
    MFRAttitudeInformation_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)MFRAttitudeStruct_get_typecode();

    /* Initialize the values for member annotations. */

    MFRAttitudeInformation_g_tc._data._sampleAccessInfo =
    MFRAttitudeInformation_get_sample_access_info();
    MFRAttitudeInformation_g_tc._data._typePlugin =
    MFRAttitudeInformation_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &MFRAttitudeInformation_g_tc;
}

#define TSeq MFRAttitudeInformationSeq
#define T MFRAttitudeInformation
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *MFRAttitudeInformation_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo MFRAttitudeInformation_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(MFRAttitudeInformationSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        MFRAttitudeInformationSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &MFRAttitudeInformation_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *MFRAttitudeInformation_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    MFRAttitudeInformation *sample;

    static RTIXCdrMemberAccessInfo MFRAttitudeInformation_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo MFRAttitudeInformation_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &MFRAttitudeInformation_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        MFRAttitudeInformation);
    if (sample == NULL) {
        return NULL;
    }

    MFRAttitudeInformation_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

    MFRAttitudeInformation_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->MFRAttitudeMessage - (char *)sample);

    MFRAttitudeInformation_g_sampleAccessInfo.memberAccessInfos = 
    MFRAttitudeInformation_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(MFRAttitudeInformation);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            MFRAttitudeInformation_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            MFRAttitudeInformation_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    MFRAttitudeInformation_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    MFRAttitudeInformation_g_sampleAccessInfo.getMemberValuePointerFcn = 
    MFRAttitudeInformation_get_member_value_pointer;

    MFRAttitudeInformation_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &MFRAttitudeInformation_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *MFRAttitudeInformation_get_type_plugin_info()
{
    static RTIXCdrTypePlugin MFRAttitudeInformation_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        MFRAttitudeInformation_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        MFRAttitudeInformation_finalize_w_return,
        NULL
    };

    return &MFRAttitudeInformation_g_typePlugin;
}
#endif

RTIBool MFRAttitudeInformation_initialize(
    MFRAttitudeInformation* sample) {
    return MFRAttitudeInformation_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool MFRAttitudeInformation_initialize_ex(
    MFRAttitudeInformation* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return MFRAttitudeInformation_initialize_w_params(
        sample,&allocParams);

}

RTIBool MFRAttitudeInformation_initialize_w_params(
    MFRAttitudeInformation* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!MessageHeader_initialize_w_params(&sample->Header,
    allocParams)) {
        return RTI_FALSE;
    }
    if (!MFRAttitudeStruct_initialize_w_params(&sample->MFRAttitudeMessage,
    allocParams)) {
        return RTI_FALSE;
    }
    return RTI_TRUE;
}

RTIBool MFRAttitudeInformation_finalize_w_return(
    MFRAttitudeInformation* sample)
{
    MFRAttitudeInformation_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void MFRAttitudeInformation_finalize(
    MFRAttitudeInformation* sample)
{

    MFRAttitudeInformation_finalize_ex(sample,RTI_TRUE);
}

void MFRAttitudeInformation_finalize_ex(
    MFRAttitudeInformation* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    MFRAttitudeInformation_finalize_w_params(
        sample,&deallocParams);
}

void MFRAttitudeInformation_finalize_w_params(
    MFRAttitudeInformation* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    MessageHeader_finalize_w_params(&sample->Header,deallocParams);

    MFRAttitudeStruct_finalize_w_params(&sample->MFRAttitudeMessage,deallocParams);

}

void MFRAttitudeInformation_finalize_optional_members(
    MFRAttitudeInformation* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool MFRAttitudeInformation_copy(
    MFRAttitudeInformation* dst,
    const MFRAttitudeInformation* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!MessageHeader_copy(
            &dst->Header,(const MessageHeader*)&src->Header)) {
            return RTI_FALSE;
        } 
        if (!MFRAttitudeStruct_copy(
            &dst->MFRAttitudeMessage,(const MFRAttitudeStruct*)&src->MFRAttitudeMessage)) {
            return RTI_FALSE;
        } 

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'MFRAttitudeInformation' sequence class.
*/
#define T MFRAttitudeInformation
#define TSeq MFRAttitudeInformationSeq

#define T_initialize_w_params MFRAttitudeInformation_initialize_w_params

#define T_finalize_w_params   MFRAttitudeInformation_finalize_w_params
#define T_copy       MFRAttitudeInformation_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *TestDDSConnectionTYPENAME = "TestDDSConnection";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * TestDDSConnection_get_typecode(void)
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member TestDDSConnection_g_tc_members[1]=
    {

        {
            (char *)"TestParam",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode TestDDSConnection_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"TestDDSConnection", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            TestDDSConnection_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for TestDDSConnection*/

    if (is_initialized) {
        return &TestDDSConnection_g_tc;
    }

    TestDDSConnection_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    TestDDSConnection_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort_w_new;

    /* Initialize the values for member annotations. */
    TestDDSConnection_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
    TestDDSConnection_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
    TestDDSConnection_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
    TestDDSConnection_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
    TestDDSConnection_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
    TestDDSConnection_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

    TestDDSConnection_g_tc._data._sampleAccessInfo =
    TestDDSConnection_get_sample_access_info();
    TestDDSConnection_g_tc._data._typePlugin =
    TestDDSConnection_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &TestDDSConnection_g_tc;
}

#define TSeq TestDDSConnectionSeq
#define T TestDDSConnection
#include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
#undef T
#undef TSeq

RTIXCdrSampleAccessInfo *TestDDSConnection_get_sample_seq_access_info()
{
    static RTIXCdrSampleAccessInfo TestDDSConnection_g_seqSampleAccessInfo = {
        RTI_XCDR_TYPE_BINDING_CPP, \
        {sizeof(TestDDSConnectionSeq),0,0,0}, \
        RTI_XCDR_FALSE, \
        DDS_Sequence_get_member_value_pointer, \
        TestDDSConnectionSeq_set_member_element_count, \
        NULL, \
        NULL, \
        NULL \
    };

    return &TestDDSConnection_g_seqSampleAccessInfo;
}

RTIXCdrSampleAccessInfo *TestDDSConnection_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    TestDDSConnection *sample;

    static RTIXCdrMemberAccessInfo TestDDSConnection_g_memberAccessInfos[1] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo TestDDSConnection_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &TestDDSConnection_g_sampleAccessInfo;
    }

    RTIXCdrHeap_allocateStruct(
        &sample, 
        TestDDSConnection);
    if (sample == NULL) {
        return NULL;
    }

    TestDDSConnection_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) ((char *)&sample->TestParam - (char *)sample);

    TestDDSConnection_g_sampleAccessInfo.memberAccessInfos = 
    TestDDSConnection_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(TestDDSConnection);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            TestDDSConnection_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            TestDDSConnection_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    TestDDSConnection_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
    RTI_XCDR_TRUE;

    TestDDSConnection_g_sampleAccessInfo.getMemberValuePointerFcn = 
    TestDDSConnection_get_member_value_pointer;

    TestDDSConnection_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_CPP ;

    RTIXCdrHeap_freeStruct(sample);
    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &TestDDSConnection_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *TestDDSConnection_get_type_plugin_info()
{
    static RTIXCdrTypePlugin TestDDSConnection_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        TestDDSConnection_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        TestDDSConnection_finalize_w_return,
        NULL
    };

    return &TestDDSConnection_g_typePlugin;
}
#endif

RTIBool TestDDSConnection_initialize(
    TestDDSConnection* sample) {
    return TestDDSConnection_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool TestDDSConnection_initialize_ex(
    TestDDSConnection* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return TestDDSConnection_initialize_w_params(
        sample,&allocParams);

}

RTIBool TestDDSConnection_initialize_w_params(
    TestDDSConnection* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    sample->TestParam = 0;

    return RTI_TRUE;
}

RTIBool TestDDSConnection_finalize_w_return(
    TestDDSConnection* sample)
{
    TestDDSConnection_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void TestDDSConnection_finalize(
    TestDDSConnection* sample)
{

    TestDDSConnection_finalize_ex(sample,RTI_TRUE);
}

void TestDDSConnection_finalize_ex(
    TestDDSConnection* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    TestDDSConnection_finalize_w_params(
        sample,&deallocParams);
}

void TestDDSConnection_finalize_w_params(
    TestDDSConnection* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void TestDDSConnection_finalize_optional_members(
    TestDDSConnection* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool TestDDSConnection_copy(
    TestDDSConnection* dst,
    const TestDDSConnection* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyUnsignedShort (
            &dst->TestParam, &src->TestParam)) { 
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (const std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'TestDDSConnection' sequence class.
*/
#define T TestDDSConnection
#define TSeq TestDDSConnectionSeq

#define T_initialize_w_params TestDDSConnection_initialize_w_params

#define T_finalize_w_params   TestDDSConnection_finalize_w_params
#define T_copy       TestDDSConnection_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

#ifndef NDDS_STANDALONE_TYPE
namespace rti { 
    namespace xcdr {
        const RTIXCdrTypeCode * type_code<MessageHeader>::get() 
        {
            return (const RTIXCdrTypeCode *) MessageHeader_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<AirThreatStruct>::get() 
        {
            return (const RTIXCdrTypeCode *) AirThreatStruct_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<AirThreatInformation>::get() 
        {
            return (const RTIXCdrTypeCode *) AirThreatInformation_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<InterceptorStruct>::get() 
        {
            return (const RTIXCdrTypeCode *) InterceptorStruct_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<InterceptorInformation>::get() 
        {
            return (const RTIXCdrTypeCode *) InterceptorInformation_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<UplinkStruct>::get() 
        {
            return (const RTIXCdrTypeCode *) UplinkStruct_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<UplinkInformation>::get() 
        {
            return (const RTIXCdrTypeCode *) UplinkInformation_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<DownlinkStruct>::get() 
        {
            return (const RTIXCdrTypeCode *) DownlinkStruct_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<DownlinkInformation>::get() 
        {
            return (const RTIXCdrTypeCode *) DownlinkInformation_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<TimeTickStruct>::get() 
        {
            return (const RTIXCdrTypeCode *) TimeTickStruct_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<TimeTickInformation>::get() 
        {
            return (const RTIXCdrTypeCode *) TimeTickInformation_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<MFRAttitudeStruct>::get() 
        {
            return (const RTIXCdrTypeCode *) MFRAttitudeStruct_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<MFRAttitudeInformation>::get() 
        {
            return (const RTIXCdrTypeCode *) MFRAttitudeInformation_get_typecode();
        }

        const RTIXCdrTypeCode * type_code<TestDDSConnection>::get() 
        {
            return (const RTIXCdrTypeCode *) TestDDSConnection_get_typecode();
        }

    } 
}
#endif
