// MP1 demonstration: This demonstration requires a program that will
// execute the following:
// • Print: “Starting count” on the terminal screen.
// • Display the 4-bit (0-15) number on the LEDs with each number displayed for about 1 second under the control of timer-based interrupts.
// • Simultaneously display the 0-15 count on the terminal screen in decimal, hexadecimal and binary.
// • Print: “Finished count” on the terminal screen.
#include <common_utils/LEDs.h>
#include <common_utils/Keypad.h>


Interrupts_handleAll() { }


int main(void) {
    Keypad_init();
    LEDs_init();

    while(1) {
        LEDs_debugBinary(Keypad_isKeyDown(EMPR_KEY_0));
    }

    return 0;
}
