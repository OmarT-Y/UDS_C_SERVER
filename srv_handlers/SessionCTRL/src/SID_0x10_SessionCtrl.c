/****************************************************************************************************
 *  File Name           : SID_10_SessionCtrl.c
 *  Description         : Source file for the service 0x10 Diagnostic Session Control Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_session_cfg.h"


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

static uint8_t UDS_FBL_notifyProgrammingSession(void)
{
    /*implementation specific*/
    /*try to set the flag 5 times*/
    uint8_t i=0;
    for( ; i<UDS_FBL_MAX_NORIFTY_TRY_COUNT ; i++ )
    {
        if(FLASH_OK == modify_flag(PROGRAMMING_SESSION,FLAG_SET))
        {
            break;
        }
    }
    if(UDS_FBL_MAX_NORIFTY_TRY_COUNT <= i)
    {
        /*fail*/
        return 0U;
    }
    i = 0;
    for(;i<UDS_FBL_MAX_NORIFTY_TRY_COUNT;i++)
    {
        if(FLASH_OK == erase_flashbank())
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
UDS_RESPONSE_SUPPRESSION_t SID_10_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
    uint8_t newSession = request->data[1U];
    newSession = (newSession & (~(1U << 7U))); /* ignore suppression bit*/
    UDS_Session_t* newSessionPtr = (UDS_Session_t*)UDS_BinaryID_Search((void*)serverSessions,sizeof(UDS_Session_t),UDS_NUMBER_OF_SESSIONS,&newSession,1);
    if(NULL == newSessionPtr)
    {
        handleNRC(request,response,UDS_NRC_0x10_GENERAL_REJECT,request->data[REQUEST_SID_INDEX]);
        /*TODO : check this*/
        return UDS_NO_SUPPRESS_RESPONSE;
    }
#ifdef UDS_PROGRAMMING_SESSION_ENABLED
    if(newSession == UDS_PROGRAMMING_SESSION_ID && bootLoaderActiveFlag==0)
    {
        if(0U == UDS_FBL_notifyProgrammingSession())
        {
            handleNRC(request,response,UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
		handleNRC(request,response,UDS_NRC_0x78_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING,request->data[REQUEST_SID_INDEX]);
        //UDS_PROGRAMMING_RESET_FUNCTION(); //TODO: Must be done through another service request??
        return UDS_SUPPRESS_RESPONSE;
    }
#endif
    server->activeSession = newSessionPtr;
    /*start timeout*/
    if(UDS_DEFAULT_SESSION_ID != newSessionPtr->SessionID)
    {
        START_TIMEOUT_FUNC(server->sessionTimeout);
    }
    if(CHECK_REQUEST_SUPPRESS_BIT(request))
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


const UDS_SubFunctionSupportivity_t* SID_10_getSubFunctSuppStruct(uint8_t subFunction)
{
    UDS_Session_t* sessionRecord = (UDS_Session_t*)UDS_BinaryID_Search((void*)serverSessions,sizeof(UDS_Session_t),UDS_NUMBER_OF_SESSIONS,&subFunction,1U);
    
    return NULL==sessionRecord?NULL:sessionRecord->SupportivityStruct;
}

#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
