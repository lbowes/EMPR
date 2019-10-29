#include "I2C.h"

// setup pins
void i2c_init(void){
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
    uint8_t data[1]={0x00};
    I2C_M_SETUP_Type setup;
	setup.sl_addr7bit = 59;

	setup.tx_data = &data[0];
	setup.tx_length = 1;
	setup.tx_count = 0;

	setup.rx_data = NULL;
	setup.rx_length = 0;
	setup.rx_count = 0;

	setup.retransmissions_max = 2;
    // TextOutput_print("Success");
    Status a = I2C_MasterTransferData(LPC_I2C1,&setup,I2C_TRANSFER_POLLING);
    if (a==SUCCESS){
    TextOutput_print("Success");
    }
    return I2C_MasterTransferData(LPC_I2C1,&setup,I2C_TRANSFER_POLLING);
}
