/****************************************************************************************************
 *  File Name           : uds_DID_cfg.h
 *  Description         : Header file for the UDS server supported DIDs
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_DID_CFG_H_
#define UDS_DID_CFG_H_


#include "uds_types.h"
#include "uds_securityLvl_cfg.h"
#include "uds_session_cfg.h"
#include "uds_sid_cfg.h"
#include "uds_helpers.h"

#include "uds_DID_types.h"
/*************************************************************************Start of generation*************************************************************************/
#define UDS_NUM_OF_DIDS                             2U
#define MAX_NUM_OF_READABLE_DIDS_IN_ONE_REQUEST     3U
#define MAX_READ_RESPONSE_LEN                       8U
#define MAX_WRITE_REQUEST_LEN                       8U
#define UDS_READ_DID_SINGLE_DID_MAX_LEN             8U
/*Here For each function used in the the struct UDS_DID_t (the read and write function) the function prototype should be generated here*/
/**************************************************************************End of generation**************************************************************************/

extern const UDS_DID_t UDS_DIDS[UDS_NUM_OF_DIDS];

/**
 * @brief Does Did specific checks ( Security level , Sessions etc) , Check whether the requested DID is valid or not
 * @param id Data identifierr
 * @param activeSessionID current server active session
 * @param activeSecurityLvl current server active security level
 * @param didRecord pointer to a didRecord that the function is to fill with the required did in the request
 * @return returns the result of the checks
 */
DID_CHECK_RES_t checkDID(uint16_t id,uint8_t activeSessionID,uint8_t activeSecurityLvl, UDS_DID_t *didRecord);

#endif
