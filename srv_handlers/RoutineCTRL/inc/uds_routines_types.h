/****************************************************************************************************
 *  File Name           : uds_routines_types.h
 *  Description         : Header file for the UDS routines Types
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 9-3-2025 File Creation
 ****************************************************************************************************/

 #ifndef UDS_ROUTINES_TYPES_H_
 #define UDS_ROUTINES_TYPES_H_

 #include "uds_types.h"

 /** 
  * @brief     UDS Routine Status 
  * @param     ROUTINE_STATUS_RUNNING            Routine is currently executing
  * @param     ROUTINE_STATUS_COMPLETED_SUCCESS  Routine completed successfully
  * @param     ROUTINE_STATUS_COMPLETED_FAILURE  Routine completed with a failure
  * @param     ROUTINE_STATUS_STOPPED            Routine was Stopped
  * @param     ROUTINE_STATUS_TIMEOUT            Routine execution timed out
  */
  typedef enum
 {
    ROUTINE_STATUS_NOT_STARTED = 0, 
    ROUTINE_STATUS_RUNNING,         
    ROUTINE_STATUS_COMPLETED_SUCCESS,
    ROUTINE_STATUS_COMPLETED_FAILURE,
    ROUTINE_STATUS_STOPPED,          
    ROUTINE_STATUS_TIMEOUT    
 }UDS_RoutineStatus_t;
/**
 * @brief Pointer to Routine Start function
 * @note Parameter 1 is routineControlOptionRecord
 * @note Parameter 2 is Size of the routineControlOptionRecord array
 */
typedef uint8_t (*UDS_RoutineStartPtr_t) (uint8_t * , uint8_t);
/**
 * @brief Pointer to Routine Stop function
 * @note Parameter 1 is routineControlOptionRecord
 * @note Parameter 2 is Size of the routineControlOptionRecord array
 */
typedef uint8_t (*UDS_RoutineStopPtr_t) (uint8_t * , uint8_t);
/**
 * @brief Pointer to Routine status checking function
 * @note Parameter 1 is routineControlOptionRecord
 * @note Parameter 2 is Size of the routineControlOptionRecord array
 */
typedef UDS_RoutineStatus_t (*UDS_checkRoutineResultsPtr_t) (uint8_t *,uint8_t);


/** 
* @brief UDS RID Record context 
* @param rid Routine ID
* @param status Routine Status
* @param optionRecordSize Record size
* @param isRestartable Determines whether the routine can be restarted or not
* @param routineStartHandler Handler for routine start
* @param routineStopHandler Handler for routine stop
* @param routineCheckResultsHandler Handler for checking on results of routine 
* @param SupportivityStruct Structure to hold information about the funciton being supported in which session and which security levels
*/
typedef struct 
{
   uint16_t                                        rid;
   uint8_t                                         optionRecordSize;  
   uint8_t                                         isRestartable;
   UDS_RoutineStatus_t                             status;
   UDS_RoutineStartPtr_t                           routineStartHandler;
   UDS_RoutineStopPtr_t                            routineStopHandler;
   UDS_checkRoutineResultsPtr_t                    routineCheckResultsHandler;
   const UDS_SubFunctionSupportivity_t*            SupportivityStruct;
}UDS_RID_RECORD_t;
/**
 * @brief UDS RID Supportivity Results
 * @param RID_NO_ISSUE No issues
 * @param RID_NOT_FOUND Not Found in Supported RIDs
 * @param RID_NOT_SUPPORTED_IN_ACTIVE_SESSION RID not supported in active session
 * @param RID_NOT_SUPPORTED_IN_SECURITY_LEVEL RID not supported in security level
 */
typedef enum
{
   RID_NO_ISSUE,
   RID_NOT_FOUND,
   RID_NOT_SUPPORTED_IN_ACTIVE_SESSION,
   RID_NOT_SUPPORTED_IN_SECURITY_LEVEL
}RID_SUPPORTIVITY_RES_t;

#endif
