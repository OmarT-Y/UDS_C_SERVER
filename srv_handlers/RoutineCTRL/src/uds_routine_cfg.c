/****************************************************************************************************
 *  File Name           : uds_routine_cfg.c
 *  Description         : Source file for the UDS routines 
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/


 #include "uds_routine_cfg.h"

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
 /* Array of DID structure according to configuration */
 UDS_RID_RECORD_t UDS_Routines[UDS_NUM_OF_ROUTINES] =
 {
     {
         .rid = 0xff00,
         .optionRecordSize = 0U,
         .isRestartable = 0U,
         .status = ROUTINE_STATUS_STOPPED,
         .routineStartHandler = rid_FF00_start,
         .routineStopHandler = NULL,
         .routineCheckResultsHandler = rid_FF00_checkRes,
         .SupportivityStruct = &rid_0001_supportivity
     }
 };
 /**************************************************************************End of Generation**************************************************************************/
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    /* C11 or later: Safe to use static_assert */
    #include <assert.h>
    static_assert(sizeof(UDS_Routines) == sizeof(UDS_RID_RECORD_t) * UDS_NUM_OF_ROUTINES,
                  "The size of the supported routines array (UDS_Routines) doesn't match its size defined in the macro (UDS_NUM_OF_ROUTINES)");
#else
    typedef char SizeMismatchCheck[
        (sizeof(UDS_Routines) == sizeof(UDS_RID_RECORD_t) * UDS_NUM_OF_ROUTINES) ? 1 : -1];
#endif
 #define STOP_SEC_UDS_SEC_CONST_DATA
 #include "uds_memMap.h"
 
