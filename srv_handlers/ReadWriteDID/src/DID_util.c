/****************************************************************************************************
 *  File Name           : DID_util.c
 *  Description         : Source file fo the needed DID checks 
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/
#include "uds_DID_cfg.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
DID_CHECK_RES_t checkDID(uint16_t id,uint8_t activeSessionID,uint8_t activeSecurityLvl, UDS_DID_t *didRecord)
{
    if(NULL == didRecord)
    {
        return DID_NOT_FOUND;
    }
    /*check session*/
    const UDS_SubFunctionSupportivity_t* supportivity = didRecord->SupportivityStruct;
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
        return DID_NOT_SUPPORTED_IN_ACTIVE_SESSION;
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
        return DID_NOT_SUPPORTED_IN_SECURITY_LEVEL;
    }
#endif
    return DID_NO_ISSUE;
}
#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
