#include <mbed/7Seg.h>
#include <mbed/TextOutput.h>
#include <LPC17xx.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <mbed/I2C.h>



//Bit patterns representing each number, index = number, eg patterns[3] = bit pattern for 3
uint8_t patterns[17] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71,0x49};
//Brightness settings 0x17 being dimmest, 0x77 being brightest
uint8_t brightness_settings[7] = {0x17,0x27,0x37,0x47,0x57,0x67,0x77};

//Stores the current digits being displayed, 99 is effective NULL
int current_digits[4] = {99,99,99,99};


void display_7seg(uint8_t* data, int datalength)
{
    Status sent = i2c_send_data(0x38,data,datalength);
}


void init_7seg(void)
{   
    uint8_t data[6] = {0x00,0xF7,0x00,0x00,0x00,0x00};
    current_digits[0] = 99;
    current_digits[1] = 99;
    current_digits[2] = 99;
    current_digits[3] = 99;
    display_7seg(data,sizeof(data));
}


uint8_t get_bit_pattern(int number)
{
    return patterns[number];

}


void change_digit(int digit, int val)
{  
    uint8_t bit_pattern = get_bit_pattern(val);
    uint8_t data[2] = {digit,bit_pattern} ;
    current_digits[digit] = val;
    display_7seg(data,sizeof(data));

}





void set_colon(int state)
{
    set_top_dot(state);
    set_decimal_point(state);
}


void set_decimal_point(int state)
{
    int new_pattern;
    if (current_digits[2] == 99){
        new_pattern = 0x00;
    }
    else{
        new_pattern = get_bit_pattern(current_digits[2]);
    }
    

    if (state == 1){
        new_pattern = (new_pattern | 0x80);
        
    }
    uint8_t data[2] = {0x03,new_pattern};
    display_7seg(data,sizeof(data));
}


void set_top_dot(int state)
{
    int new_pattern ;
    if (current_digits[1] == 99){
        new_pattern = 0x00;
    }
    else{
        new_pattern = get_bit_pattern(current_digits[1]);
    }
    if (state == 1){
        new_pattern = (new_pattern | 0x80);
    }
    uint8_t data[2] = {0x02,new_pattern};
    display_7seg(data,sizeof(data));
}


void brightness_7seg(int setting)
{
    uint8_t brightness = (brightness_settings[setting-1]);
    uint8_t data[2] = {0x00, brightness};
    display_7seg(data,sizeof(data));

}


void display_hex_7seg(int digit1, int digit2 )
{
    set_values(0,0, digit1, digit2,0,0);
    
    change_digit(2,sizeof(patterns)-1);
}


void set_values(int digit_one, int digit_two, int digit_three, int digit_four, int decimal_state, int topdot_state)
{
    int new_digits[4] = {digit_one, digit_two, digit_three, digit_four};
    int index = 1;
    for (index = 1 ; index<=4 ; index++)
    {
        change_digit(index, new_digits[index-1]);
        current_digits[index-1] = new_digits[index-1];
    }
    set_top_dot(topdot_state);
    set_decimal_point(decimal_state);

}