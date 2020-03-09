#include "A3.h"

#include <mbed/Constants.h>
#include "scanner/Motion.h"

#include "scanner/PcSender.h"
#include <mbed/LCDDisplay.h>
#include <mbed/Keypad.h>


#include "stdbool.h"
#include "stdio.h"
#include "scanner/Vector3D.h"
#include "lpc17xx_pinsel.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mbed/7Seg.h"
#include "mbed/I2C.h"
#include "mbed/LCDDisplay.h"



/*
 * 'Manual Move Mode,' : the user should be able to use the keypad or another
 * input device to move all three axes back and forth, whilst the position of each axis
 * is displayed on the LCD panel.
 * • The user can move the x-y position using suitable inputs
 * • The Z-axis can be controlled to at least two positions (Up/Down)
 * • Response times should be fast enough for reasonable user interaction.
*/



char buffer[20];



int scale = 5;

Vector3D location ;


void move_x1(int change){
    Motion_moveBy(change, 0, 0);
    location = Motion_getCurrentPos() ; 
    sprintf(buffer,"%d   %d", location.x, location.y);
    LCDDisplay_print(buffer, 0);
}






void move_y1(int change){
    Motion_moveBy(0, change, 0);
    location = Motion_getCurrentPos() ; 
    sprintf(buffer,"%d   %d", location.x, location.y);
    LCDDisplay_print(buffer, 0);
   
}





void move_z1(int change){
    Motion_moveBy(0, 0, change);
    location = Motion_getCurrentPos() ; 
    sprintf(buffer,"%d", location.z);
    LCDDisplay_print(buffer, 1);
}






void A3() {
    i2c_init();
    Motion_init();
    Motion_home();
    Keypad_init();
    int neut_count  = 0;
    while (1){
        if (Keypad_isKeyDown(EMPR_KEY_1)){
            move_x1(scale);
        }
        if (Keypad_isKeyDown(EMPR_KEY_2)){
            move_x1(-scale);
        } 
        if (Keypad_isKeyDown(EMPR_KEY_4)){
            move_y1(scale);
        }
        if (Keypad_isKeyDown(EMPR_KEY_5)){
            move_y1(-scale);
        } 
        if (Keypad_isKeyDown(EMPR_KEY_7)){
            move_z1(5 * scale);
        }
        if (Keypad_isKeyDown(EMPR_KEY_8)){
            move_z1(-5 * scale);
        } 

        if(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) {
            while(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) {}
            break;
        }

        if (neut_count == 1500) {
            Motion_neutraliseAllAxes();
            neut_count = 0;
        }
        
        neut_count ++;
    }
}