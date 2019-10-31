#include "Delay.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"
#include "InterruptFunctions.h"

uint32_t elapsed_Tick = 0x0;

void SysTick_Handler(void) 
{
    elapsed_Tick++;
    if ((elapsed_Tick % 0x02) == 0) {
        Interrupt_tenMS();
    }
    if ((elapsed_Tick % 0x07) == 0) {
        Interrupt_fiftyMS();
    }
    if ((elapsed_Tick % 0x14) == 0) {
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
