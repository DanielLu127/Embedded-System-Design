/* 
 * File:   motor_queue.h
 * Author: xuanli
 *
 * Created on February 27, 2019, 3:22 PM
 */

#ifndef MOTOR_QUEUE_H
#define	MOTOR_QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include <FreeRtos.h>
#include "queue.h"
#include "portmacro.h"
#include "projdefs.h"

#include "QueueType.h"
#include "debug.h"

#define MT_QUEUE_INIT_FAIL                0
#define MT_QUEUE_LENGTH                   20
#define MT_QUEUE_ALLOWED_DELAY            0

QueueHandle_t mtQueueHandle;

// Motor Queue Basic Functions
void motorQueue_init();
void pushMtQueue(MtQueType msg);
void pushMtQueueFromISR(MtQueType msg, BaseType_t * prioprityTaskWoke);
MtQueType popMtQueue();
void sendFinishFeedBack();
void sendAdjustFeedBack();

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_QUEUE_H */

