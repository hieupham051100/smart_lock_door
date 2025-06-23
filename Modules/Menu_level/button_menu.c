#include "button_menu.h"
#include "main.h"

bool BUTTON_UP_flag			=false;
bool BUTTON_DOWN_flag		=false;
bool BUTTON_SELECT_flag	=false;
uint8_t POINT_POSITION 	=1; /*position cua currenline*/
void GPIO_BUTTON_CONFIG(void){

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

 
	GPIO_InitTypeDef        GPIO_BUTTON_InitStruction;
	GPIO_BUTTON_InitStruction.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_BUTTON_InitStruction.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10;
	GPIO_BUTTON_InitStruction.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_BUTTON_InitStruction);
	
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line=EXTI_Line1|EXTI_Line0|EXTI_Line10;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0|GPIO_PinSource1|GPIO_PinSource10);
	
	
	NVIC_InitTypeDef  NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn|EXTI1_IRQn|EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	
	NVIC_Init(&NVIC_InitStruct);
}

 
void EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1)==1){
	BUTTON_DOWN_flag=true;
	last_activity_time=millis();
	EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)==1){
	BUTTON_UP_flag=true;
	last_activity_time=millis();
	EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
void EXTI15_10_IRQnHandler(void){
	if(EXTI_GetITStatus(EXTI_Line10)==1){
	BUTTON_SELECT_flag=true;
	last_activity_time=millis();
	EXTI_ClearITPendingBit(EXTI_Line10);	
}
}
void button_up(void){
	

}
void button_down(void);
void button_select(void);
