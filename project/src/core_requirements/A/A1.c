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

#define GENERATED 1

#if GENERATED

    Vector3D pos;
    Vector3D lastPos;

    float roundCircle = 0.0f;
    const uint16_t steps = 200;
    const uint16_t padding = 50;

    uint16_t i = 0;
    for(i = 0; i < steps; i++) {
        float sinVal = sin(i / (float)steps * 2 * M_PI);
        float cosVal = cos(i / (float)steps * 2 * M_PI);

        pos.x = padding + (sinVal + 1.0f) / 2.0f * (EMPR_X_LIMIT - padding);
        pos.y = padding + (cosVal + 1.0f) / 2.0f * (EMPR_X_LIMIT - padding);

        if(lastX != x && lastY != y)
            Motion_moveTo(pos.x, pos.y, 0);

        lastPos = pos;
    }

#else

    Motion_moveTo(125, 200, 0);
    Motion_moveTo(127, 199, 0);
    Motion_moveTo(129, 199, 0);
    Motion_moveTo(132, 199, 0);
    Motion_moveTo(134, 199, 0);
    Motion_moveTo(136, 199, 0);
    Motion_moveTo(139, 198, 0);
    Motion_moveTo(141, 198, 0);
    Motion_moveTo(143, 197, 0);
    Motion_moveTo(145, 197, 0);
    Motion_moveTo(148, 196, 0);
    Motion_moveTo(150, 195, 0);
    Motion_moveTo(152, 194, 0);
    Motion_moveTo(154, 193, 0);
    Motion_moveTo(156, 192, 0);
    Motion_moveTo(159, 191, 0);
    Motion_moveTo(161, 190, 0);
    Motion_moveTo(163, 189, 0);
    Motion_moveTo(165, 188, 0);
    Motion_moveTo(167, 187, 0);
    Motion_moveTo(169, 185, 0);
    Motion_moveTo(170, 184, 0);
    Motion_moveTo(172, 182, 0);
    Motion_moveTo(174, 181, 0);
    Motion_moveTo(176, 179, 0);
    Motion_moveTo(178, 178, 0);
    Motion_moveTo(179, 176, 0);
    Motion_moveTo(181, 174, 0);
    Motion_moveTo(182, 172, 0);
    Motion_moveTo(184, 170, 0);
    Motion_moveTo(185, 169, 0);
    Motion_moveTo(187, 167, 0);
    Motion_moveTo(188, 165, 0);
    Motion_moveTo(189, 163, 0);
    Motion_moveTo(190, 161, 0);
    Motion_moveTo(191, 159, 0);
    Motion_moveTo(192, 156, 0);
    Motion_moveTo(193, 154, 0);
    Motion_moveTo(194, 152, 0);
    Motion_moveTo(195, 150, 0);
    Motion_moveTo(196, 148, 0);
    Motion_moveTo(197, 145, 0);
    Motion_moveTo(197, 143, 0);
    Motion_moveTo(198, 141, 0);
    Motion_moveTo(198, 139, 0);
    Motion_moveTo(199, 136, 0);
    Motion_moveTo(199, 134, 0);
    Motion_moveTo(199, 132, 0);
    Motion_moveTo(199, 129, 0);
    Motion_moveTo(199, 127, 0);
    Motion_moveTo(200, 125, 0);
    Motion_moveTo(199, 122, 0);
    Motion_moveTo(199, 120, 0);
    Motion_moveTo(199, 117, 0);
    Motion_moveTo(199, 115, 0);
    Motion_moveTo(199, 113, 0);
    Motion_moveTo(198, 110, 0);
    Motion_moveTo(198, 108, 0);
    Motion_moveTo(197, 106, 0);
    Motion_moveTo(197, 104, 0);
    Motion_moveTo(196, 101, 0);
    Motion_moveTo(195, 99, 0);
    Motion_moveTo(194, 97, 0);
    Motion_moveTo(193, 95, 0);
    Motion_moveTo(192, 93, 0);
    Motion_moveTo(191, 90, 0);
    Motion_moveTo(190, 88, 0);
    Motion_moveTo(189, 86, 0);
    Motion_moveTo(188, 84, 0);
    Motion_moveTo(187, 82, 0);
    Motion_moveTo(185, 80, 0);
    Motion_moveTo(184, 79, 0);
    Motion_moveTo(182, 77, 0);
    Motion_moveTo(181, 75, 0);
    Motion_moveTo(179, 73, 0);
    Motion_moveTo(178, 71, 0);
    Motion_moveTo(176, 70, 0);
    Motion_moveTo(174, 68, 0);
    Motion_moveTo(172, 67, 0);
    Motion_moveTo(170, 65, 0);
    Motion_moveTo(169, 64, 0);
    Motion_moveTo(167, 62, 0);
    Motion_moveTo(165, 61, 0);
    Motion_moveTo(163, 60, 0);
    Motion_moveTo(161, 59, 0);
    Motion_moveTo(159, 58, 0);
    Motion_moveTo(156, 57, 0);
    Motion_moveTo(154, 56, 0);
    Motion_moveTo(152, 55, 0);
    Motion_moveTo(150, 54, 0);
    Motion_moveTo(148, 53, 0);
    Motion_moveTo(145, 52, 0);
    Motion_moveTo(143, 52, 0);
    Motion_moveTo(141, 51, 0);
    Motion_moveTo(139, 51, 0);
    Motion_moveTo(136, 50, 0);
    Motion_moveTo(134, 50, 0);
    Motion_moveTo(132, 50, 0);
    Motion_moveTo(129, 50, 0);
    Motion_moveTo(127, 50, 0);
    Motion_moveTo(125, 50, 0);
    Motion_moveTo(122, 50, 0);
    Motion_moveTo(120, 50, 0);
    Motion_moveTo(117, 50, 0);
    Motion_moveTo(115, 50, 0);
    Motion_moveTo(113, 50, 0);
    Motion_moveTo(110, 51, 0);
    Motion_moveTo(108, 51, 0);
    Motion_moveTo(106, 52, 0);
    Motion_moveTo(104, 52, 0);
    Motion_moveTo(101, 53, 0);
    Motion_moveTo(99, 54, 0);
    Motion_moveTo(97, 55, 0);
    Motion_moveTo(95, 56, 0);
    Motion_moveTo(93, 57, 0);
    Motion_moveTo(90, 58, 0);
    Motion_moveTo(88, 59, 0);
    Motion_moveTo(86, 60, 0);
    Motion_moveTo(84, 61, 0);
    Motion_moveTo(82, 62, 0);
    Motion_moveTo(80, 64, 0);
    Motion_moveTo(79, 65, 0);
    Motion_moveTo(77, 67, 0);
    Motion_moveTo(75, 68, 0);
    Motion_moveTo(73, 70, 0);
    Motion_moveTo(71, 71, 0);
    Motion_moveTo(70, 73, 0);
    Motion_moveTo(68, 75, 0);
    Motion_moveTo(67, 77, 0);
    Motion_moveTo(65, 79, 0);
    Motion_moveTo(64, 80, 0);
    Motion_moveTo(62, 82, 0);
    Motion_moveTo(61, 84, 0);
    Motion_moveTo(60, 86, 0);
    Motion_moveTo(59, 88, 0);
    Motion_moveTo(58, 90, 0);
    Motion_moveTo(57, 93, 0);
    Motion_moveTo(56, 95, 0);
    Motion_moveTo(55, 97, 0);
    Motion_moveTo(54, 99, 0);
    Motion_moveTo(53, 101, 0);
    Motion_moveTo(52, 104, 0);
    Motion_moveTo(52, 106, 0);
    Motion_moveTo(51, 108, 0);
    Motion_moveTo(51, 110, 0);
    Motion_moveTo(50, 113, 0);
    Motion_moveTo(50, 115, 0);
    Motion_moveTo(50, 117, 0);
    Motion_moveTo(50, 120, 0);
    Motion_moveTo(50, 122, 0);
    Motion_moveTo(50, 124, 0);
    Motion_moveTo(50, 127, 0);
    Motion_moveTo(50, 129, 0);
    Motion_moveTo(50, 132, 0);
    Motion_moveTo(50, 134, 0);
    Motion_moveTo(50, 136, 0);
    Motion_moveTo(51, 139, 0);
    Motion_moveTo(51, 141, 0);
    Motion_moveTo(52, 143, 0);
    Motion_moveTo(52, 145, 0);
    Motion_moveTo(53, 148, 0);
    Motion_moveTo(54, 150, 0);
    Motion_moveTo(55, 152, 0);
    Motion_moveTo(56, 154, 0);
    Motion_moveTo(57, 156, 0);
    Motion_moveTo(58, 159, 0);
    Motion_moveTo(59, 161, 0);
    Motion_moveTo(60, 163, 0);
    Motion_moveTo(61, 165, 0);
    Motion_moveTo(62, 167, 0);
    Motion_moveTo(64, 169, 0);
    Motion_moveTo(65, 170, 0);
    Motion_moveTo(67, 172, 0);
    Motion_moveTo(68, 174, 0);
    Motion_moveTo(70, 176, 0);
    Motion_moveTo(71, 178, 0);
    Motion_moveTo(73, 179, 0);
    Motion_moveTo(75, 181, 0);
    Motion_moveTo(77, 182, 0);
    Motion_moveTo(79, 184, 0);
    Motion_moveTo(80, 185, 0);
    Motion_moveTo(82, 187, 0);
    Motion_moveTo(84, 188, 0);
    Motion_moveTo(86, 189, 0);
    Motion_moveTo(88, 190, 0);
    Motion_moveTo(90, 191, 0);
    Motion_moveTo(93, 192, 0);
    Motion_moveTo(95, 193, 0);
    Motion_moveTo(97, 194, 0);
    Motion_moveTo(99, 195, 0);
    Motion_moveTo(101, 196, 0);
    Motion_moveTo(104, 197, 0);
    Motion_moveTo(106, 197, 0);
    Motion_moveTo(108, 198, 0);
    Motion_moveTo(110, 198, 0);
    Motion_moveTo(113, 199, 0);
    Motion_moveTo(115, 199, 0);
    Motion_moveTo(117, 199, 0);
    Motion_moveTo(120, 199, 0);
    Motion_moveTo(122, 199, 0);

#endif
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