/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _UART_QUEUE_H    /* Guard against multiple inclusion */
#define _UART_QUEUE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
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
void game_Send_Data(int board, int mtAction, int mtDegree, int armAction);
void game_send_GET();
    
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

#endif /* _UART_QUEUE_H */

/* *****************************************************************************
 End of File
 */
