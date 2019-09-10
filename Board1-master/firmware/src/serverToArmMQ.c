#include "serverToArmMQ.h"


void serverQueue_init() {
    ServerToArmQ = xQueueCreate(SERVERQLength, sizeof(Instruction));
    if (ServerToArmQ == QueueInitFail) {
     //   everythingStop(DBG_EVERYTHING_STOP_SERVERQUEUE_INIT);
    }
}

void sendToQueueFromsServer(Instruction myMessage) {
 //  dbgOutputLoc(DBG_TASK_BEFORE_SEND_SERVERQUEUE);
   if (xQueueSendToBack(ServerToArmQ, &myMessage,  portMAX_DELAY)  == errQUEUE_FULL) {
      // everythingStop(DBG_EVERYTHING_STOP_SERVERQUEUE_SEND);
   }
  // dbgOutputLoc(DBG_TASK_AFTER_SEND_SERVERQUEUE);
}

Instruction ReceiveFromQueueFromServer() {
   // dbgOutputLoc(DBG_TASK_BEFORE_RECEIVE_SERVERQUEUE);
    Instruction buffer;
    if (xQueueReceive(ServerToArmQ, &buffer, portMAX_DELAY) == errQUEUE_EMPTY) {
       //  everythingStop(DBG_EVERYTHING_STOP_SERVERQUEUE_RECEIVE);
    }
   // dbgOutputLoc(DBG_TASK_AFTER_RECEIVE_SERVERQUEUE);
    return buffer;
}
