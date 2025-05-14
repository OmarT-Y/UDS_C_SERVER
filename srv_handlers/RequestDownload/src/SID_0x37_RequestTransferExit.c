/****************************************************************************************************
 *  File Name           : SID_0x37_RequestTransferExit.c
 *  Description         : Source file for the service 0x37 Request Transfer Exit
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 27-2-2025 File Creation
 ****************************************************************************************************/
#include "uds_DataTransfer_types.h"
extern void UDS_BL_UtilsReq_callBack(uint8_t status);
#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
/*TODO : add transfer response parameter record?*/
static uint8_t requestFlashBankVerification()
{
    BL_UDS_UtilsReq_MetaData_t BL_UtilsReq = {UDS_BL_UtilsReq_callBack,BL_UTILS_REQ_VALIDATE_FLASH_BANK,NULL,0U,1U};
    return BLUtils_createNewRequest(&BL_UtilsReq);
}

UDS_RESPONSE_SUPPRESSION_t SID_37_PositiveResponseHandler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server)
{
    response->data[RESPONSE_SID_INDEX]=SID_37_POS_RES_CODE;
    response->udsDataLen=1U;
    request->status = UDS_REQUEST_STATUS_SERVED_NOT_RESPONDED_TO;
    return UDS_NO_SUPPRESS_RESPONSE;
}

UDS_RESPONSE_SUPPRESSION_t SID_37_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server)
{
    if(request->status == UDS_REQUEST_STATUS_SERVED_NOT_RESPONDED_TO)
    {
        return SID_37_PositiveResponseHandler(request,response,server);
    }
    if(dataTransferStatus.dataRequestType == UDS_DATA_TRANSFER_NO_REQUEST || !dataTransferStatus.requestComplete)
    {
        handleNRC(request, response, UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR, request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /*Check server length < 1*/
    if(request->udsDataLen != 1U)
    {
        handleNRC(request, response, UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INVALID_FORMAT, request->data[REQUEST_SID_INDEX]);
        return  UDS_NO_SUPPRESS_RESPONSE;
    }
    dataTransferStatus.payloadSize = 0U;
    dataTransferStatus.address=0U;
    dataTransferStatus.dataRequestType = UDS_DATA_TRANSFER_NO_REQUEST;
    dataTransferStatus.expectedNextBlock = 0U;
#if (UDS_DATA_TRANSFER_USE_VARIABLE_BLOCK_SIZE == 0U)
    dataTransferStatus.maxBlockCounter = 0U;
    dataTransferStatus.maxLoopCounter = 0U;
#elif (UDS_DATA_TRANSFER_USE_VARIABLE_BLOCK_SIZE == 1U)
    dataTransferStatus.remainingPayloadSize = 0;
#endif
    dataTransferStatus.currentLoopCounter = 0U;
    dataTransferStatus.requestComplete = 0U;
    /*TODO : Notify bootloader to to verify or make it a routine and just send a positive response*/
    if(requestFlashBankVerification())
    {
        handleNRC(request, response, UDS_NRC_0x78_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING, request->data[REQUEST_SID_INDEX]);
        return  UDS_NO_SUPPRESS_RESPONSE;
    }
    else
    {
        /*TODO: should this be busy or general reject*/
        handleNRC(request, response, UDS_NRC_0x21_BUSY_REPEAT_REQUEST, request->data[REQUEST_SID_INDEX]);
        return  UDS_NO_SUPPRESS_RESPONSE;
    }
    return UDS_NO_SUPPRESS_RESPONSE;
}
#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
