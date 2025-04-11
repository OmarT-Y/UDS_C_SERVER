/****************************************************************************************************
 *  File Name           : uds_session_cfg.c
 *  Description         : Source file for the supported Sessions
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#include "../../../UDS/Service_Handlers/SessionCTRL/uds_session_cfg.h"

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
        .SessionID          = UDS_DEFAULT_SESSION_ID,
        .p2_server_max      = UDS_DEFAULT_SESSION_P2_SERVER_MAX,
        .p2_server_star_max = UDS_DEFAULT_SESSION_P2_SERVER_START_MAX,
        .supportedService   = UDS_DEFAULT_SESSION_SUPPORTED_SID_MASK,
		.SupportivityStruct = &session_0x1_supportivity
    },
    {
        .SessionID          = UDS_PROGRAMMING_SESSION_ID,
        .p2_server_max      = UDS_PROGRAMMING_SESSION_P2_SERVER_MAX,
        .p2_server_star_max = UDS_PROGRAMMING_SESSION_P2_SERVER_START_MAX,
        .supportedService   = UDS_PROGRAMMING_SESSION_SUPPORTED_SID_MASK,
		.SupportivityStruct = &session_0x2_supportivity
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

void SID_10_startTimeout(uint16_t t)
{
    return;
}
