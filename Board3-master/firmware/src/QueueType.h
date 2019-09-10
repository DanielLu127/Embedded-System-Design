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
#define MOTOR_NAME 0
#define MOTOR_ENCO_NAME 1
    
#define SONAR_NAME      2
#define PIXY_NAME 3
// motor type
typedef enum { MTInit, MTidle, Front, Back, Stop, TurnRight90, TurnLeft90, TurnLSpecific,
               TurnRSpecific, FinishTurning, ReadEncoder, FStatus } MTCMD;
    
typedef struct {
    MTCMD type;
    int degree;
} MtQueType;
    
// WiFi type
typedef enum {TX, RX, STATISTIC} WiFiType;
typedef enum {GET, PUT} HttpRequestType;
 

// pixy type 
typedef enum {RED, GREEN, BLUE, YELLOW} color_tracked; // color tracked 

typedef struct {
       uint16_t x; // keeps track of the x axis
       uint16_t y; // keeps track of where on the axis it's at 
       uint16_t width; // keeps track of the width of each object
       uint16_t height; // keeps track of the height of each object
       uint16_t sig; // draws other objects that it might be seeing, will be used in our fsm. /
       uint16_t piDir; // reprots the direction to the one being tracked
       uint16_t piDeg; // keeps track of the angle to the only one being looked at  
}Pixy2Obj;

typedef struct {
    WiFiType type;   
    char rx; 
    Pixy2Obj pixyData;
    HttpRequestType req;
    int name;
    int mtAction;
    int mtDegree;
    int mtLeft;
    int mtRight;
    int sonarDir;
    int sonarDis;
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

