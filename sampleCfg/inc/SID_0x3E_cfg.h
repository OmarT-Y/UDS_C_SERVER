/****************************************************************************************************
 *  File Name           : SID_0x3E_TesterPresent.h
 *  Description         : Header file for the service 0x3E Tester Present Request Handler
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#ifndef SID_3E_SESSTION_CTRL_HANDLER_FILE_H
#define SID_3E_SESSTION_CTRL_HANDLER_FILE_H

/* 
 * Maps starting the timeout function to SID 0x3E Timeout function to a custom function handling
 * the timeout of SID 0x10 that encapsulates any needed OS calls
 */
#define RESET_TIMER_FUNC resetTimer


#endif