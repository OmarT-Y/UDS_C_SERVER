/****************************************************************************************************
 *  File Name           : sessionCtrl_bootloader_util.h
 *  Description         : Header file for Prototype for setting and clearing the boot loader active flag
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 7-3-2025 File Creation
 ****************************************************************************************************/

 #ifndef SESSIONCTRL_BOOTLOADER_UTIL_H_
 #define SESSIONCTRL_BOOTLOADER_UTIL_H_

/**
 * @brief Sets the flag that determines whether the bootloader is active or not 
 * @note set in bootloader when first request of programming session is received
 */
void set_BootLoader_ActiveFlag(void);

/**
 * @brief clears the flag that determines whether the bootloader is active or not
 * @note Cleared when bootloader finishes flashing and checked on when second programming session request is received
 */
void clear_BootLoader_ActiveFlag(void);

#endif