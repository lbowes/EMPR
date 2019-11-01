
#include <common_utils/I2C7Seg.h>
#include <common_utils/TextOutput.h>
#include <LPC17xx.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <common_utils/I2C.h>



uint8_t patterns[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
int current_digits[4];
uint8_t brightness_settings[7] = {0x17,0x27,0x37,0x47,0x57,0x67,0x77};
//Turns off all 7seg displays


void display_7seg(uint8_t* data)
{
    Status sent = i2c_send_data(0x38,data,sizeof(data));

}


void init_7seg(void)
{   
    uint8_t data[6] = {0x00,0xF7,0x00,0x00,0x00,0x00};
    display_7seg(data);
}





int get_bit_pattern(int number)
{
    return patterns[number];

}


void change_digit(int digit, int val)
{   
    uint8_t bit_pattern = get_bit_pattern(val);
    uint8_t data[2] = {digit,bit_pattern} ;
    current_digits[digit] = val;
    display_7seg(data);

}


void seven_seg_off (void)
{
    uint8_t data[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
    display_7seg(data);

}


void set_colon(int state)
{
    set_top_dot(state);
    set_decimal_point(state);
}


void set_decimal_point(int state)
{
    int new_pattern = get_bit_pattern(current_digits[2]);

    if (state = 1){
        new_pattern = (new_pattern | 0x80);
    }

    uint8_t data[2] = {0x3,new_pattern};
    display_7seg(data);
}


void set_top_dot(int state)
{
    int new_pattern = (get_bit_pattern(current_digits[1]));
    if (state = 1){
        new_pattern = (new_pattern | 0x80);
    }
    uint8_t data[2] = {0x2,new_pattern};
    display_7seg(data);
}


void brightness_7seg(int setting)
{
    uint8_t brightness = (brightness_settings[setting-1]);
    uint8_t data[2] = {0x00, brightness};
    display_7seg(data);

}



void set_values(int digit_one, int digit_two, int digit_three, int digit_four, int colon_state, int decimal_state, int topdot_state)
{
    int new_digits[4] = {digit_one, digit_two, digit_three, digit_four};
    int index = 1;
    for (index ; index<5 ; index++)
    {
        if (new_digits[index] != current_digits[index]){
            current_digits[index-1] = new_digits[index-1];
            change_digit(index, new_digits[index-1]);
        }

    }


}
