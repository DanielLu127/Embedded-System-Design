/*
 * File:   sensor_state.c
 * Author: Team 10
 *
 * Created on February 3, 2019, 2:20 PM
 */

#include "sensor_state.h"
//#include <unistd.h>

void sensorStateMachine(stateStatus *currentState, int *totalValue,  sensorMessageType inputValue, int * average) {
    switch(*currentState){
        case(state1):
            StateMachineHelper(totalValue, currentState, inputValue, average);
            break;
        case(state2):
            StateMachineHelper(totalValue, currentState, inputValue, average);
            break;
        case(state3):
            StateMachineHelper(totalValue, currentState, inputValue, average);
            break;
        case(state4):
            StateMachineHelper(totalValue, currentState, inputValue, average);
            break;
        case(state5):
            StateMachineHelper(totalValue, currentState, inputValue, average);  
            break;
        default:
            dbgOutputLoc(DBG_FSM_ERROR);
    }   
}

void StateMachineHelper(int * curTotalValue , stateStatus * curState, sensorMessageType inputValue, int * avg) 
{
    char garbageValue = inputValue.inputData;
    static int count = 0;
    static int sumDistance = 0;
    static int newDis = 0;
    if(*curState != state5){
        if(*curState == state1){
            if(garbageValue != 'R'){
                *curTotalValue = 0;
                *curState = state1;
            }
        }
        else if(*curState == state2){
            *curTotalValue = *curTotalValue + 100 * (garbageValue - '0');
        }
        else if(*curState == state3){
            *curTotalValue = *curTotalValue + 10 * (garbageValue - '0');
        }
        else if(*curState == state4){
            *curTotalValue = *curTotalValue + (garbageValue - '0');
        }
        *curState = *curState + STATE_INCREMENT;
    }
    else{
        if(garbageValue != 0x0d){
            *curTotalValue = 0;
            *curState = state1;
        }
        *avg = *curTotalValue;
        *curTotalValue = CUMULATIVE_TOTAL_VALUE_INIT; // resets total val to zero having sampled 5 times    
        
        sumDistance = sumDistance + *avg;
        count = count + 1;
        
        if (count == NUMBER_OF_DISTANCE_DATA){
            newDis = sumDistance / NUMBER_OF_DISTANCE_DATA;
            sumDistance = 0;
            count = 0;

            WiFiQueType command;
            command.name = SONAR_NAME;
            command.type = TX;
            command.req = PUT;
            command.sonarDis = newDis;
        
            if(newDis < DISTANCE_NEED_TO_TURN){
                command.sonarDir = MOTOR_TURN_LEFT;
            }
            else{
                command.sonarDir = MOTOR_MOVE_FORWARD;
            }
            send_2_WIFI_QUEUE(command);
        }
        
        *curState = state1;
    }
}