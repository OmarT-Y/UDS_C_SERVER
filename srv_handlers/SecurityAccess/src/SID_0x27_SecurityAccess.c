/****************************************************************************************************
 *  File Name           : SID_0x27_SecurityAccess.c
 *  Description         : Source file for the service 0x27 Request Security Access
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 23-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_sid_cfg.h"

#include "uds_securityLvl_cfg.h"

#define START_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

securityAccessRequestInfo securityLevelStatus = {0,SECURITY_LEVEL_NO_REQUESTS};

uint8_t invalidTimerFlag = 0;

#define STOP_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
#include "Os.h"
void uds_secLvl_attempt_callBack(void)
{
    invalidTimerFlag = 0U;
}
UDS_RESPONSE_SUPPRESSION_t SID_27_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
    static uint8_t invalidAttemp=0;
    if(invalidTimerFlag == 1)
    {
        handleNRC(request,response,UDS_NRC_0x37_REQUIRED_TIME_DELAY_NOT_EXPIRED,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    uint8_t requestType;
    uint8_t level = (uint8_t)((request->data[1U] - 1U)/2U) + 1U;
    UDS_SecurityLevel_t* securityLevelRecord = (UDS_SecurityLevel_t*)UDS_BinaryID_Search(securityLevels,sizeof(UDS_SecurityLevel_t),UDS_NUMBER_OF_SECURITY_LEVELS,&(level),1);
    if(NULL == securityLevelRecord)
    {
        /*security level doesnt exist*/
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
        if(request->msgType==UDS_A_TA_FUNCTIONAL)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        else     
        {
            return UDS_NO_SUPPRESS_RESPONSE;
        }   
    }
    if(request->data[1U] % 2U == 1U)
    {
        requestType = UDS_SECURITY_ACCESS_REQUEST_SEED;
    }
    else
    {
        requestType = UDS_SECURITY_ACCESS_SEND_KEY;
    }

    if(requestType == UDS_SECURITY_ACCESS_SEND_KEY && securityLevelStatus.status == SECURITY_LEVEL_NO_REQUESTS)
    {
        handleNRC(request,response,UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;          
    }

    if(requestType == UDS_SECURITY_ACCESS_REQUEST_SEED && server->activeSecLvl->SecurityLvlID == level)
    {
        handleNRC(request,response,UDS_NRC_0x22_CONDITIONS_NOT_CORRECT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    if(requestType==UDS_SECURITY_ACCESS_REQUEST_SEED)
    {
        if(NULL == securityLevelRecord->seedFunc)
        {
            handleNRC(request,response,UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        const uint8_t* seedPtr = NULL;
        seedPtr =  securityLevelRecord->seedFunc();
        if(NULL != seedPtr)
        {
            securityLevelStatus.level = level;
            securityLevelStatus.status = SECURITY_LEVEL_SEED_SENT_WAITING_KEY;
            response->data[RESPONSE_SID_INDEX] = SID_27_POS_RES_CODE;
            response->data[REQUEST_SUB_FUNCTION_INDEX] = request->data[REQUEST_SUB_FUNCTION_INDEX];
            uint8_t i;
            for(i =0;i<securityLevelRecord->seedLen;i++)
            {
                response->data[2U+i] = seedPtr[i];
            }
            response->udsDataLen = 2U + securityLevelRecord->seedLen;
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        else
        {
            handleNRC(request,response,UDS_NRC_0x10_GENERAL_REJECT,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
    }
    else if(requestType == UDS_SECURITY_ACCESS_SEND_KEY)
    {
        if(NULL == securityLevelRecord->keyCheckFunc)
        {
            handleNRC(request,response,UDS_NRC_0x10_GENERAL_REJECT,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;        
        }
        uint8_t reqKeyLen = request->udsDataLen-2U;
        if(reqKeyLen != securityLevelRecord->keyLen)
        {
            handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        if(level != securityLevelStatus.level)
        {
            /*error*/
            handleNRC(request,response,UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        const uint8_t * keyPtr = &request->data[2U];
        if(1U == securityLevelRecord->keyCheckFunc(keyPtr))
        {
            /* success */
            if(SECURITY_LVL_DEFAULT_ID != securityLevelRecord->SecurityLvlID && securityLevelRecord->SecurityLvlID != server->activeSecLvl)
            {
                UDS_securityAccess_defaultLvl_timeout(securityLevelRecord->LevelTimeout);
            }
            securityLevelStatus.status = SECURITY_LEVEL_NO_REQUESTS;
            server->activeSecLvl = securityLevelRecord;
            response->data[RESPONSE_SID_INDEX] = SID_27_POS_RES_CODE;
            response->data[1U] = request->data[1U];
            response->udsDataLen = 2U;
            invalidAttemp = 0U;
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        else
        {
            invalidAttemp++;
            if(invalidAttemp == MAX_INVALID_ATTEMPTS)
            {
                invalidAttemp=0U;
                handleNRC(request,response,UDS_NRC_0x36_EXCEED_NUMBER_OF_ATTEMPS,request->data[REQUEST_SID_INDEX]);
                invalidTimerFlag = 1U;
                UDS_securityAccess_attemptCount_timeout(securityLevelRecord->LevelTimeout);
                return UDS_NO_SUPPRESS_RESPONSE;
                
            }
            handleNRC(request,response,UDS_NRC_0x35_INVALID_KEY,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
    }
    handleNRC(request,response,UDS_NRC_0x10_GENERAL_REJECT,request->data[REQUEST_SID_INDEX]);
    return UDS_NO_SUPPRESS_RESPONSE;
}

void UDS_securityAccess_attemptCount_timeout(uint16_t time)
{
    /*this should set the function "uds_secLvl_attempt_callBack" as a call back after "time" ms*/
    SetRelAlarm(udsSecurityAccessAttemptCountTimeoutAlarm, time / (OS_TICKS2MS_SYSTEMTIMER(1) * 10), 0);
    return;
}

const UDS_SubFunctionSupportivity_t* SID_27_getSubFunctSuppStruct(uint8_t subFunction)
{
    uint8_t securityLevel = (uint8_t)((subFunction - 1)/2) + 1;
    UDS_SecurityLevel_t* secLvlRecord = (UDS_SecurityLevel_t*)UDS_BinaryID_Search((void*)securityLevels,sizeof(UDS_SecurityLevel_t),UDS_NUMBER_OF_SECURITY_LEVELS,&securityLevel,1U);
    
    return NULL==secLvlRecord?NULL:secLvlRecord->SupportivityStruct;
}
#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
