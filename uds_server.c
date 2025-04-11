/****************************************************************************************************
 *  File Name           : uds_server.c
 *  Description         : Source file for the uds server
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/
#include "uds_server.h"

#define START_SEC_UDS_SEC_DATA
#include "uds_memMap.h"
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
#define STOP_SEC_UDS_SEC_DATA
#include "uds_memMap.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
void UDS_serverInit(void)
{
    udsServer.activeSession = UDS_DEFAULT_SESSION_PTR;

#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    udsServer.activeSecLvl = SECURITY_LVL_DEFAULT_STRUCT_PTR;
#endif 

#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
    supplierCheck = UDS_SUPPLIER_CHECK_FUNCTION;
#endif

#ifdef UDS_MANUFACTURER_CHECK_SUPPORTED
    manufactCheck = UDS_MANUFACTURER_CHECK_FUNCTION;
#endif
}

static UDS_SubFunctionCheckResult_t UDS_SubFunctionChecks(const UDS_SubFunctionSupportivity_t* supportivity)
{
    if(NULL == supportivity)
    {
        return UDS_SUB_FUNC_NO_SUB_FUNC;
    }
    uint8_t i = 0U;
    for(;i<supportivity->supportedSessionsLen;i++)
    {
        if(udsServer.activeSession->SessionID == supportivity->supportedSessions[i])
        {
            break;
        }
    }
    if(i>=supportivity->supportedSessionsLen)
    {
        return UDS_SUB_FUNC_NO_ACTIVE_SESSION;
    }

#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    i = 0U;
    for(;i<supportivity->supportedSecurityLvlLen;i++)
    {
        if(udsServer.activeSecLvl->SecurityLvlID == supportivity->supportedSecurityLvl[i])
        {
            break;
        }
    }
    if(i>=supportivity->supportedSecurityLvlLen)
    {
        return UDS_SUB_FUNC_NO_SECURITY_LEVEL;
    }
#endif
    return UDS_SUB_FUNC_E_OK;
}
static UDS_RESPONSE_SUPPRESSION_t  UDS_handleRequest(UDS_REQ_t* request, UDS_RES_t * response)
{
    /*TODO : Handle suppressed responses
    TODO : How to handle remote requests
    TODO : How to handle addresses
    Manufacturer specific check*/
#ifdef UDS_MANUFACTURER_CHECK_SUPPORTED
    if(NULL != manufactCheck)
    {
        return manufactCheck(request,response,&udsServer);
    }
    else
    {
        /*TODO:error*/
    }
