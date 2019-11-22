#include "Interrupts.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"


static uint32_t elapsedMs = 0;


static void (*interruptHandler)();


void SysTick_Handler(void) {
    interruptHandler();
    //Interrupts_handleAll();
    elapsedMs++;
}


void Interrupts_start(void (*callback)()) {
    interruptHandler = callback;

    SYSTICK_InternalInit(1);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
}


void Interrupts_stop(void) {
    SYSTICK_IntCmd(DISABLE);
    SYSTICK_Cmd(DISABLE);
}


bool Interrupts_every(uint32_t ms) {
    return elapsedMs % ms == 0;
}