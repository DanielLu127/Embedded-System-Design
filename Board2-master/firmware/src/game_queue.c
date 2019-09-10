#include "game_queue.h"

void gameQueue_init() {
    gameQueueHandle = xQueueCreate(GAME_QUEUE_LENGTH, sizeof(GameQueType));
    if (gameQueueHandle == GAME_QUEUE_INIT_FAIL) {
        everythingStop(DBG_EVERYTHING_STOP_MOTOR_QUEUE_INIT);
    }
}

void pushGameQueue(GameQueType msg) {
    dbgOutputLoc(DBG_MOTOR_TASK_BEFORE_SEND_QUEUE);
    if (xQueueSendToBack(gameQueueHandle, &msg, GAME_QUEUE_ALLOWED_DELAY) == errQUEUE_FULL){
       everythingStop(DBG_EVERYTHING_STOP_MTSW_SEND_TO_QUEUE_ISR);
    }
    dbgOutputLoc(DBG_MOTOR_TASK_AFTER_SEND_QUEUE);
    portEND_SWITCHING_ISR(pdTRUE);
}

void pushGameQueueFromISR(GameQueType msg, BaseType_t * prioprityTaskWoke) {
    dbgOutputLoc(DBG_MOTOR_TASK_BEFORE_SEND_QUEUE);
    if (xQueueSendToBackFromISR(gameQueueHandle, &msg, prioprityTaskWoke) == errQUEUE_FULL){
       everythingStop(DBG_EVERYTHING_STOP_MTSW_SEND_TO_QUEUE);
    }
    dbgOutputLoc(DBG_MOTOR_TASK_AFTER_SEND_QUEUE);
}

GameQueType popGameQueue() {
    dbgOutputLoc(DBG_MOTOR_TASK_BEFORE_RECEIVE_QUEUE);
    GameQueType buffer;
    if (xQueueReceive (gameQueueHandle, &buffer, portMAX_DELAY) == errQUEUE_EMPTY){
        everythingStop(DBG_EVERYTHING_STOP_MTSW_RECIEVE_QUEUE);
    }
    dbgOutputLoc(DBG_MOTOR_TASK_AFTER_RECEIVE_QUEUE);
    return buffer;
}
