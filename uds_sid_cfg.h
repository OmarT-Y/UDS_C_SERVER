/****************************************************************************************************
 *  File Name           : uds_sid_cfg.h
 *  Description         : Header file for the UDS server supported SIDs
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_SID_CFG_H
#define UDS_SID_CFG_H

#include "uds_types.h"


/**
 * @brief Returns the record of the requested service
 * @param sid The requested Service ID 
 */
UDS_SID_RECORD_t* getServiceRecord(uint8_t sid);


/* Supported Services */
#define SID_10_DIAG_SESSION_CTRL_ENABLED
#define SID_3E_TESTER_PRESENT_ENABLED
#define SID_22_READ_DID_ENABLED
#define SID_2E_WRITE_DID_ENABLED
#define SID_27_SECURITY_ACCESS_ENABLED
#define SID_31_ROUTINE_CTRL_ENABLED


//TODO: Change to STD_ON STD_OFF
 

/* Service parameters for SID 0x10 */
#ifdef SID_10_DIAG_SESSION_CTRL_ENABLED
/**
 * @brief Handler for Diagnosis Session Ctrl Service - SID 0x10
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
void SID_10_Handler(UDS_REQ_t* request,UDS_RES_t * response,UDS_Server_t * server);
UDS_SubFunctionCheckResult_t SID_10_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server);
#define SID_10_DIAG_SESSION_CTRL                    0x10
#define SID_10_DIAG_SESSION_CTRL_MIN_LEN            0x1
#define SID_10_DIAG_SESSION_CTRL_HAS_SUB_FUNC       1
#define SID_10_DIAG_SESSION_CTRL_SUB_FUNC_MASK      9
#endif

/* Service parameters for SID 0x3E */
#ifdef SID_3E_TESTER_PRESENT_ENABLED
/**
 * @brief Handler for Tester Present Service - SID 0x3E
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
void SID_3E_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
UDS_SubFunctionCheckResult_t SID_3E_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server);
#define SID_3E_TESTER_PRESENT                       0x3E
#define SID_3E_TESTER_PRESENT_MIN_LEN               0x1
#define SID_3E_TESTER_PRESENT_HAS_SUB_FUNC          0 /*not sure*/
#define SID_3E_TESTER_PRESENT_SUB_FUNC_MASK         9
#endif

/* Service parameters for SID 0x22 */
#ifdef SID_22_READ_DID_ENABLED
/**
 * @brief Handler for Read DID Service - SID 0x22
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
void SID_22_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
UDS_SubFunctionCheckResult_t SID_22_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server);
#define SID_22_READ_DID                             0x22
#define SID_22_READ_DID_MIN_LEN                     0x1
#define SID_22_READ_DID_HAS_SUB_FUNC                0 /*not sure*/
#define SID_22_READ_DID_SUB_FUNC_MASK               9
#endif

/* Service parameters for SID 0x2E */
#ifdef SID_2E_WRITE_DID_ENABLED
/**
 * @brief Handler for Write DID Service - SID 0x2E
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
void SID_2E_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
UDS_SubFunctionCheckResult_t SID_2E_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server);
#define SID_2E_WRITE_DID                            0x2E
#define SID_2E_WRITE_DID_MIN_LEN                    0x1
#define SID_2E_WRITE_DID_HAS_SUB_FUNC               0 /*not sure*/
#define SID_2E_WRITE_DID_SUB_FUNC_MASK              9
#endif

/* Service parameters for SID 0x27 */
#ifdef SID_27_SECURITY_ACCESS_ENABLED
/**
 * @brief Handler for Security Access Service - SID 0x27
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
void SID_27_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
UDS_SubFunctionCheckResult_t SID_27_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server);
#define SID_27_SECURITY_ACCESS                      0x27
#define SID_27_SECURITY_ACCESS_MIN_LEN              0x1
#define SID_27_SECURITY_ACCESS_HAS_SUB_FUNC         1
#define SID_27_SECURITY_ACCESS_SUB_FUNC_MASK        9
#endif

/* Service parameters for SID 0x31 */
#ifdef SID_31_ROUTINE_CTRL_ENABLED
/**
 * @brief Handler for Tester Present Service - SID 0x31
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
void SID_31_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
UDS_SubFunctionCheckResult_t SID_31_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server);
#define SID_31_ROUTINE_CTRL                         0x31
#define SID_31_ROUTINE_CTRL_MIN_LEN                 0x1
#define SID_31_ROUTINE_CTRL_HAS_SUB_FUNC            1
#define SID_31_ROUTINE_CTRL_SUB_FUNC_MASK           9
#endif

#endif