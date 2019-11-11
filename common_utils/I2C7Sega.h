#ifndef EMPR_I2C7SEG_H_
#define EMPR_I2C7SEG_H_
#include <stdint.h>
 
//initialises the 7segment display
void init_7seg(void);

//Changes a specified digit 1-4 to a specified value 0x00 - 0x0F
void change_digit(int digit, int val);

//Turns off 7seg display
void seven_seg_off(void);

//Controls the colon, 1 = one, 0 = off
void set_colon(int state);

//Controls top dot, functions same as set_colon
void set_top_dot(int state);

//Controls the bottom dot, ^^
void set_decimal_point(int state);

//One command to controll everthing at once, change all digits and control dots.
void set_values(int digit_one, int digit_two, int digit_three, int digit_four, int decimal_state, int topdot_state);

//changes brightness of 7seg dislay, setting range from 1-7
void brightness_7seg(int setting);

//displays 2 digit hex specified by digit 1 and digit 2
void display_hex_7seg(int digit1, int digit2);

#endif // EMPR_I2C7SEG_H_