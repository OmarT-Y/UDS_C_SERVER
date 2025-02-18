/****************************************************************************************************
 *  File Name           : SID_0x3E_SessionCtrl.h
 *  Description         : Header file for the service 0x3E Tester Present Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#ifndef SID_3E_SESSTION_CTRL_HANDLER_FILE_H
#define SID_3E_SESSTION_CTRL_HANDLER_FILE_H

#include "uds_session_cfg.h"
#include "uds_server_cfg.h"
#include "uds_types.h"
#include "uds_NR_Handler.h"

#define RESET_TIMER_FUNC resetTimer
#define SID_3E_POS_RES_CODE 0x7E

UDS_RESPONSE_SUPPRESSION_t SID_3E_TesetPresent_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server);
UDS_SubFunctionCheckResult_t SID_3E_TesterPresent_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server);

#endif