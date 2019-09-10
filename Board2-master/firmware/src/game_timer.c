#include "game_timer.h"

void Game_LEDTimer_Init() {
    //100 ms LED blinking
    Game_LEDHandle = xTimerCreate("Mt_LEDTimer",
            GAME_LED_TIME / portTICK_PERIOD_MS, pdTRUE, 
            ( void * ) GAME_SWTIMER_DEFAULT_TIMER_ID, Game_LEDTimerCallback);
    
    if( Game_LEDHandle == NULL ){
        everythingStop(DBG_EVERYTHING_STOP_MTLED_INIT);
    }
    
    if( xTimerStart( Game_LEDHandle, GAME_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTLED_START);
    }
    dbgOutputVal(DBG_MOTOR_ST_LED_START);
}

void Game_LEDTimer_Stop() {
    xTimerStop( Game_LEDHandle, GAME_SWTIMER_BLOCK_TIME );
}

void Game_LEDTimerCallback( TimerHandle_t xTimer ) {
    LED_Test();
    dbgOutputVal(DBG_MOTOR_ST_LED_CALLBACK);
}

void Game_ReqTimer_Init() {
    Game_ReqHandle = xTimerCreate("Mt_AdjustTimer", GAME_REQ_TIME / portTICK_PERIOD_MS, 
            pdTRUE, ( void * ) GAME_SWTIMER_DEFAULT_TIMER_ID, Game_ReqTimerCallback);
    
    if( Game_ReqHandle == NULL ){
        everythingStop(DBG_EVERYTHING_STOP_MTADJUST_INIT);
    }
    Game_ReqTimer_Start();
}

void Game_ReqTimer_Start() {
    if( xTimerChangePeriod( Game_ReqHandle, GAME_REQ_TIME / portTICK_PERIOD_MS, GAME_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTADJUST_CHANGEPERIOD);
    }
    if( xTimerStart( Game_ReqHandle, GAME_SWTIMER_BLOCK_TIME ) != pdPASS )
    {
        everythingStop(DBG_EVERYTHING_STOP_MTADJUST_START);
    }
    dbgOutputLoc(DBG_MOTOR_ST_ADJUST_START);
}

void Game_ReqTimer_Stop() {
    xTimerStop( Game_ReqHandle, GAME_SWTIMER_BLOCK_TIME );
    dbgOutputLoc(DBG_MOTOR_ST_ADJUST_STOP);
}

void Game_ReqTimerCallback( TimerHandle_t xTimer ) {
    dbgOutputLoc(DBG_MOTOR_ST_ADJUST_STOP);
    game_send_GET();
}