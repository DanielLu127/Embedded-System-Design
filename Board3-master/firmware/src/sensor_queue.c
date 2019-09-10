/*
 * File:   sensor_queue.h
 * Author: Team 10
 *
 * Created on February 3, 2019, 2:20 PM
 */

#include "debug.h"
#include "sensor_queue.h"
#include <FreeRtos.h>
#include "queue.h"
#include "portmacro.h"
#include "projdefs.h"

void UARTQueue_init() {
    UARTqueue = xQueueCreate(100, sizeof(sensorMessageType));
    if (UARTqueue == 0) {
        everythingStop(12);
    }
}

void sendFromISRtoQueue(sensorMessageType myMessage, BaseType_t * prioprityTaskWoke) {
//   dbgOutputLoc(DBG_TASK_BEFORE_SEND_QUEUE);               //8
   if (xQueueSendToBackFromISR(UARTqueue, &myMessage, prioprityTaskWoke) == errQUEUE_FULL){
       everythingStop(DBG_EVERYTHING_STOP_QUEUE_ISR);
   }
//   dbgOutputLoc(DBG_TASK_AFTER_SEND_QUEUE);                //a
}

sensorMessageType UARTReceiveFromQueue() {
//    dbgOutputLoc(DBG_TASK_BEFORE_RECEIVE_QUEUE);            //7
    sensorMessageType buffer;
    if (xQueueReceive (UARTqueue, &buffer, portMAX_DELAY) == errQUEUE_EMPTY){
        everythingStop(DBG_EVERYTHING_STOP_QUEUE_RECEIVE);
    }
//    dbgOutputLoc(DBG_TASK_AFTER_RECEIVE_QUEUE);             //9
    return buffer;
}

void vTimerCallback1SecExpired( TimerHandle_t timerHndl1Sec )
{
    LED_Test();
}

void softwareTimerInit(){
    timerHndl1Sec = xTimerCreate("timer", 100 / portTICK_PERIOD_MS, pdTRUE, (void*)0, vTimerCallback1SecExpired);
}

void softwareTimerStart(){
    if (xTimerStart(timerHndl1Sec, 0)!=pdPASS) {
        for(;;); /* failure!?! */
    }
}