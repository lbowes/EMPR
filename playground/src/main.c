/***********************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include "mbed/TextOutput.h"
#include "mbed/Interrupts.h"
#include "mbed/LEDs.h"
#include "mbed/Delay.h"


int main(void) {
TextOutput_init();
TextOutput_println("Hello");
Delay_ms(5000);
TextOutput_println("World");
return 0;
}
