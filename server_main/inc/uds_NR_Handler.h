/****************************************************************************************************
 *  File Name           : UDS_NR_Handler.h
 *  Description         : Header file for sending NRC Responses
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_NR_HANDLER_H
#define UDS_NR_HANDLER_H

#include "uds_types.h"

#define NEGATIVE_RESPONSE_SID_INDEX                                      0x7FU
#define FAILED_REQUEST_SID_INDEX                                         1U
#define NEGATIVE_RESPONSE_CODE_INDEX                                     2U
#define NEGATIVE_RESPONSE_LENGTH_INDEX                                   3U


/* All possible NRC */
#define UDS_NRC_0x10_GENERAL_REJECT                                      0X10U
#define UDS_NRC_0x11_SERVICE_NOT_SUPPORTED                              0X11U
#define UDS_NRC_0x12_SUB_FUNCTION_NOT_SUPPORTED                          0x12U
#define UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INVALID_FORMAT          0x13U
#define UDS_NRC_0x14_RESPONSE_TOO_LONG                                   0x14U
#define UDS_NRC_0x21_BUSY_REPEAT_REQUEST                                 0x21U
#define UDS_NRC_0x22_CONDITIONS_NOT_CORRECT                              0x22U
#define UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR                              0x24U
#define UDS_NRC_0x25_NO_RESPONSE_FROM_SUBNET_COMPONENT                   0x25U
#define UDS_NRC_0x26_FALIURE_PREVENTS_EXECUTION_OF_REQUESTED_ACTION      0x26U
#define UDS_NRC_0x31_REQUEST_OUT_OF_RANGE                                0x31U
#define UDS_NRC_0x33_SECURITY_ACCESS_DENIED                              0x33U
#define UDS_NRC_0x35_INVALID_KEY                                         0x35U
#define UDS_NRC_0x36_EXCEED_NUMBER_OF_ATTEMPS                            0x36U
#define UDS_NRC_0x37_REQUIRED_TIME_DELAY_NOT_EXPIRED                     0x37U
#define UDS_NRC_0x70_UPLOAD_DOWNLOAD_NOT_ACCEPTED                        0x70U
#define UDS_NRC_0x71_TRANSFER_DATA_SUSPENDED                             0x71U
#define UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE                         0x72U
#define UDS_NRC_0x73_WRONG_BLOCK_SEQUENCE_COUNTER                        0x73U
#define UDS_NRC_0x78_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING         0x78U
#define UDS_NRC_0x7E_SUB_FUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION        0x7EU
#define UDS_NRC_0x7F_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION             0x7FU
#define UDS_NRC_0x81_RPM_TOO_HIGH                                        0x81U
#define UDS_NRC_0x82_RPM_TOO_LOW                                         0x82U
#define UDS_NRC_0x83_ENGINE_IS_RUNNING                                   0x83U
#define UDS_NRC_0x84_ENGINE_IS_NOT_RUNNING                               0x84U
#define UDS_NRC_0x85_ENGINE_RUNTIME_TOO_LOW                              0x85U
#define UDS_NRC_0x86_TEMPERATURE_TOO_HIGH                                0x86U
#define UDS_NRC_0x87_TEMPERATURE_TOO_LOW                                 0x87U
#define UDS_NRC_0x88_VEHICLE_SPEED_TOO_HIGH                              0x88U
#define UDS_NRC_0x89_VEHICLE_SPEED_TOO_LOW                               0x89U
#define UDS_NRC_0x8A_THROTTLE_OR_PEDAL_TOO_HIGH                          0x8AU
#define UDS_NRC_0x8B_THROTTLE_OR_PEDAL_TOO_LOW                           0x8BU
#define UDS_NRC_0x8C_TRANSMISSION_RANGE_NOT_IN_NEUTRAL                   0x8CU
#define UDS_NRC_0x8D_TRANSMISSION_RANGE_NOT_IN_GEAR                      0x8DU
#define UDS_NRC_0x8F_BRAKE_SWITCH_NOT_CLOSED                             0x8FU
#define UDS_NRC_0x90_SHIFTER_LEVER_NOT_IN_PARK                           0x90U
#define UDS_NRC_0x91_TORQUE_CONVERTER_CLUTCH_LOCKED                      0x91U
#define UDS_NRC_0x92_VOLTAGE_TOO_HIGH                                    0x92U
#define UDS_NRC_0x93_VOLTAGE_TOO_LOW                                     0x93U
/**
 * @brief Handles the sending of NRC
 * @param response The response message to be modified and sent
 * @param NRC The NRC to be sent
 * @param SID The service ID of the service in which the Negative Response occured
 */
void handleNRC(UDS_REQ_t *request,UDS_RES_t * response , uint8_t NRC , uint8_t SID);

#endif