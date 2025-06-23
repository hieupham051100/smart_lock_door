
#include "main.h"
#include "menu.h"
#include "lcd16x2.h"
#include "matrix.h"
#include "mfrc522.h"
static void show_fail_update_pin(void);
 
void draw_slide(uint16_t slide){
    if (current_line >= current_menu_length) current_line = 1;

    for (int i = 0; i < 2; i++) {
        LCDI2C_setCursor(i, 0);
        uint8_t index = slide + i;
        if (index >= current_menu_length) break;

        if (index == current_line && current_menu!=Menu_lock_door)
            LCDI2C_write_String(">");
        else
            LCDI2C_write_String(" ");

        LCDI2C_write_String(current_menu[index].title);
    }
}

 uint8_t get_menu_length(MenuItem* menu) {
    uint8_t count = 0;
    while (menu[count].title != NULL) {
        count++;
    }
    return count;
}

void main_loop(void){
				if (current_menu == Menu_lock_door && !flag_save) {
						close_the_door();
					  go_to_menu_lock();
						action_menu_lock();
        }
				if (millis() - last_activity_time > timeout_inactivity) {
        go_to_menu_lock();  // Quay v? Menu_lock_door
				}

				 if (POINT_POSITION == 0) {
            draw_slide(current_line);
        } else {
            draw_slide(current_line - 1);
        }
				
			   if (BUTTON_DOWN_flag) {
            current_line++;
            if (current_line == current_menu_length) current_line = current_menu_length-1;
            BUTTON_DOWN_flag = false;
            POINT_POSITION = 1;
            LCDI2C_clear();
        }
				 if (BUTTON_UP_flag) {
					  current_line--;
						if(current_line<=1){
						current_line=1;
						POINT_POSITION = 1;
						}
						else POINT_POSITION = 0;
            BUTTON_UP_flag = false;
            LCDI2C_clear();
        }
				
        if (BUTTON_SELECT_flag) {
            MenuItem* item = &current_menu[current_line];
						
            if (item->submenu != NULL) {
								stack_menu[menu_stack_index++]=current_menu;
                current_menu = item->submenu;
                current_menu_length = item->submenu_length;
            }
            else if (strcmp(item->title, "BACK") == 0) {
							
							if(menu_stack_index>0){
                current_menu = stack_menu[--menu_stack_index];
                current_menu_length=get_menu_length(current_menu) ; 
							}	
            }
							else if (strcmp(item->title, "DONE") == 0){
							  go_to_menu_lock();
							}
            else if (item->action != NULL) {
                item->action();
            }   
								current_line = 1;
							  POINT_POSITION = 1;
								BUTTON_SELECT_flag = false;
								LCDI2C_clear();
							  //draw_slide(current_line);
        }
    }

 

/*********************      action_menu_lock    *****/		
void go_to_menu_lock(void) {
    LCDI2C_clear();
    current_line = 1;
    POINT_POSITION = 1;
    current_menu = Menu_lock_door;
    draw_slide(current_line);  // Hi?n th? l?i menu
    flag_save = true; // Ngan h? th?ng t? d?ng g?i l?i ngay sau dó
}
void action_menu_lock(void){

		 bool result = check_pin_card(pin_number, 
                                     mode_dual ? "PIN & CARD" : "PIN or CARD",
                                     array_uid_card,
                                     index_uidcard);
			flag_save = true; 

        if (result) {
            flag_unlock_door = true;
            open_the_door();
            LCDI2C_clear();
            LCDI2C_setCursor(0, 0);
            LCDI2C_write_String("DOOR IS OPEN");
            DelayMs(1000);
					  LCDI2C_clear();
            current_line = 1;
            POINT_POSITION = 1;
					  current_menu=Menu_un_lock_door;
						
        } else {
            LCDI2C_clear();
            LCDI2C_setCursor(0, 0);
            LCDI2C_write_String("TRY AGAIN AFTER 5MIN");
            DelayMin(5);
        }
	 
	 
}
bool check_pin_card(const char* expect_pin, const char*message,uint8_t expect_uid_list[][5], int num_uids){
	bool check_pin  =false;
	bool check_card = false;
  char string_math_symbol[MAX_LENG_PINNUMBER+1];                 // buffer nh?p vào (4 ký t? + '\0')
	uint8_t uid[5];
	failed_attempts=0;                             
  char c;
  int cursor_index;
	int real_pin_length = strlen(expect_pin); 
   do {
		if(failed_attempts>2) return false;
    LCDI2C_clear();
		LCDI2C_setCursor(0, 0);
		if(failed_attempts==0){
	  LCDI2C_write_String(message);
		}
		else {
    LCDI2C_write_String("Try again");
		}
    LCDI2C_setCursor(1, 0);
    LCDI2C_write_String(">");
		cursor_index = 0;
		
    // Nh?p ký t?
		 
    const uint32_t timeout_ms = 10000;  // Thoát neu không có the sau 10s

    while (cursor_index < real_pin_length &&
			millis() - last_activity_time  < timeout_ms){ 
     
			    
         c = getkey();
         if (c >= '0' && c <= '9') {
             string_math_symbol[cursor_index++] = c;
             LCDI2C_setCursor(1, cursor_index);
             LCDI2C_write(c);
         }

         // ? Ki?m tra th? t? trong khi nh?p PIN
         if (TM_MFRC522_Check(uid) == MI_OK) {
					 if (expect_uid_list != NULL){
					 for(int i=0;i<num_uids;i++){
					      if (is_uid_same(uid,expect_uid_list[i])) {
							  check_card=true;
								if(mode_dual==false)return true;
								break;
             }
					 }
				 }
         }
         
     }
  
    string_math_symbol[real_pin_length] = '\0';   
		if (strcmp(string_math_symbol, expect_pin) == 0){
			  check_pin=true;
			
				if(mode_dual==false)return true;
		}
		if(check_card && check_pin && mode_dual){
			return true;
		}
    failed_attempts++;
		LCDI2C_clear();
    LCDI2C_setCursor(0, 0);
    LCDI2C_write_String("Wrong input");
    DelayMs(50);
   
} while (1);  // l?p l?i n?u nh?p sai
	
}
void open_the_door(void){
		
}
void close_the_door(void){
		
}

