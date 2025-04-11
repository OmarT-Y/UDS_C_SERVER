/****************************************************************************************************
 *  File Name           : uds_helpers.h
 *  Description         : header file for the helper functions needed by the uds server
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 22-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_HELPERS_H
#define UDS_HELPERS_H
#include "uds_types.h"

/**
 * @brief The function is used to search of a specific instance/struct in an array of structure using the ID of the needed structure
 * @note This is a binary search alternative of the method UDS_ID_Search, The passed array must be sorted for it to work
 * @return  pointer to the found object/structure or null pointer of not found
 * @param searchArray   Pointer to the array that needs to be searched
 * @param blockSize     The size of block/structure stored in that array in bytes
 * @param arrayLen      The lenght of the array in block units (how many structures are in the array)
 * @param idPtr         Pointer to the id that needs to be looked for in the array
 * @param idLength      The size of the ID in bytes (max 2 bytes)
 */
void* UDS_BinaryID_Search(const void* searchArray, uint8_t blockSize, uint16_t arrayLen, const uint8_t* idPtr, uint8_t idLength);

/**
 * @brief The function is used to search of a specific instance/struct in an array of structure using the ID of the needed structure
 * @return  pointer to the found object/structure or null pointer of not found
 * @param searchArray   Pointer to the array that needs to be searched
 * @param blockSize     The size of block/structure stored in that array in bytes
 * @param arrayLen      The lenght of the array in block units (how many structures are in the array)
 * @param idPtr         Pointer to the id that needs to be looked for in the array
 * @param idLength      The size of the ID in bytes (max 2 bytes)
 */
void* UDS_ID_Search(const void* searchArray, uint8_t blockSize, uint16_t arrayLen, const uint8_t* idPtr, uint8_t idLength);
#endif