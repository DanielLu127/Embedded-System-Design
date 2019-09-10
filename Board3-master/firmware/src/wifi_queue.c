#include "wifi_queue.h"

 void init_WIFI_queue(){
    // Initialize tx queue
    Uart_tx_queue = xQueueCreate(50 , sizeof(Tx_msg));
   
    if (Uart_tx_queue == Failed_to_init) {
        everythingStop(DBG_EVERYTHING_STOP_MTWIFI_INIT_TX_QUEUE);
    }
    // Initialize thread queue
    UART_Thread_queue = xQueueCreate(100, sizeof(WiFiQueType) );
    if (UART_Thread_queue == Failed_to_init)
        everythingStop(DBG_EVERYTHING_STOP_MTWIFI_INIT_THREAD_QUEUE); 
 }
 
void send_2_WIFI_QUEUE(WiFiQueType msg){
    dbgOutputLoc(DBG_MT_WIFI_TASK_BEFORE_SEND_QUEUE);
    if(xQueueSendToBack(UART_Thread_queue, &msg, 0) == errQUEUE_FULL){
        everythingStop(DBG_EVERYTHING_STOP_MTWIFI_SEND_TO_QUEUE);
    }
    dbgOutputLoc(DBG_MT_WIFI_TASK_AFTER_SEND_QUEUE);
}

void send_2_WIFI_QUEUE_from_isr(WiFiQueType msg, BaseType_t * CSwitch)
{
   dbgOutputLoc(DBG_MT_WIFI_TASK_BEFORE_SEND_QUEUE_ISR);
    if (xQueueSendToBackFromISR(UART_Thread_queue, &msg, CSwitch) == errQUEUE_FULL){
       everythingStop(DBG_EVERYTHING_STOP_MTSW_SEND_TO_QUEUE_ISR);
   }
   dbgOutputLoc(DBG_MT_WIFI_TASK_AFTER_SEND_QUEUE_ISR);
}

WiFiQueType WIFI_QUEUE_Recv(){
    dbgOutputLoc(DBG_MT_WIFI_TASK_BEFORE_RECEIVE_QUEUE);
    WiFiQueType item;
    if(xQueueReceive(UART_Thread_queue, &item, portMAX_DELAY) == errQUEUE_EMPTY ){
        everythingStop(DBG_EVERYTHING_STOP_MTSW_RECIEVE_QUEUE);
     }
    dbgOutputLoc(DBG_MY_WIFI_TASK_AFTER_RECEIVE_QUEUE);
    return item;
}

void send_2_Tx_queue(Tx_msg msg){
   dbgOutputLoc(DBG_MT_WIFI_TASK_BEFORE_SEND_TX);
   if(xQueueSendToBack(Uart_tx_queue, &msg, 0) == errQUEUE_FULL)
        everythingStop(DBG_EVERYTHING_STOP_MTWIFI_SEND_TO_TX);
   dbgOutputLoc(DBG_MT_WIFI_TASK_AFTER_SEND_TX);
}

 Tx_msg Uart_tx_queue_Recv(BaseType_t * CSwitch){
    dbgOutputLoc(DBG_MT_WIFI_TASK_BEFORE_REC_TX);
    Tx_msg tmp;
    if(xQueueReceiveFromISR(Uart_tx_queue, &tmp,  CSwitch) == errQUEUE_EMPTY)
        everythingStop(DBG_EVERYTHING_STOP_MTWIFI_REC_TX);
    dbgOutputLoc(DBG_MT_WIFI_TASK_AFTER_REC_TX);
    return tmp;
 }

 bool tx_queue_empty_from_isr(){
     Tx_msg tmp;
     if(xQueuePeekFromISR(Uart_tx_queue, &tmp) == pdPASS)
         return false;
     return true;
 }

 void mt_Send_Finish() {
     WiFiQueType msg = {.type = TX, .req = PUT, .name = MOTOR_NAME, .mtAction = MTidle, .mtDegree = ZERO_SPEED};
     send_2_WIFI_QUEUE(msg); 
 }
 
 void mt_Send_Running() {
     WiFiQueType msg = {.type = TX, .req = PUT, .name = MOTOR_NAME, .mtAction = FStatus, .mtDegree = ZERO_SPEED};
     send_2_WIFI_QUEUE(msg); 
 }
 
 void mt_Send_GET() {
     WiFiQueType msg = {.type = TX, .req = GET, .name = MOTOR_NAME};
     send_2_WIFI_QUEUE(msg); 
 }
 
 void mt_Send_Encoder(int *leftPWM, int *rightPWM) {
     WiFiQueType msg = {.type = TX, .req = PUT, .name = MOTOR_ENCO_NAME, .mtLeft = *leftPWM, .mtRight = *rightPWM};
     send_2_WIFI_QUEUE(msg); 
 }