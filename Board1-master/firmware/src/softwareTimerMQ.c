
#include "softwareTimerMQ.h"
#include "debug.h"

void SWQueue_init() {
    softwareTimerQ = xQueueCreate(SWQLength, sizeof(int));
    if ( softwareTimerQ == QueueInitFail) {
      //  everythingStop(DBG_EVERYTHING_STOP_SERVERQUEUE_INIT);
    }
}

void sendToQueue(int myMessage) {
  // dbgOutputLoc(DBG_TASK_BEFORE_SEND_SERVERQUEUE);
   if (xQueueSendToBack(softwareTimerQ, &myMessage,  portMAX_DELAY)  == errQUEUE_FULL) {
     //  everythingStop(DBG_EVERYTHING_STOP_SERVERQUEUE_SEND);
   }
 //  dbgOutputLoc(DBG_TASK_AFTER_SEND_SERVERQUEUE);
}

int ReceiveFromQueue() {
 //   dbgOutputLoc(DBG_TASK_BEFORE_RECEIVE_SERVERQUEUE);
    int buffer;
    if (xQueueReceive(softwareTimerQ, &buffer, portMAX_DELAY) == errQUEUE_EMPTY) {
      //   everythingStop(DBG_EVERYTHING_STOP_SERVERQUEUE_RECEIVE);
    }
  //  dbgOutputLoc(DBG_TASK_AFTER_RECEIVE_SERVERQUEUE);
    return buffer;
}
