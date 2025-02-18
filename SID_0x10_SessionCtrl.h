/****************************************************************************************************
 *  File Name           : SID_10_SessionCtrl.c
 *  Description         : Header file for the service 0x10 Diagnostic Session Control Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#ifndef SID_10_SESSTION_CTRL_HANDLER_FILE_H
#define SID_10_SESSTION_CTRL_HANDLER_FILE_H

#include "uds_session_cfg.h"
#include "uds_server_cfg.h"
#include "uds_types.h"
#include "uds_NR_Handler.h"

#define SID_10_POS_RES_CODE 0x50
UDS_RESPONSE_SUPPRESSION_t SID_10_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server);
UDS_SubFunctionCheckResult_t SID_10_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server);

#endif