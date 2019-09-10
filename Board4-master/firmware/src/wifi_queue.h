/*
 * File:   wifi_queue.h
 * Author: xuanli
 *
 * Created on April 13, 2019, 1:31 PM
 */

#ifndef WIFI_QUEUE_H    /* Guard against multiple inclusion */
#define WIFI_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "QueueType.h"
#include "debug.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
#define Failed_to_init 0
#define ZERO_SPEED  0

QueueHandle_t Uart_tx_queue;
QueueHandle_t UART_Thread_queue;

// Quick Access Functions
void mt_Send_Finish();
void mt_Send_Running();
void mt_Send_GET();
void mt_Send_Encoder(int *leftPWM, int *rightPWM);
    
// User Preferred Functions 
void init_WIFI_queue();
void send_2_WIFI_QUEUE(WiFiQueType msg); 
void send_2_WIFI_QUEUE_from_isr(WiFiQueType msg, BaseType_t * CSwitch); 
WiFiQueType WIFI_QUEUE_Recv();
// End

bool tx_queue_empty_from_isr();
void send_2_Tx_queue(Tx_msg msg);
Tx_msg Uart_tx_queue_Recv();
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* WIFI_QUEUE_H */
