#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"
#include "InterruptFunctions.h"


void SysTick_Handler(void) {
    Interrupt_tenMS();
}


void Delay_TenMS(void) {
    SYSTICK_InternalInit(100);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
}

void Delay_Disable(void) {
    SYSTICK_IntCmd(0);
    SYSTICK_Cmd(0);
}
