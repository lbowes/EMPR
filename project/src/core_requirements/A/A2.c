#include "A2.h"

#include <scanner/Motion.h>
#include <scanner/Vector3D.h>
#include <mbed/LCDDisplay.h>
#include <mbed/Constants.h>


static void exploreEdgeBoundaries();
static void displayBoundsOnLCD();

/*
 * The X-Y Platform should perform a boundary detection setup procedure, such
 * that the edges of the platform are determined automatically by stepping the
 * motors and monitoring the microswitches.
 * • The platform will explore the edge boundaries
 * • The edge boundaries will be displayed on LCD at the end of the search.
 * • Stepping resolution should be at least 16 distinct positions per X/Yaxis.
*/
void A2() {
    exploreEdgeBoundaries();
    displayBoundsOnLCD();
}


static void exploreEdgeBoundaries() {
    Motion_home();
    Motion_localisePlatform();
    Motion_neutraliseAllAxes();
}


static void displayBoundsOnLCD() {
    LCDDisplay_init();

    char platformPos[16];
    Vector3D platPos = Motion_getPlatformOrigin();
    sprintf(platformPos, "Pos: %i, %i", platPos.x, platPos.y);

    char platformDims[16];
    Vector3D platDims = Motion_getPlatformDimensions();
    sprintf(platformDims, "Dims: %i, %i", platDims.x, platDims.y);

    LCDDisplay_print(platformPos, EMPR_LINE_1);
    LCDDisplay_print(platformDims, EMPR_LINE_2);
}