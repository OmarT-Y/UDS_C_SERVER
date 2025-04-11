/****************************************************************************************************
 *  File Name           : SID_0x11_ECUReset.c
 *  Description         : Source file for the service 0x11 Request ECU Reset
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 22-2-2025 File Creation
 ****************************************************************************************************/


#include "uds_ECUReset_cfg.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"

const UDS_SubFunctionSupportivity_t* SID_11_getSubFunctSuppStruct(uint8_t subFunction)
{
    UDS_ResetType_t* resetRecord = (UDS_ResetType_t*)UDS_BinaryID_Search((void*)SupportedResets,sizeof(UDS_ResetType_t),UDS_NUMBER_OF_SUPPORTED_RESETS,&subFunction,1U);
    return NULL==resetRecord?NULL:resetRecord->SupportivityStruct;
}

UDS_RESPONSE_SUPPRESSION_t SID_11_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
    if(request->udsDataLen != 2U)
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    uint8_t index=0U;
    UDS_ResetType_t* resetRecord = (UDS_ResetType_t*)UDS_BinaryID_Search((void*)SupportedResets,sizeof(UDS_ResetType_t),UDS_NUMBER_OF_SUPPORTED_RESETS,&request->data[1],1U);
    if(NULL == resetRecord)
    {

    }
    else
    {
        response->data[RESPONSE_SID_INDEX]=SID_11_POS_RES_CODE;
        response->data[1U]=request->data[1U];
        response->udsDataLen = 2U;
        //TODO : check this
        //TODO : add down time?
        sendResponse(response);
        resetRecord->resetFunctionPtr();
    }
    handleNRC(request,response,UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE,request->data[REQUEST_SID_INDEX]); /*Should never reach here*/
    return UDS_NO_SUPPRESS_RESPONSE; 
}

#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
