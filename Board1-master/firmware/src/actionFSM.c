#include "actionFSM.h"

threadStatus JumpToWorking()
{
    static int counter = 0;
    switch(counter){
        case(0):
            counter = 1;
            SWtimer();
            return WORKING;
        case(1):
            counter = 0;
            SWtimer();
            return WAITING;
    }
}

threadStatus BRLfsm(double *basePos) {
    baseRotateLeft(*basePos);
    SWtimer();
    *basePos = *basePos + 0.03;
    if(*basePos >= 1.85){
         return WAITING;
     }
     else {
         return WORKING;
     }
}


threadStatus BRLfsm2(double *basePos) {
    baseRotateLeft(*basePos);
    SWtimer();
    *basePos = *basePos + 0.03;
    if(*basePos >= 1.85){
         return WAITING;
     }
     else {
         return WORKING;
     }
}

threadStatus BRRfsm(double *basePos) {
     baseRotateLeft(*basePos);
     SWtimer();
     *basePos = *basePos - 0.03;
     if(*basePos <= 1.1){
         return WAITING;
     }
     else {
         return WORKING;
     }
}

threadStatus FRFfsm(double *forearm) {
    forearmRotateForeward(*forearm);
    SWtimer();
    *forearm = *forearm + 0.03;
     if(*forearm >= 0.8){
         return WAITING;
     }
     else {
         return WORKING;
     }
}

threadStatus FRBfsm(double *forearm) {
    forearmRotateForeward(*forearm);
    SWtimer();
    *forearm = *forearm - 0.03;
     if(*forearm <= 0.5){
         return WAITING;
     }
     else {
         return WORKING;
     }
}

threadStatus FRFfsm1(double *forearm){
    forearmRotateForeward(*forearm);
    SWtimer();
    *forearm = *forearm + 0.03;
     if(*forearm >= 1.0){
         return WAITING;
     }
     else {
         return WORKING;
     }
}

threadStatus clowOpenFSM()
{
    static int counter = 0;
    switch (counter){
        case(0):
            clawOpen();
            SWtimer();
            counter = 1;
            return WORKING;
        case(1):
            clawOpen();
            SWtimer();
            counter = 2;
            return WORKING;
        case(2):
            clawOpen();
            SWtimer();
            counter = 3;
            return WORKING;
        case(3):
            clawOpen();
            SWtimer();
            counter = 0;
            return WAITING;
    }
}

threadStatus clowOpenFSM2()
{
    static int counter = 0;
    switch (counter){
        case(0):
            clawOpen();
            SWtimer();
            counter = 1;
            return WORKING;
        case(1):
            clawOpen();
            SWtimer();
            counter = 2;
            return WORKING;
        case(2):
            clawOpen();
            SWtimer();
            counter = 3;
            return WORKING;
        case(3):
            clawOpen();
            SWtimer();
            counter = 0;
            return FINISHED;
    }
}

threadStatus clowCloseFSM()
{
    static int counter = 0;
    static int tracker = 2;
    switch (counter){
        case(0):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 1;
            return WORKING;
        case(1):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 2;
            return WORKING;
        case(2):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 3;
            return WORKING;
        case(3):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 4;
            return WORKING;
        case(4):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 5;
            return WORKING;
        case(5):
            clawClose(tracker);
            SWtimer();
            tracker = 2;
            counter = 0;
            return WAITING;
    }
}

threadStatus clowCloseFSM2()
{
    static int counter = 0;
    static int tracker = 2;
    switch (counter){
        case(0):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 1;
            return WORKING;
        case(1):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 2;
            return WORKING;
        case(2):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 3;
            return WORKING;
        case(3):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 4;
            return WORKING;
        case(4):
            clawClose(tracker);
            SWtimer();
            tracker = 1.0;
            counter = 5;
            return WORKING;
        case(5):
            clawClose(tracker);
            SWtimer();
            tracker = 2;
            counter = 0;
            return WAITING;
    }
}


