#include "scanner/ColourSensor.h"
#include <mbed/I2C.h>
#include <mbed/Delay.h>
#include <mbed/Constants.h>
#include <stdio.h>
#include <math.h>
#include <scanner/Motion.h>
#include <scanner/Vector3D.h>
#include <stdbool.h>
#include <scanner/LimitSwitch.h>
Vector3D ScanPos;
LimitSwitch penSwitch;


void Drawing_init() {
    Motion_init();
    ColourSensor_init();
    Motion_moveTo(0, 0, 250); // 600 is high, 250 is close, under will vary shades.     
    penSwitch.deviceAddress = 0X3C;
    penSwitch.stateBitPos = 3;
}

void Drawing_penToHead() {
    ScanPos = Motion_getCurrentPos();
    Motion_moveTo(ScanPos.x, ScanPos.y + 36, ScanPos.z); 
}

bool Drawing_penState() {
    ScanPos = Motion_getCurrentPos();
    if (ScanPos.z < 250) {
        return 1;
    }

}
void Drawing_penUp() {
    ScanPos = Motion_getCurrentPos();
    Motion_moveTo(ScanPos.x, ScanPos.y, 300);
}

void Drawing_penDownLight() {
    //Motion_moveBy(0, 0, 200);
    //while (!LimitSwitch_isDown(&penSwitch)) {
        //Motion_moveBy(0, 0, -1);
    //}
    //Motion_moveBy(0, 0, 70);
    ScanPos = Motion_getCurrentPos();
    Motion_moveTo(ScanPos.x, ScanPos.y, 150);
}

void Drawing_penDownDark() {
    ScanPos = Motion_getCurrentPos();
    Motion_moveTo(ScanPos.x, ScanPos.y, 0);
}
