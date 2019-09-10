
#include "softwareTimer.h"

void swInit() {
    xOneShotTimer = xTimerCreate("OneShot", speedONE_SHOT_TIMER_PERIOD, pdFALSE, 0, callBackFunction); 
    //speedOneShotTimer = xTimerCreate("OneShot", speedONE_SHOT_TIMER_PERIOD ,pdFALSE,0, speedCallBackFunction);
}


void callBackFunction(TimerHandle_t  xOneShotTimer) {
    Instruction inputInstruction;
    inputInstruction.type = SW;
    sendToQueueFromsServer(inputInstruction);
}


void softwareTimerStart() {
     xTimerStart(xOneShotTimer, 0);
}

void SWtimer() {
     softwareTimerStart();
}



void GET_callBack(TimerHandle_t  GEToneShot) {
     WiFiQueType init = {.type = TX, .name = ARM_NAME, .req = GET};
     send_2_WIFI_QUEUE(init);
}

void GET_swInit() {
    GEToneShot = xTimerCreate("GETOneShot", mainONE_SHOT_TIMER_PERIOD, pdTRUE, 0, GET_callBack); 
}

void GET_timerStart() {
     xTimerStart(GEToneShot,0);
}

void GET_timer() {
     GET_swInit();
}
