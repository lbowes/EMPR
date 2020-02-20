#include "MenuUtils.h"

#include <mbed/Delay.h>


void MenuUtils_selectionLoopDelay() {
    // TODO: Get this delay working correctly with the new `Delay_ms` system.

    //Delay_ms(10);

    int i, j, count = 0;
    for(i = 0; i < 1000; i++) {
        for(j = 0; j < 1000; j++)
            count++;
    }
}