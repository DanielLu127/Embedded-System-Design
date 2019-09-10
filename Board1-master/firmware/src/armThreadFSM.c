#include "armThreadFSM.h"

void threadFSM(threadStatus *armThread, Instruction newInstruction) {
    static actionList inputAction = 0;
    static int start_action = 0;
    switch(*armThread) {
        case(WAITING):
             if (newInstruction.start == 2 || newInstruction.start == 3 ||newInstruction.start == 4){
                start_action = newInstruction.start;
                xTimerStop(GEToneShot,0);
                actionFSM(&inputAction, start_action);
                *armThread = WORKING;
             }   
             else if(newInstruction.start == 0) {
                  WiFiQueType newResult = {.type = TX, .req = PUT, .name = ARM_NAME, .start = 1};
                  send_2_WIFI_QUEUE(newResult);
             }     
             else {
                GET_timerStart();
             }
            break;
        case(WORKING):
              *armThread = actionFSM(&inputAction, start_action);
              if(*armThread == WAITING) {
                  WiFiQueType next = {.type = INNER_ACTION, .name = ARM_NAME, .start = start_action};
                  send_2_WIFI_QUEUE(next);
              }
            break;
        case(FINISHED):
                *armThread = WAITING;
                WiFiQueType newResult = {.type = TX, .req = PUT, .start = 1, .name = ARM_NAME};
                WiFiQueType init = {.type = TX, .name = ARM_NAME, .req = GET};
                send_2_WIFI_QUEUE(newResult);
                send_2_WIFI_QUEUE(init);
            break;
        default:
            LED_Test();
            break;
    }
}
