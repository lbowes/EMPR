#include "B1.h"
#include <mbed/Constants.h>
#include "Motion.h"

#include "PcSender.h"
#include <mbed/LCDDisplay.h>
#include <mbed/Keypad.h>

#include "scanner/Colour.h"
#include "scanner/ColourSensor.h"
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
#include "mbed/TextOutput.h"

char buffer1[1000];
char buffer2[1000];

Colour colours;
int scalee = 1;

void colour_get(void){
    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));
    colours =  ColourSensor_seq();
    TextOutput_printInteger(colours.r);
    TextOutput_printInteger(colours.g);
    TextOutput_printInteger(colours.b);
    TextOutput_printInteger(colours.clear);
    TextOutput_println("     ");
    sprintf(buffer1,"r: %d   g: %d", colours.r, colours.g);
    sprintf(buffer2,"b: %d   c: %d", colours.b, colours.clear);
    
    LCDDisplay_print(buffer1, 0);
    LCDDisplay_print(buffer2, 1);
}


void move_x(int change){
    Motion_moveBy(change, 0, 0);
    colour_get();
}

void move_y(int change){
    Motion_moveBy(0, change, 0);
    colour_get();
   
}

void move_z(int change){
    Motion_moveBy(0, 0, change);
    colour_get();
}


void B1() { 
    i2c_init();
    TextOutput_init();
    Motion_init();
    Motion_home();
    Keypad_init();
    ColourSensor_init();
    
    while (1){
        if (Keypad_isKeyDown(EMPR_KEY_1)){
            move_x(scalee);
        }
        if (Keypad_isKeyDown(EMPR_KEY_2)){
            move_x(-scalee);
        } 
        if (Keypad_isKeyDown(EMPR_KEY_4)){
            move_y(scalee);
        }
        if (Keypad_isKeyDown(EMPR_KEY_5)){
            move_y(-scalee);
        } 
        if (Keypad_isKeyDown(EMPR_KEY_7)){
            move_z(5 * scalee);
        }
        if (Keypad_isKeyDown(EMPR_KEY_8)){
            move_z(-5 * scalee);
        } 

        
        Motion_neutraliseAllAxes();
            
    }

}