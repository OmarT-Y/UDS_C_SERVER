/****************************************************************************************************
 *  File Name           : SID_0x31_RoutineCTRL.c
 *  Description         : Source file for the service 0x31 Routine Control
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 22-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_routine_cfg.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"

static RID_SUPPORTIVITY_RES_t checkRID(uint8_t activeSessionID,uint8_t activeSecurityLvl, UDS_RID_RECORD_t *ridRecord)
{
    if(NULL == ridRecord)
    {
        return RID_NOT_FOUND;
    }
    /*check session*/
    const UDS_SubFunctionSupportivity_t* supportivity = ridRecord->SupportivityStruct;
    uint16_t i = 0U;
    for( ; i<supportivity->supportedSessionsLen ; i++)
    {
        if(supportivity->supportedSessions[i] == activeSessionID)
        {
            break;
        }
    }
    if(i>=supportivity->supportedSessionsLen)
    {
        return RID_NOT_SUPPORTED_IN_ACTIVE_SESSION;
    }

#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
    /*check security level*/
    i = 0U;
    for(;i<supportivity->supportedSecurityLvlLen;i++)
    {
        if(supportivity->supportedSecurityLvl[i] == activeSecurityLvl)
        {
            break;
        }
    }
    if(i>=supportivity->supportedSecurityLvlLen)
    {
        return RID_NOT_SUPPORTED_IN_SECURITY_LEVEL;
    }
#endif
    return RID_NO_ISSUE;
}

