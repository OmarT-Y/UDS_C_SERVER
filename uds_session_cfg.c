/****************************************************************************************************
 *  File Name           : uds_session_cfg.c
 *  Description         : Source file for the supported Sessions
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_session_cfg.h"

/**
 * Session Records
 * Generated according to supported sessions
 */

UDS_Session_t defaultSession = 
{
    .SessionID          = UDS_DEFAULT_SESSION_ID,
    .p2_server_max      = UDS_DEFAULT_SESSION_P2_SERVER_MAX,
    .p2_server_star_max = UDS_DEFAULT_SESSION_P2_SERVER_START_MAX,
    .supportedService   = UDS_DEFAULT_SESSION_SUPPORTED_SID_MASK
};

#ifdef UDS_PROGRAMMING_SESSION_ENABLED
UDS_Session_t programmingSession = 
{
    .SessionID          = UDS_PROGRAMMING_SESSION_ID,
    .p2_server_max      = UDS_PROGRAMMING_SESSION_P2_SERVER_MAX,
    .p2_server_star_max = UDS_PROGRAMMING_SESSION_P2_SERVER_START_MAX,
    .supportedService   = UDS_PROGRAMMING_SESSION_SUPPORTED_SID_MASK
};
#endif

#ifdef UDS_EXTENDED_DIAG_SESSION_ENABLED
UDS_Session_t extendedDiagSession = 
{
    .SessionID          = UDS_EXTENDED_DIAG_SESSION_ID,
    .p2_server_max      = UDS_EXTENDED_DIAG_SESSION_P2_SERVER_MAX,
    .p2_server_star_max = UDS_EXTENDED_DIAG_SESSION_P2_SERVER_START_MAX,
    .supportedService   = UDS_EXTENDED_DIAG_SESSION_SUPPORTED_SID_MASK
};
#endif

#ifdef UDS_SAFETY_SYS_DIAG_SESSION_ENABLED
UDS_Session_t safetySysDiagSession = 
{
    .SessionID          = UDS_SAFETY_SYS_DIAG_SESSION_ID,
    .p2_server_max      = UDS_SAFETY_SYS_DIAG_SESSION_P2_SERVER_MAX,
    .p2_server_star_max = UDS_SAFETY_SYS_DIAG_SESSION_P2_SERVER_START_MAX,
    .supportedService   = UDS_SAFETY_SYS_DIAG_SESSION_SUPPORTED_SID_MASK
};
#endif