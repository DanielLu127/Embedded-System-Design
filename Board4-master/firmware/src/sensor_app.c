#include "sensor_app.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/adc/plib_adc.h"
#include "system/system.h"
#include "system/devcon/sys_devcon.h"
#include "system/ports/sys_ports.h"
#include "sensor_queue.h"
#include "sensor_state.h"

void SENSOR_APP_Initialize ( void )
{
    UARTQueue_init();
    PLIB_USART_ReceiverIdleStateLowEnable(USART_ID_4);
}

void SENSOR_APP_Tasks ( void )
{
    int avg = 0;
    stateStatus myState = state1;
    int totalValue = 0;
    
//    int avg = 0;
//    avgStateStatus avgMyState = state1;
//    int totalValue = 0;
    
    while(1){
        sensorMessageType data = UARTReceiveFromQueue();
//        dbgOutputLoc(DBG_TASK_AFTER_RECEIVE_QUEUE);   //9
        sensorStateMachine(&myState,&totalValue, data, &avg);
    }
}


/*******************************************************************************
 End of File
 */
