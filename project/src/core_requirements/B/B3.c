#include "B3.h"

#include <mbed/LCDMenu.h>
#include <mbed/Constants.h>
#include <scanner/Motion.h>
#include <scanner/Vector3D.h>
#include <scanner/ColourSensor.h>



static void findHighest(uint8_t colourComponent);
static void findRed();
static void findGreen();
static void findBlue();


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
    LCDMenu colourSelectMenu;
    colourSelectMenu = LCDMenu_create();
    LCDMenu_addItem(&colourSelectMenu, "Find RED", &findRed);
    LCDMenu_addItem(&colourSelectMenu, "Find GREEN", &findGreen);
    LCDMenu_addItem(&colourSelectMenu, "Find BLUE", &findBlue);
    LCDMenu_run(&colourSelectMenu);
    LCDMenu_destroy(&colourSelectMenu);
}




static void findRed() {
    findHighest(1);
}


static void findGreen() {
    findHighest(2);
}


static void findBlue() {
    findHighest(4);
}

static void findHighest(uint8_t colourComponent) {
    // Keep track of the last point that was scanned, and what colour it was
    uint8_t searchSpaceSize_stepsx = 50;
    uint8_t searchSpaceSize_stepsy = 234;
    uint8_t search_xoffset = 29;
    uint8_t search_yoffset = 0;
    Vector3D currentPoint;
    Vector3D closestPoint;
    uint8_t currentReading;
    uint8_t closestReading = 0;
    // " • A raster scan will be performed"
    uint16_t x = 0;
    uint16_t y = 0;
    for(x = search_xoffset; x < searchSpaceSize_stepsx + search_xoffset; x+=5) {
        for(y = search_yoffset; y < searchSpaceSize_stepsy + search_yoffset; y+=5) {
            Motion_moveTo(x, y, 0);
            Motion_neutraliseAllAxes();
            if(colourComponent == 1) {
                currentReading = ColourSensor_read().r;
            }
            else if(colourComponent == 2){
                currentReading = ColourSensor_read().g;
            }
            else if(colourComponent == 4){
                currentReading = ColourSensor_read().b;
            }

            // "• The highest reading for R, G or B (as selected by user) will be located."
            if(currentReading > closestReading) {
                currentPoint = Motion_getCurrentPos();
                closestReading = currentReading;
                closestPoint = currentPoint;
            }
        }
    }
    Motion_moveTo(closestPoint.x, closestPoint.y, closestPoint.z);

}
