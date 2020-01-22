
#include "mbed/TextOutput.h"
#include <string.h>
#include "PcSender.h"
void PCSender_sendRGBAndPos (uint8_t x,uint8_t y,uint8_t z,uint8_t raw_r,uint8_t raw_g,uint8_t raw_b,uint8_t raw_c){
    char data[100] = {};
    uint8_t r,g,b =0;
    r=(int)((raw_r/raw_c)*255.0);
    g=(int)((raw_g/raw_c)*255.0);
    b=(int)((raw_b/raw_c)*255.0);
    sprintf(data,"%d %d %d %d %d %d",x,y,z,r,g,b);
    TextOutput_println(data);
}