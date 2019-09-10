/* 
 * File:   game_state.h
 * Author: xuanli
 *
 * Created on April 25, 2019, 8:12 PM
 */

#ifndef GAME_STATE_H
#define	GAME_STATE_H

#include "game_queue.h"
#include "wifi_queue.h"
#include "QueueType.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum { Init, Walk, WalkWait, sonarWait, pixyWait, armWait, armSecWait } GameState;

void GameStateMachine(GameState *curState, GameQueType *msg);

#ifdef	__cplusplus
}
#endif

#endif	/* GAME_STATE_H */

