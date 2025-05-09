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
#include "uds_helpers.h"

#define UDS_SECURITY_ACCESS_REQUEST_SEED                            0x1
#define UDS_SECURITY_ACCESS_SEND_KEY                                0x0
void UDS_securityAccess_attemptCount_timeout(uint16_t);

/*************************************************************************Start of Generation*************************************************************************/
/* maximum number of invalid attempts */
#define MAX_INVALID_ATTEMPTS                                         3U
#define UDS_NUMBER_OF_SECURITY_LEVELS                                2U



#define SECURITY_LEVEL_0x00_ID                                       0x0
#define SECURITY_LEVEL_0x00_SUPPORTED_SID_MASK                       {0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
#define SECURITY_LEVEL_0x00_SEED_LENGTH                              2U
#define SECURITY_LEVEL_0x00_KEY_LENGTH                               2U
#define SECURITY_LEVEL_0x00_TIMEOUT                                  100000UL
const uint8_t* secLvl_0x00_seedFunc(void);
uint8_t  secLvl_0x00_keyCheckFunc(uint8_t*);


#define SECURITY_LEVEL_0x01_ID                                       0x1
#define SECURITY_LEVEL_0x01_SUPPORTED_SID_MASK                       {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}
#define SECURITY_LEVEL_0x01_SEED_LENGTH                              2U
#define SECURITY_LEVEL_0x01_KEY_LENGTH                               2U
#define SECURITY_LEVEL_0x01_TIMEOUT                                  100000UL
const uint8_t* secLvl_0x01_seedFunc(void);
uint8_t  secLvl_0x01_keyCheckFunc(uint8_t*);

#define SECURITY_LVL_DEFAULT_ID                                      SECURITY_LEVEL_0x00_ID
#define SECURITY_LVL_DEFAULT_STRUCT_PTR                              &securityLevels[0U]
/**************************************************************************End of Generation**************************************************************************/

extern UDS_SecurityLevel_t  securityLevels [];

/**
 * @brief UDS Security Level status
 * @param SECURITY_LEVEL_NO_REQUESTS Request seed not received
 * @param SECURITY_LEVEL_SEED_SENT_WAITING_KEY Request seed received
 */
typedef enum
{
   SECURITY_LEVEL_NO_REQUESTS,
   SECURITY_LEVEL_SEED_SENT_WAITING_KEY
}UDS_securityLevelStatus_t;

 /**
 * @brief UDS Security Level request info
 * @param level security level
 * @param status status of the security level
 */
 typedef struct
 {
    uint8_t                     level;
    UDS_securityLevelStatus_t   status;
 }securityAccessRequestInfo;

#endif
