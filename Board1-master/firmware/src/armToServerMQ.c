#include "armToServerMQ.h"
#include "debug.h"

void armQueue_init() {
    armToServerQ = xQueueCreate(ARMQLength, sizeof(armResultMessageType)); 
    if (armToServerQ == QueueInitFail) {
      //  everythingStop(DBG_EVERYTHING_STOP_ARMQUEUE_INIT);
    }
}

void sendToQueueFromsArm(armResultMessageType myMessage) {
  // dbgOutputLoc(DBG_TASK_BEFORE_SEND_ARMQUEUE);
   if (xQueueSendToBack(armToServerQ, &myMessage,  portMAX_DELAY)  == errQUEUE_FULL) {
     //  everythingStop(DBG_EVERYTHING_STOP_ARMQUEUE_SEND);
   }
 //  dbgOutputLoc(DBG_TASK_AFTER_SEND_ARMQUEUE);
}

armResultMessageType ReceiveFromQueueFromArm() {
  //  dbgOutputLoc(DBG_TASK_BEFORE_RECEIVE_ARMQUEUE);
    armResultMessageType buffer;
    if (xQueueReceive(armToServerQ, &buffer, portMAX_DELAY) == errQUEUE_EMPTY) {
        // everythingStop(DBG_EVERYTHING_STOP_ARMQUEUE_RECEIVE);
    }
   // dbgOutputLoc(DBG_TASK_AFTER_RECEIVE_ARMQUEUE);
    return buffer;
}

