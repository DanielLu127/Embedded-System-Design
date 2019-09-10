/* 
 * File:   softwareTimer.h
 * Author: Daniel Lu
 *
 * Created on March 22, 2019, 4:26 AM
 */

#ifndef SOFTWARETIMER_H
#define	SOFTWARETIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "stdbool.h"
#include "serverToArmMQ.h"
#include "armToServerMQ.h"
#include "armThreadFSM.h"
#include "OC.h" 
#include "QueueType.h"
#define mainONE_SHOT_TIMER_PERIOD pdMS_TO_TICKS(500)
#define speedONE_SHOT_TIMER_PERIOD pdMS_TO_TICKS(200)
TimerHandle_t  xOneShotTimer;
TimerHandle_t  GEToneShot;
TimerHandle_t  speedOneShotTimer;
void callBackFunction(TimerHandle_t  xOneShotTimer);
void SWtimer();
void softwareTimerStart();
void speedCallBackFunction();
#ifdef	__cplusplus
}
#endif

#endif	/* SOFTWARETIMER_H */