threadStatus complexMotion1(actionList *action, double *basePos, double *forearm){
     threadStatus temp;
     switch(*action) {
            case(FRF):
                temp = JumpToWorking();
                if(temp == WAITING){*action = CCLOSE;}
                return temp;
            case(CCLOSE):
                temp = clowCloseFSM();
                if(temp == WAITING){*action = BRR;}
                return temp;
            case(BRR):
                temp = BRRfsm(basePos);
                if(temp == WAITING){*action = COPEN;}
                return temp;
            case(COPEN):
                temp = clowOpenFSM();
                if(temp == WAITING){*action = CLOSE2;}
                return temp;
            case(CLOSE2):
                temp = clowCloseFSM();
                if(temp == WAITING){*action = BRL;}
                return temp;
            case(BRL):
                temp = BRLfsm(basePos);
                if(temp == WAITING){*action = COPEN2;}
                return temp;
            case(COPEN2):
                temp = clowOpenFSM2();
                if(temp == FINISHED){*action = FRF;}
                return temp;
            default:
                stopAllServos();
       }
}

threadStatus complexMotion3(actionList *action, double *basePos, double *forearm)
{
     threadStatus temp;
     switch(*action) {
            case(FRF):
                temp = FRFfsm1(forearm);
                if(temp == WAITING){*action = CCLOSE;}
                return temp;
            case(CCLOSE):
                temp = clowCloseFSM();
                if(temp == WAITING){*action = BRR;}
                return temp;
            case(BRR):
                temp = BRRfsm(basePos);
                if(temp == WAITING){*action = FRB;}
                return temp;
            case(FRB):
                temp = FRBfsm(forearm);
                if(temp == WAITING){*action = COPEN;}
                return temp;
            case(COPEN):
                temp = clowOpenFSM();
                if(temp == WAITING){*action = CLOSE2;}
                return temp;
            case(CLOSE2):
                temp = clowCloseFSM();
                if(temp == WAITING){*action = BRL;}
                return temp;
            case(BRL):
                temp = BRLfsm(basePos);
                if(temp == WAITING){*action = COPEN2;}
                return temp;
            case(COPEN2):
                temp = clowOpenFSM2();
                if(temp == FINISHED){*action = FRF;}
                return temp;
            default:
                stopAllServos();
       }
}

threadStatus complexMotion2(actionList *action, double *basePos, double *forearm){
     threadStatus temp;
     switch(*action) {
            case(FRF):
                temp = FRFfsm(forearm);
                if(temp == WAITING){*action = CCLOSE;}
                return temp;
            case(CCLOSE):
                temp = clowCloseFSM();
                if(temp == WAITING){*action = FRB;}
                return temp;
            case(FRB):
                temp = FRBfsm(forearm);
                if(temp == WAITING){*action = BRR;}
                return temp;
            case(BRR):
                temp = BRRfsm(basePos);
                if(temp == WAITING){*action = COPEN;}
                return temp;
            case(COPEN):
                temp = clowOpenFSM();
                if(temp == WAITING){*action = CLOSE2;}
                return temp;
            case(CLOSE2):
                temp = clowCloseFSM();
                if(temp == WAITING){*action = BRL;}
                return temp;
            case(BRL):
                temp = BRLfsm(basePos);
                if(temp == WAITING){*action = COPEN2;}
                return temp;
            case(COPEN2):
                temp = clowOpenFSM2();
                if(temp == FINISHED){*action = FRF;}
                return temp;
            default:
                stopAllServos();
       }
}

threadStatus actionFSM(actionList *action, int indexOFcomplex) {
     static double basePos = 1.7;
     static double forearmPos = 0.5;
    
     if(indexOFcomplex == 2) {
         return complexMotion1(action, &basePos, &forearmPos);
     }
     else if (indexOFcomplex == 3){
         return complexMotion2(action, &basePos, &forearmPos);
     }
     else if (indexOFcomplex == 4){
         return complexMotion3(action, &basePos, &forearmPos);
     }
}
