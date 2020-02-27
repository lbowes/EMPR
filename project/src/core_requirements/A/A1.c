#include "A1.h"

#include <mbed/Keypad.h>
#include <mbed/TextOutput.h>
#include <mbed/I2C.h>
#include <mbed/Delay.h>
#include <mbed/LCDMenu.h>
#include <mbed/LCDDisplay.h>
#include <scanner/Motion.h>
#include <scanner/Vector3D.h>

#include <math.h>


static void traceFullSizeCircle();
static void traceSquareBoundary();
static void demoZAxis();


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

    LCDMenu motionOptions = LCDMenu_create();

    LCDMenu_addItem(&motionOptions, "Trace circle", &traceFullSizeCircle);
    LCDMenu_addItem(&motionOptions, "Trace square", &traceSquareBoundary);
    LCDMenu_addItem(&motionOptions, "Demo Z axis", &demoZAxis);

    LCDMenu_run(&motionOptions);

    // TODO: Work out why this is causing a crash
    //LCDDisplay_print("motion", 0);
    //LCDMenu_destroy(&motionOptions);
    //LCDDisplay_print("motion end", 1);
}



static void traceFullSizeCircle() {
    Motion_home();

    Vector3D pos;
    const uint16_t steps = 500;
    const uint16_t padding = 0;
    uint16_t i = 0;

    for(i = 0; i < steps; i++) {
        float sinVal = sin(i / (float)steps * 2 * M_PI);
        float cosVal = cos(i / (float)steps * 2 * M_PI);

        pos.x = padding + (sinVal + 1.0f) / 2.0f * (EMPR_X_LIMIT - padding);
        pos.y = padding + (cosVal + 1.0f) / 2.0f * (EMPR_X_LIMIT - padding);

        Motion_moveTo(pos.x, pos.y, 0);
    }

    Motion_neutraliseAllAxes();
}


static void traceSquareBoundary() {
    // TODO: This function is not technically correct (traces full range of motion, rather than the
    // boundaries of the platform)

    // The requirement states:
    //    The X-Y functional test will include scan patterns:
    //    • (b) A square at the __boundaries of the platform__

    // If there's time, the scan head should trace the platform boundaries, rather
    // the limits of each axis. Quite similar to requirement A2.

    Motion_home();

    Motion_moveTo(0, EMPR_Y_LIMIT, 0);
    Motion_moveTo(EMPR_X_LIMIT, EMPR_Y_LIMIT, 0);
    Motion_moveTo(EMPR_X_LIMIT, 0, 0);
    Motion_moveTo(0, 0, 0);

    Motion_neutraliseAllAxes();
}


static void demoZAxis() {
    Motion_home();

    Motion_moveTo(0, 0, 500);
    Delay_ms(1000);
    Motion_moveTo(0, 0, 0);

    Motion_neutraliseAllAxes();
}