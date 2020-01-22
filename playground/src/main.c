#include <scanner/Motion.h>
#include <mbed/I2C.h>
#include <mbed/LEDs.h>

#include <math.h>

int main() {
    i2c_init();
    Motion_init();
    LEDs_init();

    //Motion_moveAxisToPos(EMPR_X_AXIS, 180);

    uint32_t count = 0;
    float sinVal = 0.0f;
    float cosVal = 0.0f;

    while(1) {
        sinVal = sin((float)count / 20.0f);
        cosVal = cos((float)count / 20.0f);

        //Motion_moveAxisToPos(EMPR_Y_AXIS, 120 + sinVal * 40);
        //Motion_moveAxisToPos(EMPR_X_AXIS, 100 + cosVal * 40);

        //LEDs_debugBinary((count / 5000) % 16);
        count++;
    }

    //uint8_t t = 0;
    //for(t = 0; t < 20; t++) {
    //    Motion_moveAxisToPos(EMPR_X_AXIS, 10);
    //    Motion_moveAxisToPos(EMPR_X_AXIS, 180);
    //}

    //Motion_moveAxisToPos(EMPR_X_AXIS, 0);

    return 0;
}