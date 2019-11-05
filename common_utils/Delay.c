#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"
#include "InterruptFunctions.h"
#include "Delay.h"


static uint32_t elapsed_Tick = 0;


void SysTick_Handler(void) {
    elapsed_Tick++;
    if ((elapsed_Tick % 10) == 0) {
        Interrupt_tenMS();
    }
    if ((elapsed_Tick % 50) == 0) {
        Interrupt_fiftyMS();
    }
    if ((elapsed_Tick % 100) == 0) {
        Interrupt_hundredMS();
        elapsed_Tick = 0;
    }
}


void Delay_tenMS(void) {
    SYSTICK_InternalInit(5);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
}


void Delay_disable(void) {
    SYSTICK_IntCmd(0);
    SYSTICK_Cmd(0);
}