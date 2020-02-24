#include "LCDMenu.h"

#include "LCDDisplay.h"
#include "Delay.h"
#include "Keypad.h"
#include "Constants.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


struct Item {
    Callback function;
    const char* nameOnLCD;
};

static void shiftUp(LCDMenu* menu);
static void shiftDown(LCDMenu* menu);


LCDMenu LCDMenu_create() {
    LCDDisplay_init();
    Keypad_init();

    LCDMenu newMenu;

    newMenu.itemCount = 0;
    newMenu.activeItemIdx = 0;
    newMenu.items = NULL;

    return newMenu;
}


void LCDMenu_addItem(LCDMenu* menu, const char* nameOnLCD, Callback callback) {
    menu->itemCount++;

    if(menu->itemCount == 1)
        menu->items = (Item*)malloc(menu->itemCount * sizeof(Item));
    else
        menu->items = (Item*)realloc(menu->items, menu->itemCount * sizeof(Item));

    menu->items[menu->itemCount - 1].function = callback;
    menu->items[menu->itemCount - 1].nameOnLCD = nameOnLCD;
}


void LCDMenu_run(LCDMenu* menu) {
    if(menu->itemCount == 0)
        return;

    char label[16];

    while(1) {
        sprintf(label, "%d.%s", menu->activeItemIdx + 1, menu->items[menu->activeItemIdx].nameOnLCD);

        LCDDisplay_print(label, EMPR_LINE_1);
        LCDDisplay_print("<[1]        [4]>", EMPR_LINE_2);

        // Run active function displayed on the LCD
        if(Keypad_isKeyDown(EMPR_KEY_HASH))
            menu->items[menu->activeItemIdx].function();

        // Shift menu up
        if(Keypad_isKeyDown(EMPR_KEY_1))
            shiftDown(menu);

        // Shift menu down
        if(Keypad_isKeyDown(EMPR_KEY_4))
            shiftUp(menu);

        // Quit
        if(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) {
            while(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) { }
            break;
        }

        // Adds a delay in an LCD menu while loop.
        // Without any delay, the loop cycles too quickly for keypad presses to be used to
        // switch menu options. A button press might be 10s of millseconds, which could
        // cause the menu to skip options.
        Delay_ms(EMPR_KEYPAD_WAIT_TIME_MS);
    }
}


static void shiftUp(LCDMenu* menu) {
    menu->activeItemIdx++;
    if(menu->activeItemIdx > menu->itemCount - 1)
        menu->activeItemIdx = 0;
}


static void shiftDown(LCDMenu* menu) {
    menu->activeItemIdx--;
    if(menu->activeItemIdx < 0)
        menu->activeItemIdx = menu->itemCount - 1;
}


void LCDMenu_destroy(LCDMenu* menu) {
    if(menu->items)
        free(menu->items);
}