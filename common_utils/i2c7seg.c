
#include "i2c7seg.h"

#include <LPC17xx.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>



void init_i2c(void){
	
	PINSEL_CFG_Type pins;
	
	pins.Portnum = 0;
	pins.OpenDrain = 0;
	pins.Funcnum = 3;
	pins.Pinmode = 0;
	
	pins.Pinnum = 9;
	PINSEL_ConfigPin(&pins);
	
	pins.Pinnum = 10;
	PINSEL_ConfigPin(&pins);
	
	
	I2C_Init(LPC_I2C1, 100000);
	
	I2C_Cmd(LPC_I2C1, ENABLE);

	}


int send_data(uint8_t addr){
	
	I2C_M_SETUP_Type leds;
	
	leds.sl_addr7bit = addr;
	leds.tx_data = &data;
	leds.tx_length = sizeof(data);
	leds.rx_length = 0;
	leds.rx_data = NULL;
	leds.retransmissions_max = 0x03;
	
	
	I2C_MasterTransferData(LPC_I2C1, &leds, I2C_TRANSFER_POLLING); 
	if (I2C_MasterTransferData(LPC_I2C1, &leds, I2C_TRANSFER_POLLING) == SUCCESS ){

	return 1;
		}
	else{
	return 0;
	}
	


}
	
