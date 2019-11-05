#include "LCDDisplay.h"
#include "I2C.h"
#include <string.h> 
#include "Constants.h"

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
static uint8_t initWrite[] = {0x00, 0x34, 0x0c, 0x06, 0x35, 0x04, 0x10, 0x42, 0x9f, 0x34, 0x02};
static uint8_t cursor[] = {0x00, 0x0E};
static uint8_t line_1[] = {0x00, 0x02};
static uint8_t line_2[] = {0x00, 0xC0};
void LCDDisplay_init(void)
{
    // Lets write the first bits to get the lcd configured
    i2c_send_data(LCD_I2C_ADDRESS, initWrite, sizeof(initWrite));
    i2c_send_data(LCD_I2C_ADDRESS, cursor, sizeof(cursor));

    LCDDisplay_clear(LINE_1);
    LCDDisplay_clear(LINE_2);
}

void LCDDisplay_clear(unsigned int line_number)
{
    // To clear a line number then we will write blanks
    uint8_t clear[] = {0x40, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0};

    if (LINE_1 == line_number)
    {
        i2c_send_data(LCD_I2C_ADDRESS, line_1, sizeof(line_1));
        i2c_send_data(LCD_I2C_ADDRESS, clear, sizeof(clear));
        i2c_send_data(LCD_I2C_ADDRESS, line_1, sizeof(line_1));
    }
    else if (LINE_2 == line_number)
    {
        i2c_send_data(LCD_I2C_ADDRESS, line_2, sizeof(line_2));
        i2c_send_data(LCD_I2C_ADDRESS, clear, sizeof(clear));
        i2c_send_data(LCD_I2C_ADDRESS, line_2, sizeof(line_2));
    }
}

int LCDDisplay_print(const char *msg, unsigned int line_number)
{
    
    // Get message size
    unsigned int message_size=0;
    message_size = strlen(msg);
    // Lets perform some checks
    // If line_number is not 1 or 0 we will return -1 to show an error
    if (line_number != LINE_1 && line_number != LINE_2)
    {
        return -1;
    }
    // If messageSize is 0 then we assume you want to clear the screen
    if (message_size == 0)
    {
        LCDDisplay_clear(line_number);
    }

    // Convert msg to byte array
    // Our byte array
    uint8_t message[message_size + 1];
    message[0] = 0x40;
    int index = 0;
    char character;
    for (index = 0; index <= message_size; index++)
    {
        character= msg[index];
        switch (character)
        {
        case 0x20:
            character=0xA0;
            break;
        case 0x30 ... 0x39:
            character=character+0x80;
            break;
        case 0x41 ... 0x5A:
            character=character+0x80;
            break;
        case 0x3A ... 0x3F:
            character=character+0x80;
            break;
        case 0x21 ... 0x23:
            character=character+0x80;
            break;
        case 0x25 ... 0x2F:
            character=character+0x80;
            break;
        default:
            break;
        }
        message[index + 1] = character;
    }
    
    if (line_number == LINE_1)
    {
        LCDDisplay_clear(LINE_1);
        i2c_send_data(LCD_I2C_ADDRESS, line_1, sizeof(line_1));
    }
    else if (line_number == LINE_2){
        LCDDisplay_clear(LINE_2);
        i2c_send_data(LCD_I2C_ADDRESS, line_2, sizeof(line_2));
    }
    i2c_send_data(LCD_I2C_ADDRESS, message, sizeof(message));    
    return 0;
}
