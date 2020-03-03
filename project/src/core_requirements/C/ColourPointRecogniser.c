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
        (Colour) { 15, 17, 12 },
        (Colour) { 7, 7, 5 },
        (Colour) { 114, 58, 58 },
        (Colour) { 225, 255, 221 },
        (Colour) { 79, 96, 94 },
        (Colour) { 228, 255, 223 },
        (Colour) { 114, 56, 56 },
        (Colour) { 112, 56, 56 },
        (Colour) { 114, 66, 66 },
        (Colour) { 225, 255, 223 },
        (Colour) { 35, 56, 58 },
        (Colour) { 224, 255, 221 },
        (Colour) { 153, 130, 119 },
        (Colour) { 142, 137, 127 }
    };

    // =================================== FRANCE ===================================
    flagSignatures[FRANCE] = (FlagSignature){
        (Colour){ 7, 7, 5 },
        (Colour){ 5, 5, 5 },
        (Colour){ 28, 48, 56 },
        (Colour){ 33, 53, 66 },
        (Colour){ 28, 45, 53 },
        (Colour){ 223, 255, 221 },
        (Colour){ 224, 255, 224 },
        (Colour){ 224, 255, 221 },
        (Colour){ 226, 255, 222 },
        (Colour){ 224, 255, 222 },
        (Colour){ 221, 249, 216 },
        (Colour){ 165, 94, 89 },
        (Colour){ 163, 53, 58 },
        (Colour){ 163, 53, 58 }
    };

    // =================================== SYRIA ===================================
    flagSignatures[SYRIA] = (FlagSignature){
        (Colour){ 7, 7, 7 },
        (Colour){ 10, 10, 10 },
        (Colour){ 163, 214, 173 },
        (Colour){ 33, 35, 28 },
        (Colour){ 117, 58, 58 },
        (Colour){ 40, 43, 35 },
        (Colour){ 114, 140, 119 },
        (Colour){ 117, 56, 56 },
        (Colour){ 225, 255, 221 },
        (Colour){ 43, 45, 38 },
        (Colour){ 150, 86, 84 },
        (Colour){ 66, 71, 61 },
        (Colour){ 28, 28, 22 },
        (Colour){ 219, 255, 220 }
    };

    // =================================== ICELAND ===================================
    flagSignatures[ICELAND] = (FlagSignature){
        (Colour){ 7, 7, 7 },
        (Colour){ 7, 7, 7 },
        (Colour){ 232, 224, 198 },
        (Colour){ 255, 250, 222 },
        (Colour){ 198, 178, 158 },
        (Colour){ 43, 94, 127 },
        (Colour){ 35, 81, 107 },
        (Colour){ 33, 71, 96 },
        (Colour){ 209, 214, 186 },
        (Colour){ 35, 84, 119 },
        (Colour){ 30, 66, 91 },
        (Colour){ 35, 84, 117 },
        (Colour){ 30, 73, 102 },
        (Colour){ 211, 219, 196 }
    };

    // =================================== SUDAN ===================================
    flagSignatures[SUDAN] = (FlagSignature){
        (Colour){ 10, 10, 7 },
        (Colour){ 7, 7, 5 },
        (Colour){ 211, 234, 206 },
        (Colour){ 221, 255, 221 },
        (Colour){ 102, 38, 40 },
        (Colour){ 223, 255, 223 },
        (Colour){ 28, 30, 25 },
        (Colour){ 107, 40, 43 },
        (Colour){ 232, 255, 223 },
        (Colour){ 223, 255, 223 },
        (Colour){ 104, 40, 43 },
        (Colour){ 224, 255, 222 },
        (Colour){ 71, 76, 68 },
        (Colour){ 229, 255, 221 }
    };

    // =================================== NORTH_MACEDONIA ===================================
    flagSignatures[NORTH_MACEDONIA] = (FlagSignature){
        (Colour){ 10, 10, 7},
        (Colour){ 7, 7, 7 },
        (Colour){ 124, 56, 51 },
        (Colour){ 221, 255, 221 },
        (Colour){ 160, 104, 61 },
        (Colour){ 223, 255, 221 },
        (Colour){ 158, 91, 61 },
        (Colour){ 153, 99, 58 },
        (Colour){ 173, 130, 66 },
        (Colour){ 224, 255, 222 },
        (Colour){ 104, 43, 43 },
        (Colour){ 223, 255, 221 },
        (Colour){ 211, 183, 112 },
        (Colour){ 145, 79, 56 }
    };

    // =================================== CZECHIA ===================================
    flagSignatures[CZECHIA] = (FlagSignature){
        (Colour){ 7, 7, 7 },
        (Colour){ 5, 5, 5 },
        (Colour){ 28, 58, 73 },
        (Colour){ 145, 61, 61 },
        (Colour){ 158, 193, 175 },
        (Colour){ 147, 68, 68 },
        (Colour){ 119, 45, 48 },
        (Colour){ 225, 255, 223 },
        (Colour){ 228, 255, 223 },
        (Colour){ 142, 68, 66 },
        (Colour){ 216, 244, 214 },
        (Colour){ 147, 89, 84 },
        (Colour){ 132, 51, 53 },
        (Colour){ 227, 255, 222 }
    };

    // =================================== BURKINA_FASO ===================================
    flagSignatures[BURKINA_FASO] = (FlagSignature){
        (Colour){ 10, 10, 7 },
        (Colour){ 7, 7, 7 },
        (Colour){ 58, 104, 63 },
        (Colour){ 66, 122, 76 },
        (Colour){ 135, 43, 45 },
        (Colour){ 71, 122, 79 },
        (Colour){ 58, 104, 66 },
        (Colour){ 137, 45, 48 },
        (Colour){ 158, 79, 56 },
        (Colour){ 68, 122, 84 },
        (Colour){ 130, 40, 45 },
        (Colour){ 81, 130, 96 },
        (Colour){ 56, 104, 63 },
        (Colour){ 163, 56, 58 }
    };

    // =================================== CENTRAL_AFRICAN_REBUBLIC ===================================
    flagSignatures[CENTRAL_AFRICAN_REBUBLIC] = (FlagSignature){
        (Colour){ 7, 7, 5 },
        (Colour){ 7, 10, 7 },
        (Colour){ 51, 96, 58 },
        (Colour){ 255, 198, 91 },
        (Colour){ 224, 249, 216 },
        (Colour){ 140, 61, 63 },
        (Colour){ 107, 38, 40 },
        (Colour){ 94, 33, 35 },
        (Colour){ 99, 35, 38 },
        (Colour){ 249, 191, 94 },
        (Colour){ 221, 239, 211 },
        (Colour){ 237, 196, 107 },
        (Colour){ 209, 163, 71 },
        (Colour){ 227, 255, 222 }
    };

    // =================================== BURUNDI ===================================
    flagSignatures[BURUNDI] = (FlagSignature){
        (Colour){ 7, 7, 7 },
        (Colour){ 5, 7, 5 },
        (Colour){ 68, 119, 76 },
        (Colour){ 224, 198, 181 },
        (Colour){ 206, 216, 191 },
        (Colour){ 229, 221, 198 },
        (Colour){ 222, 255, 222 },
        (Colour){ 221, 239, 209 },
        (Colour){ 226, 247, 214 },
        (Colour){ 229, 224, 198 },
        (Colour){ 191, 178, 158 },
        (Colour){ 239, 252, 221 },
        (Colour){ 226, 255, 218 },
        (Colour){ 61, 109, 66 }
    };
}


