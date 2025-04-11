/****************************************************************************************************
 *  File Name           : SID_0x2E_WriteDID.c
 *  Description         : Source file for the service 0x2E Write DID Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "../../../UDS/Service_Handlers/ReadWriteDID/uds_DID_cfg.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
UDS_RESPONSE_SUPPRESSION_t SID_2E_Handler(UDS_REQ_t *request, UDS_RES_t *response, UDS_Server_t *server)
{
    /*Check min request length*/
    if ((request->udsDataLen < 4U))
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
        if(request->trgAddType==UDS_A_TA_FUNCTIONAL)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        else
        {
            return UDS_NO_SUPPRESS_RESPONSE;
        }
    }
    
    uint16_t currentDID = ((request->data[1U]) << 8U) | (request->data[2U]);
    UDS_DID_t* didRecord = NULL;
    didRecord = (UDS_DID_t*)UDS_BinaryID_Search((void*)UDS_DIDS,sizeof(UDS_DID_t),UDS_NUM_OF_DIDS,(uint8_t*)(&currentDID),2);
    
    DID_CHECK_RES_t resCheck = checkDID(currentDID,server->activeSession->SessionID,server->activeSecLvl->SecurityLvlID,didRecord);

    if(resCheck==DID_NOT_SUPPORTED_IN_ACTIVE_SESSION)
    {
        handleNRC(request, response, UDS_NRC_0x31_REQUEST_OUT_OF_RANGE, request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }

    if(((request->udsDataLen) - 3U) != didRecord->dataLen)/*total length should return nrc */
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
        if(request->trgAddType==UDS_A_TA_FUNCTIONAL)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        else
        {
            return UDS_NO_SUPPRESS_RESPONSE;
        }
    }

#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    if(resCheck==DID_NOT_SUPPORTED_IN_SECURITY_LEVEL)
    {
        handleNRC(request, response, UDS_NRC_0x33_SECURITY_ACCESS_DENIED, request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
#endif

    if(resCheck==DID_NOT_FOUND || didRecord->DID_Access == READ_ONLY) /*check on validity*/
    {
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
        if(request->trgAddType==UDS_A_TA_FUNCTIONAL)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        else
        {
            return UDS_NO_SUPPRESS_RESPONSE;
        }
    }
    else
    { 
        if(0U == didRecord->writeDIDptr(&request->data[3U])) /* Was not able to right  */
        {
            handleNRC(request,response,UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE; /*check*/
        }
        else
        {
            if(1U == CHECK_REQUEST_SUPPRESS_BIT(request))
            {
                return UDS_SUPPRESS_RESPONSE;
            }
            else
            {
                response->data[RESPONSE_SID_INDEX] = SID_2E_POS_RES_CODE;
                response->data[1U] = request->data[1U]; /*0x00 if we passed the subfunction check*/
                response->data[2U] = request->data[2U]; /*0x00 if we passed the subfunction check*/
                response->udsDataLen = 3U;
                return UDS_NO_SUPPRESS_RESPONSE;
            }
        }
    }    
    return UDS_NO_SUPPRESS_RESPONSE;
}
#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"