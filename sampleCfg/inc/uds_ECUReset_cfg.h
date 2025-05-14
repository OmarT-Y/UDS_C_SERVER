/****************************************************************************************************
 *  File Name           : uds_ECUReset_cfg.h
 *  Description         : Header file for the UDS ECU Reset Configurations
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 23-2-2025 File Creation
 ****************************************************************************************************/


#ifndef UDS_ECU_RESET_CFG_H
#define UDS_ECU_RESET_CFG_H

#include "uds_types.h"
#include "uds_securityLvl_cfg.h"
#include "uds_session_cfg.h"
#include "uds_helpers.h"
#include "uds_server_cfg.h"
#include "SID_0x11_ECUReset_types.h"

extern const UDS_ResetType_t SupportedResets[];

uint8_t UDS_sendResponse(UDS_RES_t* response);

/*************************************************************************Start Of Generation*************************************************************************/
#define UDS_HARD_RESET_ID                                      0x01
#define UDS_NUMBER_OF_SUPPORTED_RESETS                         1

extern void reset_ecu();
#define UDS_RESET_0x01_FUNCTION                                reset_ecu                         

/*For each Reset a function prototype should be generated*/
/*************************************************************************End Of Generation*************************************************************************/
#endif