/* 
 * File:   game_queue.h
 * Author: xuanli
 *
 * Created on April 25, 2019, 7:25 PM
 */

#ifndef GAME_QUEUE_H
#define	GAME_QUEUE_H

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

#define GAME_QUEUE_INIT_FAIL                0
#define GAME_QUEUE_LENGTH                   20
#define GAME_QUEUE_ALLOWED_DELAY            0

QueueHandle_t gameQueueHandle;

// Game Queue Basic Functions
void gameQueue_init();
void pushGameQueue(GameQueType msg);
void pushGameQueueFromISR(GameQueType msg, BaseType_t * prioprityTaskWoke);
GameQueType popGameQueue();

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* GAME_QUEUE_H */

