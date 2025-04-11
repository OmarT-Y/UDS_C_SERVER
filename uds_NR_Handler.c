/****************************************************************************************************
 *  File Name           : UDS_NR_Handler.c
 *  Description         : Source file for sending NRC Responses
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_NR_Handler.h"

#define START_SEC_UDS_SEC_CODE
#include "uds_memMap.h"
void handleNRC(UDS_REQ_t* request,UDS_RES_t* response , uint8_t NRC , uint8_t SID)
{
    response->data[RESPONSE_SID_INDEX] = NEGATIVE_RESPONSE_SID_INDEX;
    response->data[FAILED_REQUEST_SID_INDEX] = SID;
    response->data[NEGATIVE_RESPONSE_CODE_INDEX] = NRC;
    response->udsDataLen = NEGATIVE_RESPONSE_LENGTH_INDEX;
    response->srcAdd = UDS_SERVER_FUNCTION_ADDRESS;
    response->trgAdd = request->srcAdd;
    response->msgType = request->msgType;
    response->trgAddType = UDS_A_TA_PHYSICAL;
    /*TODO : Handle remote*/
}
#define STOP_SEC_UDS_SEC_CODE
#include "uds_memMap.h"