/***********************************************************************/
#include "stdbool.h"
#include "stdio.h"

uint8_t array[4] = {0x09, 0x05, 0x06, 0x0a};
int n;
int cycles;
#define MOTOR_ADDRESS 62
n = 0;
cycles = 0;
#include "common_utils/Interrupts.h"
#include "common_utils/I2CSniffer.h"
#include "common_utils/I2C.h"
#include "common_utils/LEDs.h"
#include "common_utils/TextOutput.h"
Interrupts_handleAll() { 
    RUN_EVERY(10) {
    LEDs_debugBinary(n);
    if (cycles < 100){
        TextOutput_printInteger(array[n]);
        i2c_send_data(MOTOR_ADDRESS, array[n], 1);
        n=n+1;
        if (n > 3) {
            n = 0;
            cycles = cycles + 1;
        } 
    }
    }
} 
/* Example group ----------------------------------------------------------- */
/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************/
int main(void)
{
LEDs_init();
LEDs_debugBinary(1);
i2c_init();
I2CSniffer_run();
Interrupts_start();
LEDs_debugBinary(2);
return 0;
}
