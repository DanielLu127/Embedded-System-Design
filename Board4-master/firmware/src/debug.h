/*
 * File:   debug.h
 * Author: Team 10
 *
 * Created on February 3, 2019, 2:20 PM
 */

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H

#define DBG_MOTOR_TASK_ENTER                        0x00
#define DBG_MOTOR_TASK_BEFORE_WHILE                 0x01
#define DBG_MOTOR_TASK_BEFORE_SEND_QUEUE            0x02
#define DBG_MOTOR_TASK_AFTER_SEND_QUEUE             0x03
#define DBG_MOTOR_TASK_BEFORE_RECEIVE_QUEUE         0x04
#define DBG_MOTOR_TASK_AFTER_RECEIVE_QUEUE          0x05

#define DBG_MOTOR_ST_SW_START                       0x06
#define DBG_MOTOR_ST_SW_CALLBACK                    0x07
#define DBG_MOTOR_ST_LED_START                      0x08
#define DBG_MOTOR_ST_LED_CALLBACK                   0x09
#define DBG_MOTOR_ST_ADJUST_START                   0x0a
#define DBG_MOTOR_ST_ADJUST_CALLBACK                0x0b
#define DBG_MOTOR_ST_ADJUST_STOP                    0x0c
#define DBG_STAT_TIMER_CALLBACK                     0x0d

#define DBG_MT_WIFI_TASK_ENTER                      0x20
#define DBG_MT_WIFI_TASK_BEFORE_WHILE               0x21
#define DBG_MT_WIFI_TASK_BEFORE_SEND_QUEUE          0x22
#define DBG_MT_WIFI_TASK_AFTER_SEND_QUEUE           0x23
#define DBG_MT_WIFI_TASK_BEFORE_RECEIVE_QUEUE       0x24
#define DBG_MY_WIFI_TASK_AFTER_RECEIVE_QUEUE        0x25
#define DBG_MT_WIFI_TASK_BEFORE_SEND_QUEUE_ISR      0x26
#define DBG_MT_WIFI_TASK_AFTER_SEND_QUEUE_ISR       0x27
#define DBG_MT_WIFI_TASK_BEFORE_SEND_TX             0x28
#define DBG_MT_WIFI_TASK_AFTER_SEND_TX              0x29
#define DBG_MT_WIFI_TASK_BEFORE_REC_TX              0x2a
#define DBG_MT_WIFI_TASK_AFTER_REC_TX               0x2b
#define DBG_MT_WIFI_TASK_STP_1                      0x2c
#define DBG_MT_WIFI_TASK_STP_1_NOT_EMPTY            0x2d
#define DBG_MT_WIFI_TASK_STP_2                      0x2e
#define DBG_MT_WIFI_TASK_STP_2_CHECK                0x2f

#define DBG_EVERYTHING_STOP_MTSW_INIT               0x40
#define DBG_EVERYTHING_STOP_MTSW_START              0x41
#define DBG_EVERYTHING_STOP_MTSW_SETPERIOD          0x42

#define DBG_EVERYTHING_STOP_MTLED_INIT              0x43
#define DBG_EVERYTHING_STOP_MTLED_START             0x44

#define DBG_EVERYTHING_STOP_MTADJUST_INIT           0x45
#define DBG_EVERYTHING_STOP_MTADJUST_START          0x46
#define DBG_EVERYTHING_STOP_MTADJUST_CHANGEPERIOD   0x47

#define DBG_EVERYTHING_STOP_MTTEST_INIT             0x50
#define DBG_EVERYTHING_STOP_MTTEST_START            0x51
#define DBG_EVERYTHING_STOP_MTTEST_SETPERIOD        0x52

#define DBG_EVERYTHING_STOP_MTSW_SEND_TO_QUEUE      0x53
#define DBG_EVERYTHING_STOP_MTSW_SEND_TO_QUEUE_ISR  0x54
#define DBG_EVERYTHING_STOP_MTSW_RECIEVE_QUEUE      0x55

#define DBG_EVERYTHING_STOP_MTWIFI_SEND_TO_QUEUE      0x56
#define DBG_EVERYTHING_STOP_MTWIFI_SEND_TO_QUEUE_ISR  0x57
#define DBG_EVERYTHING_STOP_MTWIFI_RECIEVE_QUEUE      0x58
#define DBG_EVERYTHING_STOP_MTWIFI_INIT_TX_QUEUE      0x59
#define DBG_EVERYTHING_STOP_MTWIFI_INIT_THREAD_QUEUE  0x5a
#define DBG_EVERYTHING_STOP_MTWIFI_SEND_TO_TX         0x5b
#define DBG_EVERYTHING_STOP_MTWIFI_REC_TX             0x5c

#define DBG_EVERYTHING_STOP_MOTOR_STATE_MACHINE     0x60
#define DBG_EVERYTHING_STOP_MOTOR_ERROR_CMD         0x61
#define DBG_EVERYTHING_STOP_MOTOR_QUEUE_INIT        0x62

