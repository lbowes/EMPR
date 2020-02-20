#include "A2.h"

#include <scanner/Motion.h>
#include <mbed/LCDDisplay.h>
#include <mbed/Constants.h>

#include <stdio.h>


// Changes to be made to the `Motion` module
// =========================================
// * Add some way of detecting the boundaries of the platform (see below).
//   This can be used when developing the scan patterns. The sensor head only needs to move around inside the bounds of
//   the platform for scanning purposes.

// * The platform should be represented internally as two vectors:
//   - The [x,y] position of the platform's 'origin' relative to the home position (in motor steps)
//   - The [x,y] dimensions of the platform (in motor steps)
//   Initially these two vectors should just copy the maximum allowable movement range (as if the platform covered)
//   the whole allowable movement range i.e (0, 0) and (X_LIMIT, Y_LIMIT) respectively.

// * The initialisation of these values should be done by a new public function called something like
//   `determinePlatformBounds()`. After this function is called, the values should accurately represent the boundaries
//   of the platform.

// This would then be called by the `exploreEdgeBoundaries()` function below.

// All motion that takes place in any *PUBLIC* functions in the `Motion` module, should be based around exact, and not relative, motion.
// i.e the user should always specify a point to move to.
// The user should be able to have access to the movement limits for the whole space, and the platform through accessors.
// If they then choose to try to move outside the allowable range, the system should not break (movement should have a soft limit) but
// they shouldn't expect their e.g. scan pattern to work.


static void exploreEdgeBoundaries() {
    // 1. Move the scan head home
    Motion_home();

    // 2. Move the scan head to a position roughly in the centre of the platform (keep hold of this position)
    Motion_localisePlatform();

    // 3. Move the scan head in one direction along one axis until either:
    //  - a platform edge is detected (when the distance between the colour currently under the cursor
    //    and the colour under the sensor during the last step is greater than some threshold), keeping
    //    track of the number of steps moved.
    //  - the internal limit of the motion range along this axis reached.

    // 4. If an edge is detected, somehow the number of steps it took to reach this edge in this direction
    //    from the (roughly) central start position and repeat this process in the other direction, returning
    //    to the original start position.

    // 5. Repeat the process outlined above for the other axis.

    // 6. We should now have all the information necessary to trace a path round the boundary of the platform.
    //    Trace this outline once.

    // 7. Lastly, trace this square.
}


static void displayBoundsOnLCD() {
    LCDDisplay_init();

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