#include "scanner/QRSCAN.h"
#include "scanner/Motion.h"

#include <scanner/ColourSensor.h>
#include <scanner/Motion.h>

#include <stdio.h>


//#include "scanner/UART_movement.h"


int main() {
    // Motion_init();
    // Motion_moveTo(400,0,0);
    // Motion_neutraliseAllAxes();
    SetupScanning();
    //UART_control_start();


//lewis stuff
    // Motion_init();
    // ColourSensor_init();
    // TextOutput_init();

    // Motion_moveTo(100, 100, 0);
    
    // while(1) {
    //     Colour c = ColourSensor_read();

    //     char buf[64];
    //     sprintf(buf, "R: %i, G: %i, B: %i", c.r, c.g, c.b);
    //     TextOutput_print(buf);
    // }

    return 0;
}
