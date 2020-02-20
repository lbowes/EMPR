#include "MenuUtils.h"

#include <mbed/Delay.h>


// Adds a delay in an LCD menu while loop.
// Without any delay, the loop cycles too quickly for keypad presses to be used to
// switch menu options. A button press might be 10s of millseconds.
void MenuUtils_selectionLoopDelay() {
    Delay_ms(100);
}