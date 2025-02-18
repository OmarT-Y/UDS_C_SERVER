/****************************************************************************************************
 *  File Name           : uds_session_cfg.h
 *  Description         : Header file for the supported Sessions
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_SESSION_CFG_H
#define UDS_SESSION_CFG_H

#include "uds_types.h"

/* Supported Sessions */
#define UDS_PROGRAMMING_SESSION_ENABLED
#define UDS_EXTENDED_DIAG_SESSION_ENABLED
#define UDS_SAFETY_SYS_DIAG_SESSION_ENABLED


/* Default Session Parameters */
#define UDS_DEFAULT_SESSION_ID                              0x1
#define UDS_DEFAULT_SESSION_P2_SERVER_MAX                   5
#define UDS_DEFAULT_SESSION_P2_SERVER_START_MAX             5
#define UDS_DEFAULT_SESSION_SUPPORTED_SID_MASK              {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}
extern UDS_Session_t defaultSession;
#define UDS_DEFAULT_SESSION_PTR (&defaultSession)


#ifdef UDS_PROGRAMMING_SESSION_ENABLED
/* Programming Session parameters */
#define UDS_PROGRAMMING_SESSION_ID                          0x2
#define UDS_PROGRAMMING_SESSION_P2_SERVER_MAX               6
#define UDS_PROGRAMMING_SESSION_P2_SERVER_START_MAX         6
#define UDS_PROGRAMMING_SESSION_SUPPORTED_SID_MASK          6
extern UDS_Session_t programmingSession;
#define UDS_PROGRAMMING_SESSION_PTR (&programmingSession)
#endif

#ifdef UDS_EXTENDED_DIAG_SESSION_ENABLED
/* Extended Diagnostics session parameters */
#define UDS_EXTENDED_DIAG_SESSION_ID                        0x3
#define UDS_EXTENDED_DIAG_SESSION_P2_SERVER_MAX             7
#define UDS_EXTENDED_DIAG_SESSION_P2_SERVER_START_MAX       7
#define UDS_EXTENDED_DIAG_SESSION_SUPPORTED_SID_MASK        7
extern UDS_Session_t extendedDiagSession;
#define UDS_EXTENDED_DIAG_SESSION_PTR (&extendedDiagSession)
#endif

#ifdef UDS_SAFETY_SYS_DIAG_SESSION_ENABLED
/* Safety System Diagnostics Session Parameters */
#define UDS_SAFETY_SYS_DIAG_SESSION_ID                      0x4
#define UDS_SAFETY_SYS_DIAG_SESSION_P2_SERVER_MAX           8
#define UDS_SAFETY_SYS_DIAG_SESSION_P2_SERVER_START_MAX     8
#define UDS_SAFETY_SYS_DIAG_SESSION_SUPPORTED_SID_MASK      8
extern UDS_Session_t safetySysDiagSession;
#define UDS_SAFETY_SYS_DIAG_SESSION_PTR (&safetySysDiagSession)
#endif

#endif