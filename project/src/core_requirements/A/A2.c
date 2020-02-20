#include "A2.h"

#include <scanner/Motion.h>
#include <mbed/LCDDisplay.h>
#include <mbed/Constants.h>


// Changes to be made to the `Motion` module
// =========================================
// * Add some way of detecting the boundaries of the platform (see below).
//   This can be used when developing the scan patterns. The sensor head only needs to move around inside the bounds of
//   the platform for scanning purposes.

// * The platform should be represented internally as two vectors:
//   - The [x,y] position of the platform's 'origin' relative to the home position (in motor steps)
//   - The [x,y] dimensions of the platform (in motor steps)
//   Initially these two vectors should just copy the maximum allowable movement range (as if the platform covered
//   the whole allowable movement range) i.e (0, 0) and (X_LIMIT, Y_LIMIT) respectively.

// * The initialisation of these values should be done by a new public function called something like
//   `localisePlatform()`. After this function is called, the values should accurately represent the boundaries
//   of the platform.

// This would then be called by the `exploreEdgeBoundaries()` function below.

static void exploreEdgeBoundaries() {
    Motion_home();
    Motion_localisePlatform();

    // TODO: Trace the boundary of the platform once its been determined by the functions
}


static void displayBoundsOnLCD() {
    LCDDisplay_init();

    // TODO: Display the boundaries of the platform on the LCD display
}


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