
#include "mbed/TextOutput.h"
#include <string.h>
#include "PcSender.h"
#include <stdio.h>
void PCSender_sendRGBAndPos (uint8_t x,uint8_t y,uint8_t z,uint8_t raw_r,uint8_t raw_g,uint8_t raw_b,uint8_t raw_c){
    char data[100] = {};
    // sprintf(data,"X:%d Y:%d Z:%d R:%d G:%d B:%d C:%d",x,y,z,raw_r,raw_g,raw_b,raw_c);
     sprintf(data,"%d %d %d %d %d %d %d",x,y,z,raw_r,raw_g,raw_b,raw_c);
    TextOutput_println(data);
}