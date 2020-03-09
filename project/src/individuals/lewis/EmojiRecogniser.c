#include "EmojiRecogniser.h"

#include <mbed/Constants.h>
#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>
#include <mbed/TextOutput.h>
#include <scanner/TextOutputUtils.h>
#include <mbed/LCDMenu.h>
#include <mbed/TextOutput.h>

#include <math.h>
#include <stdio.h>


#define NUM_CRITICAL_POINTS_PER_EMOJI 5

typedef struct {
    float x;
    float y;
} EmojiPoint;

typedef struct {
    Colour criticalPointColours[NUM_CRITICAL_POINTS_PER_EMOJI];
} EmojiSignature;

static EmojiPoint criticalPoints[NUM_CRITICAL_POINTS_PER_EMOJI];

static EmojiSignature emojiSignatures[EMOJI_COUNT];
static EmojiSignature platformReading;
// ==========================================================


static void setCriticalPoints();
static void loadEmojiSignatureData();


void EmojiPointRecogniser_init() {
    setCriticalPoints();
    loadEmojiSignatureData();
}


static void setCriticalPoints() {
    criticalPoints[0] = (EmojiPoint){ 0.1015625, -0.65234375 };
    criticalPoints[1] = (EmojiPoint){ 0.3359375, -0.63671875 };
    criticalPoints[2] = (EmojiPoint){ 0.42578125, -0.64453125 };
    criticalPoints[3] = (EmojiPoint){ 0.60546875, -0.8984375 };
    criticalPoints[4] = (EmojiPoint){ 0.0625, -0.921875 };
}


static void loadEmojiSignatureData() {
    // The 4 colours here form a 1:1 mapping to the critical points above.
    // The colours entered for each emoji should be the colours under the
    // respective points when the emoji is under the scanner.

    // =================================== CRYING_LAUGHTER ===================================
    emojiSignatures[CRYING_LAUGHTER] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== HEART_EYES ===================================
    emojiSignatures[HEART_EYES] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== POOL_OF_TEARS ===================================
    emojiSignatures[POOL_OF_TEARS] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== RED_CHEEKS ===================================
    emojiSignatures[RED_CHEEKS] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== SAD ===================================
    emojiSignatures[SAD] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== SHADES ===================================
    emojiSignatures[SHADES] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== SMILE ===================================
    emojiSignatures[SMILE] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== BURKINA_FASO ===================================
    emojiSignatures[SMILING_PILE_OF_POO] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== CENTRAL_AFRICAN_REBUBLIC ===================================
    emojiSignatures[TEETH] = (EmojiSignature){
        (Colour) { 225, 255, 221 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== BURUNDI ===================================
    emojiSignatures[THINKING] = (EmojiSignature){
        (Colour){ 224, 198, 181 },
        (Colour){ 221, 239, 209 },
        (Colour){ 239, 252, 221 }
    };
}


void EmojiPointRecogniser_gatherData() {
    ColourSensor_init();

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_EMOJI; pointIdx++) {
        // 1. Move the sensor to the critical point to be tested
        EmojiPoint* criticalPoint = &criticalPoints[pointIdx];

        // Convert the emoji point into platform coordinates
        uint16_t x = (int)((criticalPoint->x + 1.0f) * 0.5f * EMPR_X_LIMIT);
        uint16_t y = (int)((criticalPoint->y + 1.0f) * 0.5f * EMPR_Y_LIMIT);
        Motion_moveTo(x, y, 0);

        // 3. Get the colour at this point
        platformReading.criticalPointColours[pointIdx] = ColourSensor_read();

        TextOutputUtils_printColour(platformReading.criticalPointColours[pointIdx]);
    }
}


// Given the data we've got from a emoji on the platform in `EmojiPointRecogniser_getData`
// what is the error between this emoji and that with ID `emojiId`?

// This function should ideally create a total order over all emojis.

// This particular method involves iterating over each critical
// point and taking a reading at each, to calculate a squared error.
uint32_t EmojiPointRecogniser_errorFunc(EmojiId emojiId) {
    uint32_t error = 0;

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_EMOJI; pointIdx++) {
        EmojiPoint* criticalPoint = &criticalPoints[pointIdx];

        Colour reading = platformReading.criticalPointColours[pointIdx];
        Colour stored = emojiSignatures[emojiId].criticalPointColours[pointIdx];

        error += pow(reading.r - stored.r, 2) + pow(reading.g - stored.g, 2) + pow(reading.b - stored.b, 2);
    }

    return error;
}






