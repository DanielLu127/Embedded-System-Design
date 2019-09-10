#include "pixy2Func.h"


extern void fetchBlocks(uint8_t numSigMaps , uint8_t maxBlocks)
{
    static uint8_t block[6] = {
    0xae, 0xc1,
    0x20, 0x02
    };
    
    block[4] = numSigMaps; // might have to hard code this to all or 255
    block[5] = maxBlocks; // might have to hard code this to 3 
    
    dbgOutputLoc(Block_Event);
    PIXY2_UART_MSG tmp = {.value=0 , .temp_char = block};
    
    sendToISR(tmp);
}

void setXs(uint8_t datum, unsigned int counter, uint32_t * x_arr){
  // block for x_spots()) 
     if( (counter-FIRST_X) % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_X)
         x_arr[((counter - FIRST_X) / PAYLOAD_BLOCK_LENGTH)] = datum; // should initialize the correct spot

     if ( ( counter - (FIRST_X+HALF_OFFSET) )  % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_X + HALF_OFFSET ) 
         x_arr[(counter - (FIRST_X + HALF_OFFSET) ) / PAYLOAD_BLOCK_LENGTH  ] += datum * NINTH_BIT_SCALE; // should update the correct spot
}

void setYs(uint8_t datum , unsigned int counter, uint32_t * y_arr){
     if((counter -FIRST_Y) % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_Y)
         y_arr[((counter - FIRST_Y) / PAYLOAD_BLOCK_LENGTH ) ] = datum;
     // end block for x spots())
     //-------------y block----------------------------------------------------/////////////////////////////////////////
     if ( ( counter - (FIRST_Y+HALF_OFFSET) )  % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_Y + HALF_OFFSET ) 
         y_arr[(counter - (FIRST_Y + HALF_OFFSET) )  / PAYLOAD_BLOCK_LENGTH  ] += datum * NINTH_BIT_SCALE;     
}

void setSigMap(uint8_t datum , unsigned int counter, uint32_t * sig_map){
     // block for sign maps
     if((counter-FIRST_SIGMAP) % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_SIGMAP)
         sig_map[((counter - FIRST_SIGMAP) / PAYLOAD_BLOCK_LENGTH)] = datum;
     
     if ( ( counter - (FIRST_SIGMAP+HALF_OFFSET) )  % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_SIGMAP + HALF_OFFSET ) 
         sig_map[  (counter - (FIRST_SIGMAP + HALF_OFFSET) ) / PAYLOAD_BLOCK_LENGTH  ] += datum * NINTH_BIT_SCALE;
}

void setAngles(uint8_t datum , unsigned int counter, int * angles){ // stores angles
    if( (counter-FIRST_ANGLE) % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_ANGLE)
        angles[((counter - FIRST_ANGLE) / PAYLOAD_BLOCK_LENGTH)] = datum;
    
    if ( ( counter - (FIRST_ANGLE + HALF_OFFSET) )  % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_ANGLE + HALF_OFFSET ) 
         angles[ (counter - (FIRST_ANGLE + HALF_OFFSET) ) / PAYLOAD_BLOCK_LENGTH  ] += datum * NINTH_BIT_SCALE;
}

void setWidth(uint8_t datum , unsigned int counter, uint32_t * wide){
    if( (counter-FIRST_WIDTH) % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_WIDTH)
        wide[ ( (counter - FIRST_WIDTH) / PAYLOAD_BLOCK_LENGTH)] = datum;

    if ( ( counter - (FIRST_WIDTH+HALF_OFFSET) )  % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= FIRST_WIDTH + HALF_OFFSET ) 
         wide[ ((counter - (FIRST_WIDTH + HALF_OFFSET) ) / PAYLOAD_BLOCK_LENGTH  )] += datum * NINTH_BIT_SCALE;
}
 
