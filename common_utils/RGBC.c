#include "RGBC.h"
#include <common_utils/I2C.h>
#include <common_utils/TextOutput.h>
#include <common_utils/Constants.h>
#include <stdio.h>


//Global 
uint8_t rgbc_array[8];

//Struct
struct RGBC
{
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t c;
};


//Setup 
static uint8_t switchOn[] = {0x80, 0x03}; // disable WEN and enable AEN
static uint8_t setGain[] = {0x8F, 0x00}; // Set gain to 1
static uint8_t readAddress[] = {0x94}; // Set gain to 1 1011 0100 

void RGBC_init(void){
    static uint8_t switchOn[] = {0x80, 0x03}; // disable WEN and enable AEN
    static uint8_t setGain[] = {0x8F, 0x00}; // Set gain to 1
    i2c_send_data(RGBC_I2C_SENSOR_ADDRESS, switchOn, sizeof(switchOn));
    i2c_send_data(RGBC_I2C_SENSOR_ADDRESS, setGain, sizeof(setGain));
    
}

struct RGBC RGBC_SCAN(void){
    uint8_t counter =0;
    for (counter; counter<8; counter++){
        i2c_send_data(RGBC_I2C_SENSOR_ADDRESS,readAddress, sizeof(readAddress));
        i2c_receiveDataFrom(RGBC_I2C_SENSOR_ADDRESS, &rgbc_array[counter], 1);
        readAddress[0]=readAddress[0]+0x01;
    }
    struct RGBC rgbc;
    rgbc.c = (rgbc_array[1]<<8)+ rgbc_array[0];
    rgbc.r = (rgbc_array[3]<<8)+ rgbc_array[2];
    rgbc.g = (rgbc_array[5]<<8)+ rgbc_array[4];
    rgbc.b = (rgbc_array[7]<<8)+ rgbc_array[6];
    return rgbc;
}