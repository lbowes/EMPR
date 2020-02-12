#include "Delay.h"
#include "stdbool.h"
#include "mbed/Interrupts.h"
uint32_t counter=0;

void Delay_interrupt() {
        counter++;
    }


void Delay_ms(uint32_t time){
    Interrupts_start(Delay_interrupt);
    counter=0;
    while(counter<time){}
}
