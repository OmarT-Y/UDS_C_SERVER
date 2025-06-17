/****************************************************************************************************
 *  File Name           : SID_0x34_RequestDownload.c
 *  Description         : Source file for the service 0x34 Request Download
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 24-2-2025 File Creation
 ****************************************************************************************************/
#include "uds_DataTransfer_types.h"
#include "UDS_utils.h"

#define START_SEC_UDS_SEC_DATA
#include "uds_memMap.h"
UDS_dataTransferStatusRecord_t dataTransferStatus =
{
    .address = 0,
    .payloadSize = 0,
    .dataRequestType = UDS_DATA_TRANSFER_NO_REQUEST,
    .expectedNextBlock = 0,
#if (UDS_DATA_TRANSFER_USE_VARIABLE_BLOCK_SIZE == 0U)
    .maxBlockCounter = 0,
    .maxLoopCounter = 0,
#elif (UDS_DATA_TRANSFER_USE_VARIABLE_BLOCK_SIZE == 1U)
    .remainingPayloadSize = 0,
#endif
    .currentLoopCounter = 0,
    .requestComplete = 0,
};
#define STOP_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"

uint8_t startFlashFBL_notification()
{
    if(FLASH_OK == modify_flag(FLASHING_IN_PROGRESS,FLAG_SET))
    {
        return 1U;
    }
    return 0U;
}



UDS_RESPONSE_SUPPRESSION_t SID_34_Handler(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server)
{
    /*a request is already in progress*/
    if(UDS_DATA_TRANSFER_NO_REQUEST != dataTransferStatus.dataRequestType)
    {
        handleNRC(request,response,UDS_NRC_0x22_CONDITIONS_NOT_CORRECT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /*Min data length check*/
    if(request->udsDataLen < 5U)
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    if(0U==preFlashConditionsChecks())
    {
        handleNRC(request,response,UDS_NRC_0x22_CONDITIONS_NOT_CORRECT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    uint8_t requestEncryption = request->data[1U] & 0x0FU;
    uint8_t requestCompression = request->data[1U] >> 4U;
    /*Encryption technique check*/
    if(requestEncryption>ENCRYPTION_TECHNIQUE_MASK)
    {
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;        
    } 
    /*Compression technique check*/
    if(requestCompression>COMPRESSION_TECHNIQUE_MASK)
    {
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;        
    } 

    /* check the number of bytes used for the size */
    uint8_t payloadSize_ByteCount = (request->data[2U]>>4U);
    if(payloadSize_ByteCount > UDS_MAXIMUM_DOWNLOAD_SIZE_BYTES)
    {
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);  
        return UDS_NO_SUPPRESS_RESPONSE;      
    }

    /* check the number of bytes used for the address */
    uint8_t address_ByteCount = (request->data[2U]& 0x0FU);
    if(address_ByteCount > UDS_MAXIMUM_DOWNLOAD_ADDRESS_BYTES)
    {
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;        
    }

    /* Full data length check */
    if(request->udsDataLen != ( 3U + address_ByteCount + payloadSize_ByteCount ))
    {
        handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }

    /*Raise flashing in progress flag (notify bootloader)*/
    if(0U == startFlashFBL_notification())
    {
        handleNRC(request,response,UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    /*Set the address*/
    uint64_t req_address = 0U;
    uint8_t i;
    for(i = 0U ; i < address_ByteCount; i++)
    {
        /*TODO:check on endianness*/
        uint8_t nextByte = request->data[i+3U];
        req_address |= ((uint64_t)nextByte) << (8U * (address_ByteCount-1U-i));
    }
    
    /*Set the payload size*/
    uint64_t req_payloadSize = 0U;
    for(i = 0U ; i < payloadSize_ByteCount; i++)
    {
        /*TODO:check on endianness*/
        uint8_t nextByte = request->data[i+3U+address_ByteCount];
        req_payloadSize |= ((uint64_t)nextByte) << (8U * (payloadSize_ByteCount-1U-i));
    }

    /* check on address & memory size availability */
    if(req_payloadSize>= UDS_MAX_PAYLOAD_SIZE)
    {
        handleNRC(request,response,UDS_NRC_0x31_REQUEST_OUT_OF_RANGE,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    else
    {
        dataTransferStatus.address = req_address;
        dataTransferStatus.payloadSize = req_payloadSize;
        dataTransferStatus.expectedNextBlock = 1U;
        dataTransferStatus.currentLoopCounter = 0U;    
        dataTransferStatus.dataRequestType = UDS_REQUEST_DOWNLOAD;
#if (UDS_DATA_TRANSFER_USE_VARIABLE_BLOCK_SIZE == 0U)
        dataTransferStatus.maxBlockCounter = (dataTransferStatus.payloadSize/UDS_MAXIMUM_NUMBER_OF_BLOCK_LENGTH) / 256U;
        dataTransferStatus.maxLoopCounter = (dataTransferStatus.payloadSize/UDS_MAXIMUM_NUMBER_OF_BLOCK_LENGTH) % 256U;
#elif (UDS_DATA_TRANSFER_USE_VARIABLE_BLOCK_SIZE == 1U)
        dataTransferStatus.remainingPayloadSize = req_payloadSize;
#endif
        dataTransferStatus.requestComplete = 0U;
    }

    response->data[RESPONSE_SID_INDEX] = SID_34_POS_RES_CODE;
    response->data[1U] = ((uint8_t)UDS_NUMBER_OF_BYTES_FOR_BLOCK_LENGTH<<4U);
    response->udsDataLen = 2U;
    for(i = 0U ; i < UDS_NUMBER_OF_BYTES_FOR_BLOCK_LENGTH ; i++)
    {
        uint64_t size = UDS_MAXIMUM_NUMBER_OF_BLOCK_LENGTH;
        uint8_t nextByte =(uint8_t)((0xFF) & (size >> (8*(UDS_NUMBER_OF_BYTES_FOR_BLOCK_LENGTH-1U-i))));
        response->data[i+2U] = nextByte;
        response->udsDataLen++;
    }
    return UDS_NO_SUPPRESS_RESPONSE;
}

uint8_t checkAddressAndSize(uint64_t address,uint64_t payloadSize)
{
    return 1U;
}

#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
