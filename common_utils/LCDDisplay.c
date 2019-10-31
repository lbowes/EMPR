// #include "LCDDisplay.h"
// #include <common_utils/TextOutput.h>
// #include <stdio.h>
// static uint32_t I2CAddress = 0x38;

// // This LCD has 2X8 bit registers
// // Instruction reg and data Reg
// // Top 2 bytes have impact

// // First  bit  control byte
// // 0 last control byte
// // 1 another control byte follows after data
// // Second bit
// // 0 instruction reg
// // 1 data reg
// // bits 5-0 is always 0
// // Control byte has only 4 commands
// // 00h Last control byte instruction
// // 40h Last control byte data
// // 80h Another control byte will follow and instuction
// // C0h Another control byte will follow and data



// // DO NOT CHANGE this!!!!
// // Setup bold face
// static uint8_t initWrite[12] = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02};
// static uint8_t test[5] = {0x00,0x80,0x40,0x64};


// void sendData(I2C_M_SETUP_Type* setup,int address,uint8_t* Data, uint32_t dataLength)
// {
// 	setup->sl_addr7bit = address;

// 	setup->tx_data = Data;
// 	setup->tx_length = dataLength;
// 	setup->tx_count = 0;

// 	setup->rx_data = NULL;
// 	setup->rx_length = 0;
// 	setup->rx_count = 0;

// 	setup->retransmissions_max = 2;
// }

// void setupPins(void)
// {
//     // Setup for I2C pins
//     PINSEL_CFG_Type PinCFG;
// 	PinCFG.Funcnum = 3;
// 	PinCFG.OpenDrain = PINSEL_PINMODE_NORMAL;
// 	PinCFG.Pinmode = PINSEL_PINMODE_PULLUP;

// 	PinCFG.Portnum =0;
// 	PinCFG.Pinnum = 0;
// 	PINSEL_ConfigPin(&PinCFG);
// 	PinCFG.Pinnum = 1;
// 	PINSEL_ConfigPin(&PinCFG);
// }

// void LCDDisplay_init(void) 
// {
//     TextOutput_init();
//     TextOutput_print("Starting LCD");
    
//     // Initialise I2C
//     I2C_Init(LPC_I2C1,100000);
//     I2C_Cmd(LPC_I2C1,ENABLE);

//     int index =0;
//     setupPins();
//     TextOutput_print("Pins setup");
//     for (index; index<128; index ++)
//     {
//         // char buff[100];
//         // sprintf(buff,"Address is being tried %d",index);
//         // TextOutput_print(buff);
//         int data[1]={0x00};
//         I2C_M_SETUP_Type setup ;
//         sendData(&setup,index,data,1);
//         Status a = I2C_MasterTransferData(LPC_I2C1,&setup,I2C_TRANSFER_POLLING);
//         if (a==SUCCESS)
//         {
//             char buff[100];
//             sprintf(buff,"Address is being tried %d",index);
//             TextOutput_print(buff);
//         }
//         // char buff2[100];
//         // sprintf(buff2,"Yes/No  %d",index);
//         // TextOutput_print(buff2);
//     }

//     // TextOutput_print("Setup I2C complete");
//     // I2C_M_SETUP_Type setup ;
//     // setupPins();

//     // TextOutput_print("Setup Pins Complete");
    
//     // sendData(&setup,&initWrite[0],12);
    
//     // TextOutput_print("Setting up data");
//     // // Send data through the I2C port
//     // Status a = I2C_MasterTransferData(LPC_I2C1,&setup,I2C_TRANSFER_POLLING);

//     // TextOutput_print("Sending data");
//     // sendData(&setup,&test,5);
//     // I2C_MasterTransferData(LPC_I2C1,&setup,I2C_TRANSFER_POLLING);
//     // Loop
    
//     // I2C_MasterTransferData(LPC_I2C1,&tes,I2C_TRANSFER_POLLING);


//     // Clear Screen
// }

// void LCDDisplay_clear(unsigned int line_number) {

// }


// int LCDDisplay_print(const char* msg,unsigned int line_number ) {
//     // Get message size
//     unsigned int message_size;
//     message_size = strlen(msg);
//     // Lets perform some checks
//     // If line_number is not 1 or 0 we will return -1 to show an error
//     if (line_number!=LINE_1 || line_number!=LINE_2)
//     {
//         return -1;
//     }
//     // If messageSize is 0 then we assume you want to clear the screen
//     if (message_size==0){
//         LCDDisplay_clear(line_number);
//     }

//     // Convert msg to byte array


//     // We successfully sent data to the LCD display send success code
//     return 0;

// }
