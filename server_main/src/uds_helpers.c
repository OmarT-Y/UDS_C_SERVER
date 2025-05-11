/****************************************************************************************************
 *  File Name           : uds_helpers.c
 *  Description         : Source file for the helper functions needed by the uds server
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 22-2-2025 File Creation
 ****************************************************************************************************/
#include "uds_helpers.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
void* UDS_BinaryID_Search(const void* searchArray, uint8_t blockSize, uint16_t arrayLen, const uint8_t* idPtr, uint8_t idLength)
{
    uint16_t left = 0, right = arrayLen - 1;
    const uint8_t* basePtr = (const uint8_t*)searchArray;

    while (left <= right && left < arrayLen && right < arrayLen)
    {
        uint16_t mid = left + ((right - left) >> 1);
        const uint8_t* midPtr = basePtr + (mid * blockSize);

        switch (idLength)
        {
            case 1: 
            {
                uint8_t midId = *((const uint8_t*)midPtr);
                if (midId == *idPtr)
                {
                    return (void*)midPtr;
                }
                else if (midId < *idPtr)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
                break;
            }
            
            case 2: 
            {
                uint16_t midId = *((const uint16_t*)midPtr);
                uint16_t searchId = *((const uint16_t*)idPtr);
                if (midId == searchId)
                {
                    return (void*)midPtr;
                }
                else if (midId < searchId)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
                break;
            }
            default:
                return NULL;
        }
    }

    return NULL;
}

void* UDS_ID_Search(const void* searchArray, uint8_t blockSize, uint16_t arrayLen, const uint8_t* idPtr, uint8_t idLength)
{
    const uint8_t* basePtr = (const uint8_t*)searchArray;
    uint32_t arrayMaxInBytes = blockSize * arrayLen;

    uint32_t i;
    for (i = 0; i < arrayMaxInBytes; i += blockSize)
    {
        const void* currentPtr = basePtr + i;
        switch (idLength)
        {
            case 1:
                if (*((const uint8_t*)currentPtr) == *idPtr)
                    return (void*)currentPtr;
                break;
            case 2:
                if (*((const uint16_t*)currentPtr) == *((const uint16_t*)idPtr))
                    return (void*)currentPtr;
                break;
            default:
                return NULL;
        }
    }
    return NULL;
}

#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
