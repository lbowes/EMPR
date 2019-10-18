#include <stdbool.h>
#include <common_utils/TextOutput.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#ifndef EMPR_I2CSNIFFER_H_
#define EMPR_I2CSNIFFER_H_

void sniffer(void); 
void sendData(I2C_M_SETUP_Type* setup,int address, uint8_t* Data, uint32_t dataLength);
// sets up pins
void setupPins(void);
#endif // EMPR_I2CSNIFFER_H_
