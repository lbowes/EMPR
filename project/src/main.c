#include "core_requirements/CoreRequirements.h"
#include "scanner/Scanners.h"
#include "scanner/PcSender.h"
#include "scanner/ColourSensor.h"
#include "mbed/TextOutput.h"

#include <mbed/LCDDisplay.h>


int main() {
    // SimpleScan();
        ColourSensor_init();
        TextOutput_init();
        //uint64_t a =0;

        Colour result;

        while(1){
            result = ColourSensor_read();
            //PCSender_sendRGBAndPos(0, 0, 0, result.r, result.g, result.b, result.clear);
            //a++;
            //Delay_ms(3);
            //PCSender_sendRGBAndPos(a,a,a,a,a,a,a);


        }
    // A1();
    // A2();
    // A3();

    // B1();
    // B2();
    // B3();

    // C1();

    // D1();
    // D2();
    // D3();

    return 0;
}