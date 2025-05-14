/****************************************************************************************************
 *  File Name           : uds_session_cfg.c
 *  Description         : Source file for the supported Sessions
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_session_cfg.h"
extern void UDS_defaultSessionResetCallBack();
 #define START_SEC_UDS_SEC_CONST_DATA
 #include "uds_memMap.h"
/**
 * Session Records
 * Generated according to supported sessions
 */
static const uint8_t session_0x1_suppSessions[] = {1, 2};
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
static const uint8_t session_0x1_suppSecLvls[] = {0, 1};
#endif
static const UDS_SubFunctionSupportivity_t session_0x1_supportivity = 
{
    .supportedSessions = session_0x1_suppSessions,
    .supportedSessionsLen = 2U
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    ,
    .supportedSecurityLvl = session_0x1_suppSecLvls,
    .supportedSecurityLvlLen = 2U
#endif
};

static const uint8_t session_0x2_suppSessions[] = {1, 2};
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
static const uint8_t session_0x2_suppSecLvls[] = {0, 1};
#endif
static const UDS_SubFunctionSupportivity_t session_0x2_supportivity = 
{
    .supportedSessions = session_0x2_suppSessions,
    .supportedSessionsLen = 2U
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    ,
    .supportedSecurityLvl = session_0x2_suppSecLvls,
    .supportedSecurityLvlLen = 2U
#endif
};
UDS_Session_t serverSessions [UDS_NUMBER_OF_SESSIONS] =
{
    {
        .SessionID                  = UDS_DEFAULT_SESSION_ID,
        .p2_server_max              = UDS_DEFAULT_SESSION_P2_SERVER_MAX,
        .p2_server_star_max         = UDS_DEFAULT_SESSION_P2_SERVER_START_MAX,
        .s3_server_session_timeout  = UDS_DEFAULT_SESSION_S3_SESSION_TIMEOUT,
        .supportedService           = UDS_DEFAULT_SESSION_SUPPORTED_SID_MASK,
		.SupportivityStruct         = &session_0x1_supportivity
    },
    {
        .SessionID                  = UDS_PROGRAMMING_SESSION_ID,
        .p2_server_max              = UDS_PROGRAMMING_SESSION_P2_SERVER_MAX,
        .p2_server_star_max         = UDS_PROGRAMMING_SESSION_P2_SERVER_START_MAX,
        .s3_server_session_timeout  = UDS_PROGRAMMING_SESSION_S3_SESSION_TIMEOUT,
        .supportedService           = UDS_PROGRAMMING_SESSION_SUPPORTED_SID_MASK,
		.SupportivityStruct         = &session_0x2_supportivity
    }
    /* ,
     {
         .SessionID          = UDS_EXTENDED_DIAG_SESSION_ID,
         .p2_server_max      = UDS_EXTENDED_DIAG_SESSION_P2_SERVER_MAX,
         .p2_server_star_max = UDS_EXTENDED_DIAG_SESSION_P2_SERVER_START_MAX,
         .supportedService   = UDS_EXTENDED_DIAG_SESSION_SUPPORTED_SID_MASK
     },
     {
         .SessionID          = UDS_SAFETY_SYS_DIAG_SESSION_ID,
         .p2_server_max      = UDS_SAFETY_SYS_DIAG_SESSION_P2_SERVER_MAX,
         .p2_server_star_max = UDS_SAFETY_SYS_DIAG_SESSION_P2_SERVER_START_MAX,
         .supportedService   = UDS_SAFETY_SYS_DIAG_SESSION_SUPPORTED_SID_MASK
     }
    */
};

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    /* C11 or later: Safe to use static_assert */
    #include <assert.h>
    static_assert(sizeof(serverSessions) == sizeof(UDS_Session_t) * UDS_NUMBER_OF_SESSIONS,
                  "The size of the supported session array doesn't match the macro (UDS_NUMBER_OF_SESSIONS)");
#else
    typedef char SizeMismatchCheck[
        (sizeof(serverSessions) == sizeof(UDS_Session_t) * UDS_NUMBER_OF_SESSIONS) ? 1 : -1];
#endif

#define STOP_SEC_UDS_SEC_CONST_DATA
#include "uds_memMap.h"
