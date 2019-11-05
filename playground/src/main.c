#include <common_utils/I2C.h>
#include <common_utils/Interrupts.h>
#include <common_utils/LEDs.h>
#include <common_utils/TextOutput.h>
#include <common_utils/Keypad.h>
#include <common_utils/LCDDisplay.h>


void Interrupt_everyTenMS() {

}


void Interrupt_everyFiftyMS() {
    TextOutput_print("50MS");
}


void Interrupt_everyHundredMS() {
    TextOutput_print("100MS");
}


int main(void) {
    TextOutput_init();
    Interrupts_start();
    return 0;
}