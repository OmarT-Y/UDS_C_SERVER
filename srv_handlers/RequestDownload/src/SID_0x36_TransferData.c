/****************************************************************************************************
 *  File Name           : SID_0x36_TransferData.c
 *  Description         : Source file for the service 0x36 Transfer Data
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 24-2-2025 File Creation
 ****************************************************************************************************/

#include "../../../UDS/Service_Handlers/RequestDownload/uds_DataTransfer_cfg.h"

static uint8_t downloadData(UDS_REQ_t *request)
{
    uint8_t i=0;
    for(;i<UDS_TRANSFER_DOWNLOAD_MAX_WRITE_TRY_COUNT;i++)
    {
        if(FLASH_OK == parse_data(&request->data[2U],request->udsDataLen-2U))
        {
            return 1U;
        }

    }
    return 0U;
}

UDS_RESPONSE_SUPPRESSION_t SID_36_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server)
{ 
    /*minumum length check for the transfer upload*/
    if(dataTransferStatus.dataRequestType==UDS_REQUEST_UPLOAD && request->udsDataLen != 2U)
    {   
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
        return  UDS_NO_SUPPRESS_RESPONSE;
    }
    /*minumum length check for the transfer download*/
    else if(dataTransferStatus.dataRequestType==UDS_REQUEST_DOWNLOAD && request->udsDataLen < 3U)
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /*check for requests*/
    else if(dataTransferStatus.dataRequestType==UDS_DATA_TRANSFER_NO_REQUEST)
    {
        handleNRC(request,response,UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    if(1U == dataTransferStatus.requestComplete)
    {
        handleNRC(request,response,UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }

    uint8_t currentBlockCounter = request->data[1U];

    if(currentBlockCounter != dataTransferStatus.expectedNextBlock &&\
         currentBlockCounter != (dataTransferStatus.expectedNextBlock - 1U))
    {
        handleNRC(request,response,UDS_NRC_0x73_WRONG_BLOCK_SEQUENCE_COUNTER,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }

      
    if (dataTransferStatus.dataRequestType == UDS_REQUEST_DOWNLOAD)
    {
        if(request->udsDataLen- 2U > UDS_MAXIMUM_NUMBER_OF_BLOCK_LENGTH)
        {
            handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        if (0U == downloadData(request))
        {
            handleNRC(request, response, UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE, request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        else
        {
            if (currentBlockCounter == dataTransferStatus.maxBlockCounter &&\
                dataTransferStatus.currentLoopCounter == dataTransferStatus.maxLoopCounter)
                {
                    dataTransferStatus.requestComplete = 1U;
                }
                else
                {
                    /*TODO: check repeated transfer*/
                    if (currentBlockCounter == dataTransferStatus.expectedNextBlock - 1U)
                    {
                        /*Nothing to be done*/
                        /*TODO: make sure of this*/
                    }
                    else
                    {
                        if (dataTransferStatus.expectedNextBlock == 0xFFU)
                        {
                            dataTransferStatus.expectedNextBlock = 0U;
                            dataTransferStatus.currentLoopCounter++;
                        }
                        else
                        {
                            dataTransferStatus.expectedNextBlock++;
                        }
                    }
                }
                
                response->data[RESPONSE_SID_INDEX] = SID_36_POS_RES_CODE;
                response->data[1U] = currentBlockCounter;
                response->udsDataLen = 2U;
                return UDS_NO_SUPPRESS_RESPONSE;
            }
        }
        else
        {
            /*The upload functionality is not yet supported*/
            handleNRC(request, response, UDS_NRC_0x10_GENERAL_REJECT, request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        
    }
}
