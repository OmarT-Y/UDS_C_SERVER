/****************************************************************************************************
 *  File Name           : uds_DID_cfg.c
 *  Description         : Source file for the UDS server supported DIDs
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_DID_cfg.h"

UDS_DID UDS_DIDS[UDS_NUM_OF_DIDS] =
{
    {
        .ID                       = 0x0100,
        .dataLen                  = 2,
        .isSingleBlock            = 1, // TODO change to STD_TRUE
        .isReadOnly               = 1,
        .supportedSecuritryLevels = {0xFFFFFFFF, 0xFFFFFFFF},
        .supportedSessions        = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}

    },
    {   
        .ID                       = 0x0102,
        .dataLen                  = 3,
        .isSingleBlock            = 0, // TODO change to STD_FLASE
        .isReadOnly               = 0,
        .supportedSecuritryLevels = {0xFFFFFFFF, 0xFFFFFFFF},
        .supportedSessions        = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}
    }
};
