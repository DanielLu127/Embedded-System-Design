/* 
 * File:   motor_state.h
 * Author: xuanli
 *
 * Created on February 27, 2019, 7:11 PM
 */

#ifndef MOTOR_STATE_H
#define	MOTOR_STATE_H
#include "motor_queue.h"
#include "wifi_queue.h"
#include "QueueType.h"

typedef enum { Waiting, Busy } MtState;

void MtStateMachine(MtState *curState, MtQueType msg, int *leftPWM, int *rightPWM);
void WaitingStateHelper(MtState *curState, MtQueType msg, int *leftPWM, int *rightPWM);
void BusyStateHelper(MtState *curState, MtQueType msg, int *leftPWM, int *rightPWM);

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_STATE_H */

