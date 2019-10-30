#include "common_utils/Keypad.h"
#include "common_utils/LEDs.h"

#include <lpc17xx_i2c.h>
#include <LPC17xx.h>

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


    // Bus sniffer program
    // 1. Configure mbed pins to act as I2C pins
    // (function 3 at pins P0.0 (mbed 9 / MPU 46) and P0.1 (mbed 10 / MPU 47))
    PINSEL_CFG_Type PinCFG;
	PinCFG.Funcnum = 3;
	PinCFG.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCFG.Pinmode = PINSEL_PINMODE_PULLUP;

	PinCFG.Portnum = 0;
	PinCFG.Pinnum = 0;
	PINSEL_ConfigPin(&PinCFG);
	PinCFG.Pinnum = 1;
	PINSEL_ConfigPin(&PinCFG);

    // Initialise the I2C
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, ENABLE);


    return 0;
}
