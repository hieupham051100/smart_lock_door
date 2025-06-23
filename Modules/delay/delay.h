
#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

 
void TIM2_CONFIG(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);
uint32_t  millis(void);
void sysTickInit(void);
void check_active_time(void);
void DelayMin(uint32_t min);
#ifdef __cplusplus
}
#endif

#endif