#define DBG_GREATER_THAN_127                        0x61
#define MAX_OUTPUT_VALUE                            127
#define LED_INIIT_MASK                              0x0008
#define DBG_OUTPULOC_MASK                           0x00FF
#define DBG_OUTPUTVAL_MASK                          0x00FF
#define WRITE_8_BIT_END_MASK                        0xFF80


///////////////////////////////////////////////////////////////
#define DBG_TASK_BEFORE_RECEIVE_COMMAND_QUEUE   0x31
#define DBG_TASK_BEFORE_SEND_COMMAND_QUEUE      0x32
#define DBG_TASK_AFTER_RECEIVE_COMMAND_QUEUE    0x33
#define DBG_TASK_AFTER_SEND_COMMAND_QUEUE       0x34

#define DBG_TASK_ENTER                  0x35
#define DBG_TASK_BEFORE_WHILE           0x36
#define DBG_TASK_BEFORE_RECEIVE_QUEUE   0x37
#define DBG_TASK_BEFORE_SEND_QUEUE      0x38
#define DBG_TASK_AFTER_RECEIVE_QUEUE    0x39
#define DBG_TASK_AFTER_SEND_QUEUE       0xa

#define DBG_ISR_ENTER                   0x70
#define DBG_ISR_LEAVE                   0x71
#define DBG_EVERYTHING_STOP             0x72

#define DBG_EVERYTHING_STOP_QUEUE_INIT    0x73
#define DBG_EVERYTHING_STOP_QUEUE_ISR     0x74
#define DBG_EVERYTHING_STOP_QUEUE_RECEIVE 0x75
#define DBG_EVERYTHING_STOP_QUEUE_FSM     0x76
#define DBG_FSM_ERROR                     0x77
///////////////////////////////////////////////////////////////
// pixyCam defines
#define IN_SFTWRTIMR 0x90
#define TURN_ON_TX2 0x93
#define PIXY_TASK 0x9f
#define SENT_BYTE_UART_1 0x72
#define EXIT_PIXYCALLBACK_TIMER 0x91
#define Pixy_q_full 0x75
//Pixy_queue defines
#define ENABLE_TX2 0x25
#define Failed_to_init 0
#define B4_SendToTx 0x80
#define B4_Receive 0x81 // called inside pixy thread
#define B4_Tx2Recv 0x82
#define After_TxSend 0x88
#define PIXY_FREQ 400
#define PIXY_GET 500
#define B4_SENDUART 0x49
#define SEND_TO_THREAD_TMR 0x50 // from the timer
#define AFTER_SEND_FROM_TMR 0x51
#define AFTER_UART_ISR 0x60
#define First_state 0x1
#define Second_State 0x2
#define Third_State 0x3
#define Fourth_State 0x4
#define Fifth_State 0x5
//pixy2func defines
#define EXAMPLE_CONSTANT 0x0
#define MATCH 0x0
#define InReceive 0x29
#define Lamp_Event 0x73
#define send_1_lamp_event 0x74
#define Block_Event 0x83
#define sent_1_block 0x84
#define pixy_init_failed 0x12
#define BLOCK_LENGTH 0x5
#define DISABLE_TRANSMTI 19
#define PAYLOAD_BYTE 0x4    
#define PAYLOAD_BLOCK_LENGTH 14
#define FIRST_SIGMAP 7
#define FIRST_X 9
#define HALF_OFFSET 0x1
#define FIRST_Y 11
#define FIRST_WIDTH 13
#define FIRST_HEIGHT 15
#define FIRST_ANGLE 17
#define NINTH_BIT_SCALE 256
#define MSG_LENGTH 133
#define MSG_OFFSETS 44
#define FIRST_COLON 3
#define SECOND_COLON 11
#define THIRD_COLON 19

// isr stuff
#define BEFORE_WRITE 0x25
#define ENTERING_UART1_ISR 0x26
#define ENTERING_UART2_ISR 0x52
#define ENTERING_UART1_TRANSMIT 0x27
#define ENTERING_UART2_TRANSMIT 0x54
#define ENTERING_UART1_READ 0x28
#define ENTERING_UART2_READ 0x56
#define ENTERING_UART1_ERROR 0x29
#define ENTERING_UART2_ERROR 0x58
#define ENTERING_UART3_ISR 0x43
#define ENTERING_UART3_TRANSMIT 0x45
#define ENTERING_UART3_RECEIVE 0x46
#define ENTERING_UART3_ERROR 0x47
#define TWENTY_BYTES_RECV 0x5
//Define timer even
#define TIMER_PUSH 0x29
#define AFTER_PUSH 0x35
#define TIMER_RECV 0x30

// Uart events
#define UART_TX_1_PUSH 0x60
#define AFTER_TX_1_PUSH 0x61
#define SEND_STR_Tx_1 0x62

// wifly
#define TSK_B4_While 0x11

#include "system/common/sys_module.h"
#include "system_config.h"
#include "system_definitions.h"

#include "system/common/sys_module.h"
#include "system_config.h"
#include "system_definitions.h"

void dbgOutputVal(unsigned int outVal);
char dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outVal);
void everythingStop(int ErrorMessage);
void LED_Test();

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */
