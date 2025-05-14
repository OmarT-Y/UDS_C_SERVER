/****************************************************************************************************
 *  File Name           : SID_10_SessionCtrl.c
 *  Description         : Source file for the service 0x10 Diagnostic Session Control Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_session_cfg.h"
extern uint8_t UDS_sendResponse(UDS_RES_t *response);

/*Flag inficating if the boot loader is currently active*/
#ifdef UDS_PROGRAMMING_SESSION_ENABLED
#include "UDS_utils.h"
#define START_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

/*The flag*/
uint8_t bootLoaderActiveFlag = 0U;
#define STOP_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"

/*set function*/
void set_BootLoader_ActiveFlag()
{
    bootLoaderActiveFlag = 1U;
}

/*clear function*/
void clear_BootLoader_ActiveFlag()
{
    bootLoaderActiveFlag = 0U;
}
#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"

#endif


#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"

static uint8_t UDS_FBL_notifyProgrammingSession(UDS_Server_t * server)
{
    /*implementation specific*/
    /*try to set the flag 5 times*/
    UDS_Utils_FLAG flagsToBeSet[] = {PROGRAMMING_SESSION,FLASHING_IN_PROGRESS};
    uint8_t numberFlagsTobeSet = 2U;
    uint8_t i=0,currentFlagIndex=0;
    for(;currentFlagIndex<numberFlagsTobeSet;currentFlagIndex++)
    {
        i = 0;
        for( ; i<UDS_FBL_MAX_NORIFTY_TRY_COUNT ; i++ )
        {
            if(FLASH_OK == modify_flag(flagsToBeSet[currentFlagIndex],FLAG_SET))
            {
                break;
            }
        }
        if(UDS_FBL_MAX_NORIFTY_TRY_COUNT <= i)
        {
            /*fail*/
            return 0U;
        }
    }
    i = 0;
        for( ; i<UDS_FBL_MAX_NORIFTY_TRY_COUNT ; i++ )
        {
            if(FLASH_OK == modify_flag(UDS_LAST_SECURITY_LEVEL,server->activeSecLvl->SecurityLvlID))
            {
                break;
            }
        }
        if(UDS_FBL_MAX_NORIFTY_TRY_COUNT <= i)
        {
            /*fail*/
            return 0U;
        }
    return 1U;
}

UDS_RESPONSE_SUPPRESSION_t SID_10_PositiveResponseHandler(UDS_Session_t* newSessionPtr,UDS_RES_t * response,UDS_REQ_t * request, UDS_Server_t * server)
{
    /*start timeout*/
	if(UDS_DEFAULT_SESSION_ID != newSessionPtr->SessionID && server->activeSession->SessionID != newSessionPtr->SessionID)
	{
        START_TIMEOUT_FUNC(server->sessionTimeout);
	}
    server->activeSession = newSessionPtr;
	if(CHECK_REQUEST_SUPPRESS_BIT(request) && request->status != UDS_REQUEST_STATUS_SERVED_NOT_RESPONDED_TO)
	{/*suppress*/
		return UDS_SUPPRESS_RESPONSE;
	}
	response->data[RESPONSE_SID_INDEX] = SID_10_POS_RES_CODE;
	response->data[1U] = request->data[1U];
	/*timing record
	TODO: endian check*/
	response->data[2U] = ((uint8_t*)(&(newSessionPtr->p2_server_max)))[0U];
	response->data[3U] = ((uint8_t*)(&(newSessionPtr->p2_server_max)))[1U];
	response->data[4U] = ((uint8_t*)(&(newSessionPtr->p2_server_star_max)))[0U];
	response->data[5U] = ((uint8_t*)(&(newSessionPtr->p2_server_star_max)))[1U];
	response->udsDataLen = 6U;
	return UDS_NO_SUPPRESS_RESPONSE;
}
UDS_RESPONSE_SUPPRESSION_t SID_10_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
    uint8_t newSession = request->data[1U];
    newSession = (newSession & (~(1U << 7U))); /* ignore suppression bit*/
    UDS_Session_t* newSessionPtr = (UDS_Session_t*)UDS_BinaryID_Search((void*)serverSessions,sizeof(UDS_Session_t),UDS_NUMBER_OF_SESSIONS,&newSession,1);
    if(NULL == newSessionPtr)
    {
        handleNRC(request,response,UDS_NRC_0x10_GENERAL_REJECT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    if(request->status == UDS_REQUEST_STATUS_SERVED_NOT_RESPONDED_TO)
    {
        return SID_10_PositiveResponseHandler(newSessionPtr,response,request,server);
    }
#ifdef UDS_PROGRAMMING_SESSION_ENABLED
    if(newSession == UDS_PROGRAMMING_SESSION_ID && bootLoaderActiveFlag == 0)
    {
        if(0U == UDS_FBL_notifyProgrammingSession(server))
        {
            handleNRC(request,response,UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
		handleNRC(request,response,UDS_NRC_0x78_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING,request->data[REQUEST_SID_INDEX]);
        UDS_sendResponse(response);
        UDS_PROGRAMMING_RESET_FUNCTION();
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    else
#endif
    {
        return SID_10_PositiveResponseHandler(newSessionPtr,response,request,server);
    }
}


const UDS_SubFunctionSupportivity_t* SID_10_getSubFunctSuppStruct(uint8_t subFunction)
{
    UDS_Session_t* sessionRecord = (UDS_Session_t*)UDS_BinaryID_Search((void*)serverSessions,sizeof(UDS_Session_t),UDS_NUMBER_OF_SESSIONS,&subFunction,1U);
    
    return NULL==sessionRecord?NULL:sessionRecord->SupportivityStruct;
}

#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
