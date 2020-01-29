/***********************************************************************/
#include "stdbool.h"
#include "stdio.h"


void main(void)
{
    Keypad_init();
    LCDDisplay_init();
    while (1){
        //Scan Patterns
        if (Keypad_isKeyDown(EMPR_KEY_1)){
            LCDDisplay_print("Scan pattern", LINE_1);
        }
        //Manual Mode
        if (Keypad_isKeyDown(EMPR_KEY_2)){
            LCDDisplay_print("Manual ", LINE_1);
        }
        //Scan
        if (Keypad_isKeyDown(EMPR_KEY_3)){
            LCDDisplay_print("Scan", LINE_1);
        }
        //PC Control
        if (Keypad_isKeyDown(EMPR_KEY_4)){}
        LCDDisplay_print("PC Contrill", LINE_1);
        //Flag ident
        if (Keypad_isKeyDown(EMPR_KEY_5)){
            LCDDisplay_print("flag", LINE_1);
        }
        //Individual tasks
        if (Keypad_isKeyDown(EMPR_KEY_6)){
            LCDDisplay_print("indi", LINE_1);
        }
       
        //Next Page
        if (Keypad_isKeyDown(EMPR_KEY_9)){}

    }
}
