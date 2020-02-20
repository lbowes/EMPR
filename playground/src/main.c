#include <scanner/Motion.h>
#include <mbed/TextOutput.h>
#include <mbed/Constants.h>
#include <scanner/ColourSensor.h>

#include <stdio.h>


int main() {
    Motion_init();
    ColourSensor_init();
    LCDDisplay_init();
    TextOutput_init();

    Motion_moveTo(100, 100, 0);
    Motion_neutraliseAllAxes();

    Colour reading;
    char colour[32];

    while(1) {
        reading = ColourSensor_read();
        sprintf(colour, "rgb(%d, %d, %d)", reading.r, reading.g, reading.b);
        TextOutput_print(colour);
    }

    return 0;
}
