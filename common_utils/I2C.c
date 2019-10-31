#include "I2C.h"

// setup pins
void i2c_init(void){
	// Initialise I2C
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, ENABLE);
    // Setup pins
	PINSEL_CFG_Type PinCFG;
	PinCFG.Funcnum = 3;
	PinCFG.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCFG.Pinmode = PINSEL_PINMODE_PULLUP;

	PinCFG.Portnum =0;
	PinCFG.Pinnum = 0;
	PINSEL_ConfigPin(&PinCFG);
	PinCFG.Pinnum = 1;
	PINSEL_ConfigPin(&PinCFG);
}
// Send data through I2C
Status i2c_send_data(uint8_t address,uint8_t* Data, uint32_t dataLength)
{
	// Setup data structure
    I2C_M_SETUP_Type setup;
	setup.sl_addr7bit = address;

	setup.tx_data = &Data[0];
	setup.tx_length = dataLength;
	setup.tx_count = 0;

	setup.rx_data = NULL;
	setup.rx_length = 0;
	setup.rx_count = 0;

	setup.retransmissions_max = 2;

	// Return if SUCCESS =1 or ERROR=0
    return I2C_MasterTransferData(LPC_I2C1,&setup,I2C_TRANSFER_POLLING);
}
