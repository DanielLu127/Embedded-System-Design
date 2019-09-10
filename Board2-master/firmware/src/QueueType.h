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
#define ONE                 1
#define ZERO                0
#define TWO                 2
#define THREE               3
#define FOUR                4
#define TRANSMIT_ARRAY_SIZE 300
#define GAME_NAME           3

// motor type
typedef enum { MTInit, MTidle, Front, Back, Stop, TurnRight90, TurnLeft90, TurnLSpecific,
               TurnRSpecific, FinishTurning, ReadEncoder, FStatus } MTCMD;
               
// Game queue type
typedef struct {
    int armAction;
    int piStart;
    int board;
    int mtAction;
    int mtDegree;
    int piDir;
    int piDegree;
    int sonarDir;
}GameQueType;
    
// WiFi type
typedef enum {TX, RX, STATISTIC} WiFiType;
typedef enum {GET, PUT} HttpRequestType;
    
typedef struct {
    WiFiType type;   
    char rx; 
    
    HttpRequestType req;
    int name;
    int board;
    int mtAction;
    int mtDegree;
    int armAction;
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

