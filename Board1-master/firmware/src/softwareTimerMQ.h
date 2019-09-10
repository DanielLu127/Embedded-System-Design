/* 
 * File:   softwareTimerMQ.h
 * Author: Daniel Lu
 *
 * Created on March 19, 2019, 2:44 AM
 */

/* 
 * File:   messageQueue.h
 * Author: Daniel Lu
 *
 * Created on February 20, 2019, 1:01 AM
 */

#ifndef MESSAGEQUEUE_H
#define	MESSAGEQUEUE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <FreeRtos.h>
#include "queue.h"
#include "stdbool.h"
#include "actionFSM.h"
#include "QueueType.h"
#define SWQLength 20
#define QueueInitFail 0
QueueHandle_t softwareTimerQ;
void SWQueue_init();
void sendToQueue(int myMessage);
int ReceiveFromQueue();

#ifdef	__cplusplus
}
#endif

#endif	/* MESSAGEQUEUE_H */

