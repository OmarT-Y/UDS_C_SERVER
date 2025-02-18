/****************************************************************************************************
 *  File Name           : uds_securityLvl_cfg.h
 *  Description         : Header file for the Security Level configurations
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 16-2-2025 File Creation
 ****************************************************************************************************/


#ifndef UDS_SECURITY_LVL_CFG_H
#define UDS_SECURITY_LVL_CFG_H
#include "uds_server_cfg.h"
#include "uds_types.h"

/* Generate Security Level Details if it is enabled through Configuration */
#ifdef UDS_SECURITY_LEVEL_SUPPORTED

/* The enable definitions are generated */
#define SECURITY_LVL_DEFAULT
#define SECURITY_LVL_1 


/* Default level parameters */
#ifdef  SECURITY_LVL_DEFAULT
#define SECURITY_LEVEL_DEFAULT_ID                                  0x0
#define SECURITY_LEVEL_DEFAULT_SUPPORTED_SID_MASK                  0XF
extern  UDS_SecurityLevel_t securityLevelDefault;
#define UDS_SECURITY_LEVEL_DEFAULT_PTR (&securityLevelDefault)
#endif

/* Security Level 1 parameters */
#ifdef  SECURITY_LVL_1
#define SECURITY_LEVEL_1_ID                                        0x1
#define SECURITY_LEVEL_1_SUPPORTED_SID_MASK                        0X1
extern  UDS_SecurityLevel_t securityLevel_1;
#define UDS_SECURITY_LEVEL_1_PTR (&securityLevel_1)
#endif



#endif
#endif