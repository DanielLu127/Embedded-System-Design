#include "game_state.h"

void GameStateMachine(GameState *curState, GameQueType *msg) {
    static int counter = 0;
    static int check = 0;
    switch(*curState){
        case(Init):
            if (msg->board == ZERO)
                game_Send_Data(ONE, msg->mtAction, msg->mtDegree, msg->armAction);
            if (msg->board == 5){
                game_Send_Data(THREE, Front, ZERO, ONE);
                *curState = Walk;
                counter = 0;
                check = 0;
            }
            else if (msg->board == 6){
                game_Send_Data(FOUR, Front, ZERO, ONE);
                *curState = Walk;
                counter = 0;
                check = 0;
            }            
            break;
            
        case(Walk):
            if (msg->board != THREE && msg->board != FOUR)
                break;
            if (msg->piStart != 0 /*&& counter == 2*/ && check == 0){
                if (msg->board == 3) {
                    game_Send_Data(msg->board, Stop, msg->mtDegree, 2);
                    check = 1;
                }
                else if (msg->board == 4){
                    game_Send_Data(msg->board, Stop, msg->mtDegree, 3);
                    check = 1;
                }
                *curState = armWait;
            }
            else if (msg->sonarDir == ONE){
                counter++;
                if(counter == 5){
                    game_Send_Data(msg->board, Stop, msg->mtDegree, msg->armAction);
                    game_Send_Data(ONE, Stop, msg->mtDegree, msg->armAction);
                    *curState = Init;
                }
                else {
                    game_Send_Data(msg->board, TurnLeft90, msg->mtDegree, msg->armAction);
                    *curState = sonarWait;
                }
            }
            else if (msg->piDir != ZERO){
                if (msg->piDir == ONE && msg->piDegree > 0){
                    game_Send_Data(msg->board, TurnLSpecific, msg->piDegree, msg->armAction);
                    *curState = pixyWait;
                }
                else if (msg->piDir == TWO && msg->piDegree > 0){
                    game_Send_Data(msg->board, TurnRSpecific, msg->piDegree, msg->armAction);
                    *curState = pixyWait;
                }
            }
            break;   
            
        case(sonarWait):
            if (msg->mtAction == MTidle){
                *curState = Walk;
                game_Send_Data(msg->board, Front, msg->mtDegree, msg->armAction);
            }
            break;
            
        case(pixyWait):
            if (msg->mtAction == MTidle || msg->mtAction == FStatus){
                *curState = Walk;
                game_Send_Data(msg->board, Front, msg->mtDegree, msg->armAction);
            }
            break;
            
        case(armWait):
            if (msg->armAction == 1){
                if (msg->board == 4 && check == 1){
                    *curState = armSecWait;
                    game_Send_Data(msg->board, Stop, msg->mtDegree, 4);
                }
                else {
                    *curState = Walk;
                    game_Send_Data(msg->board, Front, msg->mtDegree, msg->armAction);
                }
            }
            break;
            
        case(armSecWait):
            if (msg->armAction == 1){
                *curState = Walk;
                game_Send_Data(msg->board, Front, msg->mtDegree, msg->armAction);
            }
            break;
        default:
            everythingStop(DBG_EVERYTHING_STOP_MOTOR_STATE_MACHINE);
            break;
    }
}

