#include <common_utils/I2C.h>
#include <common_utils/Delay.h>
#include <common_utils/LEDs.h>
#include <common_utils/TextOutput.h>
#include <common_utils/Keypad.h>
#include <common_utils/LCDDisplay.h>


int main(void) {
    // Init everything
    i2c_init();
    TextOutput_init();
    LEDs_init();
    Keypad_init();
    LCDDisplay_init();
    // End init

    return 0;
}