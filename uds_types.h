/****************************************************************************************************
 *  File Name           : uds_types.h
 *  Description         : Header file containing the mandatory types for the uds application layer
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_TYPES_H
#define UDS_TYPES_H


//TODO : Change to the platform specific file
//TODO : include the std boolean type

/* Includes */
#include <inttypes.h>
#include "uds_server_cfg.h"


//TODO : Compiler options to specify minimum enum size

/**
 * @brief Identifies the message type/format
 * @param UDS_MType_Diagnostics Diagnostics Message
 * @param UDS_MType_RemoteDiagnostics Remote Diagnostics Message
 * @param UDS_MType_SecureDiagnostics Secure Diagnostics Message
 * @param UDS_MType_SecureRemoteDiagnostics Secure Remote Diagnostics Message
 */
typedef enum
{
    UDS_MType_Diagnostics,
    UDS_MType_RemoteDiagnostics,
    UDS_MType_SecureDiagnostics,
    UDS_MType_SecureRemoteDiagnostics
}UDS_A_MType_t;

/**
 * @brief Type for the uds addresses used in UDS_SDU
 */
typedef uint16_t UDS_A_ADD_t;

/**
 * @brief Addressing types for Target Address
 * @param UDS_A_TA_PHYSICAL Physical Address
 * @param UDS_A_TA_FUNCTIONAL Functional Address
 */
typedef enum
{
    UDS_A_TA_PHYSICAL,
    UDS_A_TA_FUNCTIONAL
}UDS_A_TA_TYPE_t;

/**
 * @brief UDS SDU Block
 * @note Parameters ordered according to ISO Standard 
 * @param msgType SDU message type
 * @param srcAdd Source Address
 * @param trgAdd Target Address
 * @param trgAddType Target Address type Physical/Functional
 * @param remoteAdd Remote Address
 * @param udsDataLen Payload Data Length
 * @param data Payload Data
 */
typedef struct 
{
    UDS_A_MType_t       msgType;
    UDS_A_ADD_t         srcAdd;
    UDS_A_ADD_t         trgAdd;
    UDS_A_TA_TYPE_t     trgAddType;
    UDS_A_ADD_t         remoteAdd;
    uint16_t            udsDataLen;
    uint8_t*            data;
}UDS_SDU_t;

/** 
 * @brief  UDS Request Message
 */
typedef UDS_SDU_t UDS_REQ_t;
/**
 * @brief UDS Response Message
 */
typedef UDS_SDU_t UDS_RES_t;


/** 
 * @brief UDS session context 
 * @note parameters change according to iso-14229 version
 * @param SessionID Session ID
 * @param p2_server_max
 * @param p2_server_star_max
 * @param supportedService Flags/mask for Services which are supported in this session
 */
typedef struct
{
    uint8_t     SessionID;
    uint16_t    p2_server_max;
    uint16_t    p2_server_star_max; 
    uint32_t    supportedService[6];                   
}UDS_Session_t;

#ifdef UDS_SECURITY_LEVEL_SUPPORTED
/** 
 * @brief UDS Security Level context
 * @param SecurityLvlID Security Level ID
 * @param supportedService Flags/mask for Services which are supported by this security level
 */
typedef struct
{
    uint8_t     SecurityLvlID;
    uint32_t    supportedService[6]; 
}UDS_SecurityLevel_t;
#endif

/** 
 * @brief UDS Server context
 * @param activeSession current active session
 * @param sessionTimeout Time in ms after which the server should go back to the default session if not already there
 * @param activeSecLvl current security level
 */
typedef struct 
{
    UDS_Session_t*          activeSession;
    uint16_t                sessionTimeout;
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    UDS_SecurityLevel_t*    activeSecLvl;
#endif
}UDS_Server_t;

typedef enum{
    UDS_NO_SUPPRESS_RESPONSE,
    UDS_SUPPRESS_RESPONSE
}UDS_RESPONSE_SUPPRESSION_t;

/**
 * @brief UDS_ServiceHandlerPtr_t type (pointer to function)
 */
typedef UDS_RESPONSE_SUPPRESSION_t (*UDS_ServiceHandlerPtr_t)(UDS_REQ_t *,UDS_RES_t *,UDS_Server_t *);

typedef enum
{
    UDS_SUB_FUNC_E_OK,
    UDS_SUB_FUNC_NO_ACTIVE_SESSION,
    UDS_SUB_FUNC_NO_SECURITY_LEVEL,
    UDS_SUB_FUNC_REQUEST_SEQUENCE_FAIL, 
    UDS_SUB_FUNC_NO_SUB_FUNC
}UDS_SubFunctionCheckResult_t;

/**
 *@brief Pointer to function that checks if the sub function is supported in active session
 */
typedef UDS_SubFunctionCheckResult_t (*UDS_SubFuncChecksPtr_t)(uint8_t,UDS_Server_t *);

#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
//TODO: define the type for the supplier check pointer to function
typedef UDS_RESPONSE_SUPPRESSION_t (*UDS_SupplierCheckFuncPtr_t)(UDS_REQ_t *,UDS_RES_t *,UDS_Server_t *);
#endif

#ifdef UDS_MANUFACTURER_CHECK_SUPPORTED
//TODO: define the type for the manufacturer check pointer to function
typedef UDS_RESPONSE_SUPPRESSION_t (*UDS_ManufacCheckFuncPtr_t)(UDS_REQ_t *,UDS_RES_t *,UDS_Server_t *);
#endif

/** 
 * @brief UDS SID Record context 
 * @param sid Service ID
 * @param minLen Minimum length of Service PDU
 * @param handler Handler for the Service
 * @param hasSubFunc Flag for whether this Service has subfunctions or not
 */
typedef struct 
{
    uint8_t                                         sid;
    uint8_t                                         minLen;
    UDS_ServiceHandlerPtr_t                         handler;
    //TODO: change to bool habibi
    uint8_t                                         hasSubFunc;
    UDS_SubFuncChecksPtr_t                          subfuncChecskPtr;
    uint32_t                                        supportedSubFunc[4]; 
}UDS_SID_RECORD_t;

typedef struct 
{
    uint16_t ID;
    uint32_t supportedSessions[4];
    uint32_t supportedSecuritryLevels[2];
    uint8_t dataLen;
    uint8_t isSingleBlock;
    uint8_t isReadOnly;
    /*TODO: change to bool and add starting address*/ 
}UDS_DID;


#endif