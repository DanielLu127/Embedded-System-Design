/*
 * File:   motor_queue.c
 * Author: Team 10
 *
 * Created on February 24, 2019, 2:20 PM
 */
#include "motor_queue.h"

void motorQueue_init(){
    mtQueueHandle = xQueueCreate(MT_QUEUE_LENGTH, sizeof(MtQueType));
    if (mtQueueHandle == MT_QUEUE_INIT_FAIL) {
        everythingStop(DBG_EVERYTHING_STOP_MOTOR_QUEUE_INIT);
    }
}

void pushMtQueueFromISR(MtQueType msg, BaseType_t * prioprityTaskWoke){
    dbgOutputLoc(DBG_MOTOR_TASK_BEFORE_SEND_QUEUE);
    if (xQueueSendToBackFromISR(mtQueueHandle, &msg, prioprityTaskWoke) == errQUEUE_FULL){
       everythingStop(DBG_EVERYTHING_STOP_MTSW_SEND_TO_QUEUE);
    }
    dbgOutputLoc(DBG_MOTOR_TASK_AFTER_SEND_QUEUE);
}

void pushMtQueue(MtQueType msg){
    dbgOutputLoc(DBG_MOTOR_TASK_BEFORE_SEND_QUEUE);
    if (xQueueSendToBack(mtQueueHandle, &msg, MT_QUEUE_ALLOWED_DELAY) == errQUEUE_FULL){
       everythingStop(DBG_EVERYTHING_STOP_MTSW_SEND_TO_QUEUE_ISR);
    }
    dbgOutputLoc(DBG_MOTOR_TASK_AFTER_SEND_QUEUE);
    portEND_SWITCHING_ISR(pdTRUE);
}

MtQueType popMtQueue(){
    dbgOutputLoc(DBG_MOTOR_TASK_BEFORE_RECEIVE_QUEUE);
    MtQueType buffer;
    if (xQueueReceive (mtQueueHandle, &buffer, portMAX_DELAY) == errQUEUE_EMPTY){
        everythingStop(DBG_EVERYTHING_STOP_MTSW_RECIEVE_QUEUE);
    }
    dbgOutputLoc(DBG_MOTOR_TASK_AFTER_RECEIVE_QUEUE);
    return buffer;
}

void sendFinishFeedBack(){
    MtQueType sendingMsg;
    sendingMsg.type = FinishTurning;
    pushMtQueue(sendingMsg);
}

void sendAdjustFeedBack() {
    MtQueType sendingMsg;
    sendingMsg.type = ReadEncoder;
    pushMtQueue(sendingMsg);
}