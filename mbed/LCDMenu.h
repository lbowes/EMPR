#ifndef EMPR_LCDMENU_H_
#define EMPR_LCDMENU_H_

#include <stdint.h>


typedef void (*Callback)(void);
typedef struct Item Item;

typedef struct {
    uint8_t itemCount;
    int activeItemIdx;
    Item* items;
} LCDMenu;


LCDMenu LCDMenu_create();
void LCDMenu_addItem(LCDMenu* menu, const char* nameOnLCD, Callback functionToRun);
void LCDMenu_run();
void LCDMenu_destroy(LCDMenu* menu);


#endif // EMPR_LCDMENU_H_
