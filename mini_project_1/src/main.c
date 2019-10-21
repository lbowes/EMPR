// MP1 demonstration: This demonstration requires a program that will
// execute the following:
// • Print: “Starting count” on the terminal screen.
// • Display the 4-bit (0-15) number on the LEDs with each number displayed for about 1 second under the control of timer-based interrupts.
// • Simultaneously display the 0-15 count on the terminal screen in decimal, hexadecimal and binary.
// • Print: “Finished count” on the terminal screen.

#include <common_utils/LEDs.h>
#include <common_utils/TextOutput.h>

#include <stdint.h>


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
    TextOutput_print("Starting count");

    uint8_t i = 0;
    uint8_t maxVal = 1 << NUMBER_OF_LEDS;
    for(i = 0; i < maxVal; i++) {
        LEDs_debug(i);
        delay();
    }

    TextOutput_print("\rFinished count\n");

    // Shutdown close
    TextOutput_shutdown();

    return 0;
}
