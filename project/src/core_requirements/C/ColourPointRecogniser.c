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

#include <mbed/Constants.h>
#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>
#include <mbed/TextOutput.h>

#include <math.h>
#include <stdio.h>

// temp - These includes are only necessary while the flag data collection function is being implemented
#include <mbed/LCDMenu.h>
#include <mbed/TextOutput.h>
//


#define NUM_CRITICAL_POINTS_PER_FLAG 14

typedef struct {
    float x;
    float y;
} FlagPoint;

typedef struct {
    Colour criticalPointColours[NUM_CRITICAL_POINTS_PER_FLAG];
} FlagSignature;

// This is the data required by this flag recognition method
static FlagPoint criticalPoints[NUM_CRITICAL_POINTS_PER_FLAG];

static FlagSignature flagSignatures[FLAG_COUNT];
// ==========================================================

static void setCriticalPoints();
static void loadFlagSignatureData();


void ColourPointRecogniser_init() {
    setCriticalPoints();
    loadFlagSignatureData();
}


static void setCriticalPoints() {
    criticalPoints[0] = (FlagPoint){ -0.868, 0.276 };
    criticalPoints[1] = (FlagPoint){ -0.874, -0.278 };
    criticalPoints[2] = (FlagPoint){ -0.294, -0.068 };
    criticalPoints[3] = (FlagPoint){ -0.269, 0.412 };
    criticalPoints[4] = (FlagPoint){ -0.265, -0.422 };
    criticalPoints[5] = (FlagPoint){ 0.003, 0.416 };
    criticalPoints[6] = (FlagPoint){ 0.020, 0.043 };
    criticalPoints[7] = (FlagPoint){ 0.001, -0.428 };
    criticalPoints[8] = (FlagPoint){ 0.106, -0.267 };
    criticalPoints[9] = (FlagPoint){ 0.253, 0.421 };
    criticalPoints[10] = (FlagPoint){ 0.251, -0.416 };
    criticalPoints[11] = (FlagPoint){ 0.429, 0.438 };
    criticalPoints[12] = (FlagPoint){ 0.835, 0.278 };
    criticalPoints[13] = (FlagPoint){ 0.842, -0.276 };
}


static void loadFlagSignatureData() {
    // The 4 colours here form a 1:1 mapping to the critical points above.
    // The colours entered for each flag should be the colours under the
    // respective points when the flag is under the scanner.

    // =================================== UNITED_KINGDOM ===================================
    flagSignatures[UNITED_KINGDOM] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== FRANCE ===================================
    flagSignatures[FRANCE] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== SYRIA ===================================
    flagSignatures[SYRIA] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== ICELAND ===================================
    flagSignatures[ICELAND] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== SUDAN ===================================
    flagSignatures[SUDAN] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== NORTH_MACEDONIA ===================================
    flagSignatures[NORTH_MACEDONIA] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== CZECHIA ===================================
    flagSignatures[CZECHIA] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== BURKINA_FASO ===================================
    flagSignatures[BURKINA_FASO] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== CENTRAL_AFRICAN_REBUBLIC ===================================
    flagSignatures[CENTRAL_AFRICAN_REBUBLIC] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };

    // =================================== BURUNDI ===================================
    flagSignatures[BURUNDI] = (FlagSignature){
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 255, 0, 123 },
        (Colour){ 0, 255, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 },
        (Colour){ 0, 123, 255 },
        (Colour){ 0, 69, 0 }
    };
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
        FlagPoint* criticalPoint = &criticalPoints[pointIdx];

        // Convert the flag point into platform coordinates
        uint16_t x = (int)((criticalPoint->x + 1.0f) * 0.5f * EMPR_X_LIMIT);
        uint16_t y = (int)((criticalPoint->y + 1.0f) * 0.5f * EMPR_Y_LIMIT);
        Motion_moveTo(x, y, 0);

        // 2. Read the colour there
        Colour reading = ColourSensor_read();

        // 3. Get the colour we should see if the current flag being tested was the one under the scanner
        Colour stored = flagSignatures[flagId].criticalPointColours[pointIdx];

        // 4. Calculate the squared error added by this point on the flag
        error += pow(reading.r - stored.r, 2) + pow(reading.g - stored.g, 2) + pow(reading.b - stored.b, 2);
    }

    return error;
}


static void readPoints() {
    TextOutput_init();

    uint8_t pointIdx = 0;
    const Vector3D platformDims = Motion_getPlatformDimensions();
    const Vector3D platformOrigin = Motion_getPlatformOrigin();

    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_FLAG; pointIdx++) {
        // 1. Move the sensor to the critical point to be tested
        FlagPoint* criticalPoint = &criticalPoints[pointIdx];

        // Convert the flag point into platform coordinates
        uint16_t x = platformOrigin.x + (int)((criticalPoint->x + 1.0f) * 0.5f * platformDims.x);
        uint16_t y = platformOrigin.y + (int)((criticalPoint->y + 1.0f) * 0.5f * platformDims.y);
        Motion_moveTo(x, y, 0);

        // 2. Read the colour there
        Colour reading = ColourSensor_read();

        char buf[64];
        sprintf(buf, "X: %i, Y: %i, R: %i, G: %i, B: %i\n", x, y, reading.r, reading.g, reading.b);
        TextOutput_print(buf);
    }
}





void temp_gatherData() {
    // This function should allow the user to collect all flag data necessary at the critical points

    const char* flagNames[FLAG_COUNT];

    flagNames[UNITED_KINGDOM] = "United Kingom";
    flagNames[FRANCE] = "France";
    flagNames[SYRIA] = "Syria";
    flagNames[ICELAND] = "Iceland";
    flagNames[SUDAN] = "Sudan";
    flagNames[NORTH_MACEDONIA] = "North Macedonia";
    flagNames[CZECHIA] = "Czechia";
    flagNames[BURKINA_FASO] = "Burkina Faso";
    flagNames[CENTRAL_AFRICAN_REBUBLIC] = "Cent.Africa.Rep.";
    flagNames[BURUNDI] = "Burundi";

    TextOutput_init();

    FlagId flagId = 0;
    for(flagId = FIRST_FLAG; flagId < LAST_FLAG; flagId++) {
        char flagName[64];
        sprintf(flagName, "Data for %s", flagNames[flagId]);
        TextOutput_print(flagName);

        readPoints();
        TextOutput_println("");
    }
}