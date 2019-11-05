#include "Interrupts.h"
#include "InterruptFunctions.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"


static uint32_t elapsedTicks = 0;


void SysTick_Handler(void) {
    if ((elapsedTicks % 10) == 0) {
        Interrupt_everyTenMS();
    }
    if ((elapsedTicks % 50) == 0) {
        Interrupt_everyFiftyMS();
    }
    if ((elapsedTicks % 100) == 0) {
        Interrupt_everyHundredMS();
        elapsedTicks = 0;
    }

    elapsedTicks++;
}


void Interrupts_start(void) {
    SYSTICK_InternalInit(5);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
}


void Interrupts_stop(void) {
    SYSTICK_IntCmd(DISABLE);
    SYSTICK_Cmd(DISABLE);
}