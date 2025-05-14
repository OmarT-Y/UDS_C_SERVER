/****************************************************************************************************
 *  File Name           : uds_securityLvl_cfg.c
 *  Description         : Source file for the Security Level configurations
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 16-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_securityLvl_cfg.h"

extern void UDS_defaultSecurityLevelResetCallBack();
extern void uds_secLvl_attempt_callBack();

 #define START_SEC_UDS_SEC_CONST_DATA
 #include "uds_memMap.h"

static const uint8_t secLvl_0x00_suppSessions[] = {0, 1};
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
static const uint8_t secLvl_0x00_suppSecLvls[] = {1, 2};
#endif
static const UDS_SubFunctionSupportivity_t secLvl_0x00_supportivity = 
{
    .supportedSessions = secLvl_0x00_suppSessions,
    .supportedSessionsLen = 2U
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    ,
    .supportedSecurityLvl = secLvl_0x00_suppSecLvls,
    .supportedSecurityLvlLen = 2U
#endif
};

static const uint8_t secLvl_0x01_suppSessions[] = {0, 1};
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
static const uint8_t secLvl_0x01_suppSecLvls[] = {0, 1};
#endif
static const UDS_SubFunctionSupportivity_t secLvl_0x01_supportivity = 
{
    .supportedSessions = secLvl_0x01_suppSessions,
    .supportedSessionsLen = 2U
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    ,
    .supportedSecurityLvl = secLvl_0x01_suppSecLvls,
    .supportedSecurityLvlLen = 2U
#endif
};
UDS_SecurityLevel_t  securityLevels [UDS_NUMBER_OF_SECURITY_LEVELS] =
{
    {
        .SecurityLvlID    = SECURITY_LEVEL_0x00_ID,
        .supportedService = SECURITY_LEVEL_0x00_SUPPORTED_SID_MASK,
        .SupportivityStruct = &secLvl_0x00_supportivity,
        .keyLen = SECURITY_LEVEL_0x00_KEY_LENGTH,
        .seedLen = SECURITY_LEVEL_0x00_SEED_LENGTH,
        .seedFunc = secLvl_0x00_seedFunc,
        .keyCheckFunc = secLvl_0x00_keyCheckFunc,
        .LevelTimeout = SECURITY_LEVEL_0x00_TIMEOUT
    },
    {
        .SecurityLvlID    = SECURITY_LEVEL_0x01_ID,
        .supportedService = SECURITY_LEVEL_0x01_SUPPORTED_SID_MASK,
        .SupportivityStruct = &secLvl_0x01_supportivity,
        .keyLen = SECURITY_LEVEL_0x01_KEY_LENGTH,
        .seedLen = SECURITY_LEVEL_0x01_SEED_LENGTH,
        .seedFunc = secLvl_0x01_seedFunc,
        .keyCheckFunc = secLvl_0x01_keyCheckFunc,
        .LevelTimeout = SECURITY_LEVEL_0x01_TIMEOUT
    }
};

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    /* C11 or later: Safe to use static_assert */
    #include <assert.h>
    static_assert(sizeof(securityLevels) == sizeof(UDS_SecurityLevel_t) * UDS_NUMBER_OF_SECURITY_LEVELS,
                  "The size of the supported security level array (securityLevels) doesn't match its size defined in the macro (UDS_NUMBER_OF_SECURITY_LEVELS)");
#else
    typedef char SizeMismatchCheck[
        (sizeof(securityLevels) == sizeof(UDS_SecurityLevel_t) * UDS_NUMBER_OF_SECURITY_LEVELS) ? 1 : -1];
#endif

#define STOP_SEC_UDS_SEC_CONST_DATA
#include "uds_memMap.h"
