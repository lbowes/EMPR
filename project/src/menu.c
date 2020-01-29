/***********************************************************************/
#include "stdbool.h"
#include "stdio.h"
#include "common_utils/LCDDisplay.h"
#include "common_utils/Constants.h"
#include "common_utils/I2C.h"
#include "Motion.h"
#include "common_utils/7Seg.h"


static char* menu [3][2] = {
    {"1. Scan Pattern", "2. Manual  9->"},
    {"1. PC Control","2. Scan    9->"},
    {"1. Independent", "2. Flag    9->"}
};
void delay2() {
    int i, j, count = 0;
    for(i = 0; i < 1000; i++) {
        for(j = 0; j < 10000; j++)
            count++;
    }
}
void start_menu(void)
{   
    int page_count = 0;
    Keypad_init();
    init_7seg();
    LCDDisplay_init(); 
    while (1){
        //Scan Patterns
        if (Keypad_isKeyDown(EMPR_KEY_1) && page_count == 0 ){
            change_digit(4,0x01);
        }
        //Manual Mode
        if (Keypad_isKeyDown(EMPR_KEY_2) && page_count == 0){
            change_digit(4,0x02);
        }
        //Scan
        if (Keypad_isKeyDown(EMPR_KEY_1) && page_count == 1 ){
            change_digit(4,0x03);
        }
        //PC Control
        if (Keypad_isKeyDown(EMPR_KEY_2) && page_count == 1 ){
            change_digit(4,0x04);
        }
        //Flag ident
        if (Keypad_isKeyDown(EMPR_KEY_1) && page_count == 2 ){
            change_digit(4,0x05);
        }
        //Individual tasks
        if (Keypad_isKeyDown(EMPR_KEY_2) && page_count == 2 ){
            change_digit(4,0x06);
        }
       
        //Next Page
        if (Keypad_isKeyDown(EMPR_KEY_9)){
            page_count++;
            if (page_count > 2) {
                page_count = 0;
            } 
        }
        LCDDisplay_print(menu[page_count][1], 1);
        LCDDisplay_print(menu[page_count][0], 0);
        delay2();
    }
}
