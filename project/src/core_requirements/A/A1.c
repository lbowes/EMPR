#include "A1.h"

#include <mbed/Keypad.h>
#include <mbed/TextOutput.h>
#include <mbed/I2C.h>
#include <scanner/Motion.h>
#include <scanner/Vector3D.h>

#include <math.h>


static void motionPauseDelay() {
    int i, j, count = 0;
    for(i = 0; i < 8000; i++) {
        for(j = 0; j < 1000; j++)
            count++;
    }
}


static void drawFullSizeCircle() {
    Motion_home();

    Vector3D pos;
    Vector3D lastPos;

    float roundCircle = 0.0f;
    const uint16_t steps = 500;
    const uint16_t padding = 80;

    uint16_t i = 0;
    for(i = 0; i < steps; i++) {
        float sinVal = sin(i / (float)steps * 2 * M_PI);
        float cosVal = cos(i / (float)steps * 2 * M_PI);

        pos.x = padding + (sinVal + 1.0f) / 2.0f * (EMPR_X_LIMIT - padding);
        pos.y = padding + (cosVal + 1.0f) / 2.0f * (EMPR_X_LIMIT - padding);

        Motion_moveTo(pos.x, pos.y, 0);

        lastPos = pos;
    }

    Motion_neutraliseAllAxes();
}


static void traceSquareBoundary() {
    Motion_home();
    motionPauseDelay();

    Motion_moveTo(0, 0, 0);
    Motion_moveTo(0, EMPR_Y_LIMIT, 0);
    Motion_moveTo(EMPR_X_LIMIT, EMPR_Y_LIMIT, 0);
    Motion_moveTo(EMPR_X_LIMIT, 0, 0);

    Motion_neutraliseAllAxes();
}


static void demoZAxis() {
    Motion_home();

    Motion_moveTo(0, 0, 500);
    motionPauseDelay();
    Motion_moveTo(0, 0, 0);

    Motion_neutraliseAllAxes();
}


static void menuOptionDelay() {
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

    func requirementDemos[3] = {
        &drawFullSizeCircle,
        &traceSquareBoundary,
        &demoZAxis
    };

    static const char* menuLabels[3] = {
        "1. Trace circle",
        "2. Trace square",
        "3. Demo Z axis"
    };

    int activeReqIdx = 0;

    while(1) {
        LCDDisplay_print(menuLabels[activeReqIdx], LINE_1);
        LCDDisplay_print("<[1]        [4]>", LINE_2);

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