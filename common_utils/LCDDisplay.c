#include "LCDDisplay.h"
#include "I2C.h"
#include <stdio.h>

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


static uint32_t I2CAddress = 0x38;


// DO NOT CHANGE this!!!!
// Setup bold face
static uint8_t initWrite[11] = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02};
static uint8_t test[5] = {0x00,0x80,0x40,0x64};




void LCDDisplay_init(void) 
{
    // Lets write the first bits to get the lcd configured
    i2c_send_data(I2CAddress,initWrite,sizeof(initWrite));
    i2c_send_data(I2CAddress,test,sizeof(test));
}

void LCDDisplay_clear(unsigned int line_number) {
    // To clear a line number then we will write blanks
    
}


int LCDDisplay_print(const char* msg,unsigned int line_number ) {
    // Get message size
    unsigned int message_size;
    message_size = strlen(msg);
    // Lets perform some checks
    // If line_number is not 1 or 0 we will return -1 to show an error
    if (line_number!=LINE_1 || line_number!=LINE_2)
    {
        return -1;
    }
    // If messageSize is 0 then we assume you want to clear the screen
    if (message_size==0){
        LCDDisplay_clear(line_number);
    }

    // Convert msg to byte array


    // We successfully sent data to the LCD display send success code
    return 0;

}
