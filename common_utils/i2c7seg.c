
#include "i2c7seg.h"
#include <LPC17xx.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <common_utils/I2C.h>





int send_data(uint8_t addr, uint8_t[7] Data){
	
	done = i2c_send_data(uint8_t addr,uint8_t* Data, uint32_t 7);
	if (done == SUCCESS){
		return 1;
	}
	else{
		return 0;
	}

}
	
