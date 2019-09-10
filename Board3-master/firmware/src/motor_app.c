/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    motor_app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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

#include "motor_app.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/adc/plib_adc.h"
#include "system/system.h"
#include "system/devcon/sys_devcon.h"
#include "framework/driver/adc/drv_adc_static.h"
#include "framework/driver/tmr/drv_tmr_static.h"
#include "system/ports/sys_ports.h"


void MOTOR_APP_Initialize ( void )
{
    MOTROR_INIT();
    motorQueue_init();
    Mt_SWTimer_Init();
    Mt_LEDTimer_Init();
    Mt_AdjustTimer_Init();
    Mt_ReqTimer_Init();
}


/******************************************************************************
  Function:
    void MOTOR_APP_Tasks ( void )

  Remarks:
    See prototype in motor_app.h.
 */

void MOTOR_APP_Tasks ( void )
{
    dbgOutputLoc(DBG_MOTOR_TASK_ENTER);
    int leftPWM  = MT_STOP_SPEED;
    int rightPWM = MT_STOP_SPEED;
    MtState curState = Waiting;
    MtQueType data;
    dbgOutputLoc(DBG_MOTOR_TASK_BEFORE_WHILE);
    while(TRUE_VALUE){
        data = popMtQueue();
        MtStateMachine(&curState, data, &leftPWM, &rightPWM);
    }
}

 

/*******************************************************************************
 End of File
 */
