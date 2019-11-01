#ifndef EMPR_I2C7SEG_H_
#define EMPR_I2C7SEG_H_

void init_7seg(void);

void display_7seg(uint8_t* data);

int get_bit_pattern(int number);

void change_digit(int digit, int val);

void seven_seg_off(void);

void set_colon(int state);

void set_top_dot(int state);

void set_decimal_point(int state);

void set_values(int digit_one, int digit_two, int digit_three, int digit_four, int colon_state, int decimal_state, int topdot_state);

void brightness_7seg(int setting);

#endif // EMPR_I2C7SEG_H_