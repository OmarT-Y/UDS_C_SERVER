/****************************************************************************************************
 *  File Name           : uds_sid_cfg.h
 *  Description         : Source file for the UDS server supported SIDs
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_sid_cfg.h"

#define START_SEC_UDS_SEC_CONST_DATA
#include "uds_memMap.h"
/**
 * Service Records
 * Generated according to supported services
 */

/*TODO : change the == 1 to == STD_ON*/
UDS_SID_RECORD_t UDS_a_supportedSID_Record[] = 
{
		{
				.sid                                    = SID_10_DIAG_SESSION_CTRL,
				.minLen                                 = SID_10_DIAG_SESSION_CTRL_MIN_LEN,
				.handler                                = SID_10_Handler,
				.hasSubFunc                             = SID_10_DIAG_SESSION_CTRL_HAS_SUB_FUNC,
#if (SID_10_DIAG_SESSION_CTRL_HAS_SUB_FUNC==1)
				.subfuncSupportivityStructGet           = SID_10_getSubFunctSuppStruct
#else
				.subfuncSupportivityStructGet           = NULL
#endif
		},
		{
				.sid                                    = SID_11_ECU_RESET,
				.minLen                                 = SID_11_ECU_RESET_MIN_LEN,
				.handler                                = SID_11_Handler,
				.hasSubFunc                             = SID_11_ECU_RESET_HAS_SUB_FUNC,
#if (SID_11_ECU_RESET_HAS_SUB_FUNC==1)
				.subfuncSupportivityStructGet           = SID_11_getSubFunctSuppStruct
#else
				.subfuncSupportivityStructGet           = NULL
#endif
		},
		{
				.sid                        = SID_22_READ_DID,
				.minLen                     = SID_22_READ_DID_MIN_LEN,
				.handler                    = SID_22_Handler,
				.hasSubFunc                 = SID_22_READ_DID_HAS_SUB_FUNC,
#if (SID_22_READ_DID_HAS_SUB_FUNC==1)
				.subfuncSupportivityStructGet           = SID_22_getSubFunctSuppStruct
#else 
				.subfuncSupportivityStructGet           = NULL
#endif
		},
		//    {
		//        .sid                        = SID_27_SECURITY_ACCESS,
		//        .minLen                     = SID_27_SECURITY_ACCESS_MIN_LEN,
		//        .handler                    = SID_27_Handler,
		//        .hasSubFunc                 = SID_27_SECURITY_ACCESS_HAS_SUB_FUNC,
		//#if (SID_27_SECURITY_ACCESS_HAS_SUB_FUNC==1)
		//        .subfuncSupportivityStructGet           = SID_27_getSubFunctSuppStruct
		//#else
		//        .subfuncSupportivityStructGet           = NULL
		//#endif
		//    },
		{
				.sid                        = SID_2E_WRITE_DID,
				.minLen                     = SID_2E_WRITE_DID_MIN_LEN,
				.handler                    = SID_2E_Handler,
				.hasSubFunc                 = SID_2E_WRITE_DID_HAS_SUB_FUNC,
#if (SID_2E_WRITE_DID_HAS_SUB_FUNC==1)
				.subfuncSupportivityStructGet           = SID_2E_getSubFunctSuppStruct
#else 
				.subfuncSupportivityStructGet           = NULL
#endif
		},
		{
				.sid                        = SID_31_ROUTINE_CTRL,
				.minLen                     = SID_31_ROUTINE_CTRL_MIN_LEN,
				.handler                    = SID_31_Handler,
				.hasSubFunc                 = SID_31_ROUTINE_CTRL_HAS_SUB_FUNC,
#if (SID_31_ROUTINE_CTRL_HAS_SUB_FUNC==1)
				.subfuncSupportivityStructGet           = SID_31_getSubFunctSuppStruct
#else 
				.subfuncSupportivityStructGet           = NULL
#endif
		},
		{
				.sid                        = SID_34_REQUEST_DOWNLOAD,
				.minLen                     = SID_34_REQUEST_DOWNLOAD_MIN_LEN,
				.handler                    = SID_34_Handler,
				.hasSubFunc                 = SID_34_REQUEST_DOWNLOAD_HAS_SUB_FUNC,
#if (SID_34_REQUEST_DOWNLOAD_HAS_SUB_FUNC == 1)
				.subfuncSupportivityStructGet           = SID_34_getSubFunctSuppStruct
#else
				.subfuncSupportivityStructGet           = NULL
#endif
		},

		{
				.sid                        = SID_36_TRANSFER_DATA,
				.minLen                     = SID_36_TRANSFER_DATA_MIN_LEN,
				.handler                    = SID_36_Handler,
				.hasSubFunc                 = SID_36_TRANSFER_DATA_HAS_SUB_FUNC,
#if (SID_36_TRANSFER_DATA_HAS_SUB_FUNC == 1)
				.subfuncSupportivityStructGet           = SID_36_getSubFunctSuppStruct
#else
				.subfuncSupportivityStructGet           = NULL
#endif
		},
		{
			.sid                        = SID_37_REQUEST_TRANSFER_EXIT,
			.minLen                     = SID_37_REQUEST_TRANSFER_EXIT_MIN_LEN,
			.handler                    = SID_37_Handler,
			.hasSubFunc                 = SID_37_TRANSFER_DATA_HAS_SUB_FUNC,
#if (SID_37_TRANSFER_DATA_HAS_SUB_FUNC == 1)
			.subfuncSupportivityStructGet           = SID_37_getSubFunctSuppStruct
#else
			.subfuncSupportivityStructGet           = NULL
#endif
	},
		{
				.sid                                    = SID_3E_TESTER_PRESENT,
				.minLen                                 = SID_3E_TESTER_PRESENT_MIN_LEN,
				.handler                                = SID_3E_Handler,
				.hasSubFunc                             = SID_3E_TESTER_PRESENT_HAS_SUB_FUNC,
#if (SID_3E_TESTER_PRESENT_HAS_SUB_FUNC==1)
				.subfuncSupportivityStructGet           = SID_3E_getSubFunctSuppStruct
#else
				.subfuncSupportivityStructGet           = NULL
#endif
		}
};

#define STOP_SEC_UDS_SEC_CONST_DATA
#include "uds_memMap.h"
