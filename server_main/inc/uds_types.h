/****************************************************************************************************
 *  File Name           : uds_types.h
 *  Description         : Header file containing the mandatory types for the uds application layer
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_TYPES_H
#define UDS_TYPES_H


/*TODO : Change to the platform specific file
TODO : include the std boolean type*/

/* Includes */
#include <inttypes.h>
#include "uds_server_cfg.h"

#define REQUEST_SID_INDEX                               0U
#define RESPONSE_SID_INDEX                              0U
#define REQUEST_SUB_FUNCTION_INDEX                      1U

#define CHECK_REQUEST_SUPPRESS_BIT(request)     (request->data[1] & (1<<7))
#define CHECK_ARRAY_BIT_OVER_32(array,bitNum)   ((array[(bitNum)>>5]) & (1<<((bitNum)&32))) 




/*TODO : Compiler options to specify minimum enum size*/

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

/*
 * @brief Structure to hold information about the funciton being supported in which session and which security levels
 * @param supportedSessions Pointer to an array of sessions that support The function to this session
 * @param supportedSessionsLen Length of the array of sessions 
 * @param supportedSecurityLvl Pointer to an array of security levels that supports transition to this session
 * @param supportedSecurityLvlLen Length of the array of security levels
*/
typedef struct
{
    const uint8_t*            supportedSessions;
    const uint8_t             supportedSessionsLen;
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
    const uint8_t*            supportedSecurityLvl;
    const uint8_t             supportedSecurityLvlLen;
#endif
}UDS_SubFunctionSupportivity_t;
/** 
 * @brief UDS session context 
 * @note parameters change according to iso-14229 version
 * @param SessionID Session ID
 * @param p2_server_max
 * @param p2_server_star_max
 * @param supportedService Flags/mask for Services which are supported in this session
 * @param SupportivityStruct Structure to hold information about the funciton being supported in which session and which security levels
 */
typedef struct
{
    uint8_t                             SessionID;
    uint16_t                            p2_server_max;
    uint16_t                            p2_server_star_max; 
    uint32_t                            supportedService[6];
    UDS_SubFunctionSupportivity_t*      SupportivityStruct;
}UDS_Session_t;


/**
 * @brief Pointer to the function that generates the security seed
 * @note Returns pointer to the security seed
 * @note the function must retain the last generated seed for key check later
*/
typedef uint8_t* (*securitySeedFuncPtr)(void);
/**
 * @brief Pointer to the function that checks the key
 * @param key pointer to the key to be checked
 * @note Returns True/False = Pass/Fail
*/
typedef uint8_t (*securityKeyCheckFuncPtr)(const uint8_t* key);
 /** 
  * @brief UDS Security Level context
  * @param SecurityLvlID Security Level ID
  * @param Status Security level status
  * @param supportedService Flags/mask for Services which are supported by this security level
  * @param SupportivityStruct Structure to hold information about the funciton being supported in which session and which security levels
  * @param seedLen The length of the seed used in the security level
  * @param keyLen The length of the key used in the security level
  * @param seedFunc Pointer to the funciton that generates the seed
  * @param keyCheckFunc pointer to the funciton that checks the key
  */
 typedef struct
 {
    uint8_t                                         SecurityLvlID;
    uint32_t                                        supportedService[6];
    const UDS_SubFunctionSupportivity_t*            SupportivityStruct;
    uint8_t                                         seedLen;
    uint8_t                                         keyLen;
    securitySeedFuncPtr                             seedFunc;
    securityKeyCheckFuncPtr                         keyCheckFunc;
 }UDS_SecurityLevel_t;

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

/** 
 * @brief Determines whether the responce will be suppressed or not
 * @param UDS_NO_SUPPRESS_RESPONSE Response will be sent normally
 * @param UDS_SUPPRESS_RESPONSE Response will be suppressed
 */
typedef enum{
    UDS_NO_SUPPRESS_RESPONSE,
    UDS_SUPPRESS_RESPONSE
}UDS_RESPONSE_SUPPRESSION_t;

/**
 * @brief UDS_ServiceHandlerPtr_t type (pointer to function)
 */
typedef UDS_RESPONSE_SUPPRESSION_t (*UDS_ServiceHandlerPtr_t)(UDS_REQ_t *,UDS_RES_t *,UDS_Server_t *);

/**
 * @brief Determines what SID_XX_getSubFunctSuppStruct returns
 * @param UDS_SUB_FUNC_E_OK No problem occured 
 * @param UDS_SUB_FUNC_NO_ACTIVE_SESSION Theres no active session
 * @param UDS_SUB_FUNC_NO_SECURITY_LEVEL Theres no active security level
 * @param UDS_SUB_FUNC_REQUEST_SEQUENCE_FAIL The sequence of serving the sub function is not correct
 * @param UDS_SUB_FUNC_NO_SUB_FUNC Sub function not supported
 */
typedef enum
{
    UDS_SUB_FUNC_E_OK,
    UDS_SUB_FUNC_NO_ACTIVE_SESSION,
    UDS_SUB_FUNC_REQUEST_SEQUENCE_FAIL, 
    UDS_SUB_FUNC_NO_SUB_FUNC
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
    ,
    UDS_SUB_FUNC_NO_SECURITY_LEVEL
#endif
}UDS_SubFunctionCheckResult_t;


#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
/*TODO: define the type for the supplier check pointer to function*/
/**
 *@brief Pointer to function that does the supplier specific checks
 */
typedef UDS_RESPONSE_SUPPRESSION_t (*UDS_SupplierCheckFuncPtr_t)(UDS_REQ_t *,UDS_RES_t *,UDS_Server_t *);
#endif

#ifdef UDS_MANUFACTURER_CHECK_SUPPORTED
/*TODO: define the type for the manufacturer check pointer to function*/
/**
 * @brief Pointer to function that does the Manufacturer specific checks
 */
typedef UDS_RESPONSE_SUPPRESSION_t (*UDS_ManufacCheckFuncPtr_t)(UDS_REQ_t *,UDS_RES_t *,UDS_Server_t *);
#endif


/**
* @brief Pointer to function that gets the sub function supportivity structure
*/
typedef const UDS_SubFunctionSupportivity_t* (*UDS_SubFunctionSuppStructFuncPtr_t)(uint8_t);

/** 
 * @brief UDS SID Record context 
 * @param sid Service ID
 * @param minLen Minimum length of Service PDU
 * @param handler Handler for the Service
 * @param hasSubFunc Flag for whether this Service has subfunctions or not
 * @param subfuncSupportivityStructGet Pointer to function that gets the sub function supportivity structure
 */

typedef struct 
{
    uint8_t                                         sid;
    uint8_t                                         minLen;
    UDS_ServiceHandlerPtr_t                         handler;
    /*TODO: change to bool*/
    uint8_t                                         hasSubFunc;
    UDS_SubFunctionSuppStructFuncPtr_t              subfuncSupportivityStructGet;                                 
}UDS_SID_RECORD_t;


#endif