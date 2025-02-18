/****************************************************************************************************
 *  File Name           : SID_10_SessionCtrl.c
 *  Description         : Source file for the service 0x10 Diagnostic Session Control Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "SID_0x10_SessionCtrl.h"
//TODO : Generation
//TODO : Supported in active session
static UDS_Session_t * getSession(uint8_t SessionID,uint8_t activeSessionID)
{
    switch(SessionID)
    {
        default:
        return NULL;
    }
}
//TODO : Generation
static SID_10_startTimeout(uint16_t t)
{

}
UDS_RESPONSE_SUPPRESSION_t SID_10_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
    uint8_t newSession = request->data[1];
    newSession = (newSession & (~(1<<7)));//ignore suppression bit
    UDS_Session_t* newSessionPtr = getSession(newSession,server->activeSession->SessionID);
    if(NULL == newSessionPtr)
    {
        handleNRC(request,response,UDS_NRC_0x10_GENERAL_REJECT,request->data[0]);
        //TODO : check this
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    server->activeSession = newSessionPtr;
    //start timeout
    if(UDS_DEFAULT_SESSION_ID != newSessionPtr->SessionID)
    {
        SID_10_startTimeout(server->sessionTimeout);
    }

    if(request->data[1] & (1<<7))
    {//suppress
        return UDS_SUPPRESS_RESPONSE;
    }
    response->data[0] = SID_10_POS_RES_CODE;
    response->data[1] = request->data[1];
    //timing record
    //TODO: endian check
    response->data[2] = ((uint8_t*)(&(newSessionPtr->p2_server_max)))[0];
    response->data[3] = ((uint8_t*)(&(newSessionPtr->p2_server_max)))[1];
    response->data[4] = ((uint8_t*)(&(newSessionPtr->p2_server_star_max)))[0];
    response->data[5] = ((uint8_t*)(&(newSessionPtr->p2_server_star_max)))[1];
    response->udsDataLen = 6;

    //TODO : do this in a function
    response->srcAdd = UDS_SERVER_FUNCTION_ADDRESS;
    response->trgAdd = request->srcAdd;
    response->msgType = request->msgType;
    response->trgAddType = UDS_A_TA_PHYSICAL;
    //TODO : Handle remote

    return UDS_NO_SUPPRESS_RESPONSE;
}

UDS_SubFunctionCheckResult_t SID_10_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server)
{

}