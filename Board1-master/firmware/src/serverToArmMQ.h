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
#include "armThreadFSM.h"
#include "debug.h"
#include "QueueType.h"
/*typedef struct {
    bool takeAction;
    int newAction; 
} armActionMessageType ;*/

#define SERVERQLength 100
#define QueueInitFail 0


/*typedef enum {SW, WIFI,SPEED} messageType;
typedef enum {one, two, three} complexMotion;
typedef enum {BRL, BRR, COPEN, FRF, CCLOSE, FRB} actionList;*/
    
/*typedef struct {
    messageType type;
    actionList actionStatus;
}  Instruction;*/

QueueHandle_t ServerToArmQ;
void serverQueue_init();
void sendToQueueFromsServer(Instruction myMessage);
Instruction ReceiveFromQueueFromServer();
//void threadFSM(threadStatus *armThread, Instruction newInstruction);
//void actionFSM(Instruction actionState);

#ifdef	__cplusplus
}
#endif

#endif	/* MESSAGEQUEUE_H */

