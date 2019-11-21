#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_pinsel.h"
#include <stdint.h>
#include <math.h>

PINSEL_CFG_Type DacPinCfg;


void DAC_init(void) {
    // Pin 26 ; 18 On Header board configured.
    DacPinCfg.Funcnum = 2;
    DacPinCfg.OpenDrain = 0;
    DacPinCfg.Pinmode = 0;
    DacPinCfg.Pinnum = 26;
    DacPinCfg.Portnum = 0;
    PINSEL_ConfigPin(&DacPinCfg);
    DAC_Init(LPC_DAC);
}


void DAC_set_maxVoltage(void) {
    uint32_t dac_Value = 0x3FF;
    DAC_UpdateValue(LPC_DAC, dac_Value);
}

void DAC_off(void) {
    DacPinCfg.Funcnum = 0;
    PINSEL_ConfigPin(&DacPinCfg);
}


void DAC_set_low(void) {
    DAC_UpdateValue(LPC_DAC, 0);
}
void DAC_set_mVoltage(uint32_t set_Voltage) {
    if (set_Voltage > 3069) {
        set_Voltage = 3069;
    }
    //Voltage DAC provides is roughly 20-40mv above given value.
    set_Voltage = set_Voltage - 20;
    uint32_t dac_Value = floor(set_Voltage / 3);
    DAC_UpdateValue(LPC_DAC, dac_Value);

}


