#include "pixy_queue.h"
// one is used for rx and the other for both timer and what to transmit
void PixyQueueInit(){
    PixyThread = xQueueCreate(21, sizeof(PIXY2_THREAD_MSG));
    if (PixyThread == Failed_to_init) {
        everythingStop(DBG_EVERYTHING_STOP_QUEUE_INIT);
    }
    
    Pixy_UART_ISR = xQueueCreate(10, sizeof(PIXY2_UART_MSG) );
    if (Pixy_UART_ISR == Failed_to_init)
        everythingStop(DBG_EVERYTHING_STOP_QUEUE_INIT);
}
// receives from one queue
PIXY2_THREAD_MSG PixyThreadReceive()
{
    dbgOutputLoc(B4_Receive);
    PIXY2_THREAD_MSG buf;
     if (xQueueReceive (PixyThread, &buf, portMAX_DELAY) == errQUEUE_EMPTY){
        // buf.Type = INIT; // tells fsm to go back to initial state
      //   buf.temp_char = 0; // initialized value
       everythingStop(DBG_EVERYTHING_STOP_QUEUE_RECEIVE);
    }
    dbgOutputLoc(DBG_TASK_AFTER_RECEIVE_QUEUE);
    return buf;
}
// receives from the other queue aka tx queue
PIXY2_UART_MSG Pixy_UART2_ISR_Receive(BaseType_t * priorityTaskWoke){
    dbgOutputLoc(B4_Tx2Recv);
    PIXY2_UART_MSG buf;
     if (xQueueReceiveFromISR(Pixy_UART_ISR, &buf, priorityTaskWoke) == errQUEUE_EMPTY){
        //everythingStop(DBG_EVERYTHING_STOP_QUEUE_RECEIVE);
    }
    dbgOutputLoc(DBG_TASK_AFTER_RECEIVE_QUEUE);
    return buf;
}
// this goes to my thread queue
void sendFromUARTISR(PIXY2_THREAD_MSG msg,  BaseType_t * priorityTaskWoke){
    dbgOutputLoc(B4_SENDUART);
    if (xQueueSendToBackFromISR(PixyThread, &msg, priorityTaskWoke) == errQUEUE_FULL){
       everythingStop(DBG_EVERYTHING_STOP_QUEUE_ISR);
   }
   dbgOutputLoc(AFTER_UART_ISR);
}

void sendFromTimer(PIXY2_THREAD_MSG msg){
    dbgOutputLoc(SEND_TO_THREAD_TMR);
        if (xQueueSendToBack(PixyThread, &msg, 0) == errQUEUE_FULL){
            everythingStop(DBG_EVERYTHING_STOP_QUEUE_ISR);
        }
   dbgOutputLoc(AFTER_SEND_FROM_TMR);
}



void sendToISR(PIXY2_UART_MSG msg)
{
    dbgOutputLoc(B4_SendToTx); // will be read by tx 
    
    if (xQueueSendToBack(Pixy_UART_ISR , &msg, 0) == errQUEUE_FULL){
       everythingStop(DBG_EVERYTHING_STOP_QUEUE_ISR);
   }
   dbgOutputLoc(After_TxSend);
}

bool Pixy_queueIsEmpty(){
    PIXY2_THREAD_MSG buf; 
    if(xQueuePeek(PixyThread, &buf, 0) != pdPASS)
        return true;
    return false;
        
}

 bool tx_queueIsEmpty(){
     PIXY2_UART_MSG buf;
     if(xQueuePeek(Pixy_UART_ISR, &buf, 0) != pdPASS ) // means its empty
         return true;
     return false;
 }

void pixy2fsm(PIXY2_THREAD_MSG  * curState)
{
    // byte_counter = 0, num_vars must be reset
    static int byte_counter = 0, num_vars = 0;
    static PIXY2_THREAD_MSG temp = {.Type = INIT, .temp_char = 0x00};
    static int deg[3];
    static uint32_t wide[4], x_arr[4] , y_arr[4], sig_map[4], ylen[4];
    static WiFiQueType itm = {.req = GET , .type = TX};
    
    
    static uint16_t i = 0; 
    switch(temp.Type){
        case INIT: // initial state only RECEIVE is enabled and error not transmit
            dbgOutputLoc(First_state);
            if(curState->Type == start) 
                temp.Type = TRANSMIT;
            break;
            
        case TRANSMIT:
            dbgOutputLoc(Second_State);
            fetchBlocks(255, 4); // we might need to change this receives from all signatures for up to 4 objects
            dbgOutputLoc(ENABLE_TX2);
            temp.Type = RECEIVE; 
            SYS_INT_SourceEnable(INT_SOURCE_USART_2_TRANSMIT);
          
            
            if(curState->Type == RECEIVE)
                queueData(curState->temp_char, ++byte_counter,  x_arr , y_arr, sig_map, deg, wide, ylen,  &num_vars);
            break;
            
         // this is purely from the point of view of my uart module 
        case RECEIVE:
            dbgOutputLoc(Third_State);
            // this means if our queue was empty it will be init, if it came from timer it's going to be a start
            if(curState->Type == RECEIVE)
                queueData(curState->temp_char, ++byte_counter,  x_arr , y_arr, sig_map, deg, wide, ylen, &num_vars);
            
            if( (byte_counter == (num_vars*14 + 6) )  || (num_vars == 0  && byte_counter == 6) || i == 2 )    { // this means our pixy_thread queue is empty, if the last message was of type init and there's no back log from the receive buffer, more than likely it's empty
                SendValsToUART(num_vars, x_arr, y_arr, sig_map, deg , wide, ylen ); // this means we are done
                byte_counter = 0; num_vars = 0;
                temp.Type = TRANSMIT;
                i = 0;
                reStartTimer(); // next time its called should be in 200 ms
            }
            
            else if(curState->Type == start)
                i++;
            break;
            
    }
}
/* *****************************************************************************
 End of File
 */
