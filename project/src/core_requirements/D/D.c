#include "D.h"
#include "scanner/Motion.h"
#include <mbed/Constants.h>
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "scanner/Full_Scan.h"
#include "scanner/QRSCAN.h"
#include "scanner/UART_movement.h"
#include <stdio.h>


uint8_t commanding[3];

void D() {
    Motion_init();
    i2c_init();
    LCDDisplay_init();
    serial_init();
    UART_IntConfig((LPC_UART_TypeDef *) LPC_UART0, UART_INTCFG_RBR, ENABLE);
    NVIC_EnableIRQ(UART0_IRQn);
    ColourSensor_init();
    Motion_neutraliseAllAxes();
}


void UART0_IRQHandler(void){
    NVIC_DisableIRQ(UART0_IRQn);
    memset(commanding, 0, sizeof(commanding));
    serial_read(&commanding, sizeof(commanding));
    if (commanding[0] == 2){
        full_scan_start();
    }
    else if (commanding[0] == 4){
        uart_move(commanding[1], commanding[2]);
    }
    else if (commanding[0] == 6){
        QR_scan_start();
    }
   
    memset(commanding, 0, sizeof(commanding));
    NVIC_EnableIRQ(UART0_IRQn);
}