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

        // Print LED number to the console
        char i_str[3];
        sprintf(i_str, "%d", ledIndex);
        TextOutput_println(i_str);

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
    // Initialisation
    LEDs_init();
    TextOutput_init();

    ledIndex = 16;

    // Running
    TextOutput_print("Starting count...");

    int i = 0;
    while(i < 2) {
        if (ledIndex == 16) {
            ledIndex = 0;
            cycleLEDs();
            i++;
        }
    }

    TextOutput_print("Finished count.");

    return 1;
}
