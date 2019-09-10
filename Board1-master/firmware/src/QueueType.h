/* 
 * File:   QueueType.h
 * Author: xuanli
 *
 * Created on April 13, 2019, 2:34 PM
 */

#ifndef QUEUETYPE_H
#define	QUEUETYPE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#define TRANSMIT_ARRAY_SIZE 300
#define ARM_NAME 0
#define START 1
#define STOP  0
#define BaseLeft   0
#define ForeArm  1
#define InitValue 0
#define BufferLength 100                    
#define DBG_TX_BEFORE_SEND_QUEUE 0x10
#define DBG_TX_AFTER_SEND_QUEUE  0x20
#define PIXY_NAME 2
// motor type
    
    
typedef enum {SW, WIFI} messageType;
typedef enum {FRF, CCLOSE, COPEN, BRL, FRB, BRR, COPEN2, CLOSE2} actionList;
    
typedef struct {
    messageType type;
    actionList actionStatus;
    int start;
}  Instruction;

// WiFi type
typedef enum {TX, RX, STATISTIC, INNER_ACTION} WiFiType;
typedef enum {GET, PUT} HttpRequestType;
    
// pixy type 
typedef enum {NONE , RED, GREEN, BLUE, YELLOW} color_tracked; // color tracked 

typedef struct {
       uint16_t x; // keeps track of the x axis
       uint16_t y; // keeps track of where on the axis it's at 
       uint16_t width; // keeps track of the width of each object
       uint16_t height; // keeps track of the height of each object
       uint16_t piStart;
}Pixy2Obj;

typedef struct {
    WiFiType type;   
    char rx; 
    Pixy2Obj pixyData;
    HttpRequestType req;
    int name;
    int start;
} WiFiQueType;
    
    
typedef struct {
    uint16_t len;
    char temp_char[TRANSMIT_ARRAY_SIZE];
} Tx_msg;

    typedef enum {
    idle, recieve, GETrecieve, GETnum, GETcontent
    } parseState;
    
#ifdef	__cplusplus
}
#endif

#endif	/* QUEUETYPE_H */

