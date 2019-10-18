#include "LCDDisplay.h"
#include <stdbool.h>
#include <lpc17xx_i2c.h>
static uint32_t I2CAddress = 0x38;

// This LCD has 2X8 bit registers
// Instruction reg and data Reg
// Top 2 bytes have impact

// First  bit  control byte
// 0 last control byte
// 1 another control byte follows after data
// Second bit
// 0 instruction reg
// 1 data reg
// bits 5-0 is always 0
// Control byte has only 4 commands
// 00h Last control byte instruction
// 40h Last control byte data
// 80h Another control byte will follow and instuction
// C0h Another control byte will follow and data



// DO NOT CHANGE this!!!!
// Setup bold face
static uint32_t initWrite[10] = {0x00, 0x34, 0x0c, 0x06, 0x35, 0x10, 0x42, 0x9f, 0x34, 0x02};

void LCDDisplay_init(void) {
    //
    I2C_INIT(LPC_I2C0,100000);
// Clear Screen
}

void LCDDisplay_clear(void) {

}


void LCDDisplay_print(const char* msg, bool ) {

}
