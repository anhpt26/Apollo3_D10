#ifndef RTOS_H
#define RTOS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "portmacro.h"
#include "portable.h"
#include "timers.h"

#define fsl_malloc(x)         pvPortMalloc(x)
#define fsl_free(x)           vPortFree(x)
#define MS_TO_TICKS(x)        (x / portTICK_PERIOD_MS)

#define MAX_TIMER_COUNT     15
#define INVALID_TIMER_ID    255
typedef enum {
  //NOTE: We use even/odd to differentiate COMPARE0 and COMPARE1
  //Eg: event % 2 == 0  will set COMPARE0
  SYS_TIMER_0_COMPARE0_EVT=0,
  SYS_TIMER_0_COMPARE1_EVT,
  SYS_TIMER_1_COMPARE0_EVT,
  SYS_TIMER_1_COMPARE1_EVT,
  SYS_TIMER_2_COMPARE0_EVT,
  SYS_TIMER_2_COMPARE1_EVT,  
  //TODO: Add more support for remaining timers
  SYS_TIMER_MAX_EVT,  
}sys_timer_evt_t;

typedef void (*sys_timer_cb_t)(void);

int System_Init(void);
int  System_SignalEvt(QueueHandle_t queue_handle, uint8_t event);

//System Timer utilities
uint8_t System_RegisterHWTimer(uint32_t timeout_ms, sys_timer_cb_t isr_cb);
uint8_t System_RegisterHWTimerUs(uint32_t timeout_us, sys_timer_cb_t isr_cb);
void System_UnRegisterHwTimer(uint8_t timer_id);
int System_SetHWTimerTimeout(uint8_t timer_id, uint32_t timeout_ms);
int System_StartHwTimer(uint8_t timer_id);
int System_ResumeHwTimer(uint8_t timer_id);
int System_StopHwTimer(uint8_t timer_id);


#ifdef __cplusplus
}
#endif
#endif  //RTOS_H