/* 
 * File:   motor_state.c
 * Author: xuanli
 *
 * Created on February 27, 2019, 7:11 PM
 */
#include "motor_state.h"


void MtStateMachine(MtState *curState, MtQueType msg, int *leftPWM, int *rightPWM){
    switch(*curState){
        case(Waiting):
            WaitingStateHelper(curState, msg, leftPWM, rightPWM);        
            break;
        case(Busy):
            BusyStateHelper(curState, msg, leftPWM, rightPWM); 
            break;
        default:
            everythingStop(DBG_EVERYTHING_STOP_MOTOR_STATE_MACHINE);
            break;
    }
}

void WaitingStateHelper(MtState *curState, MtQueType msg, int *leftPWM, int *rightPWM){
    switch(msg.type){
        case(MTInit):
            MotorStop(leftPWM, rightPWM);
            mt_Send_Finish();
            break;
        case(MTidle):
            break;
        case(FStatus):
            break;
        case(Front):
            GoStraightLine(leftPWM, rightPWM);
            mt_Send_Running();
            break;
        case(Back):
            GoBackStraightLine(leftPWM, rightPWM);
            mt_Send_Running();
            break;
        case(Stop):
            MotorStop(leftPWM, rightPWM);
            mt_Send_Finish();
            break;
        case(TurnRight90):
            TurnRight_90_Degree(leftPWM, rightPWM);
            Mt_ReqTimer_Stop();
            *curState = Busy;
            break;
        case(TurnLeft90):
            TurnLeft_90_Degree(leftPWM, rightPWM);
            Mt_ReqTimer_Stop();
            *curState = Busy;
            break;
        case(TurnLSpecific):
            if (TurnLeftSpecificDegree(msg.degree, leftPWM, rightPWM)) {
                Mt_ReqTimer_Stop();
                *curState = Busy;
            } else
                mt_Send_Finish();
            break;
        case(TurnRSpecific):
            if (TurnRightSpecificDegree(msg.degree, leftPWM, rightPWM)) {
                Mt_ReqTimer_Stop();
                *curState = Busy;
            } else
                mt_Send_Finish();
            break;
        case(ReadEncoder):
            autoAdjustPWM(leftPWM, rightPWM);
            //mt_Send_Encoder(leftPWM, rightPWM);
            break;
        default:
            // Bad Command. Ignore it.
            mt_Send_Finish();
            break;
    }
}

void BusyStateHelper(MtState *curState, MtQueType msg, int *leftPWM, int *rightPWM){
    if(msg.type == FinishTurning) {
        MotorStop(leftPWM, rightPWM);
        Mt_ReqTimer_Start();
        mt_Send_Finish();
        *curState = Waiting;
    }
    else if (msg.type == ReadEncoder) {
        autoAdjustPWM(leftPWM, rightPWM);
        //mt_Send_Encoder(leftPWM, rightPWM);
    }
}
