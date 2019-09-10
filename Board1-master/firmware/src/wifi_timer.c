#include "wifi_timer.h"

void Stat_Timer_Init(void){
    statistic_handle = xTimerCreate("statisticTimer", pdMS_TO_TICKS(STAT_TIMER), pdTRUE ,(void*) 0, Stat_CallBack); 
    if( statistic_handle == NULL ){
        everythingStop(11);
    }
    xTimerStart(statistic_handle, 0);
}

void Stat_CallBack(TimerHandle_t xTimer) {
   WiFiQueType tmp = {.type = STATISTIC, .rx = 0x00};
   send_2_WIFI_QUEUE(tmp); 
}