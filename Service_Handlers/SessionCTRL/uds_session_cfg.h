/****************************************************************************************************
 *  File Name           : uds_session_cfg.h
 *  Description         : Header file for the supported Sessions
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_SESSION_CFG_H
#define UDS_SESSION_CFG_H

#include "uds_types.h"
#include "uds_sid_cfg.h"
#include "uds_helpers.h"

/*Array of all the session records*/
extern UDS_Session_t serverSessions[];

/*Pointer to the default uds session*/
#define UDS_DEFAULT_SESSION_PTR &(serverSessions[0])
/* Supported Sessions */
           
/************************************************************************Start of Generation************************************************************************/
#define UDS_FBL_MAX_NORIFTY_TRY_COUNT           5U
#define UDS_NUMBER_OF_SESSIONS                  3

/* 
 * Maps starting the timeout function to SID 0x10 Timeout function to a custom function handling
 * the timeout of SID 0x10 that encapsulates any needed OS calls
 */
#define START_TIMEOUT_FUNC SID_10_startTimeout
void SID_10_startTimeout(uint16_t t);


/*This part only if there is a programming session*/
#define UDS_PROGRAMMING_SESSION_ENABLED
#define UDS_PROGRAMMING_RESET_FUNCTION    reset_ecu



/* Default Session Parameters */
#define UDS_DEFAULT_SESSION_ID                              0x1
#define UDS_DEFAULT_SESSION_P2_SERVER_MAX                   5
#define UDS_DEFAULT_SESSION_P2_SERVER_START_MAX             5
#define UDS_DEFAULT_SESSION_SUPPORTED_SID_MASK              {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}



/* Programming Session parameters */
#define UDS_PROGRAMMING_SESSION_ID                          0x2
#define UDS_PROGRAMMING_SESSION_P2_SERVER_MAX               6
#define UDS_PROGRAMMING_SESSION_P2_SERVER_START_MAX         6
#define UDS_PROGRAMMING_SESSION_SUPPORTED_SID_MASK          {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}


 /* Extended Diagnostics session parameters */
 /*
 #define UDS_EXTENDED_DIAG_SESSION_ID                        0x3
 #define UDS_EXTENDED_DIAG_SESSION_P2_SERVER_MAX             7
 #define UDS_EXTENDED_DIAG_SESSION_P2_SERVER_START_MAX       7
 #define UDS_EXTENDED_DIAG_SESSION_SUPPORTED_SID_MASK        7

 /* Safety System Diagnostics Session Parameters */
 /*
 #define UDS_SAFETY_SYS_DIAG_SESSION_ID                      0x4
 #define UDS_SAFETY_SYS_DIAG_SESSION_P2_SERVER_MAX           8
 #define UDS_SAFETY_SYS_DIAG_SESSION_P2_SERVER_START_MAX     8
 #define UDS_SAFETY_SYS_DIAG_SESSION_SUPPORTED_SID_MASK      8
*/
#endif