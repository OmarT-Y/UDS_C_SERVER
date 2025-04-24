/****************************************************************************************************
 *  File Name           : uds_DID_cfg.c
 *  Description         : Source file for the UDS server supported DIDs
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

 #include "uds_DID_cfg.h"



 /* Array of DID structure according to configuration */
 #define START_SEC_UDS_SEC_CONST_DATA
 #include "uds_memMap.h"
 /*************************************************************************End Of Generation*************************************************************************/
 static const uint8_t sessions_0100[] = {0, 1};
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED 
 static const uint8_t security_0100[] = {0, 1};
 #endif
 static const UDS_SubFunctionSupportivity_t did_0100_supportivity = 
 {
     .supportedSessions = sessions_0100,
     .supportedSessionsLen = 2U
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED
     ,
     .supportedSecurityLvl = security_0100,
     .supportedSecurityLvlLen = 2U
 #endif
 };
 static const uint8_t sessions_0102[] = {0, 1};
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED 
 static const uint8_t security_0102[] = {0, 1};
 #endif
 static const UDS_SubFunctionSupportivity_t did_0102_supportivity = 
 {
     .supportedSessions = sessions_0102,
     .supportedSessionsLen = 2U
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED
     ,
     .supportedSecurityLvl = security_0102,
     .supportedSecurityLvlLen = 2U
 #endif
 };
 
 uint8_t did_0x0100Read(uint8_t* data)
 {
     data[0] = 0xfa;
     data[1] = 0xde;
     return 1;
 }
 
 uint8_t did_0x0102Read(uint8_t* data)
 {
     data[0] = 0xde;
     data[1] = 0xfa;
     return 1;
 }
 
 const UDS_DID_t UDS_DIDS[UDS_NUM_OF_DIDS] =
 {
     {
         .ID = 0x0100,
         .dataLen = 2,
         .isSingleBlock = 1,
         .DID_Access = READ_ONLY,
         .writeDIDptr = NULL,
         .readDIDptr = did_0x0100Read,
         .SupportivityStruct = &did_0100_supportivity
     },
     {
         .ID = 0x0102,
         .dataLen = 3,
         .isSingleBlock = 0,
         .DID_Access = READ_WRITE,
         .writeDIDptr = NULL,
         .readDIDptr = did_0x0102Read,
         .SupportivityStruct = &did_0102_supportivity
     }
 };
 /*************************************************************************End Of Generation*************************************************************************/
 #define STOP_SEC_UDS_SEC_CONST_DATA
 #include "uds_memMap.h"
