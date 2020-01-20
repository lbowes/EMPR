#include "LimitSwitch.h"
#include <common_utils/I2C.h>


bool LimitSwitch_isDown(LimitSwitch* lSwitch) {
    uint8_t switchStateByte = 0;
    i2c_receiveDataFrom(lSwitch->deviceAddress, &switchStateByte, 1);
    return (~switchStateByte & (1 << lSwitch->stateBitPos));
}