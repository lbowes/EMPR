#include "FlagRecogniser.h"

#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>
#include <scanner/TextOutputUtils.h>
#include <mbed/Constants.h>
#include <mbed/TextOutput.h>
#include <mbed/LCDMenu.h>


typedef enum {
    UNITED_KINGDOM = 0,
    FRANCE,
    SYRIA,
    ICELAND,
    SUDAN,
    NORTH_MACEDONIA,
    CZECHIA,
    BURKINA_FASO,
    CENTRAL_AFRICAN_REBUBLIC,
    BURUNDI
} FlagId;

#define NUM_CRITICAL_POINTS_PER_FLAG 4
#define FIRST_FLAG UNITED_KINGDOM
#define LAST_FLAG BURUNDI
#define FLAG_COUNT (LAST_FLAG - FIRST_FLAG + 1)

typedef struct {
    float x;
    float y;
} FlagPoint;

typedef struct {
    Colour criticalPointColours[NUM_CRITICAL_POINTS_PER_FLAG];
} FlagSignature;

static FlagPoint criticalPoints[NUM_CRITICAL_POINTS_PER_FLAG];
static FlagSignature flagSignatures[FLAG_COUNT];
static FlagSignature platformReading;
static const char* flagNames[FLAG_COUNT];

static void init();
static void getDataFromPlatform();
static uint32_t calcErrorBetween(FlagId flagId);
static void loadCriticalPoints();
static void loadFlagSignatures();
static void loadFlagNames();
static void printColoursAtCriticalPoints();


// Returns the name of the closest flag to the contents of the platform
const char* FlagRecogniser_getClosestFlagName() {
    init();
    getDataFromPlatform();

    FlagId closestFlagId = FIRST_FLAG;
    uint16_t minError = 0;

    FlagId flagId = 0;
    for(flagId = FIRST_FLAG; flagId <= LAST_FLAG; flagId++) {
        uint32_t error = calcErrorBetween(flagId);

        if(error < minError || flagId == 0) {
            closestFlagId = flagId;
            minError = error;
        }
    }

    return flagNames[closestFlagId];
}


static void init() {
    Motion_init();
    ColourSensor_init();

    loadCriticalPoints();
    loadFlagSignatures();
    loadFlagNames();
}


static void loadCriticalPoints() {
    criticalPoints[0] = (FlagPoint){ -0.868, 0.276 };
    criticalPoints[1] = (FlagPoint){ -0.269, 0.412 };
    criticalPoints[2] = (FlagPoint){ 0.001, -0.428 };
    criticalPoints[3] = (FlagPoint){ 0.429, 0.438 };
}


static void loadFlagSignatures() {
    // The 4 colours here form a 1:1 mapping to the critical points above.
    // The colours entered for each flag should be the colours under the
    // respective points when the flag is under the scanner.

    flagSignatures[UNITED_KINGDOM] = (FlagSignature){
        (Colour){ 234, 255, 224 },
        (Colour){ 232, 255, 227 },
        (Colour){ 137, 60, 63 },
        (Colour){ 225, 255, 223 }
    };

    flagSignatures[FRANCE] = (FlagSignature){
        (Colour){ 35, 60, 73 },
        (Colour){ 227, 255, 224 },
        (Colour){ 223, 255, 221 },
        (Colour){ 200, 66, 73 }
    };

    flagSignatures[SYRIA] = (FlagSignature){
        (Colour){ 31, 31, 25 },
        (Colour){ 35, 35, 25 },
        (Colour){ 149, 60, 63 },
        (Colour){ 35, 35, 28 }
    };

    flagSignatures[ICELAND] = (FlagSignature){
        (Colour){ 41, 105, 149 },
        (Colour){ 168, 70, 73 },
        (Colour){ 38, 89, 124 },
        (Colour){ 41, 102, 143 }
    };

    flagSignatures[SUDAN] = (FlagSignature){
        (Colour){ 41, 70, 44 },
        (Colour){ 232, 255, 221 },
        (Colour){ 146, 51, 57 },
        (Colour){ 225, 255, 221 }
    };

    flagSignatures[NORTH_MACEDONIA] = (FlagSignature){
        (Colour){ 165, 73, 70 },
        (Colour){ 255, 255, 226 },
        (Colour){ 255, 206, 94 },
        (Colour){ 234, 255, 221 }
    };

    flagSignatures[CZECHIA] = (FlagSignature){
        (Colour){ 35, 76, 95 },
        (Colour){ 153, 57, 60 },
        (Colour){ 222, 255, 220 },
        (Colour){ 175, 66, 70}
    };

    flagSignatures[BURKINA_FASO] = (FlagSignature){
        (Colour){ 63, 121, 73 },
        (Colour){ 73, 137, 82 },
        (Colour){ 184, 60, 63 },
        (Colour){ 73, 143, 86 }
    };

    flagSignatures[CENTRAL_AFRICAN_REBUBLIC] = (FlagSignature){
        (Colour){ 255, 197, 88 },
        (Colour){ 255, 195, 86 },
        (Colour){ 130, 44, 47 },
        (Colour){ 255, 196, 85 }
    };

    flagSignatures[BURUNDI] = (FlagSignature){
        (Colour){ 98, 162, 105 },
        (Colour){ 153, 63, 66 },
        (Colour){ 239, 255, 221 },
        (Colour){ 162, 79, 79 }
    };
}


