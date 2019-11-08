#include "Keypad.h"

#include <common_utils/I2C.h>
#include <common_utils/Constants.h>
#include <common_utils/TextOutput.h>


//temp
#include <stdio.h>
//

static uint8_t keyDownStateByte[1];


void Keypad_init(void) {
    TextOutput_init();
    i2c_init();
}


bool Keypad_isKeyDown(uint8_t key) {
    // Set all bits of the keypad state byte to 1's (pad is active LOW)
    // Set the keyboard register to 00001111
    uint8_t allBitsHigh[1] = { 0x0F };
    if(!i2c_send_data(KEYPAD_I2C_ADDRESS, allBitsHigh, 1)) {
        TextOutput_println("ERROR receiving keypad state byte.");
    }

    // Update the contents of the state byte
    if(!i2c_receiveDataFrom(KEYPAD_I2C_ADDRESS, &keyDownStateByte[0], 1)) {
        TextOutput_println("ERROR receiving keypad state byte.");
    }
    keyDownStateByte[0] |= 0xF0;

    // keyDownStateByte[0] is either
    // 1111 1111 = empty
    // 1111 1110 = bottom row
    // 1111 1101 = lower mid
    // 1111 1011 = upper mid
    // 1111 0111 = top row

    // char msg[3];
    // sprintf(msg, "%d", keyDownStateByte[0]);
    // TextOutput_print(msg);

    // 0111 1111
    uint8_t keyColumn = key | 0x0F;
    char msg[3];
    sprintf(msg, "%d", keyColumn);
    TextOutput_print(msg);


    return (keyDownStateByte[0] & keyColumn) == key;

    // uint8_t i = 0;
    // for(i = 0; i < EMPR_KEYPAD_COLS; i++) {
    //     uint8_t colIdx = ~(1 << (4 + i)) | 0x0F;
    //     uint8_t selectedKey = keyDownStateByte[0] & colIdx;

    //     if(selectedKey == key)
    //         return true;
    // }

    //return false;
}

