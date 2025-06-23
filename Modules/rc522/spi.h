#include "stm32f10x.h"
 

#ifndef KT_SPI_H_
#define KT_SPI_H_

void TM_SPI_Init(void);

uint8_t TM_SPI_Send(uint8_t data);

extern void TM_MFRC522_InitPins(void);

#define MFRC522_CS_LOW					GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define MFRC522_CS_HIGH					GPIO_SetBits(GPIOA, GPIO_Pin_4)

#endif
