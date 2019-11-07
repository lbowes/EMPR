#include "Keypad.h"

#include <common_utils/I2C.h>
#include <common_utils/Constants.h>
#include <common_utils/TextOutput.h>


static uint8_t keyDownStateByte[1];


void Keypad_init(void) {
    TextOutput_init();
    i2c_init();
}


bool Keypad_isKeyDown(uint8_t key) {
    // Set all bits of the keypad state byte to 1's (pad is active LOW)
    uint8_t allBitsHigh[1] = { 0xFF };
    if(!i2c_send_data(KEYPAD_I2C_ADDRESS, allBitsHigh, 1)) {
        TextOutput_println("ERROR receiving keypad state byte.");
    }

    // Update the contents of the state byte
    keyDownStateByte[0] = 0xFF;
    if(!i2c_receiveDataFrom(KEYPAD_I2C_ADDRESS, &keyDownStateByte[0], 1)) {
        TextOutput_println("ERROR receiving keypad state byte.");
    }


    // TODO: Fix logic in here
    
    //uint8_t val = ~(1 << 5);
    // 0010 0000
    // 11011111

    //char msg[128];
    //sprintf(msg, "Val: %d", val);
    //TextOutput_print(msg);

    uint8_t i = 0;
    for(i = 0; i < EMPR_KEYPAD_ROWS; i++) {
        uint8_t rowIdx = ~(1 << (4 + i));
        uint8_t selectedKey = keyDownStateByte[0] & rowIdx;
        if(selectedKey == key)
            return true;
    }

    return false;
}
