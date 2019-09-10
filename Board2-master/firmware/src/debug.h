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
