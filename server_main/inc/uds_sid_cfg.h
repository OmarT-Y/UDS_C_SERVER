/****************************************************************************************************
 *  File Name           : uds_sid_cfg.h
 *  Description         : Header file for the UDS server supported SIDs
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_SID_CFG_H
#define UDS_SID_CFG_H

#include "uds_types.h"
#include "uds_NR_Handler.h"

/**
 * @brief Returns the record of the requested service
 * @param sid The requested Service ID 
 */
extern UDS_SID_RECORD_t UDS_a_supportedSID_Record[];

/*Start of Generation*/
/* Supported Services */
#define SID_10_DIAG_SESSION_CTRL_ENABLED
#define SID_3E_TESTER_PRESENT_ENABLED
#define SID_22_READ_DID_ENABLED
#define SID_2E_WRITE_DID_ENABLED
#define SID_27_SECURITY_ACCESS_ENABLED
#define SID_31_ROUTINE_CTRL_ENABLED
#define SID_11_ECU_RESET_ENABLED
#define SID_34_REQUEST_DOWNLOAD_ENABLED
#define SID_36_TRANSFER_DATA_ENABLED
#define SID_37_TRANSFER_REQUEST_EXIT_ENABLED
#define UDS_NUMBER_OF_SUPPORTED_SERVICES            10

/*TODO: Change to STD_ON STD_OFF*/
 

/* Service parameters for SID 0x10 */
#ifdef SID_10_DIAG_SESSION_CTRL_ENABLED
/**
 * @brief Handler for Diagnosis Session Ctrl Service - SID 0x10
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_10_Handler(UDS_REQ_t* request,UDS_RES_t * response,UDS_Server_t * server);
/**
 * @brief Applies subFunction checks specific to SID_0x10
 * @param subFunction The Sub Function to be checked on
 * @param server The current server
 */
const UDS_SubFunctionSupportivity_t* SID_10_getSubFunctSuppStruct(uint8_t subFunction);
#define SID_10_DIAG_SESSION_CTRL                                0x10
#define SID_10_POS_RES_CODE                                     0x50
#define SID_10_DIAG_SESSION_CTRL_MIN_LEN                        0x2
#define SID_10_DIAG_SESSION_CTRL_HAS_SUB_FUNC                   1
#define SID_10_DIAG_SESSION_CTRL_NUMBER_OF_SUPPORTED_SUB_FUNC   0x0
#endif

/* Service parameters for SID 0x3E */
#ifdef SID_3E_TESTER_PRESENT_ENABLED
/**
 * @brief Handler for Tester Present Service - SID 0x3E
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_3E_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
/**
 * @brief Applies subFunction checks specific to SID_0x3E
 * @param subFunction The Sub Function to be checked on
 * @param server The current server
 */
const UDS_SubFunctionSupportivity_t* SID_3E_getSubFunctSuppStruct(uint8_t subFunction);
#define SID_3E_TESTER_PRESENT                                   0x3E
#define SID_3E_POS_RES_CODE                                     0x7E
#define SID_3E_TESTER_PRESENT_MIN_LEN                           0x1
#define SID_3E_TESTER_PRESENT_HAS_SUB_FUNC                      0 /*not sure*/
#define SID_3E_TESTER_PRESENT_NUMBER_OF_SUPPORTED_SUB_FUNC      0x0
#endif

/* Service parameters for SID 0x22 */
#ifdef SID_22_READ_DID_ENABLED
/**
 * @brief Handler for Read DID Service - SID 0x22
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_22_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
/**
 * @brief Applies subFunction checks specific to SID_0x22
 * @param subFunction The Sub Function to be checked on
 * @param server The current server
 */
const UDS_SubFunctionSupportivity_t* SID_22_getSubFunctSuppStruct(uint8_t subFunction);
#define SID_22_READ_DID                                         0x22
#define SID_22_POS_RES_CODE                                     0x62
#define SID_22_READ_DID_MIN_LEN                                 0x1
#define SID_22_READ_DID_HAS_SUB_FUNC                            0 /*not sure*/
#define SID_22_READ_DID_NUMBER_OF_SUPPORTED_SUB_FUNC            0x0
#endif

/* Service parameters for SID 0x2E */
#ifdef SID_2E_WRITE_DID_ENABLED
/**
 * @brief Handler for Write DID Service - SID 0x2E
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_2E_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
/**
 * @brief Applies subFunction checks specific to SID_0x2E
 * @param subFunction The Sub Function to be checked on
 * @param server The current server
 */
const UDS_SubFunctionSupportivity_t* SID_2E_getSubFunctSuppStruct(uint8_t subFunction);
#define SID_2E_WRITE_DID                                        0x2E
#define SID_2E_POS_RES_CODE                                     0x6E
#define SID_2E_WRITE_DID_MIN_LEN                                0x1
#define SID_2E_WRITE_DID_HAS_SUB_FUNC                           0 /*not sure*/
#define SID_2E_WRITE_DID_NUMBER_OF_SUPPORTED_SUB_FUNC           0x0
#endif

