#include "A2.h"

#include <scanner/Motion.h>
#include <scanner/Vector3D.h>
#include <mbed/LCDDisplay.h>
#include <mbed/Constants.h>
#include <mbed/Keypad.h>
#include <mbed/TextOutput.h>
#include <mbed/I2C.h>
#include <mbed/Delay.h>
#include <mbed/LCDMenu.h>
#include <scanner/Colour.h>
#include <scanner/Drawing.h>
#include <math.h>
#include <scanner/ColourSensor.h>

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
    ColourSensor_init();

    // Start the sensor from some position near the centre of the platform, and move left and right,
    // up and down until either an edge is detected or the platform limits are reached.
    Colour reading = ColourSensor_read();
    Vector3D platformCentre;
    platformCentre.x = (EMPR_X_LIMIT / 2);
    platformCentre.y = (EMPR_Y_LIMIT / 2);
    platformCentre.z = 0;
    Motion_moveTo(platformCentre.x, platformCentre.y, platformCentre.z);
    uint16_t xEdge1 = 0;
    TextOutput_println("Gone to middle");
    while(1) {
        TextOutput_println("Start 1");
        Motion_moveBy(1, 0, 0);
        reading = ColourSensor_read();

        if((reading.clear > 20) || ((Motion_getCurrentPos().x) == EMPR_X_LIMIT)) {
            xEdge1 = Motion_getCurrentPos().x;
            break;
        }
    }

    Motion_moveTo(platformCentre.x, platformCentre.y, platformCentre.z);

    uint16_t xEdge2 = 0;
    while(1) {
        TextOutput_println("Start 2");
        Motion_moveBy(-1, 0, 0);
        reading = ColourSensor_read();
        if((reading.clear > 20) || ((Motion_getCurrentPos().x)) == 0){
            xEdge2 = Motion_getCurrentPos().x;
            break;
        }
    }

    Motion_moveTo(platformCentre.x, platformCentre.y, platformCentre.z);

    uint16_t yEdge1 = 0;
    while(1) {
        TextOutput_println("Start 3");
        Motion_moveBy(0, 1, 0);

        reading = ColourSensor_read();
        if((reading.clear > 15) || ((Motion_getCurrentPos().x) == (EMPR_Y_LIMIT- 50))) {
            yEdge1 = Motion_getCurrentPos().y;
            break;
        }
    }

    Motion_moveTo(platformCentre.x, platformCentre.y, platformCentre.z);

    uint16_t yEdge2 = 0;
    while(1) {
        TextOutput_println("Start 4");
        Motion_moveBy(0, -1, 0);

        reading = ColourSensor_read();
        if(((reading.clear > 20) || ((Motion_getCurrentPos().y) == 0))) {
            yEdge2 = Motion_getCurrentPos().y;
            break;
        }
        
    }
    Motion_neutraliseAllAxes();
    Motion_moveTo(xEdge2, yEdge1, 0);
    TextOutput_printInteger(xEdge1);
    TextOutput_printInteger(xEdge2);
    TextOutput_printInteger(yEdge1);
    TextOutput_printInteger(yEdge2);
    Motion_moveTo(xEdge1, yEdge1, 0);
    Motion_moveTo(xEdge1, yEdge2, 0);
    Motion_moveTo(xEdge2, yEdge2, 0);
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
