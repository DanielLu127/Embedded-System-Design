#include "wifi_state.h"

void Step_1_handler(uint8_t * my_char, uint16_t *counter , uint16_t * msg_len , bool * done, BaseType_t * cSwitch){
            Tx_msg tmp;
            dbgOutputLoc(56);
            if(!tx_queue_empty_from_isr() ) { // non blociing check of the uart queue
                dbgOutputLoc(57);
                tmp = Uart_tx_queue_Recv(cSwitch);
                *msg_len = tmp.len;
                strcpy(my_char,tmp.temp_char);
                PLIB_USART_TransmitterByteSend(USART_ID_1, my_char[(*counter)++] );
                *done = true; // this result calls my step_2 handler in fsm 
            }
        
            else {
                PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT ); // this means tx queue was empty
                }
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT); // clears flag

}

void Step_2_handler(uint8_t * my_char, uint16_t *counter , uint16_t * msg_len , bool * done, BaseType_t * cSwitch){
                dbgOutputLoc(61);
                if(*counter < *msg_len){
                 dbgOutputLoc(61);
                PLIB_USART_TransmitterByteSend(USART_ID_1, my_char[(*counter)++]);
                //*counter = *counter + 1;
                }
                
                else{
                    dbgOutputLoc(62);
                    *counter = 0;
                    *done = false; // this should just look at these cases 
                }
                PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
}

void Tx_isr_fsm(void){
    static uint8_t my_char[275];
    static uint16_t counter = 0;
    static uint16_t msg_len = 0;
    static bool done = false; // this means I'm still working on last message
    BaseType_t cSwitch = pdFALSE;
    
    dbgOutputLoc(45);
    switch(done)
    {
        case true: // continue reading from buffer
            Step_2_handler(my_char, &counter, &msg_len , &done, &cSwitch);
            break;
        case false:
            Step_1_handler(my_char, &counter, &msg_len , &done, &cSwitch);
            break;
    }
}     

void UART_Proxy(parseState *curState, WiFiQueType msg){
    Tx_msg item;
    static actionList newAction = ForeArm;
    Instruction newIns;
    static int requestSend = InitValue;
    static int corRely = InitValue;
    static int missReply = InitValue;
    static char buffer[BufferLength] = {};
    static int seqNumber = InitValue;
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
        case INNER_ACTION:
            newIns.type = WIFI;
            newIns.start = msg.start;
            sendToQueueFromsServer(newIns);
    }
}

