#define DATA_GATHERING 0

#if !DATA_GATHERING

#include "core_requirements/All.h"

#include <mbed/LCDMenu.h>
#include <mbed/LCDDisplay.h>
#include <mbed/I2C.h>
#include <mbed/LEDs.h>
#include <mbed/TextOutput.h>
#include <mbed/Keypad.h>
#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>


static void run();

int main() {
    i2c_init();
    Keypad_init();
    LCDDisplay_init();
    TextOutput_init();
    LEDs_init();
    Motion_init();

    run();

    return 0;
}


static void run() {
    LCDMenu mainMenu = LCDMenu_create();

    LCDMenu_addItem(&mainMenu, "A1 Core motion", &A1);
    LCDMenu_addItem(&mainMenu, "A2 Platf edges", &A2);
    LCDMenu_addItem(&mainMenu, "A3 Manual move", &A3);
    LCDMenu_addItem(&mainMenu, "B1 Display RGB", &B1);
    LCDMenu_addItem(&mainMenu, "B2 RGB to PC", &B2);
    LCDMenu_addItem(&mainMenu, "B3 Find colour", &B3);
    LCDMenu_addItem(&mainMenu, "C1 Which flag?", &C1);
    LCDMenu_addItem(&mainMenu, "D1 RGBXYZ-> PC", &D1);
    LCDMenu_addItem(&mainMenu, "D2 Cmd & read", &D2);
    LCDMenu_addItem(&mainMenu, "D3 Show scan", &D3);

    LCDMenu_run(&mainMenu);

    //LCDDisplay_print("main prog", 0);
    //LCDMenu_destroy(&mainMenu); // TODO: Work out why this is causing a crash
    //LCDDisplay_print("main prog end", 1);
}

#else

#include <scanner/ColourSensor.h>


int main() {
    ColourPointRecogniser_init();
    temp_ColourSensor_gatherData();

    return 0;
}

#endif