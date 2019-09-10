/* 
 * File:   wifi_state.h
 * Author: xuanli
 *
 * Created on April 13, 2019, 1:31 PM
 */

#ifndef WIFI_STATE_H
#define	WIFI_STATE_H

#include "QueueType.h"
#include "debug.h"
#include "http.h"
#include "wifi_queue.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    void Step_1_handler(uint8_t * my_char, uint16_t *counter , uint16_t * msg_len , bool * done, BaseType_t * cSwitch); // handles the loop the first time it comes
    void Step_2_handler(uint8_t * my_char, uint16_t *counter , uint16_t * msg_len , bool * done, BaseType_t * cSwitch); // this just sends the string step 1 made
    
    void Tx_isr_fsm(void);
    void UART_Proxy(parseState *curState, WiFiQueType msg);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif	/* WIFI_STATE_H */

