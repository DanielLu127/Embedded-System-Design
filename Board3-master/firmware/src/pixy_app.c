#include "pixy_app.h"

/* TODO:  Add any necessary callback function*/

void INIT_UART2_IRS(){
    SYS_INT_SourceEnable(INT_SOURCE_USART_2_ERROR);
    SYS_INT_SourceEnable(INT_SOURCE_USART_2_RECEIVE);
    SYS_INT_SourceEnable(INT_SOURCE_USART_2_TRANSMIT); 
}

void DISABLE_UART2(){
    bool status;
    status = SYS_INT_SourceDisable(INT_SOURCE_USART_2_TRANSMIT) ;
    status = SYS_INT_SourceDisable(INT_SOURCE_USART_2_RECEIVE) ;
    status = SYS_INT_SourceDisable(INT_SOURCE_USART_2_ERROR);
    /* Ignore the warning */
    (void)status;
}


void PixyCallback(TimerHandle_t xTimer){
    dbgOutputLoc(IN_SFTWRTIMR);
    uint32_t ulCount = (uint32_t)pvTimerGetTimerID( xTimer );
    PIXY2_THREAD_MSG sendMe;
    bool tmp;
    
    sendMe.Type = START;
    sendMe.temp_char = 0x00; 
    sendFromTimer(sendMe); // pushes only if told to
    
    //if( (uint32_t ) pvTimerGetTimerID( xTimer ) == 0){
       // vTimerSetTimerID( xTimer, ( void * ) ++ulCount ); 
    //}
    
    dbgOutputLoc(EXIT_PIXYCALLBACK_TIMER);
}

void Pixy_Timer_Init(void)
{
    PixyT_Handle = xTimerCreate("PixyTimer", pdMS_TO_TICKS(PIXY_FREQ),
    pdTRUE ,(void*) 0, 
    PixyCallback ); 
    
    BaseType_t Success = xTimerStart(PixyT_Handle , 0); // this should start the time immediately
}


void reStartTimer(void){
    xTimerReset(PixyT_Handle, 0); // starts timer immediately
}

void PIXY_APP_Initialize ( void )
{
    PixyQueueInit();
    Pixy_Timer_Init();
    Pixy_look_up_init(-1); // initalizes my look up table
}

void PIXY_APP_Tasks ( void )
{
    PIXY2_THREAD_MSG temp = {.Type=INIT, .temp_char = 0x00};
    while(1)
    {
        temp = PixyThreadReceive();
        pixy2fsm(&temp);
        dbgOutputLoc(PIXY_TASK);
    }
    
}

 

/*******************************************************************************
 End of File
 */
