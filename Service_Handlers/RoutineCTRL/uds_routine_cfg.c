/****************************************************************************************************
 *  File Name           : uds_routine_cfg.c
 *  Description         : Source file for the UDS routines 
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/


 #include "../../../UDS/Service_Handlers/RoutineCTRL/uds_routine_cfg.h"

 #define START_SEC_UDS_SEC_CONST_DATA
 #include "uds_memMap.h"
 /*************************************************************************Start of Generation*************************************************************************/
 static const uint8_t rid_0001_sessions[] = {0, 1};
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED 
 static const uint8_t rid_0001_security[] = {0, 1};
 #endif
 static const UDS_SubFunctionSupportivity_t rid_0001_supportivity = 
 {
     .supportedSessions = rid_0001_sessions,
     .supportedSessionsLen = 2U
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED
     ,
     .supportedSecurityLvl = rid_0001_security,
     .supportedSecurityLvlLen = 2U
 #endif
 };
 static const uint8_t rid_0002_sessions[] = {0, 1};
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED 
 static const uint8_t rid_0002_security[] = {0, 1};
 #endif
 static const UDS_SubFunctionSupportivity_t rid_0002_supportivity = 
 {
     .supportedSessions = rid_0002_sessions,
     .supportedSessionsLen = 2U
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED
     ,
     .supportedSecurityLvl = rid_0002_security,
     .supportedSecurityLvlLen = 2U
 #endif
 };
 /* Array of DID structure according to configuration */
 UDS_RID_RECORD_t UDS_Routines[UDS_NUM_OF_ROUTINES] =
 {
     {
         .rid = 0x01,
         .optionRecordSize = 1U,
         .isRestartable = 0U,
         .status = ROUTINE_STATUS_STOPPED,
         .routineStartHandler = NULL,
         .routineStopHandler = NULL,
         .routineCheckResultsHandler = NULL,
         .SupportivityStruct = &rid_0001_supportivity
     },
     
     {
         .rid = 0x02,
         .optionRecordSize = 1U,
         .isRestartable = 0U,
         .status = ROUTINE_STATUS_STOPPED,
         .routineStartHandler = NULL,
         .routineStopHandler = NULL,
         .routineCheckResultsHandler = NULL,
         .SupportivityStruct = &rid_0002_supportivity
     }
 };
 /**************************************************************************End of Generation**************************************************************************/
 #define STOP_SEC_UDS_SEC_CONST_DATA
 #include "uds_memMap.h"
 