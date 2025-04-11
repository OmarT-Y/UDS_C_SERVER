/****************************************************************************************************
 *  File Name           : uds_server_q_cfg.h
 *  Description         : Configuration file for the UDS request Queue management
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 13-3-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_SERVER_Q_CFG_H_
#define UDS_SERVER_Q_CFG_H_

#define UDS_SERVER_QUEUE_MAX_NUMBER_OF_REQS              15U

#define UDS_SERVER_QUEUE_DATA_LARGE_BLOCK_SIZE          512U
#define UDS_SERVER_QUEUE_NUM_OF_LARGE_BLOCKS            2U

#define UDS_SERVER_QUEUE_DATA_MEDIUM_BLOCK_SIZE         32U
#define UDS_SERVER_QUEUE_NUM_OF_MEDIUM_BLOCKS           5U

#define UDS_SERVER_QUEUE_DATA_SMALL_BLOCK_SIZE          8U
#define UDS_SERVER_QUEUE_NUM_OF_SMALL_BLOCKS            8U


#endif