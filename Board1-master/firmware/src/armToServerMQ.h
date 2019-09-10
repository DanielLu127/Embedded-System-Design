/* 
 * File:   armToServerMQ.h
 * Author: Daniel Lu
 *
 * Created on February 27, 2019, 3:19 PM
 */

#ifndef ARMTOSERVERMQ_H
#define	ARMTOSERVERMQ_H
#include <FreeRtos.h>
#include "queue.h"
#include "stdbool.h"
#include "QueueType.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct {
    bool ifFinished; 
} armResultMessageType;

#define ARMQLength 20
#define QueueInitFail 0
QueueHandle_t armToServerQ;
void armQueue_init();
void sendToQueueFromsArm(armResultMessageType myMessage);
armResultMessageType ReceiveFromQueueFromArm();


#ifdef	__cplusplus
}
#endif

#endif	/* ARMTOSERVERMQ_H */

