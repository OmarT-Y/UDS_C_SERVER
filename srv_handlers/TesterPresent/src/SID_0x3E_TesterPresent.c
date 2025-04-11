/****************************************************************************************************
 *  File Name           : SID_0x3E_TesterPresent.c
 *  Description         : Source file for the service 0x3E Tester Present Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/


#include "uds_sid_cfg.h"

#include "../../../UDS/Service_Handlers/TesterPresent/SID_0x3E_cfg.h"
static void resetTimer(void)
{
    return;
}
UDS_RESPONSE_SUPPRESSION_t SID_3E_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
    /*reset timer*/
    RESET_TIMER_FUNC();

    if(CHECK_REQUEST_SUPPRESS_BIT(request))
    {
        return UDS_SUPPRESS_RESPONSE;
    }
    else
    {
        response->data[RESPONSE_SID_INDEX] = SID_3E_POS_RES_CODE;
        response->data[1U] = request->data[1U]; /*0x00 if we passed the subfunction check*/
        response->udsDataLen = 2U;
        return UDS_NO_SUPPRESS_RESPONSE;
    }
}