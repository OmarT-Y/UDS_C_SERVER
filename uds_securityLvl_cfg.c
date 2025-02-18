/****************************************************************************************************
 *  File Name           : uds_securityLvl_cfg.c
 *  Description         : Source file for the Security Level configurations
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 16-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_securityLvl_cfg.h"

#ifdef UDS_SECURITY_LEVEL_SUPPORTED

/* Security Level Records Generated according to Supported Security levels */

#ifdef SECURITY_LVL_DEFAULT
UDS_SecurityLevel_t securityLevelDefault =
{
    .SecurityLvlID    = SECURITY_LEVEL_DEFAULT_ID,
    .supportedService = SECURITY_LEVEL_DEFAULT_SUPPORTED_SID_MASK
};
#endif

#ifdef SECURITY_LVL_1
UDS_SecurityLevel_t securityLevel_1 =
{
    .SecurityLvlID    = SECURITY_LEVEL_1_ID,
    .supportedService = SECURITY_LEVEL_1_SUPPORTED_SID_MASK
};
#endif

#endif