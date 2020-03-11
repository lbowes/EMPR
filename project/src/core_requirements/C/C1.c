#include "C1.h"
#include "FlagRecogniser.h"

#include <mbed/LCDDisplay.h>
#include <mbed/Constants.h>
#include <mbed/Keypad.h>
#include <mbed/Delay.h>


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

    LCDDisplay_print("Flag Recogniser", EMPR_LINE_1);

    while(1) {
        // Perform flag recognition
        if(Keypad_isKeyDown(EMPR_KEY_HASH)) {
            while(Keypad_isKeyDown(EMPR_KEY_HASH)) { }

            LCDDisplay_print("Flag Recogniser", EMPR_LINE_1);

            LCDDisplay_clear(EMPR_LINE_2);
            LCDDisplay_print("...", EMPR_LINE_2);

            const char* recognisedFlagName = FlagRecogniser_getClosestFlagName();

            LCDDisplay_clear(EMPR_LINE_2);
            LCDDisplay_print(recognisedFlagName, EMPR_LINE_2);
        }

        // Move on to next requirement
        if(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) {
            while(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) { }

            break;
        }

        Delay_ms(EMPR_SMOOTH_MENU_DELAY_MS);

        Motion_neutraliseAllAxes();
    }
}