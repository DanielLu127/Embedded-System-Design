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
#define BUFFER_MAX_INDEX         300

int http_construct(WiFiQueType *msg, char buffer[], int *seqNumber);
int GET_construct_Helper(int name, char buffer[], int *seqNumber);
int MT_PUT_construct_Helper(int start, char buffer[], int *seqNumber);

int stat_http_construct(int requestSend, int correctReceive, int missReply, char buffer[], int *seqNumber);
void http_parse(parseState *curState, char data, int *corRely, int *incorRely);

void recieveHelpFunc(parseState *curState, char history[], int *pos);
void GETrecieveHelpFunc(parseState *curState, char history[],  int *pos, int *contentLenPos);
void GETnumHelpFunc(parseState *curState, char history[], int *pos, int *contentLenPos, int *contentLen);
void GETcontentHelpFunc(parseState *curState, char history[], int *pos, int *corRely, int *incorRely, int *contentLen);
int addChar(char history[], char data, int post);
bool isHttp(char history[], int pos);
void jsonDecode(char jsonString[], int *corReply, int *missReply);

// From this point on are pixy cam functions
void PixyGet(int * seqNumber, char buffer[]);
int PIXY_PUT_construct_Helper(Pixy2Obj data, char buffer[], int * seqNumber); // direction is right or left


#ifdef	__cplusplus
}
#endif

#endif	/* HTTP_H */

