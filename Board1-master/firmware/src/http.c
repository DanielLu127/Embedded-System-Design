#include "http.h"

int http_construct(WiFiQueType *msg, char buffer[], int *seqNumber) {
    int TotalSize = 0;
    if (msg->req == GET) {
       TotalSize = GET_construct_Helper(msg->name, buffer, seqNumber);
    }
    else if (msg->req == PUT) {
        if(msg->name == ARM_NAME)
            TotalSize = MT_PUT_construct_Helper(msg->start, buffer, seqNumber);
        else if(msg->name == PIXY_NAME)
            TotalSize = PIXY_PUT_construct_Helper(msg->pixyData, buffer, seqNumber);
    }
    return TotalSize;
}

int GET_construct_Helper(int name, char buffer[], int *seqNumber)
{
    strcpy(buffer, "GET /");
    if(name == ARM_NAME) {
        (*seqNumber)++;
        char tempNum [100];
        sprintf(tempNum, "%d", *seqNumber);
        strcat(buffer, "arm/");
        strcat(buffer, tempNum);
    }
    strcat(buffer, " HTTP/1.1\r\nHost: 192.168.0.10:80\r\n\r\n");
    return strlen(buffer);
}

int MT_PUT_construct_Helper(int start, char buffer[], int *seqNumber) {
    // Use cJSON to create JSON format char array
	cJSON * rootObject = cJSON_CreateObject();
    cJSON_AddItemToObject(rootObject,"armAction", cJSON_CreateNumber(start));
    char *temp = cJSON_PrintUnformatted(rootObject);
    cJSON_Delete(rootObject);
    int contentLength = strlen(temp);
    (*seqNumber)++;
    sprintf(buffer, "PUT /arm/%d HTTP/1.1\r\nHost: 192.168.0.10:80\r\nContent-type: application/json\r\nContent-length:%d \r\n\r\n", *seqNumber, contentLength);
    strcat(buffer, temp);
    vPortFree(temp);
    int totalSize = strlen(buffer);
    return totalSize;
}

int stat_http_construct(int requestSend, int correctReceive, int missReply, char buffer[], int *seqNumber)
{
    cJSON * rootObject = cJSON_CreateObject();
    cJSON_AddItemToObject(rootObject,"name", cJSON_CreateString("B1"));
    cJSON_AddItemToObject(rootObject,"reqSend",cJSON_CreateNumber(requestSend));
    cJSON_AddItemToObject(rootObject,"corRec",cJSON_CreateNumber(correctReceive));
    cJSON_AddItemToObject(rootObject,"missReply",cJSON_CreateNumber(missReply));
    char *temp = cJSON_PrintUnformatted(rootObject);
    cJSON_Delete(rootObject);
    int contentLength = strlen(temp);
    (*seqNumber)++;
    sprintf(buffer, "PUT /stat0/%d HTTP/1.1\r\nHost: 192.168.0.10:80\r\nContent-type: application/json\r\nContent-length:%d \r\n\r\n", *seqNumber, contentLength);
    strcat(buffer, temp);
    vPortFree(temp);
    int totalSize = strlen(buffer);
    return totalSize;
}

void http_parse(parseState *curState, char data, int *corRely, int *incorRely) {
    static int pos = 0;
    static int contentLen = 0;
    static int contentLenPos = 0;
    static char history[BUFFER_MAX_INDEX+1];
    pos = addChar(history, data, pos);
    switch (*curState) {
        case(idle):
            if (isHttp(history, pos)) {
                *curState = recieve;
                pos = -1;
            }
            break;
        case(recieve):
            recieveHelpFunc(curState, history, &pos);
            break;
        case(GETrecieve):
            GETrecieveHelpFunc(curState, history,  &pos, &contentLenPos);
            break;
        case(GETnum):
            GETnumHelpFunc(curState, history,  &pos, &contentLenPos, &contentLen);
            break;
        case(GETcontent):
            GETcontentHelpFunc(curState, history, &pos, corRely, incorRely, &contentLen);
            break;
        default:
            break;
    }
}

void recieveHelpFunc(parseState *curState, char history[], int *pos) {
    if (isHttp(history, *pos)) {
        *pos = -1;
    }
    else if (*pos == 7) {
        if (history[5] == '2' && history[6] == '0') {
            *curState = GETrecieve;
            *pos = -1;
        }
        else {
            *curState = idle;
        }
    }
}

void GETrecieveHelpFunc(parseState *curState, char history[],  int *pos, int *contentLenPos) {
    if (isHttp(history, *pos)) {
        *curState = recieve;
        *pos = -1;
    }
    else if (*pos > 16 && history[*pos] == ' ' && history[*pos-1] == ':' && history[*pos-2] == 'h' && history[*pos-3] == 't' && history[*pos-4] == 'g' && history[*pos-5] == 'n' && history[*pos-6] == 'e' && history[*pos-7] == 'L') {
        *curState = GETnum;
        *contentLenPos = *pos+1;
    }
}

