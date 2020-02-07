#include "A1.h"

#include <mbed/Keypad.h>
#include <mbed/TextOutput.h>
#include <mbed/I2C.h>
#include <scanner/Motion.h>

#include <math.h>


void drawFullSizeCircle() {
    Motion_home();

    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t lastX = 0;
    uint16_t lastY = 0;

    float roundCircle = 0.0f;
    const uint16_t steps = 1000;
    const uint16_t padding = 50;

    uint16_t i = 0;
    for(i = 0; i < steps; i++) {
        float sinVal = sin(i / (float)steps * 2 * M_PI);
        float cosVal = cos(i / (float)steps * 2 * M_PI);

        //TextOutput_printInteger(sinVal * 100);
        x = padding + (sinVal + 1.0f) / 2.0f * (EMPR_X_LIMIT - padding);
        y = padding + (cosVal + 1.0f) / 2.0f * (EMPR_Y_LIMIT - padding);

        if(lastX != x && lastY != y) {
            Motion_moveAxisToPos(EMPR_X_AXIS, x);
            Motion_moveAxisToPos(EMPR_Y_AXIS, y);
            //Motion_toPoint(x, y, 0);
        }

        lastX = x;
        lastY = y;
    }

    Motion_neutraliseAll();
}


void traceSquareBoundary() {
    Motion_home();

    Motion_moveAxisToPos(EMPR_X_AXIS, EMPR_X_LIMIT);
    Motion_moveAxisToPos(EMPR_Y_AXIS, EMPR_Y_LIMIT);
    Motion_moveAxisToPos(EMPR_X_AXIS, 0);
    Motion_moveAxisToPos(EMPR_Y_AXIS, 0);

    Motion_neutraliseAll();
}


void demoZAxis() {
    Motion_home();

    Motion_moveAxisToPos(EMPR_Z_AXIS, 0);
    Motion_moveAxisToPos(EMPR_Z_AXIS, 500);
    Motion_moveAxisToPos(EMPR_Z_AXIS, 0);

    Motion_neutraliseAll();
}


void menuOptionDelay() {
    int i, j, count = 0;
    for(i = 0; i < 1000; i++) {
        for(j = 0; j < 1000; j++)
            count++;
    }
}


/*
 * A scanning API should be written, to permit control of all three stepper motors.
 * It should be possible to demonstrate its functionality by performing test
 * patterns as defined below,
 * • The stepper motors should be operated via the I2C ports provided,
 * • Care should be taken to ensure that microswitch end-stops prevent motor
 * overun and belt-strain at the edges of the scanning platform.
 * • The X-Y functional test will include scan patterns:
 * • (a) A full-size circle
 * • (b) A square at the boundaries of the platform
 * • (c) You should be able to demonstrate that Z axis can be moved up and
 * down.
 * • Tests should be selectable via a user interface on the MBED board.
*/
void A1() {
    i2c_init();
    Keypad_init();
    LCDDisplay_init();
    TextOutput_init();
    Motion_init();

    typedef void (*func)(void);
    func requirementDemos[3] = { &drawFullSizeCircle, &traceSquareBoundary, &demoZAxis };
    static const char* menuLabels[3] = { "1. Trace circle", "2. Trace square", "3. Demo Z axis" };

    int activeReqIdx = 0;

    while(1) {
        LCDDisplay_print(menuLabels[activeReqIdx], LINE_1);
        LCDDisplay_print("<-[1]-[4]->", LINE_2);

        // Execute test shown
        if(Keypad_isKeyDown(EMPR_KEY_HASH))
            requirementDemos[activeReqIdx]();

        // Shift menu up
        if(Keypad_isKeyDown(EMPR_KEY_1)) {
            activeReqIdx--;
            if(activeReqIdx < 0)
                activeReqIdx = 2;
        }

        // Shift menu down
        if(Keypad_isKeyDown(EMPR_KEY_4)) {
            activeReqIdx++;
            if(activeReqIdx > 2)
                activeReqIdx = 0;
        }

        // Move on to A2
        if(Keypad_isKeyDown(EMPR_KEY_ASTERISK))
            return;

        menuOptionDelay();
    }
}