/************************action_menu_unlock***********************************/
bool check_master(void){
	    bool prev_mode = mode_dual;
	    mode_dual = false;  
		  bool result = check_pin_card(mater_pin_number,"MASTER CHECK",array_uid_card,
                                     1);
                                   
      mode_dual = prev_mode;  
			return result;
}

void action_menu_unlock(void){
			if(!check_master()){
			go_to_menu_lock();
			}
			else {
			current_menu=Menu_settings;
			current_line=1;
			current_menu_length=5;
			POINT_POSITION = 1;
			}
}
/***********************     action_enter_new_pin    ********/	

void action_enter_new_pin(void){
	/*
`	1. check master pin right -> enter new pin 
  2. 	
	*/
	/* enter new pin number of pin must be >=4 and <=10*/
	char tmp[MAX_LENG_PINNUMBER + 1];
  strcpy(tmp, pin_number);
 
	if(confirm_new_pin()==false){
	strcpy(pin_number,tmp);
	show_fail_update_pin();
	return;
	}
	LCDI2C_clear();
	LCDI2C_setCursor(0, 0);
	LCDI2C_write_String("PIN updated");
	DelayMs(1000);
	LCDI2C_clear();
	
}
static void show_fail_update_pin(void) {
    LCDI2C_clear();
    LCDI2C_setCursor(0, 0);
    LCDI2C_write_String("PIN update fail");
    DelayMs(1000);
    LCDI2C_clear();
}
bool enter_new_pin(void) {
	  char buffer[MAX_LENG_PINNUMBER + 1];
    int cursor_index;
    char c;
		failed_attempts=0;
 
    do {
		if(failed_attempts>2) return false;
    LCDI2C_clear();
		LCDI2C_setCursor(0, 0);
		if(failed_attempts==0){
	  LCDI2C_write_String("enter new pin");
		}
		else {
    LCDI2C_write_String("Try again");
		}
    LCDI2C_setCursor(1, 0);
    LCDI2C_write_String(">");
		cursor_index = 0;
		 
    const uint32_t timeout_ms = 10000;  // Thoát neu không có the sau 10s

   while (cursor_index < MAX_LENG_PINNUMBER && 
				 millis() - last_activity_time  < timeout_ms) {
         c = getkey();
         if (c >= '0' && c <= '9') {
             buffer[cursor_index++] = c;
             LCDI2C_setCursor(1, cursor_index);
             LCDI2C_write(c);
         }
				 else if (c=='C') break;
 
         DelayMs(10);
     }
  
    buffer[cursor_index] = '\0';   
   if(cursor_index>=4 && cursor_index <=MAX_LENG_PINNUMBER) {
		 strcpy(pin_number, buffer);
	   return true;
	 }
   else{
	 failed_attempts++;
	 LCDI2C_clear();
   LCDI2C_setCursor(0, 0);
   LCDI2C_write_String("PIN must be 4-10");
   DelayMs(1000);
	 } 
} while (1);  // l?p l?i n?u nh?p sai
}
bool confirm_new_pin(void){
	  bool prev_mode = mode_dual;
	  mode_dual = false; 
		bool result = check_pin_card(pin_number,"CONFIRM NEWPIN", NULL,0);                            
		mode_dual = prev_mode;  
		return result;
		
}





 /********************    action_Add_card    *****/	
 
