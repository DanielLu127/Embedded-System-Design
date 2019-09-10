#include "wifi_timer.h"

void Stat_Timer_Init(void){
    statistic_handle = xTimerCreate("statisticTimer", pdMS_TO_TICKS(STAT_TIMER), pdTRUE ,(void*) ZERO_T, Stat_CallBack); 
    if( statistic_handle == NULL ){
        everythingStop(11);
    }
    xTimerStart(statistic_handle, ZERO_T);
}

void Stat_CallBack(TimerHandle_t xTimer) {
    dbgOutputLoc(DBG_STAT_TIMER_CALLBACK);
    WiFiQueType tmp = {.type = STATISTIC};
    send_2_WIFI_QUEUE(tmp); 
}