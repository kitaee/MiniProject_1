#pragma once


/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from DDSSim.idl
using RTI Code Generator (rtiddsgen) version 3.1.2.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef DDSSimPlugin_744907754_h
#define DDSSimPlugin_744907754_h

#include "DDSSim.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

extern "C"{

    #define MessageHeaderPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define MessageHeaderPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MessageHeaderPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define MessageHeaderPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MessageHeaderPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MessageHeader*
    MessageHeaderPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MessageHeader*
    MessageHeaderPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MessageHeader*
    MessageHeaderPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MessageHeaderPluginSupport_copy_data(
        MessageHeader *out,
        const MessageHeader *in);

    NDDSUSERDllExport extern void 
    MessageHeaderPluginSupport_destroy_data_w_params(
        MessageHeader *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MessageHeaderPluginSupport_destroy_data_ex(
        MessageHeader *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MessageHeaderPluginSupport_destroy_data(
        MessageHeader *sample);

    NDDSUSERDllExport extern void 
    MessageHeaderPluginSupport_print_data(
        const MessageHeader *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    MessageHeaderPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    MessageHeaderPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    MessageHeaderPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    MessageHeaderPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    MessageHeaderPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        MessageHeader *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    MessageHeaderPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MessageHeader *out,
        const MessageHeader *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    MessageHeaderPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MessageHeader *sample); 

    NDDSUSERDllExport extern RTIBool
    MessageHeaderPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const MessageHeader *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    MessageHeaderPlugin_deserialize_from_cdr_buffer(
        MessageHeader *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    MessageHeaderPlugin_data_to_string(
        const MessageHeader *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    MessageHeaderPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MessageHeaderPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MessageHeaderPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MessageHeaderPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MessageHeaderPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MessageHeader ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * MessageHeaderPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    MessageHeaderPlugin_new(void);

    NDDSUSERDllExport extern void
    MessageHeaderPlugin_delete(struct PRESTypePlugin *);

    #define AirThreatStructPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define AirThreatStructPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define AirThreatStructPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define AirThreatStructPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define AirThreatStructPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern AirThreatStruct*
    AirThreatStructPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern AirThreatStruct*
    AirThreatStructPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern AirThreatStruct*
    AirThreatStructPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    AirThreatStructPluginSupport_copy_data(
        AirThreatStruct *out,
        const AirThreatStruct *in);

    NDDSUSERDllExport extern void 
    AirThreatStructPluginSupport_destroy_data_w_params(
        AirThreatStruct *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    AirThreatStructPluginSupport_destroy_data_ex(
        AirThreatStruct *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    AirThreatStructPluginSupport_destroy_data(
        AirThreatStruct *sample);

    NDDSUSERDllExport extern void 
    AirThreatStructPluginSupport_print_data(
        const AirThreatStruct *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    AirThreatStructPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    AirThreatStructPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    AirThreatStructPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    AirThreatStructPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    AirThreatStructPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        AirThreatStruct *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    AirThreatStructPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        AirThreatStruct *out,
        const AirThreatStruct *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    AirThreatStructPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const AirThreatStruct *sample); 

    NDDSUSERDllExport extern RTIBool
    AirThreatStructPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const AirThreatStruct *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    AirThreatStructPlugin_deserialize_from_cdr_buffer(
        AirThreatStruct *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    AirThreatStructPlugin_data_to_string(
        const AirThreatStruct *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    AirThreatStructPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    AirThreatStructPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    AirThreatStructPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    AirThreatStructPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    AirThreatStructPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        AirThreatStruct ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * AirThreatStructPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    AirThreatStructPlugin_new(void);

    NDDSUSERDllExport extern void
    AirThreatStructPlugin_delete(struct PRESTypePlugin *);

    #define AirThreatInformationPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define AirThreatInformationPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define AirThreatInformationPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define AirThreatInformationPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define AirThreatInformationPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern AirThreatInformation*
    AirThreatInformationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern AirThreatInformation*
    AirThreatInformationPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern AirThreatInformation*
    AirThreatInformationPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    AirThreatInformationPluginSupport_copy_data(
        AirThreatInformation *out,
        const AirThreatInformation *in);

    NDDSUSERDllExport extern void 
    AirThreatInformationPluginSupport_destroy_data_w_params(
        AirThreatInformation *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    AirThreatInformationPluginSupport_destroy_data_ex(
        AirThreatInformation *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    AirThreatInformationPluginSupport_destroy_data(
        AirThreatInformation *sample);

    NDDSUSERDllExport extern void 
    AirThreatInformationPluginSupport_print_data(
        const AirThreatInformation *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    AirThreatInformationPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    AirThreatInformationPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    AirThreatInformationPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    AirThreatInformationPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    AirThreatInformationPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        AirThreatInformation *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    AirThreatInformationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        AirThreatInformation *out,
        const AirThreatInformation *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    AirThreatInformationPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const AirThreatInformation *sample); 

    NDDSUSERDllExport extern RTIBool
    AirThreatInformationPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const AirThreatInformation *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    AirThreatInformationPlugin_deserialize_from_cdr_buffer(
        AirThreatInformation *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    AirThreatInformationPlugin_data_to_string(
        const AirThreatInformation *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    AirThreatInformationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    AirThreatInformationPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    AirThreatInformationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    AirThreatInformationPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    AirThreatInformationPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        AirThreatInformation ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * AirThreatInformationPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    AirThreatInformationPlugin_new(void);

    NDDSUSERDllExport extern void
    AirThreatInformationPlugin_delete(struct PRESTypePlugin *);

    #define InterceptorStructPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define InterceptorStructPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define InterceptorStructPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define InterceptorStructPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define InterceptorStructPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern InterceptorStruct*
    InterceptorStructPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern InterceptorStruct*
    InterceptorStructPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern InterceptorStruct*
    InterceptorStructPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    InterceptorStructPluginSupport_copy_data(
        InterceptorStruct *out,
        const InterceptorStruct *in);

    NDDSUSERDllExport extern void 
    InterceptorStructPluginSupport_destroy_data_w_params(
        InterceptorStruct *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    InterceptorStructPluginSupport_destroy_data_ex(
        InterceptorStruct *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    InterceptorStructPluginSupport_destroy_data(
        InterceptorStruct *sample);

    NDDSUSERDllExport extern void 
    InterceptorStructPluginSupport_print_data(
        const InterceptorStruct *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    InterceptorStructPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    InterceptorStructPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    InterceptorStructPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    InterceptorStructPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    InterceptorStructPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        InterceptorStruct *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    InterceptorStructPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        InterceptorStruct *out,
        const InterceptorStruct *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    InterceptorStructPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const InterceptorStruct *sample); 

    NDDSUSERDllExport extern RTIBool
    InterceptorStructPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const InterceptorStruct *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    InterceptorStructPlugin_deserialize_from_cdr_buffer(
        InterceptorStruct *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    InterceptorStructPlugin_data_to_string(
        const InterceptorStruct *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    InterceptorStructPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    InterceptorStructPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    InterceptorStructPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    InterceptorStructPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    InterceptorStructPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        InterceptorStruct ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * InterceptorStructPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    InterceptorStructPlugin_new(void);

    NDDSUSERDllExport extern void
    InterceptorStructPlugin_delete(struct PRESTypePlugin *);

    #define InterceptorInformationPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define InterceptorInformationPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define InterceptorInformationPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define InterceptorInformationPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define InterceptorInformationPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern InterceptorInformation*
    InterceptorInformationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern InterceptorInformation*
    InterceptorInformationPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern InterceptorInformation*
    InterceptorInformationPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    InterceptorInformationPluginSupport_copy_data(
        InterceptorInformation *out,
        const InterceptorInformation *in);

    NDDSUSERDllExport extern void 
    InterceptorInformationPluginSupport_destroy_data_w_params(
        InterceptorInformation *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    InterceptorInformationPluginSupport_destroy_data_ex(
        InterceptorInformation *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    InterceptorInformationPluginSupport_destroy_data(
        InterceptorInformation *sample);

    NDDSUSERDllExport extern void 
    InterceptorInformationPluginSupport_print_data(
        const InterceptorInformation *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    InterceptorInformationPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    InterceptorInformationPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    InterceptorInformationPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    InterceptorInformationPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    InterceptorInformationPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        InterceptorInformation *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    InterceptorInformationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        InterceptorInformation *out,
        const InterceptorInformation *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    InterceptorInformationPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const InterceptorInformation *sample); 

    NDDSUSERDllExport extern RTIBool
    InterceptorInformationPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const InterceptorInformation *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    InterceptorInformationPlugin_deserialize_from_cdr_buffer(
        InterceptorInformation *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    InterceptorInformationPlugin_data_to_string(
        const InterceptorInformation *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    InterceptorInformationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    InterceptorInformationPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    InterceptorInformationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    InterceptorInformationPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    InterceptorInformationPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        InterceptorInformation ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * InterceptorInformationPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    InterceptorInformationPlugin_new(void);

    NDDSUSERDllExport extern void
    InterceptorInformationPlugin_delete(struct PRESTypePlugin *);

    #define UplinkStructPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define UplinkStructPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define UplinkStructPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define UplinkStructPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define UplinkStructPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern UplinkStruct*
    UplinkStructPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern UplinkStruct*
    UplinkStructPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern UplinkStruct*
    UplinkStructPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    UplinkStructPluginSupport_copy_data(
        UplinkStruct *out,
        const UplinkStruct *in);

    NDDSUSERDllExport extern void 
    UplinkStructPluginSupport_destroy_data_w_params(
        UplinkStruct *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    UplinkStructPluginSupport_destroy_data_ex(
        UplinkStruct *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    UplinkStructPluginSupport_destroy_data(
        UplinkStruct *sample);

    NDDSUSERDllExport extern void 
    UplinkStructPluginSupport_print_data(
        const UplinkStruct *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    UplinkStructPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    UplinkStructPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    UplinkStructPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    UplinkStructPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    UplinkStructPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        UplinkStruct *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    UplinkStructPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        UplinkStruct *out,
        const UplinkStruct *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    UplinkStructPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const UplinkStruct *sample); 

    NDDSUSERDllExport extern RTIBool
    UplinkStructPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const UplinkStruct *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    UplinkStructPlugin_deserialize_from_cdr_buffer(
        UplinkStruct *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    UplinkStructPlugin_data_to_string(
        const UplinkStruct *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    UplinkStructPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    UplinkStructPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    UplinkStructPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    UplinkStructPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    UplinkStructPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        UplinkStruct ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * UplinkStructPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    UplinkStructPlugin_new(void);

    NDDSUSERDllExport extern void
    UplinkStructPlugin_delete(struct PRESTypePlugin *);

    #define UplinkInformationPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define UplinkInformationPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define UplinkInformationPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define UplinkInformationPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define UplinkInformationPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern UplinkInformation*
    UplinkInformationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern UplinkInformation*
    UplinkInformationPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern UplinkInformation*
    UplinkInformationPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    UplinkInformationPluginSupport_copy_data(
        UplinkInformation *out,
        const UplinkInformation *in);

    NDDSUSERDllExport extern void 
    UplinkInformationPluginSupport_destroy_data_w_params(
        UplinkInformation *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    UplinkInformationPluginSupport_destroy_data_ex(
        UplinkInformation *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    UplinkInformationPluginSupport_destroy_data(
        UplinkInformation *sample);

    NDDSUSERDllExport extern void 
    UplinkInformationPluginSupport_print_data(
        const UplinkInformation *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    UplinkInformationPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    UplinkInformationPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    UplinkInformationPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    UplinkInformationPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    UplinkInformationPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        UplinkInformation *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    UplinkInformationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        UplinkInformation *out,
        const UplinkInformation *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    UplinkInformationPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const UplinkInformation *sample); 

    NDDSUSERDllExport extern RTIBool
    UplinkInformationPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const UplinkInformation *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    UplinkInformationPlugin_deserialize_from_cdr_buffer(
        UplinkInformation *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    UplinkInformationPlugin_data_to_string(
        const UplinkInformation *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    UplinkInformationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    UplinkInformationPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    UplinkInformationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    UplinkInformationPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    UplinkInformationPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        UplinkInformation ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * UplinkInformationPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    UplinkInformationPlugin_new(void);

    NDDSUSERDllExport extern void
    UplinkInformationPlugin_delete(struct PRESTypePlugin *);

    #define DownlinkStructPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define DownlinkStructPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define DownlinkStructPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define DownlinkStructPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define DownlinkStructPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern DownlinkStruct*
    DownlinkStructPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern DownlinkStruct*
    DownlinkStructPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern DownlinkStruct*
    DownlinkStructPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    DownlinkStructPluginSupport_copy_data(
        DownlinkStruct *out,
        const DownlinkStruct *in);

    NDDSUSERDllExport extern void 
    DownlinkStructPluginSupport_destroy_data_w_params(
        DownlinkStruct *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    DownlinkStructPluginSupport_destroy_data_ex(
        DownlinkStruct *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    DownlinkStructPluginSupport_destroy_data(
        DownlinkStruct *sample);

    NDDSUSERDllExport extern void 
    DownlinkStructPluginSupport_print_data(
        const DownlinkStruct *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    DownlinkStructPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    DownlinkStructPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    DownlinkStructPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    DownlinkStructPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    DownlinkStructPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        DownlinkStruct *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    DownlinkStructPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        DownlinkStruct *out,
        const DownlinkStruct *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    DownlinkStructPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const DownlinkStruct *sample); 

    NDDSUSERDllExport extern RTIBool
    DownlinkStructPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const DownlinkStruct *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    DownlinkStructPlugin_deserialize_from_cdr_buffer(
        DownlinkStruct *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    DownlinkStructPlugin_data_to_string(
        const DownlinkStruct *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    DownlinkStructPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    DownlinkStructPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    DownlinkStructPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    DownlinkStructPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    DownlinkStructPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        DownlinkStruct ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * DownlinkStructPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    DownlinkStructPlugin_new(void);

    NDDSUSERDllExport extern void
    DownlinkStructPlugin_delete(struct PRESTypePlugin *);

    #define DownlinkInformationPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define DownlinkInformationPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define DownlinkInformationPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define DownlinkInformationPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define DownlinkInformationPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern DownlinkInformation*
    DownlinkInformationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern DownlinkInformation*
    DownlinkInformationPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern DownlinkInformation*
    DownlinkInformationPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    DownlinkInformationPluginSupport_copy_data(
        DownlinkInformation *out,
        const DownlinkInformation *in);

    NDDSUSERDllExport extern void 
    DownlinkInformationPluginSupport_destroy_data_w_params(
        DownlinkInformation *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    DownlinkInformationPluginSupport_destroy_data_ex(
        DownlinkInformation *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    DownlinkInformationPluginSupport_destroy_data(
        DownlinkInformation *sample);

    NDDSUSERDllExport extern void 
    DownlinkInformationPluginSupport_print_data(
        const DownlinkInformation *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    DownlinkInformationPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    DownlinkInformationPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    DownlinkInformationPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    DownlinkInformationPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    DownlinkInformationPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        DownlinkInformation *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    DownlinkInformationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        DownlinkInformation *out,
        const DownlinkInformation *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    DownlinkInformationPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const DownlinkInformation *sample); 

    NDDSUSERDllExport extern RTIBool
    DownlinkInformationPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const DownlinkInformation *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    DownlinkInformationPlugin_deserialize_from_cdr_buffer(
        DownlinkInformation *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    DownlinkInformationPlugin_data_to_string(
        const DownlinkInformation *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    DownlinkInformationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    DownlinkInformationPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    DownlinkInformationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    DownlinkInformationPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    DownlinkInformationPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        DownlinkInformation ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * DownlinkInformationPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    DownlinkInformationPlugin_new(void);

    NDDSUSERDllExport extern void
    DownlinkInformationPlugin_delete(struct PRESTypePlugin *);

    #define TimeTickStructPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define TimeTickStructPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define TimeTickStructPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define TimeTickStructPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define TimeTickStructPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern TimeTickStruct*
    TimeTickStructPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern TimeTickStruct*
    TimeTickStructPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TimeTickStruct*
    TimeTickStructPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    TimeTickStructPluginSupport_copy_data(
        TimeTickStruct *out,
        const TimeTickStruct *in);

    NDDSUSERDllExport extern void 
    TimeTickStructPluginSupport_destroy_data_w_params(
        TimeTickStruct *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    TimeTickStructPluginSupport_destroy_data_ex(
        TimeTickStruct *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TimeTickStructPluginSupport_destroy_data(
        TimeTickStruct *sample);

    NDDSUSERDllExport extern void 
    TimeTickStructPluginSupport_print_data(
        const TimeTickStruct *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    TimeTickStructPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    TimeTickStructPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    TimeTickStructPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    TimeTickStructPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    TimeTickStructPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        TimeTickStruct *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    TimeTickStructPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        TimeTickStruct *out,
        const TimeTickStruct *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    TimeTickStructPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const TimeTickStruct *sample); 

    NDDSUSERDllExport extern RTIBool
    TimeTickStructPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const TimeTickStruct *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    TimeTickStructPlugin_deserialize_from_cdr_buffer(
        TimeTickStruct *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    TimeTickStructPlugin_data_to_string(
        const TimeTickStruct *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    TimeTickStructPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    TimeTickStructPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    TimeTickStructPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TimeTickStructPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    TimeTickStructPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        TimeTickStruct ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * TimeTickStructPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    TimeTickStructPlugin_new(void);

    NDDSUSERDllExport extern void
    TimeTickStructPlugin_delete(struct PRESTypePlugin *);

    #define TimeTickInformationPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define TimeTickInformationPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define TimeTickInformationPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define TimeTickInformationPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define TimeTickInformationPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern TimeTickInformation*
    TimeTickInformationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern TimeTickInformation*
    TimeTickInformationPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TimeTickInformation*
    TimeTickInformationPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    TimeTickInformationPluginSupport_copy_data(
        TimeTickInformation *out,
        const TimeTickInformation *in);

    NDDSUSERDllExport extern void 
    TimeTickInformationPluginSupport_destroy_data_w_params(
        TimeTickInformation *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    TimeTickInformationPluginSupport_destroy_data_ex(
        TimeTickInformation *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TimeTickInformationPluginSupport_destroy_data(
        TimeTickInformation *sample);

    NDDSUSERDllExport extern void 
    TimeTickInformationPluginSupport_print_data(
        const TimeTickInformation *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    TimeTickInformationPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    TimeTickInformationPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    TimeTickInformationPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    TimeTickInformationPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    TimeTickInformationPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        TimeTickInformation *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    TimeTickInformationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        TimeTickInformation *out,
        const TimeTickInformation *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    TimeTickInformationPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const TimeTickInformation *sample); 

    NDDSUSERDllExport extern RTIBool
    TimeTickInformationPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const TimeTickInformation *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    TimeTickInformationPlugin_deserialize_from_cdr_buffer(
        TimeTickInformation *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    TimeTickInformationPlugin_data_to_string(
        const TimeTickInformation *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    TimeTickInformationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    TimeTickInformationPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    TimeTickInformationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TimeTickInformationPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    TimeTickInformationPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        TimeTickInformation ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * TimeTickInformationPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    TimeTickInformationPlugin_new(void);

    NDDSUSERDllExport extern void
    TimeTickInformationPlugin_delete(struct PRESTypePlugin *);

    #define MFRAttitudeStructPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define MFRAttitudeStructPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MFRAttitudeStructPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define MFRAttitudeStructPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MFRAttitudeStructPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MFRAttitudeStruct*
    MFRAttitudeStructPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MFRAttitudeStruct*
    MFRAttitudeStructPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MFRAttitudeStruct*
    MFRAttitudeStructPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MFRAttitudeStructPluginSupport_copy_data(
        MFRAttitudeStruct *out,
        const MFRAttitudeStruct *in);

    NDDSUSERDllExport extern void 
    MFRAttitudeStructPluginSupport_destroy_data_w_params(
        MFRAttitudeStruct *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MFRAttitudeStructPluginSupport_destroy_data_ex(
        MFRAttitudeStruct *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MFRAttitudeStructPluginSupport_destroy_data(
        MFRAttitudeStruct *sample);

    NDDSUSERDllExport extern void 
    MFRAttitudeStructPluginSupport_print_data(
        const MFRAttitudeStruct *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    MFRAttitudeStructPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    MFRAttitudeStructPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    MFRAttitudeStructPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    MFRAttitudeStructPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    MFRAttitudeStructPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        MFRAttitudeStruct *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    MFRAttitudeStructPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MFRAttitudeStruct *out,
        const MFRAttitudeStruct *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    MFRAttitudeStructPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MFRAttitudeStruct *sample); 

    NDDSUSERDllExport extern RTIBool
    MFRAttitudeStructPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const MFRAttitudeStruct *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    MFRAttitudeStructPlugin_deserialize_from_cdr_buffer(
        MFRAttitudeStruct *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    MFRAttitudeStructPlugin_data_to_string(
        const MFRAttitudeStruct *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    MFRAttitudeStructPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MFRAttitudeStructPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MFRAttitudeStructPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MFRAttitudeStructPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MFRAttitudeStructPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MFRAttitudeStruct ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * MFRAttitudeStructPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    MFRAttitudeStructPlugin_new(void);

    NDDSUSERDllExport extern void
    MFRAttitudeStructPlugin_delete(struct PRESTypePlugin *);

    #define MFRAttitudeInformationPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define MFRAttitudeInformationPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MFRAttitudeInformationPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define MFRAttitudeInformationPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MFRAttitudeInformationPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MFRAttitudeInformation*
    MFRAttitudeInformationPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MFRAttitudeInformation*
    MFRAttitudeInformationPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MFRAttitudeInformation*
    MFRAttitudeInformationPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MFRAttitudeInformationPluginSupport_copy_data(
        MFRAttitudeInformation *out,
        const MFRAttitudeInformation *in);

    NDDSUSERDllExport extern void 
    MFRAttitudeInformationPluginSupport_destroy_data_w_params(
        MFRAttitudeInformation *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MFRAttitudeInformationPluginSupport_destroy_data_ex(
        MFRAttitudeInformation *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MFRAttitudeInformationPluginSupport_destroy_data(
        MFRAttitudeInformation *sample);

    NDDSUSERDllExport extern void 
    MFRAttitudeInformationPluginSupport_print_data(
        const MFRAttitudeInformation *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    MFRAttitudeInformationPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    MFRAttitudeInformationPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    MFRAttitudeInformationPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    MFRAttitudeInformationPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    MFRAttitudeInformationPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        MFRAttitudeInformation *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    MFRAttitudeInformationPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MFRAttitudeInformation *out,
        const MFRAttitudeInformation *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    MFRAttitudeInformationPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MFRAttitudeInformation *sample); 

    NDDSUSERDllExport extern RTIBool
    MFRAttitudeInformationPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const MFRAttitudeInformation *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    MFRAttitudeInformationPlugin_deserialize_from_cdr_buffer(
        MFRAttitudeInformation *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    MFRAttitudeInformationPlugin_data_to_string(
        const MFRAttitudeInformation *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    MFRAttitudeInformationPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MFRAttitudeInformationPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MFRAttitudeInformationPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MFRAttitudeInformationPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MFRAttitudeInformationPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MFRAttitudeInformation ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * MFRAttitudeInformationPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    MFRAttitudeInformationPlugin_new(void);

    NDDSUSERDllExport extern void
    MFRAttitudeInformationPlugin_delete(struct PRESTypePlugin *);

    #define TestDDSConnectionPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define TestDDSConnectionPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define TestDDSConnectionPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define TestDDSConnectionPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define TestDDSConnectionPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern TestDDSConnection*
    TestDDSConnectionPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern TestDDSConnection*
    TestDDSConnectionPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TestDDSConnection*
    TestDDSConnectionPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    TestDDSConnectionPluginSupport_copy_data(
        TestDDSConnection *out,
        const TestDDSConnection *in);

    NDDSUSERDllExport extern void 
    TestDDSConnectionPluginSupport_destroy_data_w_params(
        TestDDSConnection *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    TestDDSConnectionPluginSupport_destroy_data_ex(
        TestDDSConnection *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TestDDSConnectionPluginSupport_destroy_data(
        TestDDSConnection *sample);

    NDDSUSERDllExport extern void 
    TestDDSConnectionPluginSupport_print_data(
        const TestDDSConnection *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    TestDDSConnectionPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    TestDDSConnectionPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    TestDDSConnectionPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    TestDDSConnectionPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    TestDDSConnectionPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        TestDDSConnection *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    TestDDSConnectionPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        TestDDSConnection *out,
        const TestDDSConnection *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    TestDDSConnectionPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const TestDDSConnection *sample); 

    NDDSUSERDllExport extern RTIBool
    TestDDSConnectionPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const TestDDSConnection *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    TestDDSConnectionPlugin_deserialize_from_cdr_buffer(
        TestDDSConnection *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    TestDDSConnectionPlugin_data_to_string(
        const TestDDSConnection *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    TestDDSConnectionPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    TestDDSConnectionPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    TestDDSConnectionPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TestDDSConnectionPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    TestDDSConnectionPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        TestDDSConnection ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * TestDDSConnectionPlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    TestDDSConnectionPlugin_new(void);

    NDDSUSERDllExport extern void
    TestDDSConnectionPlugin_delete(struct PRESTypePlugin *);

}

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* DDSSimPlugin_744907754_h */

