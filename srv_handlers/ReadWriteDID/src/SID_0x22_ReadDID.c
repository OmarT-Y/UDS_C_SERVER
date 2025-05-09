/****************************************************************************************************
 *  File Name           : SID_0x22_ReadDID.c
 *  Description         : Source file for the service 0x22 Read DID Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_sid_cfg.h"

#include "uds_DID_cfg.h"

#define START_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

static uint8_t readData[UDS_READ_DID_SINGLE_DID_MAX_LEN];

#define STOP_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"

/* The read function should add the DID to the response then follow it with the read data, then increase the response length by the amount of data added */
static void readDID(UDS_DID_t* DID, UDS_RES_t* response)
{
	uint8_t i;
    /* TODO : endian check */
    response->data[response->udsDataLen++] = (uint8_t)((DID->ID) >> 8U);
    response->data[response->udsDataLen++] = (uint8_t)((DID->ID) & 0x00FFU);

    if(NULL == DID->readDIDptr)
    {
        /* TODO : DET error */
    }
    else
    {   
        if(1U == DID->readDIDptr(readData))
        {
            if(NULL == readData)
            {
                return;
            }
            for(i =0 ; i<DID->dataLen ; i++)
            {
                /*TODO : add an extra length check for rets of a user*/
                response->data[response->udsDataLen++] = readData[i];
            }
        }
    }
    return;
}

UDS_RESPONSE_SUPPRESSION_t SID_22_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
	uint8_t i;
    /*Max and Min length check*/
    if ((request->udsDataLen < 3U) || (request->udsDataLen > 1U + 2U * MAX_NUM_OF_READABLE_DIDS_IN_ONE_REQUEST))
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /*TODO : change to bool and STD_NO habibi*/
    uint8_t atLeastOneSupported = 0U;
    uint8_t foundDID = 0U;
    

    /*Loop over all DIDs*/
    for (i = 0U; i < (((request->udsDataLen) - 1U) / 2U); i++)
    {
        /*TODO : endian check*/
        uint16_t currentDID = ((request->data[i * 2U + 1U]) << 8U) | (request->data[i * 2U + 2U]);
        UDS_DID_t* didRecord;
        didRecord = (UDS_DID_t*)UDS_BinaryID_Search((void*)UDS_DIDS,sizeof(UDS_DID_t),UDS_NUM_OF_DIDS,(uint8_t*)(&currentDID),2);
        
        DID_CHECK_RES_t resCheck = checkDID(currentDID,server->activeSession->SessionID,server->activeSecLvl->SecurityLvlID,didRecord);
        switch(resCheck)
        {
            case DID_NOT_FOUND:
            case DID_NOT_SUPPORTED_IN_ACTIVE_SESSION:
                break;
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
            case DID_NOT_SUPPORTED_IN_SECURITY_LEVEL:
                handleNRC(request, response, UDS_NRC_0x33_SECURITY_ACCESS_DENIED, request->data[REQUEST_SID_INDEX]);
                return UDS_NO_SUPPRESS_RESPONSE;
#endif
            case DID_NO_ISSUE:
                if(didRecord->DID_Access == READ_ONLY || didRecord->DID_Access == READ_WRITE)
                {
                    if(!atLeastOneSupported)
                    {
                        response->data[RESPONSE_SID_INDEX] = SID_22_POS_RES_CODE;
                        atLeastOneSupported  = 1U;
                        response->udsDataLen = 1U;
                    }
                    readDID(didRecord,response);
                }
                break;
        }        
    }
    
    /*If no DID is supported*/
    if(!atLeastOneSupported)
    {
        if(request->trgAddType == UDS_A_TA_PHYSICAL)
        {
            handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        else
        {
            return UDS_SUPPRESS_RESPONSE;
        }
    }

    /*If Response length is more than the max length allowed by server*/
    if(response->udsDataLen > MAX_READ_RESPONSE_LEN)
    {
        handleNRC(request,response,UDS_NRC_0x14_RESPONSE_TOO_LONG,request->data[REQUEST_SID_INDEX]);
       
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    if(response->udsDataLen == 1)
    {
        /*no did were read*/
        handleNRC(request,response,UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    return UDS_NO_SUPPRESS_RESPONSE;
    /*TODO : Handle remote*/
}
#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
