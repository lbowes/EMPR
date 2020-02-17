#include <mbed/Constants.h>
#include "Motion.h"
#include <mbed/LCDDisplay.h>
#include <mbed/Keypad.h>


#include "stdbool.h"
#include "stdio.h"
#include "lpc17xx_uart.h"
#include "Vector3D.h"
#include "lpc17xx_pinsel.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mbed/Serial.h"
#include "mbed/7Seg.h"
#include "mbed/I2C.h"
#include "mbed/LCDDisplay.h"


int len;
uint8_t command[6];

char buffer[20];


int scale = 5;

Vector3D location ;





void move_x(int change){
    Motion_moveBy(change, 0, 0);
    location = Motion_getCurrentPos() ; 
    sprintf(buffer,"%d   %d", location.x, location.y);
    LCDDisplay_print(buffer, 0);
}

void move_y(int change){
    Motion_moveBy(0, change, 0);
    location = Motion_getCurrentPos() ; 
    sprintf(buffer,"%d   %d", location.x, location.y);
    LCDDisplay_print(buffer, 0);
   
}

void move_z(int change){
    Motion_moveBy(0, 0, change);
    location = Motion_getCurrentPos() ; 
    sprintf(buffer,"%d", location.z);
    LCDDisplay_print(buffer, 1);
}



void manual_start(void){
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

void UART_control_start(void){
    Motion_init();
    i2c_init();
    LCDDisplay_init();
    init_7seg();
    serial_init();
    UART_IntConfig((LPC_UART_TypeDef *) LPC_UART0, UART_INTCFG_RBR, ENABLE);
    NVIC_EnableIRQ(UART0_IRQn);
    set_values(0,0,0,0,0,0);
    Motion_home();
    Motion_neutraliseAllAxes();
}





void UART0_IRQHandler(void){
    NVIC_DisableIRQ(UART0_IRQn);
    memset(command, 0, sizeof(command));
    serial_read(&command , sizeof(command));

    
    change_digit(2, command[0]);
    change_digit(3, command[2]);
    change_digit(4, command[4]);

    if (command[1] != 0){
        if (command[0] == 1){
            move_x(command[1] * -1);
        }
        else{
            move_x(command[1]);
        }
    }
    if (command[3] != 0){
        if (command[2] == 1){
            move_y(command[3] * -1);
        }
        else{
            move_y(command[3]);
        }
    }
    if (command[5] != 0){
            if (command[4]==1){
                move_z(command[5]* -1);
        }
        move_z(command[5]);
    }

    Motion_neutraliseAllAxes();
    NVIC_EnableIRQ(UART0_IRQn);


    

}

