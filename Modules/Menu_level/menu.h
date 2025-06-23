#ifndef __MENU_H
#define __MENU_H


#include "stm32f10x.h"
#include "button_menu.h"
#include "stdio.h" 
 /*
M?t bi?n MenuState current_menu;

M?t hàm display_menu(current_menu);

M?t hàm handle_button(current_menu, button_pressed);

M?t bi?n MenuState previous_menu; d? quay l?i khi MENU_BACK.
 */



#define MAX_LEVEL_MENU 10
typedef struct MenuItem {                                  
    char *title;
    struct MenuItem* submenu;
	  void (*action) ();
	  uint8_t submenu_length;
} MenuItem;
void go_to_menu_lock(void);
void action_menu_lock(void);
void action_menu_unlock(void);
void action_enter_new_pin(void);
void enter_pin(char* buffer, const char* message);

void action_Add_card(void );
void action_Delete_card(void  );
void action_enable_dual_mode(void  );
void action_disable_dual_mode(void  );
void action_reset_system(void  );
void draw_slide(uint16_t slide);


bool check_pin_card(const char* expect_pin, const char*message,uint8_t expect_uid_list[][5], int num_uids);
void open_the_door(void);
void close_the_door(void);

bool check_master(void);
bool enter_new_pin(void);
bool confirm_new_pin(void); 



uint8_t get_menu_length(MenuItem* menu);

/* KHAI BAO CAC MENU CAN SU DUNG */
MenuItem Menu_lock_door[],
         Menu_un_lock_door[],
         Menu_settings[],
         Menu_change_pin[],
				 Menu_enter_new_pin[],
         Menu_Manage_cards[],
         Menu_Add_card[],
         Menu_Delete_card[],
         Menu_More_settings[],
         Menu_Dual_auth[],
				 Menu_Dual_EN_DIS[],
         Menu_Reset[];
         
MenuItem* current_menu=Menu_lock_door;
/*bien dieu huong nhieu cap */
MenuItem* stack_menu[MAX_LEVEL_MENU];
uint8_t  menu_stack_index=0;

uint8_t  Menu_lock_door_length = 2;
uint8_t  current_menu_length = 2;
/* MO TA CHI TIET CAC BIEN CUA MENU CHUA CAI GI */
/*QUY UOC CURENTLINE=1 , VI CURENT LINE CHUA TITLIE */

uint8_t current_line=1;
/*flag door is lock = true */ 

MenuItem Menu_lock_door[]={
	{"  DOOR IS LOCK  ",NULL , NULL  , 0},
	
	{"ENTER PASSWORD OR CARD ",NULL,NULL,0},
};

MenuItem Menu_un_lock_door[]={
	{" DOOR IS OPEN  ",NULL,NULL,0},
	
	{"ENTER MENU SETTING",NULL,action_menu_unlock,0},
	{"DONE",NULL,NULL,0},
};
MenuItem Menu_settings[]={
	{"  MENU SETTING  ",NULL,NULL,0},
	
	{"ENTER CHANGE PIN ",Menu_change_pin,NULL,4},
	{"ENTER MANAGE CARDS ",Menu_Manage_cards,NULL,5},
	{"ENTER MORE SETTING",Menu_More_settings,NULL,5},
	{"DONE",NULL,NULL,0},
};
 
MenuItem Menu_change_pin[]={
	{" MENU CHANGE PIN  ",NULL,NULL,0},
	
	{"  CHANGE PIN   ",Menu_enter_new_pin,NULL,4},
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
}; 


MenuItem Menu_enter_new_pin[] = {
	{" MENU CHANGE PIN  ",NULL,NULL,0},
	
  { "Enter new PIN", NULL, action_enter_new_pin, 0 },
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
};


MenuItem Menu_Manage_cards[]={
	{"  MANAGE CARDS   ",NULL,NULL,0},
	
	{"ENTER ADD CADRS   ",Menu_Add_card,NULL,4},
	{"ENTER DELETE CADRS ",Menu_Delete_card,NULL,4},
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
};

MenuItem Menu_Add_card[]={
	{" MENU ADD CADRS  ",NULL,NULL,0},
	
	{"  ADD CADRS  ",NULL,action_Add_card,0},
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
};

MenuItem Menu_Delete_card[]={
	{" MENU DELETE CADRS  ",NULL,NULL,0},

  {"  DELETE CADRS  ",NULL,action_Delete_card,0},
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
}; 

MenuItem Menu_More_settings[]={
	{" MENU MORE SETTING ",NULL,NULL,0},
	
	{"ENTER DUAL AUTH ",Menu_Dual_auth,NULL,4},
	{"ENTER RESET SYSTEM ",Menu_Reset,NULL,4},
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
};

MenuItem Menu_Dual_auth[]={
	{" MENU  DUAL AUTH   ",NULL,NULL,0},
	
	{" DUAL AUTH   ",Menu_Dual_EN_DIS,NULL,5},
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
};

MenuItem Menu_Dual_EN_DIS[]={
	{" MENU DUAL AUTH   ",NULL,NULL,0},
	
	{" ENABLE ",NULL, action_enable_dual_mode,0},
	{" DISABLE ",NULL,action_disable_dual_mode,0},
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
};
MenuItem Menu_Reset[]={
	{" MENU RESET SYSTEM ",NULL,NULL,0},
	{"  RESET SYSTEM ",NULL,action_reset_system,0},
	{"BACK",NULL,NULL,0},
	{"DONE",NULL,NULL,0},
};


void draw_slide(uint16_t slide);
uint8_t get_menu_length(MenuItem* menu);
void main_loop(void);


#endif /*__MENU_H */