void setPixy2Universal(uint8_t datum, unsigned int counter, unsigned int define,  uint32_t * buf){
    if( (counter-define) % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= define)
        buf[ ( (counter - define) / PAYLOAD_BLOCK_LENGTH)] = datum;

    if ( ( counter - (define+HALF_OFFSET) )  % PAYLOAD_BLOCK_LENGTH == EXAMPLE_CONSTANT && counter >= define + HALF_OFFSET ) 
         buf[ ( (counter - (define + HALF_OFFSET) ) / PAYLOAD_BLOCK_LENGTH  )] += datum * NINTH_BIT_SCALE;
}

 void queueData(uint8_t datum, unsigned int counter, uint32_t * x_arr, uint32_t * y_arr, uint32_t * sig_map, int * deg, uint32_t * wide, uint32_t * ylen,  unsigned int * numVars){
     static unsigned int NumberOfVariables = 0;
     int whatVariable;
     int xPart1;
     // this only happens once
     if(counter == PAYLOAD_BYTE){
         *numVars = (uint32_t)datum/14; // should always be even number anyway ;
     }
     
     setXs(datum, counter, x_arr);
     setYs(datum , counter, y_arr);
     setSigMap(datum , counter, sig_map);
     setAngles(datum, counter, deg);
     setWidth(datum, counter, wide);
     setPixy2Universal(datum, counter, FIRST_HEIGHT, ylen);
 }


 void MSB(uint32_t * Data, unsigned int slot, unsigned char * msg, unsigned int location){
     uint32_t value = Data[slot];
     
     if(value >= 100)
         msg[location] = (value / 100) + '0';
     
     else
         msg[location] = '0';
 }
   
 void Midval(uint32_t * Data, unsigned int slot, unsigned char * msg, unsigned int location){
     uint32_t value = Data[slot];
     uint8_t Part1;
     uint8_t Part2;
     if(value >= 100)
     {
      Part1 = value/10;
      Part2 = Part1 % 10; // gives me the middle value
      msg[location] = Part2 + '0';
     }
     
     else if(value < 100 && value > 9)
         msg[location] = value/10 + '0';
     
     else{
         msg[location] = '0';
     }
 }
   
 void LSB(uint32_t * Data, unsigned int slot, unsigned char * msg, unsigned int location){
     uint8_t value = Data[slot];
     msg[location] = (uint8_t)(value % 10) + '0';
 }
 
 void strAssgn(unsigned char * msg, unsigned char *buf,  unsigned int len){
 unsigned int i = 0;
 for(i; i < len; i++)
     buf[i] = msg[i];
 }
 
 void SendValsToUART(unsigned int NumberOfVariables, uint32_t * x_arr, uint32_t * y_arr, uint32_t * sig_map, uint32_t * deg, uint32_t * wide , uint32_t * ylen){

     unsigned int i = 0;
     WiFiQueType tmp = {.type = TX, .req = PUT , .name = PIXY_NAME};
     static color_tracked fsm = RED;
     if(NumberOfVariables == 0){
         Pixy2Obj itm = {.piStart = 0}; // this means you need to just clear
         tmp.pixyData = itm;
         send_2_WIFI_QUEUE(tmp);  
     } 
     
     else{
         directionPixy(wide, ylen ,sig_map, x_arr, y_arr,  NumberOfVariables);
     }
     
 }
 
 void directionPixy(uint32_t * wide, uint32_t * ylen, int * sig, uint32_t * x, uint32_t * y, unsigned int num_vars){
     bool centralized = false;
     unsigned int i = 0;
     int temp_index;
     unsigned int smallestDist = 99999;
     int tempDelta = 0; 
     for(i = 0; i < num_vars; i++){
         tempDelta = (x[i] - midpoint);
         if(abs(tempDelta) < smallestDist )
             smallestDist = abs(tempDelta);
     }
     
     Pixy2Obj send = {.piStart = (smallestDist <= 25) ? 1 : 0}; // this means you need to just clear
     WiFiQueType tmp = {.type = TX, .req = PUT , .name = PIXY_NAME, .pixyData = send};
     send_2_WIFI_QUEUE(tmp);
 }

 
 void pixy_uart_fsm(void){
     static uint16_t count = 0;
     BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
     static PIXY2_UART_MSG tmp;
     static bool done = false;
     
     switch(done){
         case true:
             if (count == 6){
                 done = false;
                 count = 0;
                 PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT);
             }
             else
                  PLIB_USART_TransmitterByteSend(USART_ID_2, tmp.temp_char[count++]);
                  PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT);             
          break;
          
          
         case false:
                    if(xQueuePeekFromISR(Pixy_UART_ISR, &tmp) == pdPASS){
                       tmp = Pixy_UART2_ISR_Receive(&pxHigherPriorityTaskWoken);
                       PLIB_USART_TransmitterByteSend(USART_ID_2, tmp.temp_char[count++]);
                       PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT);
                       done = true;
                       portEND_SWITCHING_ISR(&pxHigherPriorityTaskWoken); // notifies waiting queue ;) 
                   } // non blocking read

                   else{ // this means she empty
                       dbgOutputLoc(DISABLE_TRANSMTI);
                       PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT );// stop it get some help disables the transmit source
                       PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT);
                        }
                       break;
     }
     
 }

uint16_t Pixy_look_up_init(int loc){
    static uint16_t pixy_lut[158]; 
    int i = 0; 
    if(loc == -1){
        for(i; i < 158; i++)
                pixy_lut[i] = 5 * (i/20);
    }
    
    else if (loc >= 0)
        return pixy_lut[loc];
    
    else
        return -1; // error flag;
    
    
}

uint16_t Pixy_time_lut(int loc){ // look up table for time
    static uint16_t pixy_time_lut[158]; 
    int i = 0; 
    if(loc == -1){
        for(i; i < 158; i++)
                pixy_time_lut[i] = 10 + 10* (i /15);
    }
    
    else if (loc >= 0)
        return pixy_time_lut[loc];
    
    else
        return -1; // error flag;
}

int get_color_index(color_tracked val, int * sigs, int num_vars){
    int i =0;
    switch(val){
        case RED:
            for(i; i < num_vars; i++)
                if(sigs[i] == 4) // which corresponds to red
                    return i;
            break;
            
        case GREEN:
            for(i; i < num_vars; i++)
                if(sigs[i] == 1)
                    return i;
            break;
    }
    
    return -1; // this means it wasn't found
}

color_tracked getColor(unsigned int signature){
    color_tracked sendMe;
    switch(signature){
        case 0: sendMe = NONE;
        break;
        
        case 1: sendMe = GREEN;
        break;
        
        case 2: sendMe = BLUE;
        break;
        
        case 3: sendMe = YELLOW;
        break;
        
        case 4: sendMe = RED;
        break;
    }
        return sendMe;
}
/* *****************************************************************************
 End of File
 */
