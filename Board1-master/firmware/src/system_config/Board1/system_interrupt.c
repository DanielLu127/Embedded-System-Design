/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "arm_app.h"
#include "wifi_app.h"
#include "pixy_app.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
void IntHandlerDrvUsartInstance0(void)
{
    dbgOutputLoc(ENTERING_UART1_ISR);

    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_TRANSMIT) && PLIB_INT_SourceIsEnabled( INT_ID_0, INT_SOURCE_USART_1_TRANSMIT ))
    {
        dbgOutputLoc(ENTERING_UART1_TRANSMIT );
        BaseType_t cSwitch = pdFALSE;
        Tx_isr_fsm();
    }
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_RECEIVE) )
    {
        dbgOutputLoc(ENTERING_UART1_READ);
        BaseType_t cSwitch = pdFALSE;
        WiFiQueType item = {.type = RX, .rx = PLIB_USART_ReceiverByteReceive(USART_ID_1)};
        send_2_WIFI_QUEUE_from_isr(item, &cSwitch);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        portEND_SWITCHING_ISR(&cSwitch); 
    }
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_ERROR) )
    {
        dbgOutputLoc(ENTERING_UART1_ERROR);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR);
    }
}

 
 

void IntHandlerDrvUsartInstance1(void)
{
    dbgOutputLoc(ENTERING_UART2_ISR);
    static int count = 0;
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_2_TRANSMIT) && PLIB_INT_SourceIsEnabled( INT_ID_0, INT_SOURCE_USART_2_TRANSMIT ) )
    {
        dbgOutputLoc(ENTERING_UART2_TRANSMIT );
        pixy_uart_fsm();
    }
     
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_2_RECEIVE) )
    {
        dbgOutputLoc(ENTERING_UART2_READ);
            BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
            PIXY2_THREAD_MSG temp_msg = { .Type = RECEIVE   ,  .temp_char = PLIB_USART_ReceiverByteReceive(USART_ID_2)};
            sendFromUARTISR(temp_msg, &pxHigherPriorityTaskWoken);
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_RECEIVE);
            portEND_SWITCHING_ISR(&pxHigherPriorityTaskWoken);         
    }
    
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_2_ERROR) )
    {
        dbgOutputLoc(ENTERING_UART2_ERROR );
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_ERROR);
    }  
}
 
 
 

 

 

 

 

 
void IntHandlerDrvTmrInstance0(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);
}
void IntHandlerDrvTmrInstance1(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_4);
}
void IntHandlerDrvTmrInstance2(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_3);
}
void IntHandlerDrvTmrInstance3(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_5);
}
 
/*******************************************************************************
 End of File
*/