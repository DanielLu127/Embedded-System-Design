/* 
 * File:   motor_software_timer.h
 * Author: xuanli
 *
 * Created on March 3, 2019, 4:08 PM
 */

#ifndef MOTOR_SOFTWARE_TIMER_H
#define	MOTOR_SOFTWARE_TIMER_H

#include <FreeRtos.h>
#include "timers.h"
#include "debug.h"
#include "motor_queue.h"

#define MT_SWTIMER_DEFAULT_PERIOD       1
#define MT_SWTIMER_DEFAULT_TIMER_ID     0
#define MT_SWTIMER_BLOCK_TIME           0
#define MT_LED_TIME                     100
#define MT_ADJUST_TIME                  200
#define MT_REQ_TIME                     450

TimerHandle_t Mt_SWTimerHandle;
TimerHandle_t Mt_LEDHandle;
TimerHandle_t Mt_AdjustHandle;
TimerHandle_t Mt_ReqHandle;

void Mt_SWTimer_Init();
void Mt_SWTimer_Start();
void Mt_SWTimer_SetPeriod(int NewPeriod);
void Mt_TimerCallback( TimerHandle_t xTimer );

void Mt_LEDTimer_Init();
void Mt_LEDTimer_Stop();
void Mt_LEDTimerCallback( TimerHandle_t xTimer );

void Mt_AdjustTimer_Init();
void Mt_AdjustTimerCallback( TimerHandle_t xTimer );

void Mt_ReqTimer_Init();
void Mt_ReqTimer_Start();
void Mt_ReqTimer_Stop();
void Mt_ReqTimerCallback( TimerHandle_t xTimer );

#endif	/* MOTOR_SOFTWARE_TIMER_H */

