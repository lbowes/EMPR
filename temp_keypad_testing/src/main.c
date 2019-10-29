#include "common_utils/Keypad.h"
#include "common_utils/LEDs.h"


int main() {
    // Polling keys
    // ============
    // The byte at address 33dec (0x21h) contains information about which keys
    // on the keypad are currently pressed.

    // The four pins connected to the lower nibble correspond to the 4 rows of
    // the keypad.

    // The four pins selecting which column(s) are pressed are connected to the
    // higher nibble.

    // We need to scan through the 4 columns of the keypad, moving a '0' through
    // the nibble:

    // 0111 <-
    // 1011   |
    // 1101   |
    // 1110 --

    // When a key is pressed, the pin corresponding to the ROW that this key is
    // in goes LOW.

    // i.e Anything pressed on the top row ('1', '2', '3', 'A') will cause bit 0
    // of this nibble to be LOW.

    // At this point we only know what row the key is in.
    // We need to check the value of 1 bit in memory for each row.

    uint8_t rows[4] = {
        0x00000000, // bit 0 of 0x21
        0x00000000, // bit 1 of 0x21
        0x00000000, // bit 2 of 0x21
        0x00000000  // bit 3 of 0x21
    };



    return 0;
}
