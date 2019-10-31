#ifndef EMPR_I2C_H_
#define EMPR_I2C_H_
#include <stdbool.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
// init pins
void i2c_init(void);
// Send data
Status i2c_send_data(uint8_t address,uint8_t* Data, uint32_t dataLength);
#endif 