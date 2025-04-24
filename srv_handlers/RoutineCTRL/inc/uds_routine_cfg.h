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
#define UDS_NUM_OF_ROUTINES 2U

/*Routine 0001 Functions*/
uint8_t rid_0001_start(uint8_t* data,uint8_t dataLen);
uint8_t rid_0001_stop(uint8_t* data,uint8_t dataLen);
UDS_RoutineStatus_t rid_0001_checkRes(uint8_t* data,uint8_t dataLen);
/*Routine 0002 Functions*/
uint8_t rid_0002_start(uint8_t* data,uint8_t dataLen);
uint8_t rid_0002_stop(uint8_t* data,uint8_t dataLen);
UDS_RoutineStatus_t rid_0002_checkRes(uint8_t* data,uint8_t dataLen);
/**************************************************************************End of Generation**************************************************************************/

#define UDS_START_ROUTINE_SUBFUNC 0x01
#define UDS_STOP_ROUTINE_SUBFUNC 0x02
#define UDS_REQUEST_ROUTINE_RESULTS_SUBFUNC 0x03


extern UDS_RID_RECORD_t UDS_Routines[];

#endif
