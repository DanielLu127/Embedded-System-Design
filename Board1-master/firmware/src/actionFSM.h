/* 
 * File:   ActionFSM.h
 * Author: Daniel Lu
 *
 * Created on February 27, 2019, 5:43 PM
 */

#ifndef ACTIONFSM_H
#define	ACTIONFSM_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "QueueType.h"
#include "stdbool.h"
#include "serverToArmMQ.h"
#include "armToServerMQ.h"
#include "armThreadFSM.h"
#include "softwareTimer.h"
#include "OC.h"   
//#define mainONE_SHOT_TIMER_PERIOD pdMS_TO_TICKS(1500)
#define timerFinished -1
//TimerHandle_t  xOneShotTimer;
//typedef enum {BRL, BRR, COPEN, FRF, CCLOSE, FRB,STOP} actionList;
//void actionFSM(Instruction actionState);
//threadStatus complexMotionOne(actionList *inputAction);
#ifdef	__cplusplus
}
#endif

#endif	/* ACTIONFSM_H */

