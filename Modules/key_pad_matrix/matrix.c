
#include "matrix.h"
#include "main.h" 
char matrix_array[] = {
    '7', '8', '9', '/',
    '4', '5', '6', '*',
    '1', '2', '3', '-',
    'C', '0', '=', '+'
};

#define BT  2
/*
1. keo 4 chan hang ngang xuong muoc thap: mode input pulldown 
2. keo lan luot 4 cot hang doc len muc cao sau do doc lan luot 4 chan hang ngang 

*/
#if(BT==1)
void MATRIX_CONFIG(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_MATRIX_InitStruct;
	GPIO_MATRIX_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_MATRIX_InitStruct.GPIO_Pin=MATRIX_PIN_A|MATRIX_PIN_B|MATRIX_PIN_C|MATRIX_PIN_D;
	GPIO_MATRIX_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(MATRIX_PORT,&GPIO_MATRIX_InitStruct);
	
	
	GPIO_MATRIX_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_MATRIX_InitStruct.GPIO_Pin=MATRIX_PIN_1|MATRIX_PIN_2|MATRIX_PIN_3|MATRIX_PIN_4;
	GPIO_MATRIX_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(MATRIX_PORT,&GPIO_MATRIX_InitStruct);
	

}
uint8_t read_row_matrix(uint16_t pin){
			GPIO_ResetBits(MATRIX_PORT,pin);
	  DelayMs(2);
		if(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_A)==0){
		 
		while(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_A)==0){}
		return 1;
		
		} 
		else if(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_B)==0){
		 
		while(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_B)==0){}
		return 2;
		
		} 
		else if(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_C)==0){
		 
		while(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_C)==0){}
		return 3;
		
		} 
		else if(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_D)==0){
	 
		while(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_D)==0){}
		return 4;
		
		} 
		GPIO_SetBits(MATRIX_PORT, pin);
	return 0;
}
uint8_t read_matrix(){
	uint8_t a,b,c,d;
	
	a= read_row_matrix(MATRIX_PIN_1);
	b= read_row_matrix(MATRIX_PIN_2);
	c= read_row_matrix(MATRIX_PIN_3);
	d= read_row_matrix(MATRIX_PIN_4);
	if(a!=0) {
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_1 );
	return a;
	}
	else if(b!=0) {
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_2 );
	return b+4;
	} 
	else if(c!=0){
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_3 );
	return c+8;
	} 
	else if(d!=0){
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_4 );
	return d+8;
	}  
 
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_4|MATRIX_PIN_3|MATRIX_PIN_2|MATRIX_PIN_1);
	return 0;

}
void scan_matrix(){
	uint8_t i=read_matrix();
	//char c = matrix_array[i];
	//if(c!='0')Lcd_string(&c);
	if(i!=0) {
	//Lcd_clear();
	Lcd_int(i);
	DelayMs(10);
	}
	
	
	
}
#endif
#if(BT==2)

 
/*
1. keo 4 chan hang ngang xuong muoc thap: mode input pulldown 
2. keo lan luot 4 cot hang doc len muc cao sau do doc lan luot 4 chan hang ngang 

*/

void MATRIX_CONFIG(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_MATRIX_InitStruct;
	GPIO_MATRIX_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_MATRIX_InitStruct.GPIO_Pin=MATRIX_PIN_1|MATRIX_PIN_2|MATRIX_PIN_3|MATRIX_PIN_4;
	GPIO_MATRIX_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(MATRIX_PORT,&GPIO_MATRIX_InitStruct);
	
	
	GPIO_MATRIX_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_MATRIX_InitStruct.GPIO_Pin=MATRIX_PIN_A|MATRIX_PIN_B|MATRIX_PIN_C|MATRIX_PIN_D;
	GPIO_MATRIX_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(MATRIX_PORT,&GPIO_MATRIX_InitStruct);
	

}
uint8_t read_row_matrix(uint16_t pin){
			GPIO_ResetBits(MATRIX_PORT,pin);
	  DelayMs(2);
		if(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_1)==0){
		 
		while(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_1)==0){}
		return 1;
		
		} 
		else if(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_2)==0){
		 
		while(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_2)==0){}
		return 2;
		
		} 
		else if(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_3)==0){
		 
		while(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_3)==0){}
		return 3;
		
		} 
		else if(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_4)==0){
	 
		while(GPIO_ReadInputDataBit(MATRIX_PORT,MATRIX_PIN_4)==0){}
		return 4;
		
		} 
		GPIO_SetBits(MATRIX_PORT, pin);
	return 0;
}
uint8_t read_matrix(){
	uint8_t a,b,c,d;
	
	a= read_row_matrix(MATRIX_PIN_A);
	b= read_row_matrix(MATRIX_PIN_B);
	c= read_row_matrix(MATRIX_PIN_C);
	d= read_row_matrix(MATRIX_PIN_D);
	if(a!=0) {
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_A );
	return a;
	}
	else if(b!=0) {
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_B );
	return b+4;
	} 
	else if(c!=0){
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_C );
	return c+8;
	} 
	else if(d!=0){
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_D );
	return d+12;
	}  
 
	GPIO_SetBits(MATRIX_PORT,MATRIX_PIN_A|MATRIX_PIN_B|MATRIX_PIN_C|MATRIX_PIN_D);
	return 0;

}
void scan_matrix(){
	uint8_t i=read_matrix();
	//char c = matrix_array[i];
	//if(c!='0')Lcd_string(&c);
	if(i!=0) {
	//Lcd_clear();
	LCDI2C_write_Interger(i);
	DelayMs(10);
	}
}
char getkey(){
	uint8_t i=read_matrix();
	if(i!=0){
	last_activity_time=millis();
	flag_save = false;
  LCD_Backlight_ON();
	return matrix_array[i-1];
	}
	else return 0;
}
#endif
