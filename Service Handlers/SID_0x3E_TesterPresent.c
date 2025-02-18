#include "SID_0x3E_TesterPresent.h"

UDS_RESPONSE_SUPPRESSION_t SID_3E_Handler(UDS_REQ_t * request, UDS_RES_t * response, UDS_Server_t * server)
{
    //reset timer
    RESET_TIMER_FUNC();

    if(request->data[1] & 1<<7)
    {
        return UDS_SUPPRESS_RESPONSE;
    }
    else
    {
        response->data[0] = SID_3E_POS_RES_CODE;
        response->data[1] = request->data[1]; //0x00 if we passed the subfunction check
        return UDS_NO_SUPPRESS_RESPONSE;
    }
}

void resetTimer(void)
{
    return;
}

UDS_SubFunctionCheckResult_t SID_3E_subFunctionChecks(uint8_t subFunction,UDS_Server_t* server)
{
    switch(subFunction)
    {
        case 0x00:
            return UDS_SUB_FUNC_E_OK;
        default:
            return UDS_SUB_FUNC_NO_SUB_FUNC;
    }
}
