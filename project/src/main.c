#include "scanner/ColourSensor.h"
#include "mbed/TextOutput.h"
#include "scanner/Motion.h"
#include "mbed/Delay.h"
#include "mbed/I2CSniffer.h"
#include "scanner/LimitSwitch.h"
#include "scanner/QRSCAN.h"
#include "mbed/I2C.h"
#include "scanner/Drawing.h"
#include "scanner/Shading.h"
Colour RecentScan;
//int Colour_Find(Colour Input);
//char* Colour_String(uint8_t);
//RED:0,BLUE:1,GREEN:2,CYAN:3,YELLOW:4,BLACK:5,WHITE:6,GRAY:7;
//uint16_t colour_array[8][4] = {{95, 23, 22, 126}, {29, 61, 27, 110}, {15, 42, 83, 132}, {20, 53, 66, 141}, {140, 121, 48, 320}, {8, 7, 6, 20}, {147, 154, 144, 458}, {49, 51, 48, 151}};

int main() {
    Colour TestColour;
    i2c_init();
    ColourSensor_init();
    TextOutput_init(); 
    Motion_init();
    Drawing_init();
    Drawing_penToHead();
    Motion_moveBy(29, 0, 0);
    Drawing_penDownLight();
    Drawing_penDownDark();
    Drawing_penUp();
    Motion_neutraliseAllAxes();
    Motion_home();
    TextOutput_println("BEGIN SCAN");
    Shading_scanShade();
    Motion_home();
    Delay_ms(30000);
    Shading_shade();
    return 0;
}

