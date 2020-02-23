// FLAG RECOGNITION METHOD 1
// Store a sequence of points to check, that uniquely idenfify each flag as long as the flags have been positioned correctly on the scanner.
// The more points checked the better, but say for simplicity that we check 3 points.
// Before demo day, we need to store the colour values at each of these points for all flags. For this simple method, this is the only flag
// data we would need to store.
// When the user presses a button, '#', the scanner should move to these 3 points and return the 3 colours there.
// Then flag recognition simply involves finding the distance of our reading set, to the colour set for each flag.
// The result is the flag to which our reading is closest.

// The actual location of these points is dependent on the flags to be recognised. All flags need to be presented in the same state as when their critical
// point colour data was calculated.
// The locations need to be far enough away from colour edges on all flags that there is very little chance of errors caused by placing the flags
// incorrectly.

// There are two opportunities for error here:
// 1. A poor choice of critical points to check
// 2. Inaccurate positioning of the flag on the platform on demo day


#include "ColourPointRecogniser.h"

#include <scanner/Vector3D.h>
#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>

#include <math.h>


// TODO: Configure this correctly - accuracy might still be possible with 2 or 3
#define NUM_CRITICAL_POINTS_PER_FLAG 4

typedef struct {
    Colour criticalPointColours[NUM_CRITICAL_POINTS_PER_FLAG];
} FlagSignature;

// This is the data required by this flag recognition method
static Vector3D criticalPoints[NUM_CRITICAL_POINTS_PER_FLAG];

static FlagSignature flagSignatures[FLAG_COUNT];
// ==========================================================

static void setCriticalPoints();
static void loadFlagSignatureData();


void ColourPointRecogniser_init() {
    setCriticalPoints();
    loadFlagSignatureData();
}


static void setCriticalPoints() {
    // TODO: These need to be chosen very carefully
    criticalPoints[0] = (Vector3D){ 1, 2, 3 };
    criticalPoints[1] = (Vector3D){ 1, 2, 3 };
    criticalPoints[2] = (Vector3D){ 1, 2, 3 };
    criticalPoints[3] = (Vector3D){ 1, 2, 3 };
}


static void loadFlagSignatureData() {
    // The 4 colours here form a 1:1 mapping to the critical points above.
    // The colours entered for each flag should be the colours under the
    // respective points when the flag is under the scanner.

    // =================================== BRITISH FLAG ===================================
    flagSignatures[BRITAIN] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== FRENCH FLAG ===================================
    flagSignatures[FRANCE] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== ITALIAN FLAG ===================================
    flagSignatures[ITALY] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // TODO:
}


// Given a flag placed correctly on the platform, what is the error
// between this flag and that with ID `flagId`?

// This function should ideally create a total order over all flags.

// This particular method involves iterating over each critical
// point and taking a reading at each, to calculate a squared error.
uint32_t ColourPointRecogniser_errorFunc(FlagId flagId) {
    uint32_t error = 0;

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_FLAG; pointIdx++) {
        // 1. Move the sensor to the critical point to be tested
        Vector3D* criticalPoint = &criticalPoints[pointIdx];
        Motion_moveTo(criticalPoint->x, criticalPoint->y, criticalPoint->z);

        // 2. Read the colour there
        Colour reading = ColourSensor_read();

        // 3. Get the colour we should see if the current flag being tested was the one under the scanner
        Colour stored = flagSignatures[flagId].criticalPointColours[pointIdx];

        // 4. Calculate the squared error added by this point on the flag
        error += pow(reading.r - stored.r, 2) + pow(reading.g - stored.g, 2) + pow(reading.b - stored.b, 2);
    }

    return error;
}