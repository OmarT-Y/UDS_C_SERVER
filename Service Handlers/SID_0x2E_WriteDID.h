/****************************************************************************************************
 *  File Name           : SID_0x2E_WriteDID.h
 *  Description         : Header file for the service 0x2E Write DID Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#ifndef SID_2E_WRITE_DID_HANDLER_FILE_H
#define SID_2E_WRITE_DID_HANDLER_FILE_H

#include "uds_session_cfg.h"
#include "uds_server_cfg.h"
#include "uds_types.h"
#include "uds_NR_Handler.h"
#include "uds_DID_cfg.h"

#define SID_2E_POS_RES_CODE 0x6E
#define MAX_REQUEST_LEN 8

UDS_RESPONSE_SUPPRESSION_t SID_2E_WriteDID_Handler(UDS_REQ_t *request, UDS_RES_t *response, UDS_Server_t *server);
UDS_SubFunctionCheckResult_t SID_2E_WriteDID_subFunctionChecks(uint8_t subFunction, UDS_Server_t *server);

#endif