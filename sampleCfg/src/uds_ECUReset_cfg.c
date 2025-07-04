/****************************************************************************************************
 *  File Name           : uds_ECUReset_cfg.c
 *  Description         : Source file for the UDS ECU Reset Configurations
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 23-2-2025 File Creation
 ****************************************************************************************************/
#include "uds_ECUReset_cfg.h"

#define START_SEC_UDS_SEC_CONST_DATA
#include "uds_memMap.h"

/*************************************************************************Start Of Generation*************************************************************************/
static const uint8_t sessions_01[] = {1, 2};
static const uint8_t security_01[] = {1, 2};
static const uint8_t sessions_03[] = {1, 2};
static const uint8_t security_03[] = {1, 2};
static const UDS_SubFunctionSupportivity_t reset_01_supportivity = 
{
    .supportedSessions = sessions_01,
    .supportedSessionsLen = 2U
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    ,
    .supportedSecurityLvl = security_01,
    .supportedSecurityLvlLen = 2U
#endif
};
static const UDS_SubFunctionSupportivity_t reset_03_supportivity = 
{
    .supportedSessions = sessions_03,
    .supportedSessionsLen = 2U
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    ,
    .supportedSecurityLvl = security_03,
    .supportedSecurityLvlLen = 2U
#endif
};
const UDS_ResetType_t SupportedResets[UDS_NUMBER_OF_SUPPORTED_RESETS] =
{
    {
        /*.resetFunctionPtr = hardReset,*/
        .ResetID = UDS_HARD_RESET_ID,
        .resetFunctionPtr = UDS_RESET_0x01_FUNCTION,
        .SupportivityStruct = &reset_01_supportivity
    }
};
/*************************************************************************End Of Generation*************************************************************************/
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    /* C11 or later: Safe to use static_assert */
    #include <assert.h>
    static_assert(sizeof(SupportedResets) == sizeof(UDS_ResetType_t) * UDS_NUMBER_OF_SUPPORTED_RESETS,
                  "The size of the supported resets array doesn't match its defined macro");
#else
    typedef char SizeMismatchCheck[
        (sizeof(SupportedResets) == sizeof(UDS_ResetType_t) * UDS_NUMBER_OF_SUPPORTED_RESETS) ? 1 : -1];
#endif
#define STOP_SEC_UDS_SEC_CONST_DATA
#include "uds_memMap.h"