/* Service parameters for SID 0x27 */
#ifdef SID_27_SECURITY_ACCESS_ENABLED
/**
 * @brief Handler for Security Access Service - SID 0x27
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_27_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
/**
 * @brief Applies subFunction checks specific to SID_0x27
 * @param subFunction The Sub Function to be checked on
 * @param server The current server
 */
const UDS_SubFunctionSupportivity_t* SID_27_getSubFunctSuppStruct(uint8_t subFunction);
#define SID_27_SECURITY_ACCESS                                  0x27
#define SID_27_POS_RES_CODE                                     0x67
#define SID_27_SECURITY_ACCESS_MIN_LEN                          0x1
#define SID_27_SECURITY_ACCESS_HAS_SUB_FUNC                     1
#define SID_27_SECURITY_ACCESS_NUMBER_OF_SUPPORTED_SUB_FUNC     0x0
#endif

/* Service parameters for SID 0x31 */
#ifdef SID_31_ROUTINE_CTRL_ENABLED
/**
 * @brief Handler for Tester Present Service - SID 0x31
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_31_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
/**
 * @brief Applies subFunction checks specific to SID_0x31
 * @param subFunction The Sub Function to be checked on
 * @param server The current server
 */
const UDS_SubFunctionSupportivity_t* SID_31_getSubFunctSuppStruct(uint8_t subFunction);
#define SID_31_ROUTINE_CTRL                                     0x31
#define SID_31_POS_RES_CODE                                     0x71
#define SID_31_ROUTINE_CTRL_MIN_LEN                             0x1
#define SID_31_ROUTINE_CTRL_HAS_SUB_FUNC                        1
#define SID_31_ROUTINE_CTRL_NUMBER_OF_SUPPORTED_SUB_FUNC        0x0
#endif


/* Service parameters for SID 0x11 */
#define SID_11_ECU_RESET		                                0x11
#define SID_11_POS_RES_CODE                                     0x40
#define SID_11_ECU_RESET_MIN_LEN		                        0x2
#define SID_11_ECU_RESET_HAS_SUB_FUNC		                    1
#define SID_11_ECU_RESET_NUMBER_OF_SUPPORTED_SUB_FUNC           0x0
/**
 * @brief Handler for ECU Reset Service - SID 0x11
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_11_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server);
/**
 * @brief Applies subFunction checks specific to SID_0x11
 * @param subFunction The Sub Function to be checked on
 * @param server The current server
 */
const UDS_SubFunctionSupportivity_t* SID_11_getSubFunctSuppStruct(uint8_t subFunction);


/* Service parameters for SID 0x34 */
#ifdef SID_34_REQUEST_DOWNLOAD_ENABLED
/**
 * @brief Handler for Request Download Service - SID 0x34
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_34_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);

#define SID_34_REQUEST_DOWNLOAD									0x34
#define SID_34_POS_RES_CODE                                     0x74
#define SID_34_REQUEST_DOWNLOAD_HAS_SUB_FUNC 					0
#define SID_34_REQUEST_DOWNLOAD_MIN_LEN							5 //TODO: check this
#endif

/* Service parameters for SID 0x34 */
#ifdef SID_36_TRANSFER_DATA_ENABLED

#define SID_36_TRANSFER_DATA									0x36
#define SID_36_POS_RES_CODE                                     0x76
#define SID_36_TRANSFER_DATA_HAS_SUB_FUNC    					0
#define SID_36_TRANSFER_DATA_MIN_LEN							3 

/**
 * @brief Handler for Request Download Service - SID 0x36
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_36_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
/**
 * @brief Applies subFunction checks specific to SID_0x36
 * @param subFunction The Sub Function to be checked on
 * @param server The current server
 */
const UDS_SubFunctionSupportivity_t* SID_36_getSubFunctSuppStruct(uint8_t subFunction);
#define SID_36_POS_RES_CODE                                     0x76
#endif

/* Service parameters for SID 0x34 */
#ifdef SID_37_TRANSFER_REQUEST_EXIT_ENABLED

#define SID_37_REQUEST_TRANSFER_EXIT                             0x37
#define SID_37_REQUEST_TRANSFER_EXIT_MIN_LEN                     0x1
#define SID_37_TRANSFER_DATA_HAS_SUB_FUNC                        0
/**
 * @brief Handler for Request Transfer Exit Service - SID 0x37
 * @param request Incoming UDS Request
 * @param response The response to be sent back to the UDS client
 * @param server The current UDS server
 */
UDS_RESPONSE_SUPPRESSION_t SID_37_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);

#define SID_37_POS_RES_CODE                                     0x77
#endif
/*End of generation*/

#endif
