 
#include "main.h"
#include "stm32f10x.h"
#include "mfrc522.h"
#include <stdio.h>
#include "delay.h"
#include "stdbool.h"
#include "string.h"
#include "flash_data.h"


void My_GPIO_Init(void);


static bool flag_change_data_uid = false;
 uint8_t index_uidcard=0;
uint8_t  array_uid_card[MAX_CARDS][5];
uint8_t CardID[5];
char szBuff[100];
const master_card[5];


bool is_uid_exit(uint8_t array_uid_card[MAX_CARDS][5],uint8_t CardID[5]){
	for(uint8_t i=0;i<index_uidcard;i++){
		  bool matched = true;
        for (uint8_t j = 0; j < 5; j++) {
            if (array_uid_card[i][j] != CardID[j]) {
                matched = false;
                break;
            }
					}
				if(matched==true) return true;
}
	return false ;
}

void add_new_uid_card(uint8_t array_uid_card[MAX_CARDS][5],uint8_t CardID[5]){
		for (uint8_t j = 0; j < 5; j++) {
			array_uid_card[index_uidcard][j] = CardID[j];
	  }
		index_uidcard++;
		flag_change_data_uid= true;

}

/* xoa va day cac gia tri tiep theo len */
void delete_uid_card(uint8_t array_uid_card[MAX_CARDS][5],uint8_t CardID[5]){
		uint8_t i;
		 for(i=0;i<index_uidcard;i++){
		  bool matched = true;
        for (uint8_t j = 0; j < 5; j++) {
            if (array_uid_card[i][j] != CardID[j]) {
                matched = false;
                break;
            }
					}
			if(matched==true) {
			for(uint8_t k=i;k<index_uidcard;k++){
				 for (uint8_t j = 0; j < 5; j++) {
             array_uid_card[k][j] = array_uid_card[k+1][j];
				 }
			}
			for (uint8_t j = 0; j < 5; j++) {
             array_uid_card[index_uidcard-1][j] = 0xFF;
				 }
			index_uidcard--;
			flag_change_data_uid =true;
			break;
			}

}
}
typedef	struct
  {
		
	uint8_t Parameter[5];		// 5  byte uid
		
  } tpSettings;
 
tpSettings settings;// tao  struct 5byte   khi luu chi can settings++

void FLASH_Init(void){
	/* Next commands may be used in SysClock initialization function
	   In this case using of FLASH_Init is not obligatorily */
	/* Enable Prefetch Buffer */
	FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable);
	/* Flash 2 wait state */
	FLASH_SetLatency( FLASH_Latency_2);
}


 
void FLASH_ReadSettings(void){
	uint8_t *flash_ptr = (uint8_t *)MY_FLASH_PAGE_ADDR;
		for (uint8_t i = 0; i < sizeof(settings); i++) {
			((uint8_t *)&settings)[i] = flash_ptr[i];
		}

}
void FLASH_WriteSettings(void){
		uint8_t *data=(uint8_t*)&settings;
	  uint32_t padded_len =((sizeof(settings) + 3) / 4) * 4; 
	
		FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		FLASH_ErasePage(MY_FLASH_PAGE_ADDR);
		for (uint32_t i = 0; i < padded_len; i += 4) {
		uint32_t word = 0xFFFFFFFF; // default padding
		for (uint8_t j = 0; j < 4; j++) {
			if ((i + j) < sizeof(settings)) {
				((uint8_t *)&word)[j] = data[i + j];
			}
		}
		FLASH_ProgramWord(MY_FLASH_PAGE_ADDR + i, word);
	}

	FLASH_Lock();
}
void My_GPIO_Init(void) {
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioInit.GPIO_Mode=GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC, &gpioInit);
}
int main() {
	TIM2_CONFIG(); 
	My_GPIO_Init();
	TM_MFRC522_Init();
	FLASH_Init();
//	tpSettings arr_settings[index_uidcard];
//	for(uint8_t	i=0;i<index_uidcard;i++){
//		arr_settings[i].Parameter[0]  = array_uid_card[i][0];
//		arr_settings[i].Parameter[1]  = array_uid_card[i][1];
//		arr_settings[i].Parameter[2]  = array_uid_card[i][2];
//		arr_settings[i].Parameter[3]  = array_uid_card[i][3];
//		arr_settings[i].Parameter[4]  = array_uid_card[i][4];
//	}
//	
//	FLASH_WriteSettings(); // Ghi vào Flash
//
//	// Reset vùng RAM d? ki?m tra d?c
//	for (int i = 0; i < 5; i++) settings.Parameter[i] = 0;
//
//	FLASH_ReadSettings(); // Ð?c t? Flash

 while(1) {
	 
 if (TM_MFRC522_Check(CardID) == MI_OK) {
	
 	if(is_uid_exit(array_uid_card,CardID)==true){
 		 
	 GPIO_SetBits(GPIOC, GPIO_Pin_13);
 		DelayMs(2000);
 	 GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		
 	}
 	else  {
 		add_new_uid_card(array_uid_card,CardID); 
 	}
 	}
 	
 }
	
	
}



