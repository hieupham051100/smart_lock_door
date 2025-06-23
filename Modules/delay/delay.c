
#include "delay.h"
#include "main.h"
#include "lcd16x2.h"
 

void TIM2_CONFIG(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=0xFFFF;
	TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
/*	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStruct;
		
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct); 
*/	 
	TIM_Cmd(TIM2, ENABLE);
	sysTickInit();
}
void DelayUs(uint32_t t){
	TIM2->CNT=0;
	while (TIM2->CNT < t){
	}
}
 
void DelayMs(uint32_t t){
	while(t){
	t--;
	DelayUs(1000);
	}
} 
void DelayMin(uint32_t min){
	while(min){
	DelayMs(1000*60);
	min--;
	}
	
}
void sysTickInit(void) {
  SysTick_Config(SystemCoreClock/1000);
}
void SysTick_Handler(void) {
    millis_counter++;
static uint32_t prev_check = 0;
    if (millis_counter - prev_check >= 1000) {
        prev_check = millis_counter;
        check_active_time();
    }
}
uint32_t  millis(void){
		return millis_counter;
}
void check_active_time(void){
	uint32_t time;
	time=millis();
	if(time-last_activity_time>time_to_off_lcd)LCD_Backlight_OFF();
	else LCD_Backlight_ON();
}

