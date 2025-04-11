/****************************************************************************************************
 *  File Name           : uds_DataTransfer_types.h
 *  Description         : File for the types needed by the data transfer services
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 24-2-2025 File Creation
 ****************************************************************************************************/
#ifndef UDS_TRANSFER_DATA_CFG_H
#define UDS_TRANSFER_DATA_CFG_H

#include "uds_types.h"
#include "uds_NR_Handler.h"


#define SID_34_POS_RES_CODE             0x74
#define SID_36_POS_RES_CODE             0x76
#define SID_37_POS_RES_CODE             0x77

/**
 * @brief Request Type
 * @param UDS_REQUEST_UPLOAD Upload is requested
 * @param UDS_REQUEST_DOWLOAD Download is requested
 * @param UDS_DATA_TRANSFER_NO_REQUEST No current request
 */
 typedef enum
 {
    UDS_REQUEST_UPLOAD,
    UDS_REQUEST_DOWNLOAD,
    UDS_DATA_TRANSFER_NO_REQUEST
 }UDS_dataTransferType_t;
 

/**
 * @brief Data Transfer status record
 * @param dataRequestType Type of data transfer request
 * @param addressLength The length(number of bytes) of the address
 * @param address Starting address specified
 * @param memoryLength The length(number of bytes) of the memory size
 * @param payloadSize The size of the transfered data in bytes
 * @param currentLoopCounter A counter for the current block overflow loop
 * @param expectedNextBlock The next expected block number
 * @param maxBlockCounter The maximum number for the block counter for a transfer
 * @param maxLoopCounter The maximum number of overflow loops for the block counter
 */
typedef struct 
{
    UDS_dataTransferType_t dataRequestType;
    uint64_t address;
    uint64_t payloadSize;
    uint8_t currentLoopCounter;
    uint8_t expectedNextBlock;
    uint8_t maxBlockCounter;
    uint8_t maxLoopCounter;
    uint8_t requestComplete; /*change to bool*/
} UDS_dataTransferStatusRecord_t;

#endif