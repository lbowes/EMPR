
#include "stdbool.h"
#include "stdio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mbed/Serial.h"
#include "mbed/7Seg.h"
#include "mbed/I2C.h"
#include "mbed/LCDDisplay.h"
#include "scanner/manual.h"

#include "scanner/UART_movement.h"

// int len;
// uint8_t command[3];
// uint32_t val = 0;
// //char charArray[4];



void main(void)
{
    // i2c_init();
    // LCDDisplay_init();
    // init_7seg();
    // LCDDisplay_init();
    // serial_init();
    // UART_IntConfig((LPC_UART_TypeDef *) LPC_UART0, UART_INTCFG_RBR, ENABLE);
    // NVIC_EnableIRQ(UART0_IRQn);
    // set_values(0,0,0,0,0,0);

    UART_control_start();
    //manual_start();

}
    

// //currently dispalys text in the LCD display,
// //the text recieved can be interpreted as command
// // codes for motion or whatever you can dream of, anything is possible chief

// void UART0_IRQHandler(void){
//     memset(command, 0, sizeof(command));
//     //memset(charArray, 0, sizeof(charArray));
//     serial_read(&command , sizeof(command));
    
//     change_digit(2, command[0]);
//     change_digit(3, command[1]);
//     change_digit(4, command[2]);
    


//     //  for (len = 0; len < sizeof(command) ; len++){
//     //      charArray[len] = command[len];
//     //  }
    
//     //  LCDDisplay_print(&charArray, 0);

// }

    
