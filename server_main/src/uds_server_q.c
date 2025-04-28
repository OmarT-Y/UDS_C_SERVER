/****************************************************************************************************
 *  File Name           : uds_server_q.c
 *  Description         : Source file for the UDS request Queue management
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 13-3-2025 File Creation
 ****************************************************************************************************/
#include "uds_server_q.h"

#define START_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

/**
 * @brief Incoming request buffer (FIFO Queue)
*/
static volatile UDS_REQ_t UDS_requests_Q[UDS_SERVER_QUEUE_MAX_NUMBER_OF_REQS];
/**
 * @brief index of the next request to be added to the queue
 * @note max is 255 (uint8_t)
*/
static volatile uint8_t request_q_nextIn = 0;
/**
 * @brief index of the next request to be popped to the queue
 * @note max is 255 (uint8_t)
*/
static volatile uint8_t request_q_nextOut = 0;
/**
 * @brief The number of available request in the Queue
*/
static volatile uint8_t requestsReady= 0;

/**
 * @brief Structure holding all of the data buffers
 */
static UDS_DataBufferPool_t bufferPool = {0};

#define STOP_SEC_UDS_SEC_DATA
#include "uds_memMap.h"


#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"

/**
 * @brief Function to allocate a buffer from the available buffers
 * @param size The request size to be allocated
 * @return Pointer to buffer or NULL if not possible
 */
static uint8_t* allocateBuffer(uint16_t size) {
    /*allocate small*/
	uint8_t i;
    if (size <= UDS_SERVER_QUEUE_DATA_SMALL_BLOCK_SIZE) 
    {
        for (i = 0; i < UDS_SERVER_QUEUE_NUM_OF_SMALL_BLOCKS; i++)
        {
            if (0U == bufferPool.smallFree[i]) 
            {
                bufferPool.smallFree[i] = 1U;
                return bufferPool.smallBuffers[i];
            }
        }
    }

    /*allocate mid*/
    if (size <= UDS_SERVER_QUEUE_DATA_MEDIUM_BLOCK_SIZE) 
    {
        for (i = 0; i < UDS_SERVER_QUEUE_NUM_OF_MEDIUM_BLOCKS; i++)
        {
            if (0U == bufferPool.mediumFree[i]) 
            {
                bufferPool.mediumFree[i] = 1U;
                return bufferPool.mediumBuffers[i];
            }
        }
    }

    /*allocate large*/
    if (size <= UDS_SERVER_QUEUE_DATA_LARGE_BLOCK_SIZE) 
    {
        for (i = 0; i < UDS_SERVER_QUEUE_NUM_OF_LARGE_BLOCKS; i++)
        {
            if (0U == bufferPool.largeFree[i]) 
            {
                bufferPool.largeFree[i] = 1U;
                return bufferPool.largeBuffers[i];
            }
        }
    }

    return NULL;
}

/**
 * @brief Function to free the allocated buffer
 * @param ptr pointer the buffer that should be free'd
 */
static void freeBuffer(void* ptr) {
	uint8_t i;
    for (i = 0; i < UDS_SERVER_QUEUE_NUM_OF_SMALL_BLOCKS; i++)
    {
        if (bufferPool.smallBuffers[i] == ptr) 
        {
            bufferPool.smallFree[i] = 0U;
            return;
        }
    }

    for (i = 0; i < UDS_SERVER_QUEUE_NUM_OF_MEDIUM_BLOCKS; i++)
    {
        if (bufferPool.mediumBuffers[i] == ptr) 
        {
            bufferPool.mediumFree[i] = 0U;
            return;
        }
    }

    for (i = 0; i < UDS_SERVER_QUEUE_NUM_OF_LARGE_BLOCKS; i++)
    {
        if (bufferPool.largeBuffers[i] == ptr) 
        {
            bufferPool.largeFree[i] = 0U;
            return;
        }
    }
}

/**
 * @brief Function to copy the content of the request into the queue
 * @param newReq The Incoming request to be added to the queue
 * @param index The index at which the request should be added
 * @return True/False = Pass/Fail = Added/NotAdded
 */
static uint8_t UDS_req_q_new_entry(UDS_REQ_t* newReq,uint8_t index)
{
	uint32_t i;
    uint8_t* dataPtr = allocateBuffer(newReq->udsDataLen);
    if(NULL==dataPtr)
    {
        /*Failed to allocate memory*/
        return 0U;
    }
    else
    {
        /*copy into the array index*/
        UDS_requests_Q[index].msgType       = newReq->msgType;
        UDS_requests_Q[index].remoteAdd     = newReq->remoteAdd;
        UDS_requests_Q[index].srcAdd        = newReq->srcAdd;
        UDS_requests_Q[index].trgAdd        = newReq->trgAdd;
        UDS_requests_Q[index].trgAddType    = newReq->trgAddType;
        UDS_requests_Q[index].udsDataLen    = newReq->udsDataLen;
        UDS_requests_Q[index].data          = dataPtr;
        for(i =0;i<newReq->udsDataLen;i++)
        {
            dataPtr[i]=newReq->data[i];
        }
        return 1U;
    }
    return 0U;
}
/**
 * @brief Function to enqueue a new request into the queue
 * @param newReq Pointer to the request to be added
 * @return True/False = Success/Fail
 */
uint8_t UDS_Request_enqueue(UDS_REQ_t* newReq)
{   
    /*when nextIn = nextOut the queue is either full or empty*/
    if(request_q_nextIn == request_q_nextOut && requestsReady== UDS_SERVER_QUEUE_MAX_NUMBER_OF_REQS)
    {
        /*The queue is full*/
        /*This shouldn't be reachable (check available before enqueueing)*/
        return 0U;
    }
    else
    {
        /*add new request*/
        if(UDS_req_q_new_entry(newReq,request_q_nextIn))
        {
            requestsReady++;
            request_q_nextIn++;
            if(UDS_SERVER_QUEUE_MAX_NUMBER_OF_REQS == request_q_nextIn)
            {
                request_q_nextIn = 0U;
            }
            return 1U;
        }
        else
        {
            /*TODO*/
            /*Unexpected Error*/
            return 0U;
        }
        return 0U;
    }
}
/**
 * @brief Function to dequeue the next request
 */
void UDS_Request_dequeue(void)
{
    if(0U == requestsReady)
    {
        /*Error*/
        return;
    }
    freeBuffer(UDS_requests_Q[request_q_nextOut].data);
    requestsReady--;
    request_q_nextOut++;
    if(request_q_nextOut==UDS_SERVER_QUEUE_MAX_NUMBER_OF_REQS)
    {
        request_q_nextOut = 0U;
    }
}
/**
 * @brief Function to get the next request
 * @return The next request in the queue (The next request that should be handled) or NULL if no requests
*/
UDS_REQ_t* UDS_peekNextRequest(void)
{
    return (requestsReady == 0U) ? NULL : &UDS_requests_Q[request_q_nextOut];
}
/**
 * @brief Function to check the number of available requests
 * @return The number of available requests
 */
uint8_t UDS_readyReqCheck(void)
{
    return requestsReady;
}

#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
