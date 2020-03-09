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
#include <scanner/TextOutputUtils.h>
#include <mbed/LCDMenu.h>
#include <mbed/TextOutput.h>

#include <math.h>
#include <stdio.h>



#define NUM_CRITICAL_POINTS_PER_FLAG 4

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
static FlagSignature platformReading;
// ==========================================================


static void setCriticalPoints();
static void loadFlagSignatureData();


void ColourPointRecogniser_init() {
    setCriticalPoints();
    loadFlagSignatureData();
}


static void setCriticalPoints() {
    criticalPoints[0] = (FlagPoint){ -0.868, 0.276 };
    //criticalPoints[0] = (FlagPoint){ -0.874, -0.278 };
    //criticalPoints[2] = (FlagPoint){ -0.294, -0.068 };
    criticalPoints[1] = (FlagPoint){ -0.269, 0.412 };
    //criticalPoints[4] = (FlagPoint){ -0.265, -0.422 };
    //criticalPoints[2] = (FlagPoint){ 0.003, 0.416 };
    //criticalPoints[6] = (FlagPoint){ 0.020, 0.043 };
    criticalPoints[2] = (FlagPoint){ 0.001, -0.428 };
    //criticalPoints[8] = (FlagPoint){ 0.106, -0.267 };
    //criticalPoints[4] = (FlagPoint){ 0.253, 0.421 };
    //criticalPoints[10] = (FlagPoint){ 0.251, -0.416 };
    criticalPoints[3] = (FlagPoint){ 0.429, 0.438 };
    //criticalPoints[12] = (FlagPoint){ 0.835, 0.278 };
    //criticalPoints[6] = (FlagPoint){ 0.842, -0.276 };
}


static void loadFlagSignatureData() {
    // The 4 colours here form a 1:1 mapping to the critical points above.
    // The colours entered for each flag should be the colours under the
    // respective points when the flag is under the scanner.

    // =================================== UNITED_KINGDOM ===================================
    flagSignatures[UNITED_KINGDOM] = (FlagSignature){
        (Colour){234, 255, 224},
        (Colour){232, 255, 227},
        (Colour){137, 60, 63},
        (Colour){225, 255, 223}
    };

    // =================================== FRANCE ===================================
    flagSignatures[FRANCE] = (FlagSignature){
        (Colour){35, 60, 73},
        (Colour){227, 255, 224},
        (Colour){223, 255, 221},
        (Colour){200, 66, 73}
    };

    // =================================== SYRIA ===================================
    flagSignatures[SYRIA] = (FlagSignature){
        (Colour){31, 31, 25},
        (Colour){35, 35, 25},
        (Colour){149, 60, 63},
        (Colour){35, 35, 28}
    };

    // =================================== ICELAND ===================================
    flagSignatures[ICELAND] = (FlagSignature){
        (Colour){41, 105, 149},
        (Colour){168, 70, 73},
        (Colour){38, 89, 124},
        (Colour){41, 102, 143}
    };

    // =================================== SUDAN ===================================
    flagSignatures[SUDAN] = (FlagSignature){
        (Colour){41, 70, 44},
        (Colour){232, 255, 221},
        (Colour){146, 51, 57},
        (Colour){225, 255, 221}
    };

    // =================================== NORTH_MACEDONIA ===================================
    flagSignatures[NORTH_MACEDONIA] = (FlagSignature){
        (Colour){165, 73, 70},
        (Colour){255, 255, 226},
        (Colour){255, 206, 94},
        (Colour){234, 255, 221}
    };

    // =================================== CZECHIA ===================================
    flagSignatures[CZECHIA] = (FlagSignature){
        (Colour){35, 76, 95},
        (Colour){153, 57, 60},
        (Colour){222, 255, 220},
        (Colour){175, 66, 70}
    };

    // =================================== BURKINA_FASO ===================================
    flagSignatures[BURKINA_FASO] = (FlagSignature){
        (Colour){63, 121, 73},
(Colour){73, 137, 82},
(Colour){184, 60, 63},
(Colour){73, 143, 86}

    };

    // =================================== CENTRAL_AFRICAN_REBUBLIC ===================================
    flagSignatures[CENTRAL_AFRICAN_REBUBLIC] = (FlagSignature){
        (Colour){255, 197, 88},
(Colour){255, 195, 86},
(Colour){130, 44, 47},
(Colour){255, 196, 85}

    };

    // =================================== BURUNDI ===================================
    flagSignatures[BURUNDI] = (FlagSignature){
        (Colour){98, 162, 105},
(Colour){153, 63, 66},
(Colour){239, 255, 221},
(Colour){162, 79, 79}
    };
}


