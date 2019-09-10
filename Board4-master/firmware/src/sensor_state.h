/* 
 * File:   sensor_state.h
 * Author: Team 10
 *
 * Created on February 3, 2019, 2:20 PM
 */

#ifndef SENSOR_STATE_H
#define	SENSOR_STATE_H
#include <FreeRtos.h>
#include <queue.h>
#include "debug.h"
#include "sensor_queue.h"
#include "QueueType.h"
#include "wifi_queue.h"

#define CUMULATIVE_TOTAL_VALUE_INIT      0
#define NUM_OF_STATES                    5
#define STATE_INCREMENT                  1
#define DISTANCE_NEED_TO_TURN            7
#define NUMBER_OF_DISTANCE_DATA          10
#define SONAR_NAME                       2

#define MOTOR_TURN_LEFT                  1
#define MOTOR_MOVE_FORWARD               0

typedef enum {state1, state2, state3, state4, state5} stateStatus;
void sensorStateMachine(stateStatus *currentState, int *totalValue,  sensorMessageType inputValue, int * average);
void StateMachineHelper(int * curTotalValue , stateStatus * curState, sensorMessageType inputValue, int * avg);

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_STATE_H */