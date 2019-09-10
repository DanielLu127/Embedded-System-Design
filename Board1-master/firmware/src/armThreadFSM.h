/* 
 * File:   armThreadFSM.h
 * Author: Daniel Lu
 *
 * Created on February 27, 2019, 3:01 PM
 */

#ifndef ARMTHREADFSM_H
#define	ARMTHREADFSM_H
#ifdef	__cplusplus
extern "C" {
#endif
    
#include <FreeRtos.h>
#include <queue.h>
#include "stdbool.h"
#include "actionFSM.h"
#include "serverToArmMQ.h"
#include "armToServerMQ.h"
#include "QueueType.h"
#define baseInitPosition 0.5
#define forearmPosition 1.3

typedef enum {WAITING, WORKING, FINISHED,DELAY} threadStatus;

//void threadFSM(threadStatus *armThread, Instruction newInstruction);


#ifdef	__cplusplus
}
#endif

#endif	/* ARMTHREADFSM_H */