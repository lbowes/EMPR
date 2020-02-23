#include "B3.h"

#include <mbed/LCDMenu.h>
#include <mbed/Constants.h>
#include <scanner/Motion.h>
#include <scanner/Vector3D.h>
#include <scanner/ColourSensor.h>


static Vector3D platformCentre;

static void calcPlatformCentre();
static void findHighest(uint8_t colourComponent);
static void findRed();
static void findGreen();
static void findBlue();

typedef enum {
    RED = 0,
    GREEN,
    BLUE
} ColourComponent;


/*
* Color Search: Allows a point in an image of a certain colour specification to be
* located.
* • A raster scan will be performed,
* • The highest reading for R, G or B (as selected by user) will be located.
* • The head will move to that final position once it has been identified.
* For the demonstration you can scan a smaller region than the whole bed, a minimum
* of 2x2 inches, if a full scan may take an inconveniently long time.
*/
void B3() {
    ColourSensor_init();
    Motion_init();
    calcPlatformCentre();

    LCDMenu colourSelectMenu;

    colourSelectMenu = LCDMenu_create();

    LCDMenu_addItem(&colourSelectMenu, "Find RED", &findRed);
    LCDMenu_addItem(&colourSelectMenu, "Find GREEN", &findGreen);
    LCDMenu_addItem(&colourSelectMenu, "Find BLUE", &findBlue);

    LCDMenu_run(&colourSelectMenu);

    LCDMenu_destroy(&colourSelectMenu);
}


static void calcPlatformCentre() {
    platformCentre.x = EMPR_X_LIMIT / 2;
    platformCentre.y = EMPR_Y_LIMIT / 2;
    platformCentre.z = 0;
}


static void findRed() {
    findHighest(RED);
}


static void findGreen() {
    findHighest(GREEN);
}


static void findBlue() {
    findHighest(BLUE);
}


static void findHighest(uint8_t colourComponent) {
    const uint8_t searchSpaceSize_steps = 80;
    const uint8_t halfSearchSpaceSize_steps = searchSpaceSize_steps / 2;

    // Keep track of the last point that was scanned, and what colour it was
    Vector3D currentPoint;
    Vector3D closestPoint;
    uint8_t currentReading;
    uint8_t closestReading;

    Motion_moveTo(platformCentre.x, platformCentre.y, platformCentre.z);

    // " • A raster scan will be performed"
    uint16_t x = 0;
    uint16_t y = 0;
    for(x = 0; x < searchSpaceSize_steps; x++) {
        for(y = 0; y < searchSpaceSize_steps; y++) {
            currentPoint.x = platformCentre.x + x - halfSearchSpaceSize_steps;
            currentPoint.y = platformCentre.y + y - halfSearchSpaceSize_steps;

            Motion_moveTo(currentPoint.x, currentPoint.y, 0);

            if(colourComponent == RED)
                currentReading = ColourSensor_read().r;
            else if(colourComponent == GREEN)
                currentReading = ColourSensor_read().g;
            else if(colourComponent == BLUE)
                currentReading = ColourSensor_read().b;

            // "• The highest reading for R, G or B (as selected by user) will be located."
            if(currentReading > closestReading) {
                closestReading = currentReading;
                closestPoint = currentPoint;
            }
        }
    }

    // "• The head will move to that final position once it has been identified."
    Motion_moveTo(closestPoint.x, closestPoint.y, 0);
}