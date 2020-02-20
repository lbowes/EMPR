#include "Delay.h"

#include <mbed/Interrupts.h>

#include <stdbool.h>


static uint32_t counter = 0;


void Delay_interrupt() {
    counter++;
}


void Delay_ms(uint32_t time) {
    Interrupts_start(Delay_interrupt);
    counter = 0;
    while(counter < time) { }
}