#ifndef EMPR_CONSTANTS_H_
#define EMPR_CONSTANTS_H_


// Generic
#define EMPR_INPUT   0
#define EMPR_OUTPUT  1

// Motion
#define EMPR_LEFT    1
#define EMPR_RIGHT   0
#define EMPR_X_AXIS  0
#define EMPR_X_LIMIT 200
#define EMPR_Y_AXIS  1
#define EMPR_Y_LIMIT 230
#define EMPR_Z_AXIS  2
#define EMPR_Z_LIMIT 1575

// Keypad
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

#define EMPR_KEYPAD_ROWS 4
#define EMPR_KEYPAD_COLS EMPR_KEYPAD_ROWS

// LCD display
#define EMPR_LINE_1 0
#define EMPR_LINE_2 1

// I2C addresses
#define LCD_I2C_ADDRESS                   0x3B
#define KEYPAD_I2C_ADDRESS                0x21
#define SEVEN_SEGMENT_DISPLAY_I2C_ADDRESS 0x35
#define EEPROM_I2C_ADDRESS                0x50
#define GPIO_I2C_ADDRESS                  0x20
#define RGBC_I2C_SENSOR_ADDRESS           0x29

// A delay to add in a while loop sending the LCD menu to remove flickering
#define EMPR_SMOOTH_MENU_DELAY_MS 50

#endif // EMPR_CONSTANTS_H_
