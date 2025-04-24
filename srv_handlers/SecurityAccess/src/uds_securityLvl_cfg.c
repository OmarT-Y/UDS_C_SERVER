/****************************************************************************************************
 *  File Name           : uds_securityLvl_cfg.c
 *  Description         : Source file for the Security Level configurations
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 16-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_securityLvl_cfg.h"


static const uint8_t secLvl_0x00_suppSessions[] = {1, 2};
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

static const uint8_t secLvl_0x01_suppSessions[] = {1, 2};
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
static const uint8_t secLvl_0x01_suppSecLvls[] = {1, 2};
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
        .seedFunc = NULL,
        .keyCheckFunc = NULL
    },
    {
        .SecurityLvlID    = SECURITY_LEVEL_0x01_ID,
        .supportedService = SECURITY_LEVEL_0x01_SUPPORTED_SID_MASK,
        .SupportivityStruct = &secLvl_0x01_supportivity,
        .keyLen = SECURITY_LEVEL_0x00_KEY_LENGTH,
        .seedLen = SECURITY_LEVEL_0x00_SEED_LENGTH,
        .seedFunc = NULL,
        .keyCheckFunc = NULL
    }
};

void UDS_securityAccess_timeout(void (*callBack)(void))
{
    return;
}
