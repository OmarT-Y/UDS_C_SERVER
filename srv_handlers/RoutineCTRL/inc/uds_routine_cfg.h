/****************************************************************************************************
 *  File Name           : uds_routine_cfg.h
 *  Description         : Header file for the UDS routines 
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 22-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_ROUTINE_CFG_H
#define UDS_ROUTINE_CFG_H

#include "uds_sid_cfg.h"
#include "uds_helpers.h"
#include "uds_routines_types.h"

/*************************************************************************Start of Generation*************************************************************************/
#define UDS_NUM_OF_ROUTINES 1U

/*Routine FF00 Functions*/
uint8_t rid_FF00_start(uint8_t* data,uint8_t dataLen);
uint8_t rid_FF00_checkRes(uint8_t* data,uint8_t dataLen);

/**************************************************************************End of Generation**************************************************************************/

#define UDS_START_ROUTINE_SUBFUNC 0x01
#define UDS_STOP_ROUTINE_SUBFUNC 0x02
#define UDS_REQUEST_ROUTINE_RESULTS_SUBFUNC 0x03


extern UDS_RID_RECORD_t UDS_Routines[];

#endif
