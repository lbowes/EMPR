// MP1 demonstration: This demonstration requires a program that will
// execute the following:
// • Print: “Starting count” on the terminal screen.
// • Display the 4-bit (0-15) number on the LEDs with each number displayed for about 1 second under the control of timer-based interrupts.
// • Simultaneously display the 0-15 count on the terminal screen in decimal, hexadecimal and binary.
// • Print: “Finished count” on the terminal screen.
#include <common_utils/LEDs.h>



#include <stdint.h>
#include <common_utils/TextOutput.h>
#include <common_utils/I2C.h>
#include <stdio.h>


void main(void) {
    
    TextOutput_init();
	i2c_init();
    uint8_t data[6] = {0x00,0xF7,0x00,0x00,0x00,0x00};
    Status done = i2c_send_data(0x38,data,sizeof(data));
    uint8_t data2[6] = {0x04,0x01};
    done = i2c_send_data(0x38,data2,sizeof(data2));
    if (done==SUCCESS){
        TextOutput_print("working");
    }
    else{
        TextOutput_print("na");
    }
}
