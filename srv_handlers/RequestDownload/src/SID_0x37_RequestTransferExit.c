/****************************************************************************************************
 *  File Name           : SID_0x37_RequestTransferExit.c
 *  Description         : Source file for the service 0x37 Request Transfer Exit
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 27-2-2025 File Creation
 ****************************************************************************************************/
#include "uds_DataTransfer_cfg.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
/*TODO : add transfer response parameter record?*/
UDS_RESPONSE_SUPPRESSION_t SID_37_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server)
{
    if(dataTransferStatus.dataRequestType == UDS_DATA_TRANSFER_NO_REQUEST || !dataTransferStatus.requestComplete)
    {
        handleNRC(request, response, UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR, request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /*Check server length < 1*/
    if(request->udsDataLen != 1U)
    {
        handleNRC(request, response, UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT, request->data[REQUEST_SID_INDEX]);
        return  UDS_NO_SUPPRESS_RESPONSE;
    }
    dataTransferStatus.payloadSize = 0U;
    dataTransferStatus.address=0U;
    dataTransferStatus.dataRequestType = UDS_DATA_TRANSFER_NO_REQUEST;
    dataTransferStatus.expectedNextBlock = 0U;
    dataTransferStatus.maxBlockCounter = 0U;
    dataTransferStatus.maxLoopCounter = 0U;
    dataTransferStatus.currentLoopCounter = 0U;
    dataTransferStatus.requestComplete = 0U;
    response->data[RESPONSE_SID_INDEX]=SID_37_POS_RES_CODE;
    response->udsDataLen=1U;
    return UDS_NO_SUPPRESS_RESPONSE;
}
#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
