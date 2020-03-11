#include "core_requirements/All.h"
//#include "individuals/lewis/EmojiRecogniser.h"

#include <mbed/LCDMenu.h>
#include <mbed/UART_Interrupt.h>


static void run();


int main() {
    run();

    return 0;
}


static void run() {
    LCDMenu mainMenu = LCDMenu_create();

    LCDMenu_addItem(&mainMenu, "A1 Core motion", &A1);
    LCDMenu_addItem(&mainMenu, "A2 Platf edges", &A2);
    LCDMenu_addItem(&mainMenu, "A3 Manual move", &A3);
    LCDMenu_addItem(&mainMenu, "B1 Display RGB", &B1);
    LCDMenu_addItem(&mainMenu, "B2 rasta", &B2);
    LCDMenu_addItem(&mainMenu, "B3 Find colour", &B3);
    LCDMenu_addItem(&mainMenu, "C1 Which flag?", &C1);
    LCDMenu_addItem(&mainMenu, "D PC i.facing", &UART_setup);
    //LCDMenu_addItem(&mainMenu, "Recognise emojis", &EmojiRecogniser_run);

    LCDMenu_run(&mainMenu);
}
