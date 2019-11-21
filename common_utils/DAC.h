#ifndef EMPR_DAC_UTILS_H_
#define EMPR_DAC_UTILS_H_

#include <stdint.h>

void DAC_set_mVoltage(uint32_t set_Voltage);

void DAC_init(void);

void DAC_set_maxVoltage(void);

void DAC_set_low(void);

void DAC_off(void);

#endif // EMPR_DAC_UTILS_H_