#include "A2.h"

#include <scanner/Motion.h>
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

    // TODO: Trace the boundary of the platform once its been determined by the functions
}


static void displayBoundsOnLCD() {
    LCDDisplay_init();

    // This function needs to display the information contained in the `Platform` struct in the `Motion` module.


    // TODO: Display the boundaries of the platform on the LCD display
}