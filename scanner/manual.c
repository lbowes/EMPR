#include <mbed/Constants.h>
#include "Motion.h"

#include "PcSender.h"
#include <mbed/LCDDisplay.h>
#include <mbed/Keypad.h>


#include "stdbool.h"
#include "stdio.h"
#include "Vector3D.h"
#include "lpc17xx_pinsel.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mbed/7Seg.h"
#include "mbed/I2C.h"
#include "mbed/LCDDisplay.h"






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



void manual_start1(void){
    i2c_init();
    Motion_init();
    Motion_home();
    Keypad_init();
    int neut_count  = 0;
    while (1){
        if (Keypad_isKeyDown(EMPR_KEY_1)){
            move_x(scale);
        }
        if (Keypad_isKeyDown(EMPR_KEY_2)){
            move_x(-scale);
        } 
        if (Keypad_isKeyDown(EMPR_KEY_4)){
            move_y(scale);
        }
        if (Keypad_isKeyDown(EMPR_KEY_5)){
            move_y(-scale);
        } 
        if (Keypad_isKeyDown(EMPR_KEY_7)){
            move_z(5 * scale);
        }
        if (Keypad_isKeyDown(EMPR_KEY_8)){
            move_z(-5 * scale);
        } 

        if (neut_count == 1500) {
            Motion_neutraliseAllAxes();
            neut_count = 0;
        }
        
        neut_count ++;
    }

}









