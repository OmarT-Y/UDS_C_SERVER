 /*
 * UDS_utils.h
 *
 *  Created on: Mar 8, 2025
 *      Author: Issac Amin
 */

 #ifndef UDS_UTILS_H_
 #define UDS_UTILS_H_
 
 #include <stdbool.h>
 #include <stdint.h>
 
 typedef enum{
 FLASH_OK,
 FLASH_BUSY,
 FLASH_STARTADDRESS_UNALIGNED,
 FLASH_DATALENGTH_CROSS_PAGE_BOUNDARY
 }UDS_Utils_ReturnType;
 
 typedef enum{
 FLAG_SET,
 FLAG_CLEAR,
 FLAG_TOGGLE
 }UDS_Utils_ModifyFlag;
 
 typedef enum{
 PROGRAMMING_SESSION,
 CURRENT_APP,
 FLASHBANK_VALID,
 RESET_DURING_FLASH,
 FLASHING_IN_PROGRESS
 }UDS_Utils_FLAG;
 /* 
 * Requirements: 
 *     - set programming session flag before resetting
 *     - before starting flash sequence the following function need to be called once:
 *            - erase_flashbank
 *     - after finishing the sequence of copy, add_segment operations the following functions need to be called:
 *            - flash_flashbank_metadata
 *            - activate_flashbank
 *            - reset_ecu
 *            
 *
 */
UDS_Utils_ReturnType modify_flag(UDS_Utils_FLAG flag ,UDS_Utils_ModifyFlag input);
 
uint8_t read_flags(UDS_Utils_FLAG flag);

UDS_Utils_ReturnType erase_flashbank(void);

UDS_Utils_ReturnType copy_segment(uint32_t start_address, uint32_t segment_length, uint32_t dst_address);

UDS_Utils_ReturnType add_segment(uint32_t dst_address, uint8_t *data, uint32_t segment_length);

UDS_Utils_ReturnType flash_flashbank_metadata(uint16_t crc, uint32_t app_length);

void activate_flashbank(void);

/* copy code 0x00 - start address - segment length (data length must b 9 bytes)*/
/* add  code 0x11 - start address - segment length - data[1-n]  (data length must be a minimum of 10 bytes) */

UDS_Utils_ReturnType parse_data(uint8_t* data, uint32_t data_length);

void reset_ecu(void);

void UDS_mainFunction(void);

#endif /* UDS_UTILS_H_ */