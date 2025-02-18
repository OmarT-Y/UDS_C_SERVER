/****************************************************************************************************
 *  File Name           : SID_0x22_ReadDID.c
 *  Description         : Source file for the service 0x22 Read DID Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "SID_0x22_ReadDID.h"


//TODO: implement read function
static void readDID(UDS_REQ_t * request, UDS_RES_t * response)
{
    return;
}

UDS_RESPONSE_SUPPRESSION_t SID_22_ReadDID_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
    /*Max and Min length check*/
    if ((request->udsDataLen < 3) || (request->udsDataLen > 1 + 2 * MAX_SUPPORTED_NUM_OF_DID))
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[0]);
    }
    //TODO : change to bool and STD_NO habibi
    uint8_t atLeastOneSupported = 0;
    uint8_t foundDID = 0;
    

    /*Loop over all DIDs*/
    for (uint8_t i = 0; i < (((request->udsDataLen) - 1) / 2); i++)
    {
        uint16_t currentDID = ((request->data[i * 2 + 1]) << 8) & (request->data[i * 2 + 2]);
        foundDID = 0;
        uint8_t index = 0;
        for (; index < UDS_NUM_OF_DIDS; index++)
        {
            if (UDS_DIDS[index].ID == currentDID)
            {
                foundDID = 1;
                break;
            }
            
        }
        if(foundDID)
        {
            if((UDS_DIDS[index].supportedSessions[(server->activeSession->SessionID)/32]\
            >>(server->activeSession->SessionID%32)&1) == 0 )
            {
                continue;
            }

            #ifdef UDS_SECURITY_LEVEL_SUPPORTED
            //TODO: Security Level Check

            #endif
            //TODO: Condition check ok
            atLeastOneSupported = 1;
        }
        
    }
    

    /*If no DID is supported*/
    if(atLeastOneSupported == 0)
    {
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[0]);
    }

    readDID(request,response);

    /*If Response length is more than the max length allowed by server*/
    if(response->udsDataLen > MAX_RESPONSE_LEN)
    {
        handleNRC(request,response,UDS_NRC_0x14_RESPONSE_TOO_LONG,request->data[0]);
    }


}





/*No Sub_functions supported so always return ok*/
UDS_SubFunctionCheckResult_t SID_22_ReadDID_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server)
{
    return UDS_SUB_FUNC_E_OK;
}