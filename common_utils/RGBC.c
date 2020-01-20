#include "RGBC.h"
#include <common_utils/I2C.h>
#include <common_utils/TextOutput.h>
#include <common_utils/Constants.h>
#include <stdio.h>


//Global 
uint8_t rgbc_array[8];






static uint8_t readAddress[] = {0x14 | 160}; // Set gain to 1 1011 0100 

void RGBC_init(void){
    // static uint8_t switchOn[] = {0x80, 0x03}; // disable WEN and enable AEN
    // static uint8_t setIntegration[] = {0x81, 0xFF}; // set int time
    // static uint8_t setGain[] = {0x8F, 0x00}; // Set gain to 1
    uint8_t initalSetup[1] = {0x00 | 160};
    i2c_init();
    i2c_receiveDataFrom(RGBC_I2C_SENSOR_ADDRESS, &initalSetup[0], 1);
    uint8_t enable = initalSetup[0] | 3;
    uint8_t switchOn[] = {0x80,enable | 0x03};
    i2c_send_data(RGBC_I2C_SENSOR_ADDRESS,switchOn, sizeof(switchOn));
    char atime= 256 - ((int) 100/2.4);
    uint8_t aTimeTx[] = {0x81,atime};
    i2c_send_data(RGBC_I2C_SENSOR_ADDRESS,aTimeTx, sizeof(aTimeTx));
}

RGBC RGBC_SCAN(void){
    i2c_send_data(RGBC_I2C_SENSOR_ADDRESS,readAddress, sizeof(readAddress));    
    i2c_receiveDataFrom(RGBC_I2C_SENSOR_ADDRESS, &rgbc_array[0], 8);

    RGBC rgbc;

    rgbc.c = (rgbc_array[1] << 8) + rgbc_array[0];
    rgbc.r = (rgbc_array[3]<<8)+ rgbc_array[2];
    rgbc.g = (rgbc_array[5]<<8)+ rgbc_array[4];
    rgbc.b = (rgbc_array[7]<<8)+ rgbc_array[6];
    return rgbc;
}