// MP1 demonstration:
// This demonstration requires a program that will execute the following:
// • Print: “Starting count” on the terminal screen.
// • Display the 4-bit (0-15) number on the LEDs with each number displayed for about 1 second under
//   the control of timer-based interrupts.
// • Simultaneously display the 0-15 count on the terminal screen in decimal, hexadecimal and
//   binary.
// • Print: “Finished count” on the terminal screen.

#include <common_utils/Interrupts.h>
#include <common_utils/LEDs.h>
#include <common_utils/TextOutput.h>
#include <stdio.h>


static uint8_t ledDebugValue = 0;
static uint8_t cycleCount = 0;

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

void Interrupts_handleAll() {
    RUN_EVERY(1000) {
        LEDs_debugBinary(ledDebugValue);
        char printNum[3];
        sprintf(printNum, "%d 0x%x %s", ledDebugValue,ledDebugValue,byte_to_binary(ledDebugValue));
        TextOutput_println(printNum);


        ledDebugValue++;
        if(ledDebugValue % 16 == 0) {
            ledDebugValue = 0;
            cycleCount++;
        }

        if(cycleCount >= 1) {
            
            TextOutput_println("Ending count!");

            Interrupts_stop();
            LEDs_debugBinary(0);
        }
    }
}

int main(void) {
    LEDs_init();
    TextOutput_init();

    TextOutput_println("Starting count");

    Interrupts_start();
    return 0;
}
