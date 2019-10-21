#include "TextOutput.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"

#include <string.h>


// Copied from https://www-users.cs.york.ac.uk/~nep/teach/empr/serialEx/serial.c
void TextOutput_init(void) {
    UART_CFG_Type UARTConfigStruct;
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;
    PINSEL_CFG_Type PinCfg;

    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;

    PinCfg.Portnum = 0;
    PinCfg.Pinnum = 2;
    PINSEL_ConfigPin(&PinCfg);

    PinCfg.Pinnum = 3;
    PINSEL_ConfigPin(&PinCfg);

    /* Initialize UART Configuration parameter structure to default state:
     * - Baudrate = 9600bps
     * - 8 data bit
     * - 1 Stop bit
     * - None parity
     */
    UART_ConfigStructInit(&UARTConfigStruct);

    /* Initialize FIFOConfigStruct to default state:
     * - FIFO_DMAMode = DISABLE
     * - FIFO_Level = UART_FIFO_TRGLEV0
     * - FIFO_ResetRxBuf = ENABLE
     * - FIFO_ResetTxBuf = ENABLE
     * - FIFO_State = ENABLE
     */
    UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

    // Once configuration is complete, start the devices
    UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);
    UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);
    UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);
}


static void TextOutput_resetCursor(void)
    // TODO: A more efficient implementation of  this function would involve
    // pre/appending the return and newline characters to the message passed in
    // and then only call UART_Send(...) once.
{
    UART_Send((LPC_UART_TypeDef*)LPC_UART0, (uint8_t*)"\n", 1, BLOCKING);
    UART_Send((LPC_UART_TypeDef*)LPC_UART0, (uint8_t*)"\r", 1, BLOCKING);
}


void TextOutput_print(const char* msg) {
    const uint32_t msgLength = strlen(msg);
    TextOutput_resetCursor();
    UART_Send((LPC_UART_TypeDef*)LPC_UART0, (uint8_t*)msg, msgLength, BLOCKING);
}


void TextOutput_println(const char* msg) {
    const uint32_t msgLength = strlen(msg);
    UART_Send((LPC_UART_TypeDef*)LPC_UART0, (uint8_t*)msg, msgLength, BLOCKING);
    TextOutput_resetCursor();
}


void TextOutput_memeText(void) {

}


void TextOutput_shutdown(void) {

}
