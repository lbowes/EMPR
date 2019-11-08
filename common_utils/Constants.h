#ifndef EMPR_CONSTANTS_H_
#define EMPR_CONSTANTS_H_


// Generic
#define EMPR_INPUT        0
#define EMPR_OUTPUT       1

// Keys
#define EMPR_KEY_1        0b01110111 // Top row
#define EMPR_KEY_2        0b10110111
#define EMPR_KEY_3        0b11010111
#define EMPR_KEY_A        0b11100111
#define EMPR_KEY_4        0b01111011 // Upper middle row
#define EMPR_KEY_5        0b10111011
#define EMPR_KEY_6        0b11011011
#define EMPR_KEY_B        0b11101011
#define EMPR_KEY_7        0b01111101 // Lower middle row
#define EMPR_KEY_8        0b10111101
#define EMPR_KEY_9        0b11011101
#define EMPR_KEY_C        0b11101101
#define EMPR_KEY_0        0b10111110 // Bottom row
#define EMPR_KEY_D        0b11101110
#define EMPR_KEY_ASTERISK 0b01111110
#define EMPR_KEY_HASH     0b11011110

#define EMPR_KEYPAD_ROWS  4
#define EMPR_KEYPAD_COLS  EMPR_KEYPAD_ROWS

// I2C address
#define LCD_I2C_ADDRESS 0x3B
#define KEYPAD_I2C_ADDRESS 0x21
#define SEVEN_SEGMENT_DISPLAY_I2C_ADDRESS 0x35
#define EEPROM_I2C_ADDRESS 0x50
#define GPIO_I2C_ADDRESS 0x20

// UART address

#endif // EMPR_CONSTANTS_H_
