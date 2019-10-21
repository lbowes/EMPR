// MP1 demonstration: This demonstration requires a program that will
// execute the following:
// • Print: “Starting count” on the terminal screen.
// • Display the 4-bit (0-15) number on the LEDs with each number displayed for about 1 second under the control of timer-based interrupts.
// • Simultaneously display the 0-15 count on the terminal screen in decimal, hexadecimal and binary.
// • Print: “Finished count” on the terminal screen.

#include <common_utils/LEDs.h>
#include <common_utils/TextOutput.h>

#include <stdint.h>
#include <stdio.h>


#define ONE_SECOND 0xFFFFF800


void delay() {
    uint32_t count = 0;
    uint32_t i = 0;
    uint32_t j = 0;

    for(i = ONE_SECOND; i < 0xFFFFFFFF; i++) {
        for(j = ONE_SECOND; j < 0xFFFFFFFF; j++) {
            count++;
        }
    }
}


int main() {
    // Initialisation
    LEDs_init();
    TextOutput_init();

    // Run
    TextOutput_println("Starting count");
    uint8_t i = 0;
    for(i = 0; i < (1 << NUMBER_OF_LEDS); i++) {
        LEDs_debugBinary(i);

        // Convert the current LED number to a string
        char i_str[3];
        sprintf(i_str, "%d", i);

        TextOutput_println(i_str);
        delay();
    }
    TextOutput_println("Finished count");
    TextOutput_debugMsg("someFunction", "something is broken!");

    // Shutdown
    TextOutput_shutdown();

    return 0;
}
