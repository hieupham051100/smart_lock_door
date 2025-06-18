#ifndef __FLASH_DATA_H
#define __FLASH_DATA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include "main.h"
 #define MY_FLASH_PAGE_ADDR 0x800FC00

 
#define SETTINGS_WORDS sizeof(settings)/4
 
void FLASH_ReadSettings(void);
void FLASH_WriteSettings(void);
void FLASH_Init(void);
void WriteUIDListToFlash(void);


#ifdef __cplusplus
}
#endif

#endif /*__FLASH_DATA_H*/

