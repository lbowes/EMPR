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
int ledIndex = 0;
char stringIndex[3];

void Interrupt_fiftyMS(void) {
    TextOutput_print("50MS");

}
void Interrupt_hundredMS(void) {
    TextOutput_print("100MS");

}
void Interrupt_tenMS(void) {
    TextOutput_print("10MS");
}


int main(void) {
    // Initialisating
    TextOutput_init();
    TextOutput_print("Starting count");
    LEDs_init();
    Delay_tenMS();
    return 1;
}
