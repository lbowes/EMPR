// #include "common_utils/DAC.h"

#include <math.h>
#include "common_utils/DAC.h"
#include "common_utils/Interrupts.h"
#include "common_utils/LEDs.h"
uint32_t tick = 0;

Interrupts_handleAll() { 
    RUN_EVERY(100000000); {
    DAC_set_low(); 
        LEDs_debugBinary(15);
    }
}


int main(void) {
    LEDs_init();
    LEDs_debugBinary(3);
    DAC_init();
    DAC_set_maxVoltage();
    Interrupts_start();
    return 0;
}
