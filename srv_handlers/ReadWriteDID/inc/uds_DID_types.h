/****************************************************************************************************
 *  File Name           : uds_DID_types.h
 *  Description         : Header file for the UDS DID services Types
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/


#ifndef UDS_DID_H
#define UDS_DID_H

#include "uds_types.h"

/**
 * @brief DID access type 
 * @param READ_ONLY Read only access
 * @param WRITE_ONLY Write only access 
 * @param READ_WRITE Read and write access
 */
typedef enum
{
    READ_ONLY,
    WRITE_ONLY,
    READ_WRITE
}UDS_DID_ACCESS_t;

/**
 * @brief Pointer to function that writes or reads DID
 */
typedef uint8_t (*UDS_readWriteDIDptr_t) (uint8_t*);
/**
 * @brief DID block 
 * @param ID Data identifier
 * @param dataLen length of data
 * @param isSingleBlock Data is stored in a single block or more
 * @param DID_Access DID Access type
 * @param readDIDptr Pointer to the read function
 * @param writeDIDptr Pointer to the write funciton
 * @param SupportivityStruct Structure to hold information about the funciton being supported in which session and which security levels
 */
typedef struct 
{               
    uint16_t                            ID;
    uint8_t                             dataLen;
    uint8_t                             isSingleBlock;
    UDS_DID_ACCESS_t                    DID_Access;
    UDS_readWriteDIDptr_t               readDIDptr;
    UDS_readWriteDIDptr_t               writeDIDptr;
    const UDS_SubFunctionSupportivity_t*      SupportivityStruct;
    /*TODO: change to bool and add starting address*/ 
}UDS_DID_t;

/**
 * @brief Return type for DIDCheck function 
 * @param DID_NO_ISSUE No issues
 * @param DID_NOT_FOUND Did not found in generated array
 * @param DID_NOT_SUPPORTED_IN_ACTIVE_SESSION Did not supported in active session
 * @param DID_NOT_SUPPORTED_IN_SECURITY_LEVEL Did not supported in security level
 */
typedef enum
{
    DID_NO_ISSUE,
    DID_NOT_FOUND,
    DID_NOT_SUPPORTED_IN_ACTIVE_SESSION
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
    ,
    DID_NOT_SUPPORTED_IN_SECURITY_LEVEL
#endif
}DID_CHECK_RES_t;


#endif