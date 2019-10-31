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
#include <common_utils/I2C.h>
int count = 0;
int ledIndex = 0;
char stringIndex[3];

void Interrupt_tenMS(void) {
    count++;
    if (count == 10) {
        count = 0;
        sprintf(stringIndex, "%d", ledIndex);
        TextOutput_print(stringIndex);
        LEDs_debugBinary(ledIndex++);
        if (ledIndex == 16) {
            
            TextOutput_print("Count Finished");
            ledIndex = 0;
            Delay_Disable();
        }
    }
}



int main(void) {
    // Initialisating
    TextOutput_init();
    TextOutput_print("Starting init");
    i2c_init();
    TextOutput_print("Init done");
    uint8_t data[1]={0x00};
    char buff[100];
    if (i2c_send_data(32,&data[0],1)==SUCCESS){
        TextOutput_print("Done m8");
    }
    TextOutput_print("Don m8");
    // LEDs_init();
    // Delay_TenMS();
    return 1;
}
