/*
 * File:   motor.c
 * Author: Team 10
 *
 * Created on February 24, 2019, 2:20 PM
 */

#include "motor.h"

void MOTROR_INIT() {
    DRV_TMR1_Start();   // PWM generator
    DRV_TMR2_Start();   // left motor read timer
    DRV_TMR3_Start();   // right motor read timer
    
    DRV_OC0_Start();
    DRV_OC1_Start();
    
    SET_LEFT_DIRC(MT_DIRC_FRONT);
    SET_RIGHT_DIRC(MT_DIRC_FRONT);
    SET_LEFT_PWM(MT_STOP_SPEED);
    SET_RIGHT_PWM(MT_STOP_SPEED);
}
void SET_LEFT_DIRC(bool dirc) {
    if (dirc)
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
    else
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
}

void SET_RIGHT_DIRC(bool dirc) {
    if (dirc)
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
    else
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
}

void SET_LEFT_PWM(int percentage) {
    int timerPeriod = DRV_TMR1_PeriodValueGet();
    int pulseWidth = (int) (percentage * timerPeriod / MT_ONE_HUNDRED_PERCENTAGE);
    DRV_OC1_PulseWidthSet(pulseWidth);
}

void SET_RIGHT_PWM(int percentage) {
    int timerPeriod = DRV_TMR1_PeriodValueGet();
    int pulseWidth = (int) (percentage * timerPeriod / MT_ONE_HUNDRED_PERCENTAGE);
    DRV_OC0_PulseWidthSet(pulseWidth);
}

void autoAdjustPWM(int *leftPWM, int *rightPWM) {
    // If motor is static, nothing to be done.
    if (*leftPWM == MT_STOP_SPEED || *rightPWM == MT_STOP_SPEED){
        // clear timer counters
        DRV_TMR2_CounterClear();
        DRV_TMR3_CounterClear();
        return;
    }

    // Calculate speed difference: Left - Right
    int speedDiff = DRV_TMR2_CounterValueGet() - DRV_TMR3_CounterValueGet();
    if((speedDiff > MT_SPEED_DIFF_TOLARANCE)){
        (*leftPWM) -= MT_CATCH_UP_SPEED;
        (*rightPWM) += MT_CATCH_UP_SPEED;
        SET_LEFT_PWM(*leftPWM);
        SET_RIGHT_PWM(*rightPWM);
    }
    else if (speedDiff < - MT_SPEED_DIFF_TOLARANCE){
        (*leftPWM) += MT_CATCH_UP_SPEED;
        (*rightPWM) -= MT_CATCH_UP_SPEED;
        SET_LEFT_PWM(*leftPWM);
        SET_RIGHT_PWM(*rightPWM);
    }
    
    // clear timer counters
    DRV_TMR2_CounterClear();
    DRV_TMR3_CounterClear();
}

void GoStraightLine(int *leftPWM, int *rightPWM){
    *leftPWM = MT_STAIGHT_LINE_SPEED;
    *rightPWM = MT_STAIGHT_LINE_SPEED;
    SET_LEFT_DIRC(MT_DIRC_FRONT);
    SET_RIGHT_DIRC(MT_DIRC_FRONT);
    SET_LEFT_PWM(MT_STAIGHT_LINE_SPEED);
    SET_RIGHT_PWM(MT_STAIGHT_LINE_SPEED);
}

void TurnLeft_90_Degree(int *leftPWM, int *rightPWM){
    TurnLeftSpecificDegree(MT_TRUNING_90_DEG, leftPWM, rightPWM);
}

void TurnRight_90_Degree(int *leftPWM, int *rightPWM){
    TurnRightSpecificDegree(MT_TRUNING_90_DEG, leftPWM, rightPWM);
}

void GoBackStraightLine(int *leftPWM, int *rightPWM){
    *leftPWM = MT_STAIGHT_LINE_SPEED;
    *rightPWM = MT_STAIGHT_LINE_SPEED;
    SET_LEFT_DIRC(MT_DIRC_BACK);
    SET_RIGHT_DIRC(MT_DIRC_BACK);
    SET_LEFT_PWM(MT_STAIGHT_LINE_SPEED);
    SET_RIGHT_PWM(MT_STAIGHT_LINE_SPEED);
}

void MotorStop(int *leftPWM, int *rightPWM){
    *leftPWM = MT_STOP_SPEED;
    *rightPWM = MT_STOP_SPEED;
    SET_LEFT_PWM(MT_STOP_SPEED);
    SET_RIGHT_PWM(MT_STOP_SPEED);
}

bool TurnLeftSpecificDegree(int degree, int *leftPWM, int *rightPWM){
    if (degree > MT_TRUNING_90_DEG || degree <= MT_STOP_SPEED) {
        MotorStop(leftPWM, rightPWM);
        return false;
    }
    *leftPWM = MT_STAIGHT_LINE_SPEED;
    *rightPWM = MT_STAIGHT_LINE_SPEED;
    int newValue = degree * MT_TRUNING_90_DEG_MAX_COUT / MT_TRUNING_90_DEG;
    Mt_SWTimer_SetPeriod(newValue);
    SET_LEFT_DIRC(MT_DIRC_BACK);
    SET_RIGHT_DIRC(MT_DIRC_FRONT);
    SET_LEFT_PWM(MT_STAIGHT_LINE_SPEED);
    SET_RIGHT_PWM(MT_STAIGHT_LINE_SPEED);
    Mt_SWTimer_Start();
    return true;
}

bool TurnRightSpecificDegree(int degree, int *leftPWM, int *rightPWM){
    if (degree > MT_TRUNING_90_DEG || degree <= MT_STOP_SPEED) {
        MotorStop(leftPWM, rightPWM);
        return false;
    }
    *leftPWM = MT_STAIGHT_LINE_SPEED;
    *rightPWM = MT_STAIGHT_LINE_SPEED;
    int newValue = degree * MT_TRUNING_90_DEG_MAX_COUT / MT_TRUNING_90_DEG;
    Mt_SWTimer_SetPeriod(newValue); 
    SET_LEFT_DIRC(MT_DIRC_FRONT);
    SET_RIGHT_DIRC(MT_DIRC_BACK);
    SET_LEFT_PWM(MT_STAIGHT_LINE_SPEED);
    SET_RIGHT_PWM(MT_STAIGHT_LINE_SPEED);
    Mt_SWTimer_Start();
    return true;
}