void action_Add_card(void){
	  uint8_t CardID[5];
		LCDI2C_clear();
		LCDI2C_setCursor(0, 0);
		LCDI2C_write_String("ADD newcard");
    const uint32_t timeout_ms = 10000;  // Thoát neu không có the sau 10s
    while (millis() - last_activity_time < timeout_ms) {
				
        if (TM_MFRC522_Check(CardID) == MI_OK) {
            if (is_uid_exit(CardID)) {
                // N?u th? dã t?n t?i thì thoát
                LCDI2C_clear();
                LCDI2C_setCursor(0, 0);
                LCDI2C_write_String("Card existed");
                DelayMs(1000);
                return;
            } else {
                add_new_uid_card(CardID);
                LCDI2C_clear();
                LCDI2C_setCursor(0, 0);
                LCDI2C_write_String("Card is added");
                DelayMs(1000);
                return;
            }
        }
        DelayMs(50);  
    }

    LCDI2C_clear();
    LCDI2C_setCursor(0, 0);
    LCDI2C_write_String("No card found");
    DelayMs(1000);
}
 
/********************    action_Delete_card    *****/	
void action_Delete_card(void){
		uint8_t CardID[5];
		LCDI2C_clear();
		LCDI2C_setCursor(0, 0);
		LCDI2C_write_String("DELETE card");
	 
    const uint32_t timeout_ms = 10000;  // Thoát neu không có the sau 10s
    while (millis() - last_activity_time  < timeout_ms) {
			   
        if (TM_MFRC522_Check(CardID) == MI_OK) {
            if (!is_uid_exit(CardID)) {
                // N?u th? dã t?n t?i thì thoát
                LCDI2C_clear();
                LCDI2C_setCursor(0, 0);
                LCDI2C_write_String("Card not found");
                DelayMs(1000);
                return;
            } else {
                delete_uid_card(CardID);
                LCDI2C_clear();
                LCDI2C_setCursor(0, 0);
                LCDI2C_write_String("Card is deleted");
                DelayMs(1000);
                return;
            }
        }
        DelayMs(50);  
    }

    LCDI2C_clear();
    LCDI2C_setCursor(0, 0);
    LCDI2C_write_String("No card found");
    DelayMs(1000);

}
 
/*******************action_enable_dual_mode*****/
void action_enable_dual_mode(void  ){
	  mode_dual=true;
  	LCDI2C_clear();
	  LCDI2C_setCursor(0,0);
	  LCDI2C_write_String("DUALMODE IS SET");
	  LCDI2C_setCursor(1,0);
	  LCDI2C_write_String("PIN AND CARD ");
    DelayMs(1000);	
}
void action_disable_dual_mode(void  ){
		mode_dual=false;
  	LCDI2C_clear();
	  LCDI2C_setCursor(0,0);
	  LCDI2C_write_String("DUALMODE IS UNSET");
	  LCDI2C_setCursor(1,0);
	  LCDI2C_write_String("PIN OR CARD ");
    DelayMs(1000);	
}
void action_reset_system(void ){
    
	  LCDI2C_clear();
	  LCDI2C_setCursor(0,0);
	  LCDI2C_write_String("ARE U SURE ");
	  LCDI2C_setCursor(1,0);
	  LCDI2C_write_String("TYPE C TO RESET");
 
    const uint32_t timeout_ms = 10000;  // Thoát neu không làm j sau 10s
    while (millis() - last_activity_time  < timeout_ms) {
		char c=getkey();
		if(c=='C'){
		   strcpy(mater_pin_number, "0000");
		   
       // Reset user PIN
       strcpy(pin_number, "0000");
		   
       // Xoá t?t c? UID
       for (int i = 0; i < index_uidcard; i++) {
           for (int j = 0; j < 5; j++) {
               array_uid_card[i][j] = 0;
           }
       }
       index_uidcard = 0;
		   
       // Thông báo
       LCDI2C_clear();
       LCDI2C_setCursor(0, 0);
       LCDI2C_write_String("RESET DONE");
       LCDI2C_setCursor(1, 0);
       LCDI2C_write_String("PIN:0000 M:0000");
       DelayMs(1500);
		      
       // Quay v? menu chính
       go_to_menu_lock();
			 return;
		 }
		  DelayMs(10);
		}
		LCDI2C_clear();
    LCDI2C_setCursor(0, 0);
    LCDI2C_write_String("RESET FAIL");
    DelayMs(1000);
    LCDI2C_clear();
}