static void loadFlagNames() {
    flagNames[UNITED_KINGDOM] = "United Kingdom";
    flagNames[FRANCE] = "France";
    flagNames[SYRIA] = "Syria";
    flagNames[ICELAND] = "Iceland";
    flagNames[SUDAN] = "Sudan";
    flagNames[NORTH_MACEDONIA] = "North Macedonia";
    flagNames[CZECHIA] = "Czechia";
    flagNames[BURKINA_FASO] = "Burkina Faso";
    flagNames[CENTRAL_AFRICAN_REBUBLIC] = "Cent.Africa.Rep.";
    flagNames[BURUNDI] = "Burundi";
}


static void getDataFromPlatform() {
    const Vector3D platformDims = Motion_getPlatformDimensions();
    const Vector3D platformOrigin = Motion_getPlatformOrigin();

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_FLAG; pointIdx++) {
        // 1. Fetch the flag-space (-1.0, 1.0) critical point to be tested
        FlagPoint* criticalPoint = &criticalPoints[pointIdx];

        // 2. Convert this point into platform coordinates and move the scan head there
        uint16_t x = platformOrigin.x + (int)((criticalPoint->x + 1.0f) * 0.5f * platformDims.x);
        uint16_t y = platformOrigin.y + (int)((criticalPoint->y + 1.0f) * 0.5f * platformDims.y);
        Motion_moveTo(x, y, 0);

        // 3. Store the colour at this point
        platformReading.criticalPointColours[pointIdx] = ColourSensor_read();
    }
}


// Given the data we've got from a flag on the platform in `getDataFromPlatform()`,
// how different is this flag to that with ID `flagId`?
static uint32_t calcErrorBetween(FlagId flagId) {
    uint32_t error = 0;

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_FLAG; pointIdx++) {
        // This is the colour we've just read from the platform in `getDataFromPlatform()`.
        Colour colourReading = platformReading.criticalPointColours[pointIdx];

        // This is the expected colour at the same position, that we saved during development
        Colour expectedColour = flagSignatures[flagId].criticalPointColours[pointIdx];

        // The error is the squared distance between these two colours
        error += pow(colourReading.r - expectedColour.r, 2) + pow(colourReading.g - expectedColour.g, 2) + pow(colourReading.b - expectedColour.b, 2);
    }

    return error;
}


void FlagRecogniser_showDevMenu() {
    LCDMenu flagSelectMenu = LCDMenu_create();
    LCDMenu_addItem(&flagSelectMenu, "Crit point cols", &printColoursAtCriticalPoints);
    LCDMenu_run(&flagSelectMenu);
}


void printColoursAtCriticalPoints() {
    init();
    TextOutput_init();

    Motion_home();

    TextOutput_print("Flag colours at critical points");

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