


#include "stm32f10x.h"

#define En 0x04  // Enable bit
#define Rw 0x02  // Read/Write bit
#define Rs 0x01  // Register select bit

#define CLEAR_DISPLAY 0x01

#define RETURN_HOME     0x02
#define LCD_BACKLIGHT   0x08
#define LCD_NOBACKLIGHT 0x00
#define LCD_ADDRESS     0x4E



#define ENTRY_MODE_SET 0x04
#define OPT_S	0x01					// Shift entire display to right
#define OPT_INC 0x02					// Cursor increment

#define DISPLAY_ON_OFF_CONTROL 0x08
#define OPT_D	0x04					// Turn on display
#define OPT_C	0x02					// Turn on cursor
#define OPT_B 	0x01					// Turn on cursor blink

#define CURSOR_DISPLAY_SHIFT 0x10		// Move and shift cursor
#define OPT_SC 0x08
#define OPT_RL 0x04

#define FUNCTION_SET 0x20
#define OPT_DL 0x10						// Set interface data length
#define OPT_N 0x08						// Set number of display lines
#define OPT_F 0x04						// Set alternate font
#define SETCGRAM_ADDR 0x040
#define SET_DDRAM_ADDR 0x80				// Set DDRAM address





void init_I2C1(void);
void LCDI2C_init(void);

void LCDI2C_Sendbyte(uint8_t _data);
void LCDI2C_pulseEnable(uint8_t _data);
void LCDI2C_write4bits(uint8_t value);
void LCDI2C_send(uint8_t value, uint8_t mode);

void LCDI2C_command(uint8_t value);
void LCDI2C_setCursor(uint8_t col, uint8_t row);
void LCDI2C_clear(void);
void LCDI2C_write_String(char* str);
void LCDI2C_write(uint8_t value);
void LCDI2C_write_Interger(int data);
void LCD_Backlight_ON(void);
void LCD_Backlight_OFF(void);