void ColourPointRecogniser_gatherData() {
    ColourSensor_init();

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_FLAG; pointIdx++) {
        // 1. Move the sensor to the critical point to be tested
        FlagPoint* criticalPoint = &criticalPoints[pointIdx];

        // Convert the flag point into platform coordinates
        uint16_t x = (int)((criticalPoint->x + 1.0f) * 0.5f * EMPR_X_LIMIT);
        uint16_t y = (int)((criticalPoint->y + 1.0f) * 0.5f * EMPR_Y_LIMIT);
        Motion_moveTo(x, y, 0);

        // 3. Get the colour at this point
        platformReading.criticalPointColours[pointIdx] = ColourSensor_read();

        TextOutputUtils_printColour(platformReading.criticalPointColours[pointIdx]);
    }
}


// Given the data we've got from a flag on the platform in `ColourPointRecogniser_getData`
// what is the error between this flag and that with ID `flagId`?

// This function should ideally create a total order over all flags.

// This particular method involves iterating over each critical
// point and taking a reading at each, to calculate a squared error.
uint32_t ColourPointRecogniser_errorFunc(FlagId flagId) {
    uint32_t error = 0;

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_FLAG; pointIdx++) {
        FlagPoint* criticalPoint = &criticalPoints[pointIdx];

        Colour reading = platformReading.criticalPointColours[pointIdx];
        Colour stored = flagSignatures[flagId].criticalPointColours[pointIdx];

        error += pow(reading.r - stored.r, 2) + pow(reading.g - stored.g, 2) + pow(reading.b - stored.b, 2);
    }

    return error;
}






// =================== DATA GATHERING UTILITY FUNCTIONS ======================
static void scanCriticalPoints(FlagId flagId) {
    Motion_home();

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

    char flagNameMenuLabel[64];
    sprintf(flagNameMenuLabel, "Data for %s", flagNames[flagId]);
    TextOutput_print(flagNameMenuLabel);

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

        TextOutputUtils_printColour(reading);
    }

    TextOutput_println("");

    Motion_neutraliseAllAxes();
}


static void scanUnitedKingdom() { scanCriticalPoints(UNITED_KINGDOM); }
static void scanFrance() { scanCriticalPoints(FRANCE); }
static void scanSyria() { scanCriticalPoints(SYRIA); }
static void scanIceland() { scanCriticalPoints(ICELAND); }
static void scanSudan() { scanCriticalPoints(SUDAN); }
static void scanNorthMacedonia() { scanCriticalPoints(NORTH_MACEDONIA); }
static void scanCzechia() { scanCriticalPoints(CZECHIA); }
static void scanBurkinaFaso() { scanCriticalPoints(BURKINA_FASO); }
static void scanAfricanRepublic() { scanCriticalPoints(CENTRAL_AFRICAN_REBUBLIC); }
static void scanBurundi() { scanCriticalPoints(BURUNDI); }


void getCriticalPointColours() {
    // This function should allow the user to collect all flag data necessary at the critical points
    Motion_init();
    TextOutput_init();
    ColourPointRecogniser_init();

    LCDMenu flagSelectMenu = LCDMenu_create();

    LCDMenu_addItem(&flagSelectMenu, "United Kingom", &scanUnitedKingdom);
    LCDMenu_addItem(&flagSelectMenu, "France", &scanFrance);
    LCDMenu_addItem(&flagSelectMenu, "Syria", &scanSyria);
    LCDMenu_addItem(&flagSelectMenu, "Iceland", &scanIceland);
    LCDMenu_addItem(&flagSelectMenu, "Sudan", &scanSudan);
    LCDMenu_addItem(&flagSelectMenu, "North Macedonia", &scanNorthMacedonia);
    LCDMenu_addItem(&flagSelectMenu, "Czechia", &scanCzechia);
    LCDMenu_addItem(&flagSelectMenu, "Burkina Faso", &scanBurkinaFaso);
    LCDMenu_addItem(&flagSelectMenu, "Cent.Africa.Rep.", &scanAfricanRepublic);
    LCDMenu_addItem(&flagSelectMenu, "Burundi", &scanBurundi);

    LCDMenu_run(&flagSelectMenu);
}