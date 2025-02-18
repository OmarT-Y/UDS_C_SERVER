/****************************************************************************************************
 *  File Name           : uds_server.c
 *  Description         : Source file for the uds server
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/
#include "uds_server.h"

/**
 * @brief Current UDS server
 * @param activeSession  Current Active Session in the UDS Server -Initialized to Default Session
 * @param Current Active Security level in the UDS Server -Only created if Security level is supported -Initialized to Default Security level according to Configuration
 */
static UDS_Server_t udsServer = 
{
    .activeSession  = NULL
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    ,
    .activeSecLvl   = NULL
#endif
};


#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
/**
 * @brief Pointer to function specific to supplier checks 
 * @note Only created if supplier checks are enabled through configurations
 */
static UDS_SupplierCheckFuncPtr_t supplierCheck = NULL;
#endif

#ifdef UDS_MANUFACTURER_CHECK_SUPPORTED
/**
 * @brief Pointer to function specific to manufacturer checks
 * @note Only created if manufacturer checks are enabled through configurations
 */
static UDS_ManufacCheckFuncPtr_t manufactCheck = NULL;
#endif

void UDS_serverInit(void)
{
    udsServer.activeSession = &defaultSession;

#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    udsServer.activeSecLvl = UDS_SECURITY_LEVEL_DEFAULT_PTR;
#endif 

#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
    supplierCheck = UDS_SUPPLIER_CHECK_FUNCTION;
#endif

#ifdef UDS_MANUFACTURER_CHECK_SUPPORTED
    manufactCheck = UDS_MANUFACTURER_CHECK_FUNCTION;
#endif
}

static UDS_RESPONSE_SUPPRESSION_t UDS_handleRequest(UDS_REQ_t* request,UDS_RES_t * response)
{
    //TODO : Handle suppressed responses
    //TODO : How to handle remote requests
    //TODO : How to handle addresses
    //Manufacturer specific check
#ifdef UDS_MANUFACTURER_CHECK_SUPPORTED
    if(NULL != manufactCheck)
    {
        return manufactCheck(request,response,&udsServer);
    }
    else
    {
        //TODO:error
    }
#endif
    //Check if the SID is supported
    UDS_SID_RECORD_t* sid_record = UDS_getServiceRecord(request->data[0]);
    if(NULL==sid_record)
    {
        if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        handleNRC(request,response,UDS_NRC_0x11_SERRVICE_NOT_SUPPORTED,request->data[1]);
        return UDS_NO_SUPPRESS_RESPONSE;
        //negative response 0x11 (service not supported)
    }
    //check if the SID is supported in the
    //TODO : change the == 0 to == STD_NO
    if(((udsServer.activeSession->supportedService[(sid_record->sid)>>5])&1<<((sid_record->sid)%32))==0)
    {
        if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        //negative response 0x7F (not supported in active session)
        handleNRC(request,response,UDS_NRC_0x7F_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION,request->data[1]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }

    //security check
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    if(((udsServer.activeSecLvl->supportedService[(sid_record->sid)>>5])&1<<((sid_record->sid)%32))==0)
    {
        if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        //negative response 0x33 (not supported in security level)
        handleNRC(request,response,UDS_NRC_0x33_SECURITY_ACCESS_DENIED,request->data[1]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
#endif

    //Supplier Specific check
#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
    if(NULL != supplierCheck)
    {
        return supplierCheck(request,response,&udsServer);
    }
    else
    {
        //TODO:error
    }
#endif

    //check if 0x31
#ifdef SID_31_ROUTINE_CTRL_ENABLED
    if(sid_record->sid == SID_31_ROUTINE_CTRL)
    {
        //invoke the service handler
        sid_record->handler(request,response,&udsServer);
    }
#endif
    //chekc if the service has sub function
    if(sid_record->hasSubFunc)
    {
        //minimum lenght check 
        if(request->udsDataLen<2)
        {
            if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
            {
                return UDS_SUPPRESS_RESPONSE;;
            }
            //NRC 0x13 (invalid length)
            handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[1]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        //sub function ever supported check
        if(((sid_record->supportedSubFunc[(request->data[1])>>5])&1<<((request->data[1])%32))==0)
        {
            if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
            {
                return UDS_SUPPRESS_RESPONSE;
            }
            //TODO : NRC 0x12 (sub funciton not supported)
            handleNRC(request,response,UDS_NRC_0x12_SUB_FUNCTION_NOT_SUPPORTED,request->data[1]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        UDS_SubFunctionCheckResult_t subFunctionCheckResults = sid_record->subfuncChecskPtr(request->data[1],&udsServer);
        if(UDS_SUB_FUNC_E_OK!=subFunctionCheckResults && UDS_A_TA_FUNCTIONAL==request->trgAddType)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        switch(subFunctionCheckResults)
        {
            case UDS_SUB_FUNC_E_OK:
                //call the handler
                return sid_record->handler(request,response,&udsServer);
                //TODO:check if a positive response should be suppressed
                break;
            case UDS_SUB_FUNC_NO_ACTIVE_SESSION:
                handleNRC(request,response,UDS_NRC_0x7E_SUB_FUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION,request->data[1]);
                break;
            case UDS_SUB_FUNC_NO_SECURITY_LEVEL:
                handleNRC(request,response,UDS_NRC_0x33_SECURITY_ACCESS_DENIED,request->data[1]);
                break;
            case UDS_SUB_FUNC_REQUEST_SEQUENCE_FAIL:
                handleNRC(request,response,UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR,request->data[1]);
                break;
            default:
                handleNRC(request,response,UDS_NRC_0x10_GENERAL_REJECT,request->data[1]);
                break;
            return UDS_NO_SUPPRESS_RESPONSE;
        }
    }
}

void UDS_defaultSessionResetCallBack()
{
    if(udsServer.activeSession->SessionID != UDS_DEFAULT_SESSION_ID)
    {
        udsServer.activeSession = UDS_DEFAULT_SESSION_PTR;
    }
}

static void sendResponse(UDS_RES_t* response)
{

}

void UDS_RequestIndication(UDS_REQ_t* request)
{
    //TODO : SERVER Busy
    //TODO : How to handle response buffer
    UDS_RES_t response = 
    {
        .msgType    = request->msgType,
        .remoteAdd  = request->remoteAdd,
        .srcAdd     = request->srcAdd,
        .trgAdd     = request->trgAdd,
        .udsDataLen = 0,
        .trgAddType = request->trgAddType
    };
    UDS_handleRequest(request,&response);
    if(UDS_NO_SUPPRESS_RESPONSE==UDS_handleRequest(request,&response))
    {
        sendResponse(&response);
    }
}