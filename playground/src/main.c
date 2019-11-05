#include <common_utils/I2C.h>
#include <common_utils/Interrupts.h>
#include <common_utils/LEDs.h>
#include <common_utils/TextOutput.h>
#include <common_utils/Keypad.h>
#include <common_utils/LCDDisplay.h>


static uint8_t ledDebugValue = 0;
static uint8_t cycleCount = 0;


void Interrupts_handleAll() {
    RUN_EVERY(500) {
        LEDs_debugBinary(ledDebugValue);
        ledDebugValue++;
        TextOutput_println("iteration");

        if(ledDebugValue % 16 == 0) {
            cycleCount++;
        }

        if(cycleCount >= 2) {
            Interrupts_stop();
        }
    }
}


int main(void) {
    LEDs_init();
    TextOutput_init();

    Interrupts_start();

    return 0;
}