
#include "main.h"
#include "lcd16x2.h"
static uint8_t ROW[] = {0x00, 0x40, 0x14, 0x54};
void init_I2C1(void)
{
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  
   
	  I2C_InitTypeDef I2C_InitStruct;
    I2C_InitStruct.I2C_ClockSpeed = 100000;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitStruct);
     
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

  
    I2C_Cmd(I2C1, ENABLE);
}
 void LCDI2C_init(void){
	 init_I2C1();
   LCDI2C_command(0x33);
   DelayUs(4500); // wait min 4.1ms

   // second try
   LCDI2C_command(0x33);
   DelayUs(4500); // wait min 4.1ms

   // third go!
   LCDI2C_command(0x33);
   DelayUs(150);
   LCDI2C_command(0x32);
	// set # lines, font size, etc.
	LCDI2C_command (0x08); 
	LCDI2C_command (0x01);
	DelayUs(3000);
	LCDI2C_command (0x06);
	LCDI2C_command(0x0C);
}
 /*send 1 byte to i2c */
void LCDI2C_Sendbyte(uint8_t _data){
	 
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1,ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));	
	
	
	I2C_Send7bitAddress(I2C1, LCD_ADDRESS, I2C_Direction_Transmitter);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	if(flag_save==true)I2C_SendData(I2C1,_data|LCD_NOBACKLIGHT);
	else I2C_SendData(I2C1,_data|LCD_BACKLIGHT);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	
	I2C_GenerateSTOP(I2C1,ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

}
void LCDI2C_pulseEnable(uint8_t _data){
	LCDI2C_Sendbyte(_data | En);	// En high
	DelayUs(1);		// enable pulse must be >450ns

	LCDI2C_Sendbyte(_data & ~En);	// En low
	DelayUs(50);		// commands need > 37us to settle
}

void LCDI2C_send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
  LCDI2C_write4bits((highnib)|mode);
	LCDI2C_write4bits((lownib)|mode);
}

void LCDI2C_write4bits(uint8_t value) {
	LCDI2C_Sendbyte(value);
	LCDI2C_pulseEnable(value);
}

void LCDI2C_command(uint8_t value) {
	LCDI2C_send(value, 0);
}

void LCDI2C_setCursor(uint8_t col, uint8_t row){
 
	LCDI2C_command(SET_DDRAM_ADDR + ROW[row] + col);
}

void LCDI2C_clear(void){
	LCDI2C_command(CLEAR_DISPLAY);// clear display, set cursor position to zero
	DelayUs(3000);  // this command takes a long time!
}
void LCDI2C_write_String(char* str) {
  uint8_t i=0;
  while(str[i])
  {
    LCDI2C_write(str[i]);
    i++;
  }
}
void LCDI2C_write(uint8_t value){
	LCDI2C_send(value, Rs);
}

void LCDI2C_write_Interger(int data){
 
	char buffer[11];
	sprintf(buffer, "%d", data);

	LCDI2C_write_String( buffer);
}

void LCD_Backlight_ON(void){
		flag_save=false;
		LCDI2C_command(0x00);
}
void LCD_Backlight_OFF(void){
		flag_save=true;
		LCDI2C_command(0x00);

}