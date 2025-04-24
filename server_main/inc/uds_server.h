/****************************************************************************************************
 *  File Name           : uds_server.h
 *  Description         : Header file for the uds server
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/
#ifndef UDS_SERVER_H
#define UDS_SERVER_H
#include "uds_server_cfg.h"
#include "uds_types.h"
#include "uds_session_cfg.h"
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
#include "uds_securityLvl_cfg.h"
#endif
#include "uds_sid_cfg.h"
#include "uds_session_cfg.h"
#include "uds_supplier_manufacturer_cfg.h"
#include "uds_securityLvl_cfg.h"
#include "uds_NR_Handler.h"
#include "uds_helpers.h"
#include "uds_server_q.h"

#include "CanTp.h"

/**
 * @brief Initializes the UDS server
 * @note Sets session to Default Session.
 * @note Sets Security Level to Default if it is enabled through configurations.
 * @note Maps Manufacturer Specific checks and Supplier Specific checks functions if enabled.
 */
void UDS_serverInit(void);

/**
 * @brief Handles the request of the UDS client
 * @param request pointer to the request to be handled by the server
 */
void UDS_RequestIndication(UDS_REQ_t* request);

/**
 * @brief Callback funciton for the reset back to the default session
 */
void UDS_defaultSessionResetCallBack();

/**
 * @brief This funciton is used to send the response over any communication bus
 * @brief The function should be implemented in the uds_wrapper to be complient with any need standard (AUTOSAR,openBSW)
 * @param response The response prepared by the uds server
 * @return 1/0 = True/False = Success/Fail
 */
uint8_t UDS_sendResponse(UDS_RES_t *response);

#endif
