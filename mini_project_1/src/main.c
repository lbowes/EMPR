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


void TEMP_cycleAllLEDsOn() {
    uint8_t ledIdx = 0;
    for(ledIdx = 0; ledIdx < NUMBER_OF_LEDS; ledIdx++) {
        LEDs_turnOn(ledIdx);
        delay();
        LEDs_turnOff(ledIdx);
    }
}

int main() {
    // Initialisation
    LEDs_init();
    TextOutput_init();

    // Run
    TextOutput_print("Starting count");

    // temp - testing LED cycling
    // ==========================
    uint8_t i = 0;
    const uint8_t cycleCount = 2;
    for(i = 0; i < cycleCount; i++)
        TEMP_cycleAllLEDsOn();
    // ==========================

    //TextOutput_print("Finished count");

    LEDs_debug(3);

    TextOutput_shutdown();

    return 0;
}
