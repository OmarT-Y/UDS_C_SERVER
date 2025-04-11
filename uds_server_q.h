/****************************************************************************************************
 *  File Name           : uds_server_q.h
 *  Description         : Header file for the UDS request Queue management
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 13-3-2025 File Creation
 ****************************************************************************************************/
#ifndef UDS_SERVER_Q_H_
#define UDS_SERVER_Q_H_

#include "uds_types.h"
#include "uds_server_q_cfg.h"
#include "uds_NR_Handler.h"

/**
 * @brief Structure to hold all the arrays of data buffers which are later allocated to requests
 * @param smallBuffers Holds the buffers of the smallest block size
 * @param mediumBuffers Holds the buffers of the medium block size
 * @param largeBuffers Holds the buffers of the largest block size
 * @param smallFree Holds flags for which small buffer is free
 * @param mediumFree Holds flags for which medium buffer is free
 * @param largeFree Holds flags for which large buffer is free
 */
typedef struct {
    uint8_t smallBuffers[UDS_SERVER_QUEUE_NUM_OF_SMALL_BLOCKS][UDS_SERVER_QUEUE_DATA_SMALL_BLOCK_SIZE];  
    uint8_t mediumBuffers[UDS_SERVER_QUEUE_NUM_OF_MEDIUM_BLOCKS][UDS_SERVER_QUEUE_DATA_MEDIUM_BLOCK_SIZE];  
    uint8_t largeBuffers[UDS_SERVER_QUEUE_NUM_OF_LARGE_BLOCKS][UDS_SERVER_QUEUE_DATA_LARGE_BLOCK_SIZE];  

    uint8_t smallFree[UDS_SERVER_QUEUE_NUM_OF_SMALL_BLOCKS];
    uint8_t mediumFree[UDS_SERVER_QUEUE_NUM_OF_MEDIUM_BLOCKS];
    uint8_t largeFree[UDS_SERVER_QUEUE_NUM_OF_LARGE_BLOCKS];

}UDS_DataBufferPool_t;

/**
 * @brief Function to enqueue a new request into the queue
 * @param newReq Pointer to the request to be added
 * @return True/False = Success/Fail
 */
uint8_t UDS_Request_enqueue(UDS_REQ_t* newReq);

/**
 * @brief Function to dequeue the next request
 */
void UDS_Request_dequeue(void);

/**
 * @brief Function to get the next request
 * @return The next request in the queue (The next request that should be handled) or NULL if no requests
*/
UDS_REQ_t* UDS_peekNextRequest(void);

/**
 * @brief Function to check the number of available requests
 * @return The number of available requests
 */
uint8_t UDS_readyReqCheck(void);

#endif