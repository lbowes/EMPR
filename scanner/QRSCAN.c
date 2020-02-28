#include "Motion.h"
#include "PcSender.h"
#include "Scanners.h"
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
//x is 200
//y is 230

char buffer1[1000];


////yayayayya

void scan_start(void){
    int x_ax, y_ax;
    Colour col_vals;
    int col_line ;
    int x_scale = 3, y_scale = 3;
    int x_offset = 20, y_offset = 0;
    //Motion_home();
    LEDs_init();
    for (x_ax = x_offset; x_ax< 240; x_ax+=x_scale){
        //Motion_moveAxisToLimit(EMPR_Y_AXIS);
        for (y_ax = y_offset; y_ax < 240; y_ax+=y_scale){
            LEDs_debugBinary(1);
            Motion_moveTo(x_ax, y_ax, 0);
            LEDs_debugBinary(2);
            //Delay_ms(5);   figure out what is going on here
            col_vals = ColourSensor_read();
            LEDs_debugBinary(4);
            sprintf(buffer1,"r: %d   g: %d", col_vals.r, col_vals.g);
            
            LCDDisplay_print(buffer1, 0);
            
            PCSender_sendRGBAndPos(((x_ax + x_offset)/x_scale),((y_ax + y_offset)/y_scale),0, col_vals.r, col_vals.g, col_vals.b, col_vals.clear);
            LEDs_debugBinary(8);
        Motion_neutraliseAllAxes();

        }
    }
    LCDDisplay_print("done", 1);
}



void SetupScanning(void)
{   
    i2c_init();
    LCDDisplay_init();
    serial_init();
    UART_IntConfig((LPC_UART_TypeDef *) LPC_UART0, UART_INTCFG_RBR, ENABLE);
    NVIC_EnableIRQ(UART0_IRQn);
    ColourSensor_init();
    Motion_init();
    Motion_neutraliseAllAxes();
    
    
}



    void UART0_IRQHandler(void){
        scan_start();
}


