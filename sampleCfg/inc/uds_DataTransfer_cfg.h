/****************************************************************************************************
 *  File Name           : uds_DataTransfer_cfg.h
 *  Description         : Header file for the Data Transfer Services configurations
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 24-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_DATA_TRANSFER_CFG_H
#define UDS_DATA_TRANSFER_CFG_H

/*****************************************************Start of Generation*****************************************************/
/*Mask for which encryption technique is used (requests will raise error if greater than the mask, ie: treated as max)(max is 15)*/
#define ENCRYPTION_TECHNIQUE_MASK                                   2U
/*Mask for which comperssion technique is used (requests will raise error if greater than the mask, ie: treated as max)(max is 15)*/
#define COMPRESSION_TECHNIQUE_MASK                                  2U

/*The number of bytes which determine the size of a transfer block size (max is 8)*/
#define UDS_NUMBER_OF_BYTES_FOR_BLOCK_LENGTH                        4U

/*The maximum Block size to be transmitted while downloading*/
#define UDS_MAXIMUM_NUMBER_OF_BLOCK_LENGTH                         512UL     /*must be multiples of 2*/

#define UDS_TRANSFER_DOWNLOAD_MAX_WRITE_TRY_COUNT            	    5U

/*The maximum number of bytes for the address (max is 8)*/
#define UDS_MAXIMUM_DOWNLOAD_ADDRESS_BYTES                          5U
/*The maximum number of bytes for size of data to be downloaded (max is 8)*/
#define UDS_MAXIMUM_DOWNLOAD_SIZE_BYTES                             5U


#define UDS_MAX_PAYLOAD_SIZE                                        524288ULL

#define UDS_DATA_TRANSFER_USE_VARIABLE_BLOCK_SIZE                   1U

extern uint8_t preFlashConditionsChecks(void);
/******************************************************End of Generation******************************************************/

#endif
