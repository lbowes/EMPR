// MP1 demonstration: This demonstration requires a program that will
// execute the following:
// • Print: “Starting count” on the terminal screen.
// • Display the 4-bit (0-15) number on the LEDs with each number displayed for about 1 second under the control of timer-based interrupts.
// • Simultaneously display the 0-15 count on the terminal screen in decimal, hexadecimal and binary.
// • Print: “Finished count” on the terminal screen.
#include <common_utils/LEDs.h>
#include <common_utils/UART.h>
#include <common_utils/Delay.h>
#include <stdint.h>
#define ONE_SECOND 0xFFFFF800

int count = 0;
void myInterrupt(void) {
    if (count == 20) {
    LEDs_turnOn(count % 3);
    count = 0;
    }
    else{
    Delay_TenMS();
    count += 1;
    }
    return 0;
}
int main(void)
{   
    LEDs_init();
    Delay_TenMS();
    LEDs_turnOn(1);
    while(1);
    return 1;
}
