#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"
#include "InterruptFunctions.h"

void SysTick_Handler(void) {
    myInterrupt();
}
void Delay_TenMS(void) {
    SYSTICK_InternalInit(10);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
}
