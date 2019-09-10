/* 
 * File:   sensor_queue.h
 * Author: Team 10
 *
 * Created on February 2, 2019, 6:40 PM
 */

#ifndef SENSOR_QUEUE_H
#define	SENSOR_QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
    int value;
    char inputData;
} sensorMessageType ;

QueueHandle_t UARTqueue;
TimerHandle_t timerHndl1Sec;

void UARTQueue_init();
void sendFromISRtoQueue(sensorMessageType myMessage, BaseType_t * prioprityTaskWoke);
sensorMessageType UARTReceiveFromQueue();

void vTimerCallback1SecExpired( TimerHandle_t timerHndl1Sec );
void softwareTimerInit();
void softwareTimerStart();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_QUEUE_H */

