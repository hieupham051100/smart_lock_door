#ifndef __MATRIX_4X4_H
#define __MATRIX_4X4_H

#include "stm32f10x.h"
#define MATRIX_PORT   GPIOA
#define MATRIX_PIN_A  GPIO_Pin_8
#define MATRIX_PIN_B  GPIO_Pin_9
#define MATRIX_PIN_C  GPIO_Pin_10
#define MATRIX_PIN_D  GPIO_Pin_11


#define MATRIX_PIN_1  GPIO_Pin_12
#define MATRIX_PIN_2  GPIO_Pin_13
#define MATRIX_PIN_3  GPIO_Pin_14
#define MATRIX_PIN_4  GPIO_Pin_15

extern char matrix_array[16]; 

void MATRIX_CONFIG(void);
uint8_t read_matrix(void);
uint8_t read_row_matrix(uint16_t pin);
 
void scan_matrix(void);
char getkey(void);
#endif /*__MATRIX_4X4_H */