// =================== DATA GATHERING UTILITY FUNCTIONS ======================
static void scanCriticalPoints(EmojiId emojiId) {
    Motion_home();

    const char* emojiNames[EMOJI_COUNT];

    emojiNames[CRYING_LAUGHTER] = "Crying laughter";
    emojiNames[HEART_EYES] = "Heart eyes";
    emojiNames[POOL_OF_TEARS] = "Pool of tears";
    emojiNames[RED_CHEEKS] = "Red cheeks";
    emojiNames[SAD] = "Sad";
    emojiNames[SHADES] = "Shades";
    emojiNames[SMILE] = "Smile";
    emojiNames[SMILING_PILE_OF_POO] = "Pile of poo";
    emojiNames[TEETH] = "Teeth";
    emojiNames[THINKING] = "Thinking";

    char emojiNameMenuLabel[64];
    sprintf(emojiNameMenuLabel, "Data for %s", emojiNames[emojiId]);
    TextOutput_print(emojiNameMenuLabel);

    uint8_t pointIdx = 0;
    const Vector3D platformDims = Motion_getPlatformDimensions();
    const Vector3D platformOrigin = Motion_getPlatformOrigin();

    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_EMOJI; pointIdx++) {
        // 1. Move the sensor to the critical point to be tested
        EmojiPoint* criticalPoint = &criticalPoints[pointIdx];

        // Convert the emoji point into platform coordinates
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


static void scanUnitedKingdom() { scanCriticalPoints(CRYING_LAUGHTER); }
static void scanFrance() { scanCriticalPoints(HEART_EYES); }
static void scanSyria() { scanCriticalPoints(POOL_OF_TEARS); }
static void scanIceland() { scanCriticalPoints(RED_CHEEKS); }
static void scanSudan() { scanCriticalPoints(SAD); }
static void scanNorthMacedonia() { scanCriticalPoints(SHADES); }
static void scanCzechia() { scanCriticalPoints(SMILE); }
static void scanBurkinaFaso() { scanCriticalPoints(SMILING_PILE_OF_POO); }
static void scanAfricanRepublic() { scanCriticalPoints(TEETH); }
static void scanBurundi() { scanCriticalPoints(THINKING); }


void getEmojiCriticalPointColours() {
    // This function should allow the user to collect all emoji data necessary at the critical points
    Motion_init();
    TextOutput_init();

    LCDMenu emojiSelectMenu = LCDMenu_create();

    LCDMenu_addItem(&emojiSelectMenu, "United Kingom", &scanUnitedKingdom);
    LCDMenu_addItem(&emojiSelectMenu, "France", &scanFrance);
    LCDMenu_addItem(&emojiSelectMenu, "Syria", &scanSyria);
    LCDMenu_addItem(&emojiSelectMenu, "Iceland", &scanIceland);
    LCDMenu_addItem(&emojiSelectMenu, "Sudan", &scanSudan);
    LCDMenu_addItem(&emojiSelectMenu, "North Macedonia", &scanNorthMacedonia);
    LCDMenu_addItem(&emojiSelectMenu, "Czechia", &scanCzechia);
    LCDMenu_addItem(&emojiSelectMenu, "Burkina Faso", &scanBurkinaFaso);
    LCDMenu_addItem(&emojiSelectMenu, "Cent.Africa.Rep.", &scanAfricanRepublic);
    LCDMenu_addItem(&emojiSelectMenu, "Burundi", &scanBurundi);

    LCDMenu_run(&emojiSelectMenu);
}