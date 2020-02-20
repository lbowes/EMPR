#include "D2.h"


/*
 * PC Move and Measure:
 * The PC will be able to send commands to MBED to move axes, and then receive
 * a color data measurement from the new location.
 * • Minimum requirement is for a 16x16 grid resolution.
 * • Color data should be displayed as RGB values on the PC.
*/
void D2() {
    RGBC_init();
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


void UART0_IRQHandler(void){
    NVIC_DisableIRQ(UART0_IRQn);
    memset(command, 0, sizeof(command));
    serial_read(&command , sizeof(command));

    move(command[0],command[1]);

    scan_vals = RGBC_SCAN();
    PCSender_sendRGBAndPos (0,0,0,scan_vals.r, scan_vals.g, scan_vals.b, scan_vals.c);
    Motion_neutraliseAllAxes();
    NVIC_EnableIRQ(UART0_IRQn);
}