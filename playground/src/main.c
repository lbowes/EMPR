/***********************************************************************/
#include "stdbool.h"
#include "stdio.h"
#include <common_utils/Constants.h>
#include <common_utils/Keypad.h>
#include <common_utils/Constants.h>
#include "LPC17xx.h"
#include "lpc_types.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"





void Interrupts_handleAll(){}
int main(void)
{
    Keypad_init();
    TextOutput_init();
    NVIC_EnableIRQ(EINT3_IRQn);

    __enable_irq();

    //uint8_t keylist [2] = {EMPR_KEY_1, EMPR_KEY_2};
    

}

void EINT3_IRQHandler (void){
        TextOutput_print("yes");
        GPIO_ClearInt(2,0);
    }