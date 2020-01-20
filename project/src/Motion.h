#ifndef EMPR_MOTION_H_
#define EMPR_MOTION_H_

#include <stdint.h>
#include <stdbool.h>

#include "LimitSwitch.h"
#include <common_utils/Constants.h>

typedef struct {
    uint32_t deviceAddress;  // i2c device address of the motor
    bool nibble;             // Which nibble of `deviceAddress` corresponds to this motor (EMPR_<side>)
} Motor;

typedef struct {
    Motor motor;
    LimitSwitch limitSwitch;
    uint16_t maxSteps;       // Maximum number of 'motor steps' that can be moved from the limit switch
    uint16_t currentStepPos; // Current number of 'motor steps' away from the limit switch (0 - EMPR_<axis>_MOTOR_MAX_STEPS inc)
} Axis;

void Motion_init();
void Motion_moveAxisToPos(uint8_t axis, uint16_t pos);
void Motion_toPoint(uint16_t x, uint16_t y, uint16_t z);
void Motion_home();


#endif