void ColourPointRecogniser_gatherData() {
    TextOutput_print("gathering data");

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
        // 1. Move the sensor to the critical point to be tested
        FlagPoint* criticalPoint = &criticalPoints[pointIdx];

        // 2. Read the colour there
        Colour reading = platformReading.criticalPointColours[pointIdx];

        // 3. Get the colour we should see if the current flag being tested was the one under the scanner
        Colour stored = flagSignatures[flagId].criticalPointColours[pointIdx];

        // 4. Calculate the squared error added by this point on the flag
        error += pow(reading.r - stored.r, 2) + pow(reading.g - stored.g, 2) + pow(reading.b - stored.b, 2);
    }

    return error;
}








// temp
// =======================================================================================================================================
static void scan(FlagId flagId) {
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

        char buf[64];
        sprintf(buf, "X: %i, Y: %i, R: %i, G: %i, B: %i\n", x, y, reading.r, reading.g, reading.b);
        TextOutput_print(buf);
    }

    TextOutput_println("");

    Motion_neutraliseAllAxes();
}


static void scanUnitedKingdom() { scan(UNITED_KINGDOM); }
static void scanFrance() { scan(FRANCE); }
static void scanSyria() { scan(SYRIA); }
static void scanIceland() { scan(ICELAND); }
static void scanSudan() { scan(SUDAN); }
static void scanNorthMacedonia() { scan(NORTH_MACEDONIA); }
static void scanCzechia() { scan(CZECHIA); }
static void scanBurkinaFaso() { scan(BURKINA_FASO); }
static void scanAfricanRepublic() { scan(CENTRAL_AFRICAN_REBUBLIC); }
static void scanBurundi() { scan(BURUNDI); }


