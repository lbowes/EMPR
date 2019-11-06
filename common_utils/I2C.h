#ifndef EMPR_I2C_H_
#define EMPR_I2C_H_


#include <stdbool.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>


void i2c_init(void);

Status i2c_send_data(uint8_t address, uint8_t* data, uint32_t dataLength);


#endif // EMPR_I2C_H_
