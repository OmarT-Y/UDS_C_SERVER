/*
 * UDS_utils.h
 *
 *  Created on: Mar 8, 2025
 *      Author: Issac Amin
 */

#ifndef UDS_UTILS_H_
#define UDS_UTILS_H_

#include "Fls.h"
#include "flags.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include "BootLoader_cfg.h"
#include "Mcu.h"

#define ADD_SEGMENT_BYTE_CODE 		0x00
#define COPY_SEGMENT_BYTE_CODE		0x11
#define JUMP_SEGMENT_BYTE_CODE 		0x01
#define METADATA_SEGMENT_BYTE_CODE	0x10

#define APPLICATION_UPDATE_OP_CODE	0x05
#define BOOTLOADER_UPDATE_OP_CODE	0x10

typedef enum {
	PRIMARY_APP = 0,
	SECONDARY_APP
} FlashBankType;

typedef enum
{
	BL_UTILS_REQ_NO_REQ,
	BL_UTILS_REQ_ERASE_FLASH_BANK,
	BL_UTILS_REQ_PARSE_DATA,
	BL_UTILS_REQ_VALIDATE_FLASH_BANK,
	BL_UTILS_REQ_SWITCH_FLASH_BANK
}BL_UDS_UtilsReq_t;

typedef void (*BL_UTILS_CallBackPtr)(uint8_t);

typedef struct
{
	BL_UTILS_CallBackPtr 	callBack;
	BL_UDS_UtilsReq_t		requestType;
	uint8_t* 				requestData;
	uint32_t				requestDataLen;
	uint8_t					requestTrialCount;
}BL_UDS_UtilsReq_MetaData_t;

typedef enum{
	FLASH_OK,
	FLASH_BUSY,
	FLASH_STARTADDRESS_UNALIGNED,
	FLASH_DATALENGTH_CROSS_PAGE_BOUNDARY,
	PARAMETERS_INVALID,
	FLASH_FAILED,
	FLASH_BANK_VALID,
	FLASH_BANK_NOT_VALID,
}UDS_Utils_ReturnType;

typedef enum{
	FLAG_SET,
	FLAG_CLEAR,
	FLAG_TOGGLE
}UDS_Utils_ModifyFlag;

typedef enum{
	PROGRAMMING_SESSION,
	CURRENT_APP,
	FLASHBANK_A_VALID,
	FLASHBANK_B_VALID,
	RESET_DURING_FLASH,
	FLASHING_IN_PROGRESS, 
	FLASHBANK_A_ERASED, 
	FLASHBANK_B_ERASED,
	UDS_LAST_SECURITY_LEVEL,
	BOOTLOADER_UPDATE_REQUEST,
	BOOTLOADER_UPDATE_SIZE
}UDS_Utils_FLAG;
/* 
* Requirements: 
*     - set programming session flag before resetting
*     - before starting flash sequence the following function need to be called once:
*            - erase_flashbank
*     - after finishing the sequence of copy, add_segment operations the following functions need to be called:
*            - flash_flashbank_metadata
*            - switch_and_validate_flashbank
*            - reset_ecu
*            
*
*/

void flsWaitUntilJobDone(void);
UDS_Utils_ReturnType init_flags(void);

UDS_Utils_ReturnType modify_flag(UDS_Utils_FLAG flag ,UDS_Utils_ModifyFlag input);

uint8_t read_flags(UDS_Utils_FLAG flag);

void reset_ecu(void);

void BLUtil_mainFunction(void);

uint8_t BLUtils_createNewRequest(BL_UDS_UtilsReq_MetaData_t* reqType);

UDS_Utils_ReturnType flash_flashbank_metadata(uint16_t crc, uint32_t app_length);
 
#endif /* UDS_UTILS_H_ */
