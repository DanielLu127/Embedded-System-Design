/* 
 * File:   motor_software_timer.c
 * Author: xuanli
 *
 * Created on February 27, 2019, 7:11 PM
 */
#include "motor_software_timer.h"

void Mt_SWTimer_Init(){
    Mt_SWTimerHandle = xTimerCreate("Mt_Timer", MT_SWTIMER_DEFAULT_PERIOD, 
            pdTRUE, ( void * ) MT_SWTIMER_DEFAULT_TIMER_ID, Mt_TimerCallback);
    
    if( Mt_SWTimerHandle == NULL ){
        everythingStop(DBG_EVERYTHING_STOP_MTSW_INIT);
    }
}

void Mt_SWTimer_Start(){
    if( xTimerStart( Mt_SWTimerHandle, MT_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTSW_START);
    }
    dbgOutputVal(DBG_MOTOR_ST_SW_START);
}

void Mt_SWTimer_SetPeriod(int NewPeriod){
    if( xTimerChangePeriod( Mt_SWTimerHandle, NewPeriod / portTICK_PERIOD_MS, MT_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTSW_SETPERIOD);
    }
}

void Mt_TimerCallback( TimerHandle_t xTimer ){
    dbgOutputVal(DBG_MOTOR_ST_SW_CALLBACK);
    sendFinishFeedBack();
    xTimerStop( xTimer, MT_SWTIMER_BLOCK_TIME );
}

void Mt_LEDTimer_Init(){
    //100 ms LED blinking
    Mt_LEDHandle = xTimerCreate("Mt_LEDTimer",
            MT_LED_TIME / portTICK_PERIOD_MS, pdTRUE, 
            ( void * ) MT_SWTIMER_DEFAULT_TIMER_ID, Mt_LEDTimerCallback);
    
    if( Mt_LEDHandle == NULL ){
        everythingStop(DBG_EVERYTHING_STOP_MTLED_INIT);
    }
    
    if( xTimerStart( Mt_LEDHandle, MT_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTLED_START);
    }
    dbgOutputVal(DBG_MOTOR_ST_LED_START);
}

void Mt_LEDTimer_Stop(){
    xTimerStop( Mt_LEDHandle, MT_SWTIMER_BLOCK_TIME );
}

void Mt_LEDTimerCallback( TimerHandle_t xTimer ){
    LED_Test();
    dbgOutputVal(DBG_MOTOR_ST_LED_CALLBACK);
}

void Mt_AdjustTimer_Init(){
    Mt_AdjustHandle = xTimerCreate("Mt_AdjustTimer", MT_ADJUST_TIME / portTICK_PERIOD_MS, 
            pdTRUE, ( void * ) MT_SWTIMER_DEFAULT_TIMER_ID, Mt_AdjustTimerCallback);
    
    if( Mt_AdjustHandle == NULL ){
        everythingStop(DBG_EVERYTHING_STOP_MTADJUST_INIT);
    }
    
    if( xTimerStart( Mt_AdjustHandle, MT_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTADJUST_START);
    }
    dbgOutputVal(DBG_MOTOR_ST_ADJUST_START);
}

void Mt_AdjustTimerCallback( TimerHandle_t xTimer ){
    dbgOutputVal(DBG_MOTOR_ST_ADJUST_CALLBACK);
    sendAdjustFeedBack();
}

void Mt_ReqTimer_Init() {
    Mt_ReqHandle = xTimerCreate("Mt_AdjustTimer", MT_REQ_TIME / portTICK_PERIOD_MS, 
            pdTRUE, ( void * ) MT_SWTIMER_DEFAULT_TIMER_ID, Mt_ReqTimerCallback);
    
    if( Mt_ReqHandle == NULL ){
        everythingStop(DBG_EVERYTHING_STOP_MTADJUST_INIT);
    }
    Mt_ReqTimer_Start();
}

void Mt_ReqTimer_Start() {
    if( xTimerChangePeriod( Mt_ReqHandle, MT_REQ_TIME / portTICK_PERIOD_MS, MT_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTADJUST_CHANGEPERIOD);
    }
    if( xTimerStart( Mt_ReqHandle, MT_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTADJUST_START);
    }
    dbgOutputLoc(DBG_MOTOR_ST_ADJUST_START);
}

void Mt_ReqTimer_Stop() {
    xTimerStop( Mt_ReqHandle, MT_SWTIMER_BLOCK_TIME );
    dbgOutputLoc(DBG_MOTOR_ST_ADJUST_STOP);
}

void Mt_ReqTimerCallback( TimerHandle_t xTimer ) {
    dbgOutputLoc(DBG_MOTOR_ST_ADJUST_STOP);
    mt_Send_GET();
}