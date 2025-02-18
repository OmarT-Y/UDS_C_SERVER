/****************************************************************************************************
 *  File Name           : SID_0x2E_WriteDID.c
 *  Description         : Source file for the service 0x2E Write DID Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "SID_0x2E_WriteDID.h"

static void writeDID(UDS_REQ_t *request, UDS_RES_t *response)
{

}

UDS_RESPONSE_SUPPRESSION_t SID_2E_WriteDID_Handler(UDS_REQ_t *request, UDS_RES_t *response, UDS_Server_t *server)
{
    /*Check max and min request length*/
    if ((request->udsDataLen < 4) || (request->udsDataLen > MAX_REQUEST_LEN))
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[0]);
    }
    uint16_t currentDID = ((request->data[1]) << 8) & (request->data[2]);
    uint8_t index = 0;
    for (; index < UDS_NUM_OF_DIDS; index++)
    {
        if (UDS_DIDS[index].ID == currentDID)
        {
            break;
        }
        
    }

    if((UDS_DIDS[index].isReadOnly == 1)||((UDS_DIDS[index].supportedSessions[(server->activeSession->SessionID)/32]\
    >>(server->activeSession->SessionID%32)&1) == 0) )
    {
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[0]);
    }

    #ifdef UDS_SECURITY_LEVEL_SUPPORTED
    //TODO: Security Level Check

    #endif
    //TODO: Data record valid check
    writeDID(request,response);

    if(request->data[1] & 1<<7)
    {
        return UDS_SUPPRESS_RESPONSE;
    }
    else
    {
        response->data[0] = SID_2E_POS_RES_CODE;
        response->data[1] = request->data[1]; //0x00 if we passed the subfunction check
        response->data[2] = request->data[2]; //0x00 if we passed the subfunction check
        return UDS_NO_SUPPRESS_RESPONSE;
    }
}

/*No Sub_functions supported so always return ok*/
UDS_SubFunctionCheckResult_t SID_2E_WriteDID_subFunctionChecks(uint8_t subFunction, UDS_Server_t *server)
{
    return UDS_SUB_FUNC_E_OK;
}
