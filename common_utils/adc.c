#include <LPC17xx.h>
#include <lpc_types.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_adc.h>
#include <common_utils/TextOutput.h>
#include <stdio.h>

void adc_init(void)
{
    PINSEL_CFG_Type pin_config;
    pin_config.Funcnum = PINSEL_FUNC_1;
    pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;
    pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
    pin_config.Portnum = 0;
    pin_config.Pinnum = 24;

    PINSEL_ConfigPin(&pin_config);

    ADC_Init(LPC_ADC, 70000);

    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_1, ENABLE);

    ADC_BurstCmd(LPC_ADC, ENABLE);

    NVIC_EnableIRQ(ADC_IRQn);

    __enable_irq();


}

void ADC_IRQHandler(void)
{
    
    
    uint16_t anologue_val = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_1);
    char buffer[100];
    sprintf(buffer, "%d",anologue_val);
    TextOutput_print(buffer);


}