#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"
#include "InterruptFunctions.h"
#define PERIOD_10MS 0x02
#define PERIOD_1S 0x14
#define BITMASK (PERIOD_10MS | PERIOD_1S)
uint32_t Elapsed_Tick = 0x0;
uint32_t Comparator;
void SysTick_Handler(void) 
{
    Elapsed_Tick++;
    if ((Elapsed_Tick % 0x02) == 0) {
        Interrupt_tenMS();
    }
    if ((Elapsed_Tick % 0x14) == 0) {
        Interrupt_oneS();
    }
}


void Delay_TenMS(void) {
    SYSTICK_InternalInit(50);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
}



void Delay_Disable(void) {
    SYSTICK_IntCmd(0);
    SYSTICK_Cmd(0);
}
