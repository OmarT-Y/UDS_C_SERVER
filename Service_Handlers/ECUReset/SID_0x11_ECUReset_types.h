/****************************************************************************************************
 *  File Name           : SID_0x11_ECUReset_types.h
 *  Description         : Header file for the types of service 0x11 ECU Reset
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 7-3-2025 File Creation
 ****************************************************************************************************/
#ifndef SID_0x11_ECU_RESET_TYPES_H_
#define SID_0x11_ECU_RESET_TYPES_H_

/**
 * @brief Pointer to function that does the Reset
 */
 typedef void (*UDS_ResetFuncPtr_t)(void);

/** 
 * @brief UDS Reset types 
 * @param ResetID Reset ID
 * @param resetFunctionPtr Pointer to function that does the reset
 * @param SupportivityStruct Structure to hold information about the funciton being supported in which session and which security levels
 */
 typedef struct 
 {
    uint8_t                                   ResetID;
    UDS_ResetFuncPtr_t                        resetFunctionPtr;
    const UDS_SubFunctionSupportivity_t*      SupportivityStruct;
 }UDS_ResetType_t;

 #endif