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
 static const uint8_t sessions_0000[] = {0, 1};
 
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED 
 static const uint8_t security_0000[] = {0, 1};
 #endif

 static const UDS_SubFunctionSupportivity_t did_0000_supportivity = 
 {
     .supportedSessions = sessions_0000,
     .supportedSessionsLen = 2U
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED
     ,
     .supportedSecurityLvl = security_0000,
     .supportedSecurityLvlLen = 2U
 #endif
 };
 static const uint8_t sessions_0001[] = {0, 1};
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED 
 static const uint8_t security_0001[] = {0, 1};
 #endif
 static const UDS_SubFunctionSupportivity_t did_0001_supportivity = 
 {
     .supportedSessions = sessions_0001,
     .supportedSessionsLen = 2U
 #ifdef UDS_SECURITY_LEVEL_SUPPORTED
     ,
     .supportedSecurityLvl = security_0001,
     .supportedSecurityLvlLen = 2U
 #endif
 };
 
 uint8_t did_0x0000Write(uint8_t* data)
 {

    return 1;
 }
 
 uint8_t did_0x0001Write(uint8_t* data)
 {
    uint16_t crc = (data[0] << 8) | data[1];
    uint32_t app_length = (data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5];
    flash_flashbank_metadata(crc, app_length);
    return 1;
 }

 uint8_t did_0x0002Write(uint8_t* data)
 {

    return 1;
 }  

 uint8_t did_0x0003Write(uint8_t* data)
 {

     return 1;
 }
 
 const UDS_DID_t UDS_DIDS[UDS_NUM_OF_DIDS] =
 {
     {
        /*app B Valid flag*/
         .ID = 0x0000,
         .dataLen = 1,
         .isSingleBlock = 1,
         .DID_Access = WRITE_ONLY,
         .writeDIDptr = did_0x0000Write,
         .readDIDptr = NULL,
         .SupportivityStruct = &did_0000_supportivity
     },
     {
        /*app B Meta Data*/
         .ID = 0x0001,
         .dataLen = 6,
         .isSingleBlock = 1,
         .DID_Access = WRITE_ONLY,
         .writeDIDptr = did_0x0001Write,
         .readDIDptr = NULL,
         .SupportivityStruct = &did_0001_supportivity
     }
};
 /*************************************************************************End Of Generation*************************************************************************/
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    /* C11 or later: Safe to use static_assert */
    #include <assert.h>
    static_assert(sizeof(UDS_DIDS) == sizeof(UDS_DID_t) * UDS_NUM_OF_DIDS,
                  "The number of the supported DIDs doesn't match its generated macro (UDS_NUM_OF_DIDS)");
#else
    typedef char SizeMismatchCheck[
        (sizeof(UDS_DIDS) == sizeof(UDS_DID_t) * UDS_NUM_OF_DIDS) ? 1 : -1];
#endif


 #define STOP_SEC_UDS_SEC_CONST_DATA
 #include "uds_memMap.h"
