/* 
 * File:   game_timer.h
 * Author: xuanli
 *
 * Created on April 26, 2019, 1:23 PM
 */

#ifndef GAME_TIMER_H
#define	GAME_TIMER_H

#include <FreeRtos.h>
#include "timers.h"
#include "debug.h"
#include "game_queue.h"

#define GAME_SWTIMER_DEFAULT_TIMER_ID     0
#define GAME_SWTIMER_BLOCK_TIME           0
#define GAME_LED_TIME                     100
#define GAME_REQ_TIME                     420

#ifdef	__cplusplus
extern "C" {
#endif

TimerHandle_t Game_LEDHandle;
TimerHandle_t Game_ReqHandle;

void Game_LEDTimer_Init();
void Game_LEDTimer_Stop();
void Game_LEDTimerCallback( TimerHandle_t xTimer );

void Game_ReqTimer_Init();
void Game_ReqTimer_Start();
void Game_ReqTimer_Stop();
void Game_ReqTimerCallback( TimerHandle_t xTimer );

#ifdef	__cplusplus
}
#endif

#endif	/* GAME_TIMER_H */

