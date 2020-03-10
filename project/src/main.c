#include "core_requirements/All.h"

#include <mbed/LCDMenu.h>
#include <mbed/LCDDisplay.h>
#include <mbed/I2C.h>
#include <mbed/LEDs.h>
#include <mbed/TextOutput.h>
#include <mbed/Keypad.h>
#include <mbed/UART_Interrupt.h>
#include <scanner/Motion.h>
#include <scanner/QRSCAN.h>
#include <scanner/ColourSensor.h>
#include <mbed/UART_Interrupt.h>


static void run();


int main() {
    Motion_init();
    ColourSensor_init();

    //ColourPointRecogniser_getCriticalPointColours();

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
     LCDMenu_addItem(&mainMenu, "D PC i.facing", &UART_setup);

     LCDMenu_run(&mainMenu);
}
