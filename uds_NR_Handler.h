/****************************************************************************************************
 *  File Name           : UDS_NR_Handler.h
 *  Description         : Header file for sending NRC Responses
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 17-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_NR_HANDLER_H
#define UDS_NR_HANDLER_H

#include "uds_types.h"

/* All possible NRC */
#define UDS_NRC_0x10_GENERAL_REJECT                                      0X10
#define UDS_NRC_0x11_SERRVICE_NOT_SUPPORTED                              0X11
#define UDS_NRC_0x12_SUB_FUNCTION_NOT_SUPPORTED                          0x12
#define UDS_NRC_0x13_INCORRCT_MESSAGE_LENGTH_OR_INNVALID_FORMAT          0x13
#define UDS_NRC_0x14_RESPONSE_TOO_LONG                                   0x14
#define UDS_NRC_0x21_BUSY_REPEAT_REQUEST                                 0x21
#define UDS_NRC_0x22_CONDITIONS_NOT_CORRECT                              0x22
#define UDS_NRC_0x24_REQUEST_SEQUENCE_ERROR                              0x24
#define UDS_NRC_0x25_NO_RESPONSE_FROM_SUBNET_COMPONENT                   0x25
#define UDS_NRC_0x26_FALIURE_PREVENTS_EXECUTION_OF_REQUESTED_ACTION      0x26
#define UDS_NRC_0x31_REQUEST_OUT_OF_RANGE                                0x31
#define UDS_NRC_0x33_SECURITY_ACCESS_DENIED                              0x33
#define UDS_NRC_0x35_INVALID_KEY                                         0x35
#define UDS_NRC_0x36_EXCEED_NUMBER_OF_ATTEMPS                            0x36
#define UDS_NRC_0x37_REQUIRED_TIME_DELAY_NOT_EXPIRED                     0x37
#define UDS_NRC_0x70_UPLOAD_DOWNLOAD_NOT_ACCEPTED                        0x70
#define UDS_NRC_0x71_TRANSFER_DATA_SUSPENDED                             0x71
#define UDS_NRC_0x72_GENERAL_PROGRAMMING_FAILURE                         0x72
#define UDS_NRC_0x73_WRONG_BLOCK_SEQUENCE_COUNTER                        0x73
#define UDS_NRC_0x78_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING         0x78
#define UDS_NRC_0x7E_SUB_FUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION        0x7E
#define UDS_NRC_0x7F_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION             0x7F
#define UDS_NRC_0x81_RPM_TOO_HIGH                                        0x81
#define UDS_NRC_0x82_RPM_TOO_LOW                                         0x82
#define UDS_NRC_0x83_ENGINE_IS_RUNNING                                   0x83
#define UDS_NRC_0x84_ENGINE_IS_NOT_RUNNING                               0x84
#define UDS_NRC_0x85_ENGINE_RUNTIME_TOO_LOW                              0x85
#define UDS_NRC_0x86_TEMPERATURE_TOO_HIGH                                0x86
#define UDS_NRC_0x87_TEMPERATURE_TOO_LOW                                 0x87
#define UDS_NRC_0x88_VEHICLE_SPEED_TOO_HIGH                              0x88
#define UDS_NRC_0x89_VEHICLE_SPEED_TOO_LOW                               0x89
#define UDS_NRC_0x8A_THROTTLE_OR_PEDAL_TOO_HIGH                          0x8A
#define UDS_NRC_0x8B_THROTTLE_OR_PEDAL_TOO_LOW                           0x8B
#define UDS_NRC_0x8C_TRANSMISSION_RANGE_NOT_IN_NEUTRAL                   0x8C
#define UDS_NRC_0x8D_TRANSMISSION_RANGE_NOT_IN_GEAR                      0x8D
#define UDS_NRC_0x8F_BRAKE_SWITCH_NOT_CLOSED                             0x8F
#define UDS_NRC_0x90_SHIFTER_LEVER_NOT_IN_PARK                           0x90
#define UDS_NRC_0x91_TORQUE_CONVERTER_CLUTCH_cOCKED                      0x91
#define UDS_NRC_0x92_VOLTAGE_TOO_HIGH                                    0x92
#define UDS_NRC_0x93_VOLTAGE_TOO_LOW                                     0x93

/**
 * @brief Handles the sending of NRC
 * @param response The response message to be modified and sent
 * @param NRC The NRC to be sent
 * @param SID The service ID of the service in which the Negative Response occured
 */
void handleNRC(UDS_REQ_t *request,UDS_RES_t * response , uint8_t NRC , uint8_t SID);

#endif