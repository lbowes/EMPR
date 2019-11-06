#include "I2C.h"

#include <lpc17xx_pinsel.h>


void i2c_init(void) {
	// Initialise I2C
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, ENABLE);

	// Setup pins
	PINSEL_CFG_Type PinCFG;
	PinCFG.Funcnum = 3;
	PinCFG.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCFG.Pinmode = PINSEL_PINMODE_PULLUP;
	PinCFG.Portnum = 0;
	PinCFG.Pinnum = 0;
	PINSEL_ConfigPin(&PinCFG);
	PinCFG.Pinnum = 1;
	PINSEL_ConfigPin(&PinCFG);
}


Status i2c_send_data(uint8_t address, uint8_t* dataSource, uint32_t dataLength) {
    I2C_M_SETUP_Type write;

	write.sl_addr7bit = address;
	write.tx_data = &dataSource[0];
	write.tx_length = dataLength;
	write.tx_count = 0;
	write.rx_data = NULL;
	write.rx_length = 0;
	write.rx_count = 0;
	write.retransmissions_max = 2;

    return I2C_MasterTransferData(LPC_I2C1, &write, I2C_TRANSFER_POLLING);
}


Status i2c_receiveDataFrom(uint8_t address, uint8_t* dataDest, uint32_t dataLength) {
	I2C_M_SETUP_Type read;

	// Set the MSB of this to 1 to specify that this is a read operation
	read.sl_addr7bit = address | 0x80;
	read.tx_data = NULL;
	read.tx_length = 0;
	read.tx_count = 0;
	read.rx_data = &dataDest[0];
	read.rx_length = dataLength;
	read.rx_count = 0;
	read.retransmissions_max = 2;

    return I2C_MasterTransferData(LPC_I2C1, &read, I2C_TRANSFER_POLLING);
}