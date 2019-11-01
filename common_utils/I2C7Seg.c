
#include "I2C7Seg.h"
#include <common_utils/TextOutput.h>
#include <LPC17xx.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <common_utils/I2C.h>



//Turns off all 7seg displays


static void display(uint8_t* data)
{
    Status sent = i2c_send_data(0x38,data,sizeof(data));

}



void seven_seg_off (void)
{
    uint8_t data[6] = {0x00,0xF7,0x00,0x00,0x00,0x00};
    display(data);

}


void set_colon(state)
{
    uint8_t data[6] = {0x00,0xF7,0x00,0x80,0x80,0x00};
    display(data);
}


void set_decimal_point(state)
{
    uint8_t data[6] = {0x00,0xF7,0x00,0x80,0x80,0x00};
  

}




void set_values(int digit_one, int digit_two, int digit_three, int digit_four, char colon_state, char decimal_state, char topdot_state)
{
    int numbers[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
    uint8_t data[6];
    if(colon_state == 1){
        data[6] = {0x00,0xF7,numbers[digit_one],numbers[digit_two],numbers[digit_three],numbers[digit_four]};
        display(data);
    }


}