#include "wifi_queue.h"

 void init_WIFI_queue(){
    dbgOutputLoc(03);
    // Initialize tx queue
    Uart_tx_queue = xQueueCreate(50 , sizeof(Tx_msg));
   
    if (Uart_tx_queue == Failed_to_init) {
        everythingStop(4);
    }
    // Initialize thread queue
    UART_Thread_queue = xQueueCreate(100, sizeof(WiFiQueType) );
    if (UART_Thread_queue == Failed_to_init)
        everythingStop(5); 
 }
 
void send_2_WIFI_QUEUE(WiFiQueType msg){
    dbgOutputLoc(7);
    if(xQueueSendToBack(UART_Thread_queue, &msg, 0) == errQUEUE_FULL){
        everythingStop(0);
    }
    dbgOutputLoc(8);
}

//this one is from ISR
void send_2_WIFI_QUEUE_from_isr(WiFiQueType msg, BaseType_t * CSwitch)
{
   dbgOutputLoc(9);
    if (xQueueSendToBackFromISR(UART_Thread_queue, &msg, CSwitch) == errQUEUE_FULL){
       everythingStop(0);
   }
   dbgOutputLoc(10);
}

WiFiQueType WIFI_QUEUE_Recv(){
    dbgOutputLoc(11);
    WiFiQueType item;
    if(xQueueReceive(UART_Thread_queue, &item, portMAX_DELAY) == errQUEUE_EMPTY ){
        return item;
     }
    dbgOutputLoc(12);
    return item;
}

void send_2_Tx_queue(Tx_msg msg){
   dbgOutputLoc(DBG_TX_BEFORE_SEND_QUEUE);
   if(xQueueSendToBack(Uart_tx_queue, &msg, 0) == errQUEUE_FULL)
        everythingStop(0);
//   dbgOutputLoc(DBG_TX_AFTER_SEND_QUEUE);
}

 Tx_msg Uart_tx_queue_Recv(BaseType_t * CSwitch){
    dbgOutputLoc(Tx_Recv);
    Tx_msg tmp;
    if(xQueueReceiveFromISR(Uart_tx_queue, &tmp,  CSwitch) == errQUEUE_EMPTY)
        everythingStop(0);
    return tmp;
 }

 bool tx_queue_empty_from_isr(){
     Tx_msg tmp;
     if(xQueuePeekFromISR(Uart_tx_queue, &tmp) == pdPASS)
         return false;
     return true;
 }

 /*void mt_Send_Finish() {
     WiFiQueType msg = {.type = TX, .req = PUT, .name = ARM_NAME};
     send_2_WIFI_QUEUE(msg); 
 }
 
 void mt_Send_GET() {
     WiFiQueType msg = {.type = TX, .req = GET, .name = ARM_NAME};
     send_2_WIFI_QUEUE(msg); 
 }
*/