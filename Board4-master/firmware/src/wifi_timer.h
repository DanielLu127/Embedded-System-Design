/*
 * File:   wifi_timer.h
 * Author: xuanli
 *
 * Created on April 13, 2019, 1:31 PM
 */

#ifndef WIFI_TIMER_H    /* Guard against multiple inclusion */
#define WIFI_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "FreeRTOS.h"
#include "timers.h"

#define STAT_TIMER 1000
#define ZERO_T     0


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
TimerHandle_t statistic_handle;
    
void Stat_Timer_Init(void);
void Stat_CallBack(TimerHandle_t xTimer);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* WIFI_TIMER_H */

