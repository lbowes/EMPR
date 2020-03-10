
#include "mbed/TextOutput.h"
#include <string.h>
#include "PcSender.h"
#include <stdio.h>

void PCSender_sendRGBAndPos ( uint32_t x,uint32_t y,uint32_t z,uint32_t raw_r,uint32_t raw_g,uint32_t raw_b,uint32_t raw_c){
    char data[32] = {};
    // sprintf(data,"X:%d Y:%d Z:%d R:%d G:%d B:%d C:%d",x,y,z,raw_r,raw_g,raw_b,raw_c);
    sprintf(data,"%lx %lx %lx %lx %lx %lx %lx",x,y,z,raw_r,raw_g,raw_b,raw_c);
    TextOutput_println(data);
}

void PCSender_sendDebugMessage(char* message){

    char messageArray [1000];
    strcpy(messageArray,"Debug:");
    strcpy(messageArray,message);
    TextOutput_println("Debug:");
}

void PCSender_quicksend( uint8_t x, uint8_t y,uint8_t z,uint8_t raw_r,uint8_t raw_g, uint8_t raw_b,uint8_t raw_c){
    char data2[7] = {};
    // sprintf(data,"X:%d Y:%d Z:%d R:%d G:%d B:%d C:%d",x,y,z,raw_r,raw_g,raw_b,raw_c);
    sprintf(data2,"%hhx %hhx %hhx %hhx %hhx %hhx %hhx",x,y,z,raw_r,raw_g,raw_b,raw_c);
    TextOutput_println(data2);
}