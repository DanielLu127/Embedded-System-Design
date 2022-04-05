# Embedded-System-Design
# Overview
![image](https://user-images.githubusercontent.com/29085565/161748946-0ed13a42-341f-40a5-8f6f-692a9f4cc56e.png)

# Diagrams of Robotic arm Implementation
##  Block Diagram
![image](https://user-images.githubusercontent.com/29085565/161749223-457835b7-4057-4f1c-9d56-98e27474cadc.png)
##  Task Diagram
![image](https://user-images.githubusercontent.com/29085565/161749142-79c33646-60be-42f3-b57f-0938b1662f57.png)

# Implementation detail
Define small actions, such as forearm from left to right or base from right to left, such as

```c
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
```

A complexMotion is defined by a set of small actions, such as

```c
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
```

Main FSM
```c
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
                //send GET request every x miliseconds
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
```

The blocking queue. This thread is blocked here and wait for receive message from the queue

```c
void ARM_APP_Tasks ( void )
{
    GET_timerStart();
    threadStatus inputStatus = WAITING;
    WiFiQueType init = {.type = TX, .name = ARM_NAME, .req = GET};
    send_2_WIFI_QUEUE(init);
    
    while(1){
        Instruction inputInstruction = ReceiveFromQueueFromServer();
        threadFSM(&inputStatus, inputInstruction);
    }
}
```

The init state is WAITING, and this thread send GET request every x miliseconds. The result will be send to the queue.

```c
void GET_timerStart() {
     xTimerStart(GEToneShot,0);
}

void GET_callBack(TimerHandle_t  GEToneShot) {
     WiFiQueType init = {.type = TX, .name = ARM_NAME, .req = GET};
     send_2_WIFI_QUEUE(init);
}
```

If the result of the GET request is (newInstruction.start == 2 || newInstruction.start == 3 ||newInstruction.start == 4). 

Then start execute a complex motion. The state is changed to WORKING

After a small action is finshed, the state is changed to WAITING, and a message will be send to the queue to WIFI thread, and WIFI thread will send a message to arm thread. Then the arm thread will execute next samll action

After a complex motion is finhsed, the state is changed to FINISHE, a message will be send to the queue to WIFI thread. The WIFI thread will send a message to server. The robotic arm is waiting for next instruction from server (send GET request every x millilseconds)

In addition, in order to decrease the moving speed. A software timer is used when execute small actions. 


# Implementation of server

```python
#Name:         flaskServer.py
#Goal:         Run a flask server at a fixed address/port
#Written by:   Xuan Li
#For:          Team 10
#Last update:  
#Comments:     Address: localhost / Port: 5000
#              Database: localhost:27017

from flask import Flask
app = Flask(__name__)
import pymongo
from pymongo import MongoClient
from flaskServerLogic import *

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test" (or create it)
db = client['ECE4534_test']
collection = db['collection']

#########################################################
#                   APP ROUTES - START
#########################################################
#Test your app with this (home)
@app.route("/")
def hello():
    return "Hello World!"
    
@app.route("/arm/<int:seqNum>", methods=['GET', 'PUT'])
def armRoutine(seqNum):
    checkSequence(0, seqNum)
    if request.method == 'GET':
        return get_logic("arm", collection, seqNum)
    elif request.method == 'PUT':
        return put_arm_logic("arm", collection, seqNum)
        
@app.route("/game/<int:seqNum>", methods=['GET', 'PUT'])
def gameRoutine(seqNum):
    checkSequence(1, seqNum)
    if request.method == 'GET':
        return get_game_logic(collection, seqNum)
    elif request.method == 'PUT':
        return put_game_logic("game", collection, seqNum)
        
@app.route("/pixy2/<int:seqNum>", methods=['GET', 'PUT'])
def pixytwoRoutine(seqNum):
    checkSequence(1, seqNum)
    if request.method == 'GET':
        return get_logic("pixy2", collection, seqNum)
    elif request.method == 'PUT':
        return put_pixytwo_logic("pixy2", collection, seqNum)
        
@app.route("/pixy3/<int:seqNum>", methods=['GET', 'PUT'])
def pixythreeRoutine(seqNum):
    checkSequence(2, seqNum)
    if request.method == 'GET':
        return get_logic("pixy3", collection, seqNum)
    elif request.method == 'PUT':
        return put_pixy_logic("pixy3", collection, seqNum)
        
@app.route("/pixy4/<int:seqNum>", methods=['GET', 'PUT'])
def pixyfourRoutine(seqNum):
    checkSequence(3, seqNum)
    if request.method == 'GET':
        return get_logic("pixy4", collection, seqNum)
    elif request.method == 'PUT':
        return put_pixy_logic("pixy4", collection, seqNum)
        
@app.route("/sonar3/<int:seqNum>", methods=['GET', 'PUT'])
def sonarthreeRoutine(seqNum):
    checkSequence(2, seqNum)
    if request.method == 'GET':
        return get_logic("sonar3", collection, seqNum)
    elif request.method == 'PUT':
        return put_sonar_logic("sonar3", collection, seqNum)
        
@app.route("/sonar4/<int:seqNum>", methods=['GET', 'PUT'])
def sonarfourRoutine(seqNum):
    checkSequence(3, seqNum)
    if request.method == 'GET':
        return get_logic("sonar4", collection, seqNum)
    elif request.method == 'PUT':
        return put_sonar_logic("sonar4", collection, seqNum)

@app.route("/motor3/<int:seqNum>", methods=['GET', 'PUT'])
def motorRoutine(seqNum):
    checkSequence(2, seqNum)
    if request.method == 'GET':
        return get_logic("motor3", collection, seqNum)
    elif request.method == 'PUT':
        return put_motor_logic("motor3", collection, seqNum)
        
@app.route("/motor4/<int:seqNum>", methods=['GET', 'PUT'])
def motorRoutines(seqNum):
    checkSequence(3, seqNum)
    if request.method == 'GET':
        return get_logic("motor4", collection, seqNum)
    elif request.method == 'PUT':
        return put_motor_logic("motor4", collection, seqNum)
        
@app.route("/enco/<int:seqNum>", methods=['PUT'])
def encoRoutine(seqNum):
    checkSequence(0, seqNum)
    if request.method == 'PUT':
        return put_enco_logic("enco", collection, seqNum)
        
@app.route("/stat0/<int:seqNum>", methods=['PUT'])
def stat0(seqNum):
    checkSequence(0, seqNum)
    if request.method == 'PUT':
        return board_stat_logic(collection, seqNum)

@app.route("/stat1/<int:seqNum>", methods=['PUT'])
def stat1(seqNum):
    checkSequence(1, seqNum)
    if request.method == 'PUT':
        return board_stat_logic(collection, seqNum)
        
@app.route("/stat2/<int:seqNum>", methods=['PUT'])
def stat2(seqNum):
    checkSequence(2, seqNum)
    if request.method == 'PUT':
        return board_stat_logic(collection, seqNum)
        
@app.route("/stat3/<int:seqNum>", methods=['PUT'])
def stat3(seqNum):
    checkSequence(3, seqNum)
    if request.method == 'PUT':
        return board_stat_logic(collection, seqNum)

@app.errorhandler(404)
def not_found(error=None):
    stat_Req_Helper(False)
    stat_Reply_Helper(False)
    return buildError(404)

@app.errorhandler(400)
def not_found(error=None):
    stat_Req_Helper(False)
    stat_Reply_Helper(False)
    return buildError(400)

#########################################################
#                    APP ROUTES - END
#########################################################


if __name__ == '__main__':
    app.run(debug = True,host='localhost',port = 5000)
    #app.run(debug = True, host = 'localhost', port = 5000, threaded=True)

```
