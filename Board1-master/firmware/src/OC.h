/* 
 * File:   OC.h
 * Author: Daniel Lu
 *
 * Created on February 20, 2019, 12:50 AM
 */
#include "peripheral/oc/plib_oc.h"
#include "system/common/sys_module.h"
#include "system_config.h"
#include "system_definitions.h"
#include <FreeRtos.h>
#include "timers.h"
#include "QueueType.h"


#ifndef OC_H
#define	OC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define armPeriod 20
#define clawClosePosition 1
#define clawOpenPosition 2
#define forearmForwardPosition 2.0
#define forearmBackwardPsotion 1.3
#define baseLeftPosition 1.9
#define baseMiddlePosition 1.2
#define baseRightPosition 0.5
#define incrementPosition 0.1
#define stop  0
#define incrementDelay 30

    

void OCInit();
void TMRInit();
void set_OC2_PWM(float value);
void set_OC1_PWM(float value);
void set_OC3_PWM(float value);
void clawClose(float clawClose);
void clawOpen();
void forearmRotateForeward(float forearmValue);
void forearmRotateBackward();
void baseRotateLeft(float baseValue);
void baseRotateMiddle();
void baseRotateRight();
void stopAllServos();
void LED_Test();
void delayHelper();
void callBackFunction();

#ifdef	__cplusplus
}
#endif

#endif	/* OC_H */

