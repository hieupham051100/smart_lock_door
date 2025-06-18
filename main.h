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
/*store up to 225 uid card but i using 100 */

#define MAX_CARDS  100 
#define FLASH_PAGE_UID_ADDR 0x800FC00
  
#endif