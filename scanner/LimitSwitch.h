#ifndef EMPR_LIMIT_SWITCH_
#define EMPR_LIMIT_SWITCH_

#include <stdint.h>
#include <stdbool.h>


typedef struct {
    uint32_t deviceAddress; // i2c device address of the switch
    uint32_t stateBitPos;   // Bit position in `deviceAddress` storing switch state
} LimitSwitch;

bool LimitSwitch_isDown(LimitSwitch* lSwitch);


#endif // EMPR_LIMIT_SWITCH_
