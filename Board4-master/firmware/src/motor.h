/* 
 * File:   motor.h
 * Author: xuanli
 *
 * Created on February 24, 2019, 3:44 PM
 */

#ifndef MOTOR_H
#define	MOTOR_H

#include "system/common/sys_module.h"
#include "system_config.h"
#include "system_definitions.h"
#include "debug.h"

#define MT_STAIGHT_LINE_SPEED       75
#define MT_CATCH_UP_SPEED           1
#define MT_STOP_SPEED               0       
#define MT_DIRC_FRONT               0
#define MT_DIRC_BACK                1
#define MT_ONE_HUNDRED_PERCENTAGE   100
#define MT_SPEED_DIFF_TOLARANCE     3
#define MT_TRUNING_COUNTER_INIT     0
#define MT_TRUNING_90_DEG_MAX_COUT  4200
#define MT_TRUNING_90_DEG           90
#define MT_TRUNING_INUSE_ON         true
#define MT_TRUNING_INUSE_OFF        false
#define MT_START_ON                 true
#define MT_START_OFF                false

// User-preferred function

void MOTROR_INIT();
void GoStraightLine(int *leftPWM, int *rightPWM);  
void TurnLeft_90_Degree(int *leftPWM, int *rightPWM);
void TurnRight_90_Degree(int *leftPWM, int *rightPWM);
void GoBackStraightLine(int *leftPWM, int *rightPWM);
void MotorStop(int *leftPWM, int *rightPWM);
    
bool TurnLeftSpecificDegree(int degree, int *leftPWM, int *rightPWM);
bool TurnRightSpecificDegree(int degree, int *leftPWM, int *rightPWM);

// Basic Motor Control function

void SET_LEFT_DIRC(bool dirc);
void SET_RIGHT_DIRC(bool dirc);
void SET_LEFT_PWM(int percentage);
void SET_RIGHT_PWM(int percentage);
void autoAdjustPWM(int *leftPWM, int *rightPWM); 

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