UDS_RESPONSE_SUPPRESSION_t SID_31_Handler(UDS_REQ_t *request, UDS_RES_t *response, UDS_Server_t *server)
{
    /*Min length check*/
    if (request->udsDataLen < 4U)
    {
        handleNRC(request, response, UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INVALID_FORMAT, request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /*parse the Routien ID*/
    uint16_t routine_id = (request->data[2U] << 8U) & request->data[3U];
    /*Get the routine record instance*/
    UDS_RID_RECORD_t* routine_record = (UDS_RID_RECORD_t*)UDS_BinaryID_Search((void*)UDS_Routines,sizeof(UDS_RID_RECORD_t),UDS_NUM_OF_ROUTINES,(uint8_t*)(&routine_id),2U);
    switch (checkRID(server->activeSession->SessionID,server->activeSecLvl->SecurityLvlID,routine_record))
    {
        case RID_NOT_FOUND:
            if(request->trgAddType==UDS_A_TA_FUNCTIONAL)
            {
                handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
                return UDS_NO_SUPPRESS_RESPONSE;
            }
            else
            {
                return UDS_SUPPRESS_RESPONSE;    
            }
            break;
        case RID_NOT_SUPPORTED_IN_ACTIVE_SESSION:
            handleNRC(request, response, UDS_NRC_0x31_REQUEST_OUT_OF_RANGE, request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
            break;
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
        case RID_NOT_SUPPORTED_IN_SECURITY_LEVEL:
            handleNRC(request, response, UDS_NRC_0x33_SECURITY_ACCESS_DENIED, request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
            break;
#endif
        case RID_NO_ISSUE:
        default:
            break;
    }
    
    /*Sub funciton supported for routine ID checks*/
    if(     request->data[1U] == UDS_START_ROUTINE_SUBFUNC && routine_record->routineStartHandler == NULL \
        ||  request->data[1U] == UDS_STOP_ROUTINE_SUBFUNC && routine_record->routineStopHandler == NULL \
        ||  request->data[1U] == UDS_REQUEST_ROUTINE_RESULTS_SUBFUNC && routine_record->routineCheckResultsHandler == NULL
    )
    {
        handleNRC(request,response,UDS_NRC_0x12_SUB_FUNCTION_NOT_SUPPORTED,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /*RID checks*/

    /*Total length check*/
    if(((request->udsDataLen) - 4U) != routine_record->optionRecordSize)
    {
        if(request->trgAddType==UDS_A_TA_FUNCTIONAL)
        {
            handleNRC(request, response, UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INVALID_FORMAT, request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        else
        {
            return UDS_SUPPRESS_RESPONSE;    
        }
    }
    /*TODO : routineControlOptionRecord contains valid data for the requested RID check*/

    /* Restarting a routine */
    if(routine_record->status == ROUTINE_STATUS_RUNNING && request->data[1U] == UDS_START_ROUTINE_SUBFUNC && !routine_record->isRestartable )
    {
        handleNRC(request, response, UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR, request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /* Stopping an already stopped routine */
    if (routine_record->status == ROUTINE_STATUS_STOPPED && request->data[1U] == UDS_STOP_ROUTINE_SUBFUNC)
    {
        handleNRC(request, response, UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR, request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }

    /*Handle the request*/
    uint8_t *dataRecordPtr = NULL;
    uint8_t dataRecordLen = (request->udsDataLen - 4U);
    if(dataRecordLen>0U)
    {
        dataRecordPtr = &request->data[4U];
    }
    if(request->data[1U] == UDS_START_ROUTINE_SUBFUNC)
    {
        if(routine_record->routineStartHandler(dataRecordPtr,dataRecordLen))
        {
            routine_record->status = ROUTINE_STATUS_RUNNING;
            response->data[RESPONSE_SID_INDEX] = SID_31_POS_RES_CODE;
            response->data[1U] = request->data[1U];
            response->data[2U] = request->data[2U];
            response->data[3U] = request->data[3U];
            response->udsDataLen = 4U;
        }
        else
        {
            handleNRC(request, response, UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE, request->data[REQUEST_SID_INDEX]);
        }
        return UDS_NO_SUPPRESS_RESPONSE;

    }
    else if (request->data[1U] == UDS_STOP_ROUTINE_SUBFUNC)
    {
        if(routine_record->routineStopHandler(dataRecordPtr,dataRecordLen))
        {
            routine_record->status = ROUTINE_STATUS_STOPPED;
            response->data[RESPONSE_SID_INDEX] = SID_31_POS_RES_CODE;
            response->data[1U] = request->data[1U];
            response->data[2U] = request->data[2U];
            response->data[3U] = request->data[3U]; 
            response->udsDataLen = 4U;
        }
        else
        {
            handleNRC(request, response, UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE, request->data[REQUEST_SID_INDEX]);
        }
        return UDS_NO_SUPPRESS_RESPONSE;       
    }
    else if (request->data[1U] == UDS_REQUEST_ROUTINE_RESULTS_SUBFUNC)
    {
        UDS_RoutineStatus_t newStatus = routine_record->routineCheckResultsHandler(dataRecordPtr,dataRecordLen);
        switch(newStatus)
        {
            case ROUTINE_STATUS_RUNNING:
                handleNRC(request, response, UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR, request->data[REQUEST_SID_INDEX]);
                return UDS_NO_SUPPRESS_RESPONSE;
                break;
                break;
                case ROUTINE_STATUS_STOPPED:
                handleNRC(request, response, UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR, request->data[REQUEST_SID_INDEX]);
                return UDS_NO_SUPPRESS_RESPONSE;
                break;
            case ROUTINE_STATUS_COMPLETED_SUCCESS:
            case ROUTINE_STATUS_TIMEOUT:
            case ROUTINE_STATUS_COMPLETED_FAILURE:
                routine_record->status = newStatus;
                response->data[RESPONSE_SID_INDEX] = SID_31_POS_RES_CODE;
                response->data[1U] = request->data[1U];
                response->data[2U] = request->data[2U];
                response->data[3U] = request->data[3U];
                response->data[4U] = newStatus;
                response->udsDataLen = 5U;
                break;
            default:
                break;
        }
    }
    handleNRC(request, response, UDS_NRC_0x10_GENERAL_REJECT, request->data[REQUEST_SID_INDEX]);
    return UDS_NO_SUPPRESS_RESPONSE;
}

const UDS_SubFunctionSupportivity_t* SID_31_getSubFunctSuppStruct(uint8_t subFunction)
{
    UDS_RID_RECORD_t* ridRecord = (UDS_RID_RECORD_t*)UDS_BinaryID_Search((void*)UDS_Routines,sizeof(UDS_RID_RECORD_t),UDS_NUM_OF_ROUTINES,&subFunction,1U);
    return (NULL==ridRecord) ? NULL : ridRecord->SupportivityStruct;
}

#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
