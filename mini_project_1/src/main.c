// MP1 demonstration: This demonstration requires a program that will
// execute the following:
// • Print: “Starting count” on the terminal screen.
// • Display the 4-bit (0-15) number on the LEDs with each number displayed for about 1 second under the control of timer-based interrupts.
// • Simultaneously display the 0-15 count on the terminal screen in decimal, hexadecimal and binary.
// • Print: “Finished count” on the terminal screen.
#include <common_utils/LEDs.h>
#include <common_utils/Delay.h>
#include <stdint.h>
#include <common_utils/TextOutput.h>
#include <stdio.h>


int count = 0;
int ledIndex = 16;


void cycleLEDs(void) {
    if (count == 10) {
        LEDs_debugBinary(ledIndex++);



        TextOuptut_print()
        count = 0;
        Delay_TenMS();
    }
    else {
        Delay_TenMS();
        count++;
    }
}


void myInterrupt(void) {
    if (ledIndex < 16) {
        cycleLEDs();
    }
}


int main(void) {
    LEDs_init();
    TextOutput_init();

    ledIndex = 16;

    int i = 0;
    while(i < 2) {
        if (ledIndex == 16) {
            ledIndex = 0;
            cycleLEDs();
            i++;
        }
    }

    return 1;
}
