// MP1 demonstration: This demonstration requires a program that will
// execute the following:
// • Print: “Starting count” on the terminal screen.
// • Display the 4-bit (0-15) number on the LEDs with each number displayed for about 1 second under the control of timer-based interrupts.
// • Simultaneously display the 0-15 count on the terminal screen in decimal, hexadecimal and binary.
// • Print: “Finished count” on the terminal screen.
#include <common_utils/I2C.h>
#include <common_utils/LEDs.h>
#include <common_utils/TextOutput.h>
#include <common_utils/Keypad.h>
#include <common_utils/LCDDisplay.h>
#include <common_utils/RealTimeClock.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {

    // Init everything
    i2c_init();
    TextOutput_init();
    LEDs_init();
    keypad_init();
    LCDDisplay_init();
    Real_Time_Clock_init();
    // End init
   LCDDisplay_print("Initlising ...",LINE_1);
   
    return 1;

}
