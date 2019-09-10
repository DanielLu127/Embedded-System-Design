#include "wifi_state.h"

void Step_1_handler(uint8_t * my_char, uint16_t *counter , uint16_t * msg_len , bool * done, BaseType_t * cSwitch){
            Tx_msg tmp;
            dbgOutputLoc(DBG_MT_WIFI_TASK_STP_1);
            if(!tx_queue_empty_from_isr() ) { 
                dbgOutputLoc(DBG_MT_WIFI_TASK_STP_1_NOT_EMPTY);
                tmp = Uart_tx_queue_Recv(cSwitch);
                *msg_len = tmp.len;
                strcpy(my_char,tmp.temp_char);
                PLIB_USART_TransmitterByteSend(USART_ID_1, my_char[(*counter)++] );
                *done = true; // this result calls my step_2 handler in fsm 
            }
        
            else {
                PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT );
                }
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);

}

void Step_2_handler(uint8_t * my_char, uint16_t *counter , uint16_t * msg_len , bool * done, BaseType_t * cSwitch){
                dbgOutputLoc(DBG_MT_WIFI_TASK_STP_2);
                if(*counter < *msg_len){
                    dbgOutputLoc(DBG_MT_WIFI_TASK_STP_2_CHECK);
                    PLIB_USART_TransmitterByteSend(USART_ID_1, my_char[(*counter)++]);
                }
                else{
                    dbgOutputLoc(DBG_MT_WIFI_TASK_STP_2_CHECK);
                    *counter = 0;
                    *done = false; // this should just look at these cases 
                }
                PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
}

void Tx_isr_fsm(void){
    static uint8_t my_char[275];
    static uint16_t counter = 0;
    static uint16_t msg_len = 0;
    static bool done = false;
    BaseType_t cSwitch = pdFALSE;
    
    dbgOutputLoc(DBG_MT_WIFI_TASK_STP_2_CHECK);
    switch(done)
    {
        case true:
            Step_2_handler(my_char, &counter, &msg_len , &done, &cSwitch);
            break;
        case false:
            Step_1_handler(my_char, &counter, &msg_len , &done, &cSwitch);
            break;
    }
}     

void UART_Proxy(parseState *curState, WiFiQueType msg){
    Tx_msg item;
    static int requestSend = 0;
    static int corRely = 0;
    static int missReply = 0;
    static char buffer[500] = {};
    static int seqNumber = 0;
    int length;
    
    switch(msg.type){
        case TX: // this case means from thread
               requestSend++;
               length = http_construct(&msg, buffer, &seqNumber);
               strcpy(item.temp_char,buffer);
               item.len = length;
               send_2_Tx_queue(item);  
               SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
            break;     
        case RX: 
            http_parse(curState, msg.rx, &corRely, & missReply);
            break;
        case STATISTIC:
            length = stat_http_construct(requestSend, corRely, missReply, buffer, &seqNumber);
            strcpy(item.temp_char,buffer);
            item.len = length;
            send_2_Tx_queue(item);  
            SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
            break;
    }
}

