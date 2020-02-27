#ifndef EMPR_MOTION_H_
#define EMPR_MOTION_H_

#include "Vector3D.h"


void Motion_init();
void Motion_localisePlatform();
void Motion_neutraliseAllAxes();
void Motion_moveTo(int x, int y, int z);
void Motion_moveBy(int deltaX, int deltaY, int deltaZ);
Vector3D Motion_getCurrentPos();
void Motion_home();
void Motion_moveAxisToLimit(uint8_t axisId);

#endif // EMPR_MOTION_H_