void GETnumHelpFunc(parseState *curState, char history[], int *pos, int *contentLenPos, int *contentLen) {
    if (isHttp(history, *pos)) {
        *curState = recieve;
        *pos = -1;
    }
    else if (history[*pos - 2] == '\n' && history[*pos - 1] == '\r' && history[*pos] == '\n') {
        int i, j = 0;
        *contentLen = 0;
        for (i = *pos - 4, j = 0; i >= *contentLenPos; i--, j++) {
            *contentLen += (int)(history[i] - '0')*pow(10, j);
        }
        *curState = GETcontent;
        *pos = -1;
    }
}

void GETcontentHelpFunc(parseState *curState, char history[], int *pos, int *corRely, int *incorRely, int *contentLen) {
    if (isHttp(history, *pos)) {
        *curState = recieve;
        *pos = -1;
    }
    // end case
    else if ( history[*pos] == '}') {
        if (*pos == *contentLen - 1) {
            int i;
            char jsonString[*contentLen];
            for (i = 0; i < *contentLen; i++) {
                jsonString[i] = history[i];
                //DRV_USART1_WriteByte(history[i]);
                //PLIB_USART_TransmitterByteSend(USART_ID_2, history[i]);
            }
            jsonDecode(jsonString, corRely, incorRely);
        }
        *curState = idle;
    }
}

int addChar(char history[], char data, int post) {
    int pos = (post == BUFFER_MAX_INDEX)? 0: post+1;
    history[pos] = data;
    return pos;
}

bool isHttp(char history[], int pos) {
    if (pos > 2) {
        if (history[pos] == 'P' && history[pos-1] == 'T' && history[pos-2] == 'T' && history[pos-3] == 'H')
            return true;
    }
    else if (pos == 2) {
        if (history[2] == 'P' && history[1] == 'T' && history[0] == 'T' && history[BUFFER_MAX_INDEX] == 'H')
            return true;
    }
    else if (pos == 1) {
        if (history[1] == 'P' && history[0] == 'T' && history[BUFFER_MAX_INDEX] == 'T' && history[BUFFER_MAX_INDEX-1] == 'H')
            return true;
    }
    else{
        if (history[0] == 'P' && history[BUFFER_MAX_INDEX] == 'T' && history[BUFFER_MAX_INDEX-1] == 'T' && history[BUFFER_MAX_INDEX-2] == 'H')
            return true;
    }
    return false;
}

void jsonDecode(char jsonString[], int *corReply, int *missReply) {
    static int seqLocal = 0;
    static char *nameTestChar;
    cJSON *rootObject = cJSON_Parse(jsonString);
    if(rootObject != NULL) {
        cJSON *seqInput = cJSON_GetObjectItem(rootObject, "seq");
        cJSON *name = cJSON_GetObjectItem(rootObject, "name");
        if (name != NULL) {
            if (*(name->valuestring) == 'a') {
                cJSON *armAction = cJSON_GetObjectItem(rootObject, "armAction");
                if (armAction != NULL) {
                    Instruction msg = {.type = WIFI, .start = armAction->valueint};
                    sendToQueueFromsServer(msg);
                }   
            }
            // add more here
        }
        // Check sequence number
        if(seqInput != NULL) {
            (*corReply)++;
            
            seqLocal++;
            int diff = (seqInput->valueint - seqLocal);
            if ( diff >= 1) {
                *missReply += diff;
            }
            seqLocal = (seqInput->valueint)+1;
        }
    }
    cJSON_Delete(rootObject);
}

/*---Author Cristian Diaz, Pixy Cam functions    -------------------------*/
void PixyGet(int * seqNumber, char buffer[]){
        (*seqNumber)++;
        char tempNum [6];
        sprintf(tempNum, "%d", *seqNumber);
        strcat(buffer, "pixymotor/");
        strcat(buffer, tempNum);
}

int PIXY_PUT_construct_Helper(Pixy2Obj data,  char buffer[], int * seqNumber){ // direction is right or left
    cJSON * rootObject = cJSON_CreateObject();
    cJSON_AddItemToObject(rootObject,"piStart", cJSON_CreateNumber(data.piStart));
    char *temp = cJSON_PrintUnformatted(rootObject);
    cJSON_Delete(rootObject);
    int contentLength = strlen(temp);
    (*seqNumber)++;
    sprintf(buffer, "PUT /pixy2/%d HTTP/1.1\r\nHost: 192.168.0.10:80\r\nContent-type: application/json\r\nContent-length:%d \r\n\r\n", *seqNumber, contentLength);
    strcat(buffer, temp);
    vPortFree(temp);
    int totalSize = strlen(buffer);
    return totalSize;
}





