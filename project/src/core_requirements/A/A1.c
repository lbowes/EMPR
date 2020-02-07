#include "A1.h"

#include <mbed/Keypad.h>
#include <mbed/TextOutput.h>
#include <mbed/I2C.h>
#include <scanner/Motion.h>

#include <math.h>


void drawFullSizeCircle() {
    Motion_home();

#define GENERATED 1

#if GENERATED

    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t lastX = 0;
    uint16_t lastY = 0;

    float roundCircle = 0.0f;
    const uint16_t steps = 200;
    const uint16_t padding = 50;

    uint16_t i = 0;
    for(i = 0; i < steps; i++) {
        float sinVal = sin(i / (float)steps * 2 * M_PI);
        float cosVal = cos(i / (float)steps * 2 * M_PI);

        x = padding + (sinVal + 1.0f) / 2.0f * (EMPR_X_LIMIT - padding);
        y = padding + (cosVal + 1.0f) / 2.0f * (EMPR_Y_LIMIT - padding);

        if(lastX != x && lastY != y)
            Motion_toPoint(x, y, 0);

        lastX = x;
        lastY = y;
    }

#else

    Motion_toPoint(100, 186, 0);
    motionPauseDelay();
Motion_toPoint(101, 185, 0);
Motion_toPoint(103, 185, 0);
Motion_toPoint(104, 185, 0);
Motion_toPoint(106, 185, 0);
Motion_toPoint(107, 185, 0);
Motion_toPoint(109, 184, 0);
Motion_toPoint(110, 184, 0);
Motion_toPoint(112, 183, 0);
Motion_toPoint(113, 183, 0);
Motion_toPoint(115, 182, 0);
Motion_toPoint(116, 181, 0);
Motion_toPoint(118, 181, 0);
Motion_toPoint(119, 180, 0);
Motion_toPoint(121, 179, 0);
Motion_toPoint(122, 178, 0);
Motion_toPoint(124, 177, 0);
Motion_toPoint(125, 176, 0);
Motion_toPoint(126, 175, 0);
Motion_toPoint(128, 174, 0);
Motion_toPoint(129, 173, 0);
Motion_toPoint(130, 171, 0);
Motion_toPoint(131, 170, 0);
Motion_toPoint(133, 169, 0);
Motion_toPoint(134, 167, 0);
Motion_toPoint(135, 166, 0);
Motion_toPoint(136, 164, 0);
Motion_toPoint(137, 162, 0);
Motion_toPoint(138, 161, 0);
Motion_toPoint(139, 159, 0);
Motion_toPoint(140, 157, 0);
Motion_toPoint(141, 156, 0);
Motion_toPoint(142, 154, 0);
Motion_toPoint(143, 152, 0);
Motion_toPoint(143, 150, 0);
Motion_toPoint(144, 148, 0);
Motion_toPoint(145, 146, 0);
Motion_toPoint(145, 145, 0);
Motion_toPoint(146, 143, 0);
Motion_toPoint(147, 141, 0);
Motion_toPoint(147, 139, 0);
Motion_toPoint(148, 136, 0);
Motion_toPoint(148, 134, 0);
Motion_toPoint(148, 132, 0);
Motion_toPoint(149, 130, 0);
Motion_toPoint(149, 128, 0);
Motion_toPoint(149, 126, 0);
Motion_toPoint(149, 124, 0);
Motion_toPoint(149, 122, 0);
Motion_toPoint(149, 120, 0);
Motion_toPoint(150, 118, 0);
Motion_toPoint(149, 115, 0);
Motion_toPoint(149, 113, 0);
Motion_toPoint(149, 111, 0);
Motion_toPoint(149, 109, 0);
Motion_toPoint(149, 107, 0);
Motion_toPoint(149, 105, 0);
Motion_toPoint(148, 103, 0);
Motion_toPoint(148, 101, 0);
Motion_toPoint(148, 99, 0);
Motion_toPoint(147, 96, 0);
Motion_toPoint(147, 94, 0);
Motion_toPoint(146, 92, 0);
Motion_toPoint(145, 90, 0);
Motion_toPoint(145, 89, 0);
Motion_toPoint(144, 87, 0);
Motion_toPoint(143, 85, 0);
Motion_toPoint(143, 83, 0);
Motion_toPoint(142, 81, 0);
Motion_toPoint(141, 79, 0);
Motion_toPoint(140, 78, 0);
Motion_toPoint(139, 76, 0);
Motion_toPoint(138, 74, 0);
Motion_toPoint(137, 73, 0);
Motion_toPoint(136, 71, 0);
Motion_toPoint(135, 69, 0);
Motion_toPoint(134, 68, 0);
Motion_toPoint(133, 66, 0);
Motion_toPoint(131, 65, 0);
Motion_toPoint(130, 64, 0);
Motion_toPoint(129, 62, 0);
Motion_toPoint(128, 61, 0);
Motion_toPoint(126, 60, 0);
Motion_toPoint(125, 59, 0);
Motion_toPoint(124, 58, 0);
Motion_toPoint(122, 57, 0);
Motion_toPoint(121, 56, 0);
Motion_toPoint(119, 55, 0);
Motion_toPoint(118, 54, 0);
Motion_toPoint(116, 54, 0);
Motion_toPoint(115, 53, 0);
Motion_toPoint(113, 52, 0);
Motion_toPoint(112, 52, 0);
Motion_toPoint(110, 51, 0);
Motion_toPoint(109, 51, 0);
Motion_toPoint(107, 50, 0);
Motion_toPoint(106, 50, 0);
Motion_toPoint(104, 50, 0);
Motion_toPoint(103, 50, 0);
Motion_toPoint(101, 50, 0);
Motion_toPoint(100, 50, 0);
Motion_toPoint(98, 50, 0);
Motion_toPoint(96, 50, 0);
Motion_toPoint(95, 50, 0);
Motion_toPoint(93, 50, 0);
Motion_toPoint(92, 50, 0);
Motion_toPoint(90, 51, 0);
Motion_toPoint(89, 51, 0);
Motion_toPoint(87, 52, 0);
Motion_toPoint(86, 52, 0);
Motion_toPoint(84, 53, 0);
Motion_toPoint(83, 54, 0);
Motion_toPoint(81, 54, 0);
Motion_toPoint(80, 55, 0);
Motion_toPoint(78, 56, 0);
Motion_toPoint(77, 57, 0);
Motion_toPoint(75, 58, 0);
Motion_toPoint(74, 59, 0);
Motion_toPoint(73, 60, 0);
Motion_toPoint(71, 61, 0);
Motion_toPoint(70, 62, 0);
Motion_toPoint(69, 64, 0);
Motion_toPoint(68, 65, 0);
Motion_toPoint(66, 66, 0);
Motion_toPoint(65, 68, 0);
Motion_toPoint(64, 69, 0);
Motion_toPoint(63, 71, 0);
Motion_toPoint(62, 73, 0);
Motion_toPoint(61, 74, 0);
Motion_toPoint(60, 76, 0);
Motion_toPoint(59, 78, 0);
Motion_toPoint(58, 79, 0);
Motion_toPoint(57, 81, 0);
Motion_toPoint(56, 83, 0);
Motion_toPoint(56, 85, 0);
Motion_toPoint(55, 87, 0);
Motion_toPoint(54, 89, 0);
Motion_toPoint(54, 90, 0);
Motion_toPoint(53, 92, 0);
Motion_toPoint(52, 94, 0);
Motion_toPoint(52, 96, 0);
Motion_toPoint(51, 99, 0);
Motion_toPoint(51, 101, 0);
Motion_toPoint(51, 103, 0);
Motion_toPoint(50, 105, 0);
Motion_toPoint(50, 107, 0);
Motion_toPoint(50, 109, 0);
Motion_toPoint(50, 111, 0);
Motion_toPoint(50, 113, 0);
Motion_toPoint(50, 115, 0);
Motion_toPoint(50, 117, 0);
Motion_toPoint(50, 120, 0);
Motion_toPoint(50, 122, 0);
Motion_toPoint(50, 124, 0);
Motion_toPoint(50, 126, 0);
Motion_toPoint(50, 128, 0);
Motion_toPoint(50, 130, 0);
Motion_toPoint(51, 132, 0);
Motion_toPoint(51, 134, 0);
Motion_toPoint(51, 136, 0);
Motion_toPoint(52, 139, 0);
Motion_toPoint(52, 141, 0);
Motion_toPoint(53, 143, 0);
Motion_toPoint(54, 145, 0);
Motion_toPoint(54, 146, 0);
Motion_toPoint(55, 148, 0);
Motion_toPoint(56, 150, 0);
Motion_toPoint(56, 152, 0);
Motion_toPoint(57, 154, 0);
Motion_toPoint(58, 156, 0);
Motion_toPoint(59, 157, 0);
Motion_toPoint(60, 159, 0);
Motion_toPoint(61, 161, 0);
Motion_toPoint(62, 162, 0);
Motion_toPoint(63, 164, 0);
Motion_toPoint(64, 166, 0);
Motion_toPoint(65, 167, 0);
Motion_toPoint(66, 169, 0);
Motion_toPoint(68, 170, 0);
Motion_toPoint(69, 171, 0);
Motion_toPoint(70, 173, 0);
Motion_toPoint(71, 174, 0);
Motion_toPoint(73, 175, 0);
Motion_toPoint(74, 176, 0);
Motion_toPoint(75, 177, 0);
Motion_toPoint(77, 178, 0);
Motion_toPoint(78, 179, 0);
Motion_toPoint(80, 180, 0);
Motion_toPoint(81, 181, 0);
Motion_toPoint(83, 181, 0);
Motion_toPoint(84, 182, 0);
Motion_toPoint(86, 183, 0);
Motion_toPoint(87, 183, 0);
Motion_toPoint(89, 184, 0);
Motion_toPoint(90, 184, 0);
Motion_toPoint(92, 185, 0);
Motion_toPoint(93, 185, 0);
Motion_toPoint(95, 185, 0);
Motion_toPoint(96, 185, 0);
Motion_toPoint(98, 185, 0);

#endif
    Motion_neutraliseAll();
}


void traceSquareBoundary() {
    Motion_home();
    motionPauseDelay();

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
    motionPauseDelay();
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


void motionPauseDelay() {
    int i, j, count = 0;
    for(i = 0; i < 8000; i++) {
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