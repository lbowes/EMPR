#include <mbed/Constants.h>
#include "Motion.h"
#include "Colour.h"
#include "PcSender.h"

#include "stdbool.h"
#include "stdio.h"
#include "lpc17xx_uart.h"
#include "Vector3D.h"
#include "lpc17xx_pinsel.h"
#include "ColourSensor.h"



#include "mbed/Serial.h"
#include "mbed/7Seg.h"
#include "mbed/I2C.h"
#include "mbed/LCDDisplay.h"
#include "mbed/TextOutput.h"

#include "UART_movement.h"



uint8_t command[2];

Vector3D location ;

Colour scan_vals;


void UART_control_start(void){
    ColourSensor_init();
    Motion_init();
    i2c_init();
    serial_init();
    UART_IntConfig((LPC_UART_TypeDef *) LPC_UART0, UART_INTCFG_RBR, ENABLE);
    NVIC_EnableIRQ(UART0_IRQn);
    Motion_home();
    Motion_neutraliseAllAxes();
}





void move(int x, int y){
    Motion_moveTo(x,y,0);

}








// void UART0_IRQHandler(void){
//     NVIC_DisableIRQ(UART0_IRQn);
//     memset(command, 0, sizeof(command));
//     serial_read(&command , sizeof(command));

//     move(command[0],command[1]);

//     scan_vals = ColourSensor_read();
//     PCSender_sendRGBAndPos (0,0,0,scan_vals.r, scan_vals.g, scan_vals.b, scan_vals.clear);
//     Motion_neutraliseAllAxes();
//     NVIC_EnableIRQ(UART0_IRQn);
// }