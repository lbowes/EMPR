#include "Keypad.h"

#include <mbed/I2C.h>
#include <mbed/Constants.h>
#include <stdio.h>

void Keypad_init(void)
{
    i2c_init();
}

bool Keypad_isKeyDown(uint8_t key)
{
    uint8_t col = 0;
    for (col = 0; col < EMPR_KEYPAD_COLS; col++)
    {
        uint8_t colMask[1] = {~(1 << (4 + col)) | 0x0F};
        i2c_send_data(KEYPAD_I2C_ADDRESS, colMask, 1);

        uint8_t keyDownStateByte[1];
        i2c_receiveDataFrom(KEYPAD_I2C_ADDRESS, &keyDownStateByte[0], 1);

        if (key == keyDownStateByte[0])
            return true;
    }

    return false;
}
