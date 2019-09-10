/* 
 * File:   http.h
 * Author: xuanli
 *
 * Created on April 13, 2019, 1:54 PM
 */

#ifndef HTTP_H
#define	HTTP_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "math.h"
#include "QueueType.h"
#include "cJSON.h"
#include "game_queue.h"
#define BUFFER_MAX_INDEX         200
#define ZERO_SIZE                0
#define ONE_INCREMENT            1
#define INVALID_POS              -1
#define NUM_CHAR_MAX_SIZE        6

// Add new thread-network function procedure:
//  0) add sending data type to wifi thread queue type
//  1) add new put helper function
//  2) use this function in http construct function for one case
//  3) no need for GET request
//  4) add parsing and sending msg back to new thread function by editing jsonDecode
    
// Functions needed to be changed
int http_construct(WiFiQueType *msg, char buffer[], int *seqNumber);
int Game_PUT_construct_Helper(WiFiQueType *msg, char buffer[], int *seqNumber);
void jsonDecode(char jsonString[], int *corReply, int *missReply);
int stat_http_construct(int requestSend, int correctReceive, int missReply, char buffer[], int *seqNumber);

// Helper functions
int GET_construct_Helper(int name, char buffer[], int *seqNumber);
void http_parse(parseState *curState, char data, int *corRely, int *incorRely);
void recieveHelpFunc(parseState *curState, char history[], int *pos);
void GETrecieveHelpFunc(parseState *curState, char history[],  int *pos, int *contentLenPos);
void GETnumHelpFunc(parseState *curState, char history[], int *pos, int *contentLenPos, int *contentLen);
void GETcontentHelpFunc(parseState *curState, char history[], int *pos, int *corRely, int *incorRely, int *contentLen);
int addChar(char history[], char data, int post);
bool isHttp(char history[], int pos);

#ifdef	__cplusplus
}
#endif

#endif	/* HTTP_H */

