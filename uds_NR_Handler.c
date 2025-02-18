/****************************************************************************************************
 *  File Name           : UDS_NR_Handler.c
 *  Description         : Source file for sending NRC Responses
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_NR_Handler.h"

void handleNRC(UDS_REQ_t* request,UDS_RES_t* response , uint8_t NRC , uint8_t SID)
{
    response->data[0] = 0x7F;
    response->data[1] = SID;
    response->data[2] = NRC;
    response->udsDataLen = 3;
    response->srcAdd = UDS_SERVER_FUNCTION_ADDRESS;
    response->trgAdd = request->srcAdd;
    response->msgType = request->msgType;
    response->trgAddType = UDS_A_TA_PHYSICAL;
    //TODO : Handle remote
}