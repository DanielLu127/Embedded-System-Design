/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
 To provide a msall api to initiate and add to queue

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _PIXY_QUEUE_H   /* Guard against multiple inclusion */
#define _PIXY_QUEUE_H



/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "FreeRTOS.h"
#include "timers.h"
#include "queue.h"
#include "debug.h"
#include "pixy_app.h"
#include "QueueType.h"
/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */
typedef enum {INIT, START , TRANSMIT, RECEIVE, SEND_GET} PIXY_THREAD_STATE ;    

typedef struct {
    unsigned int value;
    char * temp_char;
} PIXY2_UART_MSG ;


typedef struct{
    PIXY_THREAD_STATE Type;
    uint8_t temp_char;
} PIXY2_THREAD_MSG;



    void PixyQueueInit();
    
    PIXY2_THREAD_MSG PixyThreadReceive();
    
    PIXY2_UART_MSG Pixy_UART2_ISR_Receive(BaseType_t * priorityTaskWoke);
    
    //functions that can come from rx or timer ;)
    void sendFromUARTISR(PIXY2_THREAD_MSG msg,  BaseType_t * priorityTaskWoke);
    void sendFromTimer(PIXY2_THREAD_MSG msg);
    
    void sendToISR(PIXY2_UART_MSG msg); // for tx ti read from and then send
    
    void Recv_Controller(PIXY2_THREAD_MSG tmp, PIXY2_THREAD_MSG * fsm);
    void pixy2fsm(PIXY2_THREAD_MSG * curState );
    
    bool tx_queueIsEmpty();
    bool Pixy_queueIsEmpty();
    
    QueueHandle_t PixyThread; // global queue handle
    QueueHandle_t Pixy_UART_ISR; // this is for the uart2_tx queueu

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif 

/* *****************************************************************************
 End of File
 */
