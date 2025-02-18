/****************************************************************************************************
 *  File Name           : uds_sid_cfg.h
 *  Description         : Source file for the UDS server supported SIDs
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_sid_cfg.h"

/**
 * Service Records
 * Generated according to supported services
 */

#ifdef SID_10_DIAG_SESSION_CTRL_ENABLED
const UDS_SID_RECORD_t Sid_0x10_DiagSessionCtrl_record = 
{
    .sid                        = SID_10_DIAG_SESSION_CTRL,
    .minLen                     = SID_10_DIAG_SESSION_CTRL_MIN_LEN,
    .handler                    = SID_10_Handler,
    .hasSubFunc                 = SID_10_DIAG_SESSION_CTRL_HAS_SUB_FUNC,
    .subfuncChecskPtr           = SID_10_subFunctionChecks,
    .supportedSubFunc           = SID_10_DIAG_SESSION_CTRL_SUB_FUNC_MASK
};
#endif

#ifdef SID_3E_TESTER_PRESENT_ENABLED
const UDS_SID_RECORD_t Sid_0x3E_TesterPresent_record = 
{
    .sid              = SID_3E_TESTER_PRESENT,
    .minLen           = SID_3E_TESTER_PRESENT_MIN_LEN,
    .handler          = SID_3E_Handler,
    .hasSubFunc       = SID_3E_TESTER_PRESENT_HAS_SUB_FUNC,
    .subfuncChecskPtr = SID_3E_subFunctionChecks,
    .supportedSubFunc = SID_3E_TESTER_PRESENT_SUB_FUNC_MASK
};
#endif

#ifdef SID_22_READ_DID_ENABLED
const UDS_SID_RECORD_t Sid_0x22_ReadDID_record = 
{
    .sid              = SID_22_READ_DID,
    .minLen           = SID_22_READ_DID_MIN_LEN,
    .handler          = SID_22_Handler,
    .hasSubFunc       = SID_22_READ_DID_HAS_SUB_FUNC,
    .subfuncChecskPtr = SID_22_subFunctionChecks,
    .supportedSubFunc = SID_22_READ_DID_SUB_FUNC_MASK
};
#endif

#ifdef SID_2E_WRITE_DID_ENABLED
const UDS_SID_RECORD_t Sid_0x2E_WriteDID_record = 
{
    .sid              = SID_2E_WRITE_DID,
    .minLen           = SID_2E_WRITE_DID_MIN_LEN,
    .handler          = SID_2E_Handler,
    .hasSubFunc       = SID_2E_WRITE_DID_HAS_SUB_FUNC,
    .subfuncChecskPtr = SID_2E_subFunctionChecks,
    .supportedSubFunc = SID_2E_WRITE_DID_SUB_FUNC_MASK
};
#endif

#ifdef SID_27_SECURITY_ACCESS_ENABLED
const UDS_SID_RECORD_t Sid_0x27_SecurityAccess_record = 
{
    .sid              = SID_27_SECURITY_ACCESS,
    .minLen           = SID_27_SECURITY_ACCESS_MIN_LEN,
    .handler          = SID_27_Handler,
    .hasSubFunc       = SID_27_SECURITY_ACCESS_HAS_SUB_FUNC,
    .subfuncChecskPtr = SID_27_subFunctionChecks,
    .supportedSubFunc = SID_27_SECURITY_ACCESS_SUB_FUNC_MASK
};
#endif

#ifdef SID_31_ROUTINE_CTRL_ENABLED
const UDS_SID_RECORD_t Sid_0x31_RountineCtrl_record = 
{
    .sid              = SID_31_ROUTINE_CTRL,
    .minLen           = SID_31_ROUTINE_CTRL_MIN_LEN,
    .handler          = SID_31_Handler,
    .hasSubFunc       = SID_31_ROUTINE_CTRL_HAS_SUB_FUNC,
    .subfuncChecskPtr = SID_31_subFunctionChecks,
    .supportedSubFunc = SID_31_ROUTINE_CTRL_SUB_FUNC_MASK
};
#endif



UDS_SID_RECORD_t* UDS_getServiceRecord(uint8_t sid)
{
    switch(sid)
    {
#ifdef SID_10_DIAG_SESSION_CTRL_ENABLED
        case SID_10_DIAG_SESSION_CTRL:
            return &Sid_0x10_DiagSessionCtrl_record;
#endif

#ifdef SID_3E_TESTER_PRESENT_ENABLED
        case SID_3E_TESTER_PRESENT:
            return &Sid_0x3E_TesterPresent_record;
#endif

#ifdef SID_22_READ_DID_ENABLED
        case SID_22_READ_DID:
            return &Sid_0x22_ReadDID_record;
#endif

#ifdef SID_2E_WRITE_DID_ENABLED
        case SID_2E_WRITE_DID:
            return &Sid_0x2E_WriteDID_record;
#endif

#ifdef SID_27_SECURITY_ACCESS_ENABLED
        case SID_27_SECURITY_ACCESS:
            return &Sid_0x27_SecurityAccess_record;
#endif

#ifdef SID_31_ROUTINE_CTRL_ENABLED
        case SID_31_ROUTINE_CTRL:
            return &Sid_0x31_RountineCtrl_record;
#endif
        default:
        return NULL;
    }
}