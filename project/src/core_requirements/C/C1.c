#include "C1.h"
#include "FlagData.h"
#include "../MenuUtils.h"

#include <scanner/Image.h>
#include <mbed/LCDDisplay.h>
#include <mbed/Constants.h>
#include <mbed/Keypad.h>

#include <stddef.h>


static const char* flagNames[EMPR_FLAG_COUNT];

static void populateFlagNames();
static uint8_t recognise(Image* flag);


/*
 * FLAGS OF THE WORLD:
 * Your solution must be capable of scanning a set of color flag cards and
 * recognising the identity of the relevant country to which that flag pertains.
 * • Recognise at least 5 flags out of a set of 10
 * • Displays the country identity on LCD
 * • recognises a flag within 30 seconds.
 * • There are many options here to gain extra marks. Fast detection algorithms
 * for instance, the range of flags detectable, the ability to deal with scale, and
 * so-on.
*/
void C1() {
    LCDDisplay_init();
    Keypad_init();
    populateFlagNames();

    LCDDisplay_print("Flag recognition", EMPR_LINE_1);

    Image* flagImage = NULL;
    uint8_t flagId = 0;

    while(1) {
        // Perform a scan and recognition of the contents of the platform
        if(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) {
            LCDDisplay_print("...", EMPR_LINE_2);

            //flagImage = Scanner_someScanFunction();
            //flagId = recognise(flagImage);

            LCDDisplay_print(flagNames[flagId], EMPR_LINE_2);
        }

        // Move on to next requirement
        if(Keypad_isKeyDown(EMPR_KEY_HASH))
            break;

        MenuUtils_selectionLoopDelay();
    }

    Image_destroy(flagImage);
}


static void populateFlagNames() {
    // TODO: Initialise these properly

    flagNames[EMPR_FLAG_UK] = "united_kingdom";
    flagNames[EMPR_FLAG_FRANCE] = "france";
    flagNames[EMPR_FLAG_TODO] = "todo";
    flagNames[EMPR_FLAG_INITIALISE] = "set";
    flagNames[EMPR_FLAG_THESE] = "these";
    flagNames[EMPR_FLAG_DEFINES] = "names";
    flagNames[EMPR_FLAG_WITH] = "with";
    flagNames[EMPR_FLAG_FLAGS] = "flags";
    flagNames[EMPR_FLAG_TO] = "to";
    flagNames[EMPR_FLAG_RECOGNISE] = "initialise";
}


static uint8_t recognise(Image* flag) {
    uint8_t closestFlagID = EMPR_FLAG_TODO;
    
    // TODO: Take in an `Image` and return the ID of the closest matching flag.

    // This is where the core of flag recognition will take place.
    // Pixel data can be obtained with:
    
    for(uint16_t i = 0; i < flag->width; i++) {
        for(uint16_t j = 0; j < flag->width; j++) {
            
            Colour flagColour = Image_getColourAt(flag, i, j);

        }
    }

    // It's likely that this function will involve iterating over some data for each flags.
    // E.g image histograms, average colours etc
    // This can be done with:
    
    for(uint8_t id = EMPR_FIRST_FLAG; id < EMPR_LAST_FLAG; id++) {
        // ... = someData[id];
    }

    return closestFlagID;
}