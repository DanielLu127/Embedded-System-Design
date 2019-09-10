/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _UART_TIMER_H    /* Guard against multiple inclusion */
#define _UART_TIMER_H

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "FreeRTOS.h"
#include "timers.h"

#define STAT_TIMER 1000
    
    TimerHandle_t statistic_handle;
    
    void Stat_Timer_Init(void);
    void Stat_CallBack(TimerHandle_t xTimer);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _UART_TIMER_H */

/* *****************************************************************************
 End of File
 */
