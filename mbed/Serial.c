

#include "TextOutput.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "Serial.h"

uint32_t serial_read(uint8_t *buffer, int length){
    
    return UART_Receive((LPC_UART_TypeDef *) LPC_UART0, buffer, length, BLOCKING);
}

void serial_init(void){
    UART_CFG_Type UARTConfigStruct;
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;
    PINSEL_CFG_Type PinCfg;

    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;

    PinCfg.Portnum = 0;
    PinCfg.Portnum = 0;
    PinCfg.Pinnum = 2;
    PINSEL_ConfigPin(&PinCfg);

    PinCfg.Pinnum = 3;
    PINSEL_ConfigPin(&PinCfg);

    UART_ConfigStructInit(&UARTConfigStruct);
    //baudrate 9600
    
    UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
    
    UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);
    UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);
    UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);

}