#endif
    /*Check if the SID is supported*/
    UDS_SID_RECORD_t* sid_record = (UDS_SID_RECORD_t*)UDS_BinaryID_Search(UDS_a_supportedSID_Record,sizeof(UDS_SID_RECORD_t),UDS_NUMBER_OF_SUPPORTED_SERVICES,&(request->data[0]),1);
    if(NULL==sid_record)
    {
        if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        handleNRC(request,response,UDS_NRC_0x11_SERRVICE_NOT_SUPPORTED,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
        /*negative response 0x11 (service not supported)*/
    }
    /*check if the SID is supported in the active seesion
    TODO : change the == 0 to == STD_ON*/
    if(0 == CHECK_ARRAY_BIT_OVER_32(udsServer.activeSession->supportedService,sid_record->sid))
    {
        if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        /*negative response 0x7F (not supported in active session)*/
        handleNRC(request,response,UDS_NRC_0x7F_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }

    /*security check*/
#ifdef UDS_SECURITY_LEVEL_SUPPORTED
    if(0 == CHECK_ARRAY_BIT_OVER_32(udsServer.activeSecLvl->supportedService,sid_record->sid))
    {
        if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        /*negative response 0x33 (not supported in security level)*/
        handleNRC(request,response,UDS_NRC_0x33_SECURITY_ACCESS_DENIED,request->data[REQUEST_SID_INDEX]);
        return UDS_NO_SUPPRESS_RESPONSE;
    }
#endif

    /*Supplier Specific check*/
#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
    if(NULL != supplierCheck)
    {
        return supplierCheck(request,response,&udsServer);
    }
    else
    {
        /*TODO:error*/
    }
#endif

    /*check if 0x31*/
#ifdef SID_31_ROUTINE_CTRL_ENABLED
    if(sid_record->sid == SID_31_ROUTINE_CTRL)
    {
        /*invoke the service handler*/
        sid_record->handler(request,response,&udsServer);
    }
#endif
    /*check if the service has sub function*/
    if(sid_record->hasSubFunc)
    {
        /*minimum length check transfer exit case may be length =1 */
        if(request->udsDataLen < 2U)
        {
            if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
            {
                return UDS_SUPPRESS_RESPONSE;
            }
            /*NRC 0x13 (invalid length)*/
            handleNRC(request,response,UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT,request->data[REQUEST_SID_INDEX]);
            return UDS_NO_SUPPRESS_RESPONSE;
        }
        const UDS_SubFunctionSupportivity_t* subFuncSuppStruct = sid_record->subfuncSupportivityStructGet(request->data[REQUEST_SUB_FUNCTION_INDEX] & 0x7FU);
        UDS_SubFunctionCheckResult_t subFunctionCheckResults = UDS_SubFunctionChecks(subFuncSuppStruct);
        if(UDS_SUB_FUNC_E_OK!=subFunctionCheckResults && UDS_A_TA_FUNCTIONAL==request->trgAddType)
        {
            return UDS_SUPPRESS_RESPONSE;
        }
        switch(subFunctionCheckResults)
        {
            case UDS_SUB_FUNC_E_OK:
                /*call the handler*/
                return sid_record->handler(request,response,&udsServer);
                /*TODO:check if a positive response should be suppressed*/
                break;
            case UDS_SUB_FUNC_NO_ACTIVE_SESSION:
                handleNRC(request,response,UDS_NRC_0x7E_SUB_FUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION,request->data[REQUEST_SID_INDEX]);
                break;
#ifdef UDS_SECURITY_LEVEL_SUPPORTED 
            case UDS_SUB_FUNC_NO_SECURITY_LEVEL:
                handleNRC(request,response,UDS_NRC_0x33_SECURITY_ACCESS_DENIED,request->data[REQUEST_SID_INDEX]);
                break;
#endif
            case UDS_SUB_FUNC_REQUEST_SEQUENCE_FAIL:
                handleNRC(request,response,UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR,request->data[REQUEST_SID_INDEX]);
                break;
            case UDS_SUB_FUNC_NO_SUB_FUNC:
                if(UDS_A_TA_FUNCTIONAL==request->trgAddType)
                {
                    return UDS_SUPPRESS_RESPONSE;
                }
                handleNRC(request,response,UDS_NRC_0x12_SUB_FUNCTION_NOT_SUPPORTED,request->data[REQUEST_SID_INDEX]);
                break;
            default:
                handleNRC(request,response,UDS_NRC_0x10_GENERAL_REJECT,request->data[REQUEST_SID_INDEX]);
                break;
        }
        return UDS_NO_SUPPRESS_RESPONSE;
    }
    else 
    {
        return sid_record->handler(request,response,&udsServer);
    }
}

void UDS_defaultSessionResetCallBack()
{
    if(udsServer.activeSession->SessionID != UDS_DEFAULT_SESSION_ID)
    {
        udsServer.activeSession = UDS_DEFAULT_SESSION_PTR;
    }
}

void sendResponse(UDS_RES_t* response)
{
    /*sync call*/
}

void UDS_RequestIndication(UDS_REQ_t* request)
{
    if(UDS_SERVER_QUEUE_MAX_NUMBER_OF_REQS == UDS_readyReqCheck())
    {
        /*Full Queue*/
        uint8_t responseData[4U] = {0U};
        UDS_RES_t response =
        {
            .remoteAdd  = request->remoteAdd,
            .data       = responseData
        };
        handleNRC(request,&response,UDS_NRC_0x21_BUSY_REPEAT_REQUEST,request->data[REQUEST_SID_INDEX]);
        sendResponse(&response);
    }
    else
    {
        if(0U == UDS_Request_enqueue(request))
        {
            uint8_t responseData[4U] = {0U};
            UDS_RES_t response =
            {
                .remoteAdd  = request->remoteAdd,
                .data       = responseData
            };
            handleNRC(request,&response,UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE,request->data[REQUEST_SID_INDEX]);
            sendResponse(&response);
        }
    }
}
 void UDS_mainFunction(void)
 {
    if(UDS_readyReqCheck()>0U)
    {
        uint8_t responseData[UDS_MAX_RESPONSE_DATA_LENGTH] = {0U};
        UDS_RES_t response =
        {
            .data       = responseData
        };
        UDS_REQ_t* request = UDS_peekNextRequest();
        if(NULL != request)
        {
            if(UDS_NO_SUPPRESS_RESPONSE==UDS_handleRequest(request,&response))
            {
                
                response.srcAdd = UDS_SERVER_FUNCTION_ADDRESS;
                response.trgAdd = request->srcAdd;
                response.msgType = request->msgType;
                response.trgAddType = UDS_A_TA_PHYSICAL;
                sendResponse(&response);
                UDS_Request_dequeue();
            }
        }
    }
 }

#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"