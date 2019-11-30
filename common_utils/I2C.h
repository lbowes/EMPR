#ifndef EMPR_I2C_H_
#define EMPR_I2C_H_

#include <lpc17xx_i2c.h>


void i2c_init(void);

Status i2c_send_data(uint8_t address, uint8_t* dataSource, uint32_t dataLength);
Status i2c_receiveDataFrom(uint8_t address, uint8_t* dataDest, uint32_t dataLength);


#endif // EMPR_I2C_H_
