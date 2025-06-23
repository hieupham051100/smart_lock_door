#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_flash.h"
#include "stdio.h" 
#include "string.h" 
#include "stdbool.h"
#include "stm32f10x_exti.h"
#include "delay.h"
#include "stm32f10x_tim.h"


/*store up to 225 uid card but i using 100 */

#define MAX_CARDS  100 
#define MAX_LENG_PINNUMBER 10
#define FLASH_PAGE_UID_ADDR 0x800FC00
#define time_to_off_lcd 20000// sau 20s ko lam gi thi tat lcd

extern uint8_t  array_uid_card[MAX_CARDS][5];
extern uint8_t index_uidcard;
extern bool flag_change_data_uid ;
extern char pin_number[MAX_LENG_PINNUMBER];
extern int failed_attempts ;
extern uint8_t UID_MASTER_CARD[5];
extern char mater_pin_number[MAX_LENG_PINNUMBER];
extern bool flag_unlock_door ;
extern bool flag_save ;
extern volatile uint32_t millis_counter;
extern uint32_t last_activity_time;
extern const uint32_t timeout_inactivity;
extern bool mode_dual;
#endif