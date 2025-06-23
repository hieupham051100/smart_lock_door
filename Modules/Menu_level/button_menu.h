#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "stm32f10x.h"
#include "stdbool.h"

#define BUTTON_PORT       GPIOB
#define BUTTON_UP         GPIO_Pin_0
#define BUTTON_DOWN       GPIO_Pin_1
#define BUTTON_SELECT     GPIO_Pin_10


void GPIO_BUTTON_CONFIG (void);
extern bool BUTTON_UP_flag			;
extern bool BUTTON_DOWN_flag		;
extern bool BUTTON_SELECT_flag	;
extern uint8_t POINT_POSITION 	;/*position cua currenline*/
void button_up(void);
void button_down(void);
void button_select(void);
#endif /*_BUTTON_H_*/