void temp_ColourSensor_gatherData() {
    // This function should allow the user to collect all flag data necessary at the critical points
    Motion_init();
    TextOutput_init();

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


/*
Data for United Kingom
15, 17, 12
7, 7, 5
114, 58, 58
225, 255, 221
79, 96, 94
228, 255, 223
114, 56, 56
112, 56, 56
114, 66, 66
225, 255, 223
35, 56, 58
224, 255, 221
153, 130, 119
142, 137, 127

Data for France
7, 7, 5
5, 5, 5
28, 48, 56
33, 53, 66
28, 45, 53
223, 255, 221
224, 255, 224
224, 255, 221
226, 255, 222
224, 255, 222
221, 249, 216
165, 94, 89
163, 53, 58
163, 53, 58

Data for Syria
7, 7, 7
10, 10, 10
163, 214, 173
33, 35, 28
117, 58, 58
40, 43, 35
114, 140, 119
117, 56, 56
225, 255, 221
43, 45, 38
150, 86, 84
66, 71, 61
28, 28, 22
219, 255, 220

Data for Iceland
7, 7, 7
7, 7, 7
232, 224, 198
255, 250, 222
198, 178, 158
43, 94, 127
35, 81, 107
33, 71, 96
209, 214, 186
35, 84, 119
30, 66, 91
35, 84, 117
30, 73, 102
211, 219, 196

Data for Sudan
10, 10, 7
7, 7, 5
211, 234, 206
221, 255, 221
102, 38, 40
223, 255, 223
28, 30, 25
107, 40, 43
232, 255, 223
223, 255, 223
104, 40, 43
224, 255, 222
71, 76, 68
229, 255, 221

Data for North Macedonia
10, 10, 7
7, 7, 7
124, 56, 51
221, 255, 221
160, 104, 61
223, 255, 221
158, 91, 61
153, 99, 58
173, 130, 66
224, 255, 222
104, 43, 43
223, 255, 221
211, 183, 112
145, 79, 56

Data for Burkina Faso
10, 10, 7
7, 7, 7
58, 104, 63
66, 122, 76
135, 43, 45
71, 122, 79
58, 104, 66
137, 45, 48
158, 79, 56
68, 122, 84
130, 40, 45
81, 130, 96
56, 104, 63
163, 56, 58

Data for Burundi
7, 7, 7
5, 7, 5
68, 119, 76
224, 198, 181
206, 216, 191
229, 221, 198
222, 255, 222
221, 239, 209
226, 247, 214
229, 224, 198
191, 178, 158
239, 252, 221
226, 255, 218
61, 109, 66

Data for Cent.Africa.Rep.
7, 7, 5
7, 10, 7
51, 96, 58
255, 198, 91
224, 249, 216
140, 61, 63
107, 38, 40
94, 33, 35
99, 35, 38
249, 191, 94
221, 239, 211
237, 196, 107
209, 163, 71
227, 255, 222

Data for Czechia
7, 7, 7
5, 5, 5
28, 58, 73
145, 61, 61
158, 193, 175
147, 68, 68
119, 45, 48
225, 255, 223
228, 255, 223
142, 68, 66
216, 244, 214
147, 89, 84
132, 51, 53
227, 255, 222
*/