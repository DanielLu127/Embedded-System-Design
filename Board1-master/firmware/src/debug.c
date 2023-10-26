/*
 * File:   debug.c
 * Author: Team 10
 *
 * Created on February 3, 2019, 2:20 PM
 */

#include "debug.h"

void dbgOutputLoc(unsigned int outVal){
    if (outVal > MAX_OUTPUT_VALUE)
        dbgOutputLoc(DBG_GREATER_THAN_127);
    uint32_t preValue = PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_E) & WRITE_8_BIT_END_MASK;
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, preValue | outVal);
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_7);
}

char dbgUARTVal(unsigned char outVal) {
    //DRV_USART0_WriteByte(outVal); 
    return outVal;
}

void dbgOutputVal(unsigned int outVal) {
    if (outVal > MAX_OUTPUT_VALUE)
        dbgOutputVal(DBG_GREATER_THAN_127);
    uint32_t preValue = PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_D) & WRITE_8_BIT_END_MASK;
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7);
}

void everythingStop(int ErrorMessage) {
    vTaskSuspendAll();
    SYS_INT_Disable();
    dbgOutputLoc(ErrorMessage);
    while(1) {}
}

void LED_Test(){
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
}
