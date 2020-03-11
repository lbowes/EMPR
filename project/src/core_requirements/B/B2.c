#include "B2.h"
#include "scanner/Motion.h"

#include "scanner/PcSender.h"
#include "scanner/Scanners.h"
#include <mbed/Constants.h>
#include <mbed/I2C.h>
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include <mbed/TextOutput.h>
#include <mbed/Interrupts.h>
#include <scanner/ColourSensor.h>
#include <mbed/Delay.h>
#include <mbed/LCDDisplay.h>
#include "mbed/TextOutput.h"
#include "mbed/LEDs.h"
#include <stdio.h>
#include "mbed/Keypad.h"



char buf3r[1000];
char buf4r[1000];
char buf5r[1000];



void B2() { 
    int x_ax, y_ax;
    Colour col_vals;
    int col_line ;
    int x_scale = 10, y_scale = 10;
    int x_offset = 0, y_offset = 0;
    
    Keypad_init();
    TextOutput_init();
    Motion_init();
    LCDDisplay_init();
    ColourSensor_init();

    //by default x_ax, y_ax < 240
    for (x_ax = 0; x_ax< 250; x_ax+=x_scale){
        Motion_moveAxisToLimit(EMPR_Y_AXIS);
        for (y_ax = 0; y_ax < 220; y_ax+=y_scale){
 
            Motion_moveTo(x_ax + x_offset, y_ax + y_offset, 0);

            
            col_vals = ColourSensor_seq();
            sprintf(buf3r,"r: %d   g: %d", col_vals.r, col_vals.g);
            sprintf(buf4r,"b: %d   c: %d", col_vals.b, col_vals.clear);
            LCDDisplay_print(buf3r, 0);
            LCDDisplay_print(buf4r, 1);
            if (Keypad_isKeyDown(EMPR_KEY_A)){
                sprintf(buf5r,"r: %d   g: %d  b: %d   c: %d", col_vals.r, col_vals.g, col_vals.b, col_vals.clear);
                TextOutput_println(buf5r);
            }

            
            
            //LEDs_debugBinary(8);
            
        Motion_neutraliseAllAxes();
        }
        
        
        
    }
    
    Motion_home();
    Motion_neutraliseAllAxes();


}