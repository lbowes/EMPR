#include "Interrupts.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"

static uint32_t elapsedMs = 0;
// Create 100 callbackes
static void (*callbacks[100])();
static uint8_t head = 0;
static void (*interruptHandler)();

void Do_Nothing(void)
{
}

void SysTick_Handler(void)
{
    int handler;
    for (handler = 0; handler < head; handler++)
    {
        callbacks[handler]();
    }
    interruptHandler();
    elapsedMs++;
}

int Interrupt_add(void (*callback)())
{
    head++;
    callbacks[head] = callback;
    return head;
}

int Interrupt_add_at_head(int loc, void (*callback)())
{
    if (head >= loc && loc >= 0)
    {
        callbacks[loc] = callback;
        return loc;
    }
    return -1
}

void Interrupt_remove(int callback)
{
    callbacks[callback] = Do_Nothing;
}

void Interrupts_start(void (*callback)())
{
    callbacks[head] = callback;

    SYSTICK_InternalInit(1);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
}

void Interrupts_stop(void)
{
    SYSTICK_IntCmd(DISABLE);
    SYSTICK_Cmd(DISABLE);
}

bool Interrupts_every(uint32_t ms)
{
    return elapsedMs % ms == 0;
}