#include "LCDDisplay.h"
#include <stdbool.h>
#include <lpc17xx_i2c.h>
static uint32_t I2CAddress = 0x38;

// This LCD has 2X8 bit registers
// Instruction reg and data Reg


// DO NOT CHANGE this!!!!
static uint32_t initWrite[10] = {0x00, 0x34, 0x0c, 0x06, 0x35, 0x10, 0x42, 0x9f, 0x34, 0x02};

void LCDDisplay_init(void) {
    I2C_INIT(LPC_I2C0,)
// Clear Screen
}

void LCDDisplay_clear(void) {

}


void LCDDisplay_print(const char* msg, bool ) {

}
