#include "I2CSniffer.h"

#include <stdio.h>

void sendData(I2C_M_SETUP_Type* setup,int address,uint8_t* Data, uint32_t dataLength)
{
	setup->sl_addr7bit = address;

	setup->tx_data = Data;
	setup->tx_length = dataLength;
	setup->tx_count = 0;

	setup->rx_data = NULL;
	setup->rx_length = 0;
	setup->rx_count = 0;

	setup->retransmissions_max = 2;
}

void setupPins(void)
{
    // Setup for I2C pins
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

void sniffer(void) 
{
    TextOutput_init();
    TextOutput_print("Starting sniffer");
    
    // Initialise I2C
    I2C_Init(LPC_I2C1,100000);
    I2C_Cmd(LPC_I2C1,ENABLE);

    int index =0;
    setupPins();
    TextOutput_print("Pins setup");
    for (index; index<128; index ++)
    {
        uint8_t data[1]={0x00};
        I2C_M_SETUP_Type setup ;
        sendData(&setup,index,data,1);
        Status a = I2C_MasterTransferData(LPC_I2C1,&setup,I2C_TRANSFER_POLLING);
        if (a==SUCCESS)
        {
            char buff[100];
            sprintf(buff,"Address is up: %d",index);
            TextOutput_print(buff);
        }

    }


}


