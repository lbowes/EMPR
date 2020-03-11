#include "EmojiRecogniser.h"

#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>
#include <scanner/TextOutputUtils.h>
#include <mbed/Constants.h>
#include <mbed/TextOutput.h>
#include <mbed/LCDMenu.h>

#include <math.h>


typedef enum {
    CRYING_LAUGHTER_UP = 0,
    CRYING_LAUGHTER_LEFT,
    CRYING_LAUGHTER_DOWN,
    CRYING_LAUGHTER_RIGHT,
    HEART_EYES_UP,
    HEART_EYES_LEFT,
    HEART_EYES_DOWN,
    HEART_EYES_RIGHT,
    POOL_OF_TEARS_UP,
    POOL_OF_TEARS_LEFT,
    POOL_OF_TEARS_DOWN,
    POOL_OF_TEARS_RIGHT,
    RED_CHEEKS_UP,
    RED_CHEEKS_LEFT,
    RED_CHEEKS_DOWN,
    RED_CHEEKS_RIGHT,
    SAD_UP,
    SAD_LEFT,
    SAD_DOWN,
    SAD_RIGHT,
    SHADES_UP,
    SHADES_LEFT,
    SHADES_DOWN,
    SHADES_RIGHT,
    SMILE_UP,
    SMILE_LEFT,
    SMILE_DOWN,
    SMILE_RIGHT,
    SMILING_PILE_OF_POO_UP,
    SMILING_PILE_OF_POO_LEFT,
    SMILING_PILE_OF_POO_DOWN,
    SMILING_PILE_OF_POO_RIGHT,
    TEETH_UP,
    TEETH_LEFT,
    TEETH_DOWN,
    TEETH_RIGHT,
    THINKING_UP,
    THINKING_LEFT,
    THINKING_DOWN,
    THINKING_RIGHT
} EmojiId;

#define NORMALISED_SCAN_RANGE 0.5f
#define SAMPLES_PER_AXIS 5
#define NUM_CRITICAL_POINTS_PER_EMOJI (SAMPLES_PER_AXIS * SAMPLES_PER_AXIS)
#define FIRST_EMOJI CRYING_LAUGHTER_UP
#define LAST_EMOJI THINKING_RIGHT
#define EMOJI_COUNT (LAST_EMOJI - FIRST_EMOJI + 1)

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
static const char* emojiNames[EMOJI_COUNT];

static const char* getClosestEmojiName();
static void init();
static void getDataFromPlatform();
static uint32_t calcErrorBetween(EmojiId emojiId);
static void loadCriticalPoints();
static void loadEmojiSignatures();
static void loadEmojiNames();
static void printColoursAtCriticalPoints();


void EmojiRecogniser_run() {
    LCDDisplay_init();

    LCDDisplay_print("Emoji Recogniser", EMPR_LINE_1);

    while(1) {
        // Perform emoji recognition
        if(Keypad_isKeyDown(EMPR_KEY_HASH)) {
            while(Keypad_isKeyDown(EMPR_KEY_HASH)) { }

            LCDDisplay_print("Emoji Recogniser", EMPR_LINE_1);

            LCDDisplay_clear(EMPR_LINE_2);
            LCDDisplay_print("...", EMPR_LINE_2);

            const char* recognisedEmojiName = getClosestEmojiName();

            LCDDisplay_clear(EMPR_LINE_2);
            LCDDisplay_print(recognisedEmojiName, EMPR_LINE_2);
        }

        // Move on to next requirement
        if(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) {
            while(Keypad_isKeyDown(EMPR_KEY_ASTERISK)) { }

            break;
        }

        Delay_ms(EMPR_SMOOTH_MENU_DELAY_MS);

        Motion_neutraliseAllAxes();
    }
}


static const char* getClosestEmojiName() {
    init();
    getDataFromPlatform();

    EmojiId closestEmojiId = FIRST_EMOJI;
    uint16_t minError = 0;

    EmojiId emojiId = 0;
    for(emojiId = FIRST_EMOJI; emojiId <= LAST_EMOJI; emojiId++) {
        uint32_t error = calcErrorBetween(emojiId);

        if(error < minError || emojiId == 0) {
            closestEmojiId = emojiId;
            minError = error;
        }
    }

    return emojiNames[closestEmojiId];
}


void init() {
    Motion_init();
    ColourSensor_init();

    loadCriticalPoints();
    loadEmojiSignatures();
    loadEmojiNames();
}


static void loadCriticalPoints() {
    for(uint8_t x = 0; x < SAMPLES_PER_AXIS; x++) {
        for(uint8_t y = 0; y < SAMPLES_PER_AXIS; y++) {
            float x_normalised = ((x / (float)(SAMPLES_PER_AXIS - 1)) * 2.0f - 1.0f) * NORMALISED_SCAN_RANGE;
            float y_normalised = ((y / (float)(SAMPLES_PER_AXIS - 1)) * 2.0f - 1.0f) * NORMALISED_SCAN_RANGE;

            criticalPoints[x * SAMPLES_PER_AXIS + y] = (EmojiPoint){ x_normalised, y_normalised };
        }
    }
}


static void loadEmojiSignatures() {
    // The 4 colours here form a 1:1 mapping to the critical points above.
    // The colours entered for each emoji should be the colours under the
    // respective points when the emoji is under the scanner.

    // =================================== CRYING_LAUGHTER ===================================
    emojiSignatures[CRYING_LAUGHTER_UP] = (EmojiSignature){
        (Colour){ 130, 95, 54 },
        (Colour){ 133, 111, 60 },
        (Colour){ 79, 165, 200 },
        (Colour){ 73, 165, 210 },
        (Colour){ 105, 175, 191 },
        (Colour){ 255, 190, 93 },
        (Colour){ 73, 57, 38 },
        (Colour){ 255, 192, 96 },
        (Colour){ 229, 255, 221 },
        (Colour){ 111, 86, 51 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 196, 97 },
        (Colour){ 225, 255, 221 },
        (Colour){ 76, 60, 41 },
        (Colour){ 255, 193, 96 },
        (Colour){ 79, 63, 41 },
        (Colour){ 255, 198, 97 },
        (Colour){ 226, 255, 217 },
        (Colour){ 165, 121, 70 },
        (Colour){ 137, 105, 57 },
        (Colour){ 223, 175, 95 },
        (Colour){ 86, 194, 242 },
        (Colour){ 86, 191, 239 },
        (Colour){ 130, 230, 255 }
    };

    emojiSignatures[CRYING_LAUGHTER_LEFT] = (EmojiSignature){
        (Colour){82, 66, 41 },
        (Colour){255, 191, 97 },
        (Colour){255, 192, 96 },
        (Colour){117, 95, 54 },
        (Colour){255, 190, 98 },
        (Colour){162, 130, 70 },
        (Colour){255, 190, 96 },
        (Colour){255, 192, 96 },
        (Colour){156, 124, 66 },
        (Colour){229, 178, 92 },
        (Colour){255, 200, 111 },
        (Colour){255, 195, 97 },
        (Colour){255, 192, 96 },
        (Colour){255, 194, 98 },
        (Colour){124, 194, 200 },
        (Colour){175, 232, 235 },
        (Colour){240, 255, 219 },
        (Colour){242, 255, 219 },
        (Colour){230, 255, 230 },
        (Colour){79, 175, 219 },
        (Colour){108, 140, 137 },
        (Colour){73, 57, 38 },
        (Colour){73, 57, 41 },
        (Colour){82, 79, 63 },
        (Colour){79, 178, 223 }
    };

    emojiSignatures[CRYING_LAUGHTER_DOWN] = (EmojiSignature){
        (Colour){ 73, 162, 204 },
        (Colour){ 79, 168, 207 },
        (Colour){ 98, 102, 79 },
        (Colour){ 255, 188, 95 },
        (Colour){ 255, 195, 99 },
        (Colour){ 216, 219, 168 },
        (Colour){ 188, 137, 76 },
        (Colour){ 102, 86, 51 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 193, 98 },
        (Colour){ 234, 255, 222 },
        (Colour){ 229, 168, 89 },
        (Colour){ 255, 196, 99 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 194, 99 },
        (Colour){ 178, 178, 149 },
        (Colour){ 181, 133, 73 },
        (Colour){ 98, 82, 47 },
        (Colour){ 255, 195, 94 },
        (Colour){ 255, 192, 99 },
        (Colour){ 76, 175, 216 },
        (Colour){ 79, 178, 219 },
        (Colour){ 188, 159, 105 },
        (Colour){ 181, 146, 76 },
        (Colour){ 255, 195, 99 }
    };

    emojiSignatures[CRYING_LAUGHTER_RIGHT] = (EmojiSignature){
        (Colour){ 73, 114, 130 },
        (Colour){ 70, 60, 44 },
        (Colour){ 73, 63, 47 },
        (Colour){ 70, 79, 76 },
        (Colour){ 86, 191, 239 },
        (Colour){ 92, 121, 117 },
        (Colour){ 82, 79, 57 },
        (Colour){ 89, 82, 60 },
        (Colour){ 114, 133, 117 },
        (Colour){ 82, 178, 223 },
        (Colour){ 255, 194, 102 },
        (Colour){ 200, 156, 82 },
        (Colour){ 229, 181, 92 },
        (Colour){ 255, 194, 99 },
        (Colour){ 223, 216, 162 },
        (Colour){ 255, 190, 93 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 191, 95 },
        (Colour){ 255, 189, 93 },
        (Colour){ 114, 95, 54 },
        (Colour){ 105, 86, 51 },
        (Colour){ 255, 193, 98 },
        (Colour){ 255, 195, 97 },
        (Colour){ 98, 79, 47 },
        (Colour){ 255, 192, 97 }
    };

    // =================================== HEART_EYES ===================================
    emojiSignatures[HEART_EYES_UP] = (EmojiSignature){
        (Colour){ 200, 76, 73 },
        (Colour){ 229, 124, 86 },
        (Colour){ 255, 194, 97 },
        (Colour){ 245, 191, 98 },
        (Colour){ 255, 196, 98 },
        (Colour){ 213, 79, 76 },
        (Colour){ 255, 181, 98 },
        (Colour){ 255, 194, 98 },
        (Colour){ 70, 51, 35 },
        (Colour){ 255, 188, 98 },
        (Colour){ 255, 189, 93 },
        (Colour){ 255, 196, 99 },
        (Colour){ 255, 195, 96 },
        (Colour){ 70, 54, 38 },
        (Colour){ 124, 92, 57 },
        (Colour){ 216, 79, 79 },
        (Colour){ 251, 143, 95 },
        (Colour){ 255, 194, 98 },
        (Colour){ 70, 54, 38 },
        (Colour){ 255, 191, 98 },
        (Colour){ 223, 82, 79 },
        (Colour){ 255, 156, 99 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 194, 98 },
        (Colour){255, 196, 99}
    };

    emojiSignatures[HEART_EYES_LEFT] = (EmojiSignature){
        (Colour){ 200, 73, 73 },
        (Colour){ 204, 76, 73 },
        (Colour){ 239, 130, 86 },
        (Colour){ 213, 76, 76 },
        (Colour){ 216, 79, 76 },
        (Colour){ 210, 76, 76 },
        (Colour){ 255, 180, 94 },
        (Colour){ 255, 191, 95 },
        (Colour){ 223, 82, 79 },
        (Colour){ 229, 92, 82 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 193, 98 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 193, 96 },
        (Colour){ 255, 197, 98 },
        (Colour){ 70, 54, 35 },
        (Colour){ 70, 54, 35 },
        (Colour){ 73, 57, 38 },
        (Colour){ 70, 54, 38 },
        (Colour){ 255, 200, 98 },
        (Colour){ 255, 195, 99 },
        (Colour){ 73, 57, 38 },
        (Colour){ 73, 57, 38 },
        (Colour){ 242, 178, 95 },
        (Colour){ 255, 200, 100 }
    };

    emojiSignatures[HEART_EYES_DOWN] = (EmojiSignature){
        (Colour){ 248, 188, 95 },
        (Colour){ 248, 188, 95 },
        (Colour){ 255, 185, 98 },
        (Colour){ 216, 79, 79 },
        (Colour){ 219, 82, 79 },
        (Colour){ 66, 47, 35 },
        (Colour){ 255, 188, 95 },
        (Colour){ 255, 192, 99 },
        (Colour){ 219, 82, 79 },
        (Colour){ 219, 82, 79 },
        (Colour){ 66, 47, 35 },
        (Colour){ 255, 192, 97 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 191, 94 },
        (Colour){ 255, 184, 99 },
        (Colour){ 70, 51, 35 },
        (Colour){ 255, 189, 96 },
        (Colour){ 255, 179, 98 },
        (Colour){ 245, 89, 89 },
        (Colour){ 248, 92, 92 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 189, 97 },
        (Colour){ 245, 92, 89 },
        (Colour){ 248, 92, 92 }
    };

    emojiSignatures[HEART_EYES_RIGHT] = (EmojiSignature){
        (Colour){ 226, 175, 89 },
        (Colour){ 66, 47, 35 },
        (Colour){ 66, 51, 35 },
        (Colour){ 146, 111, 63 },
        (Colour){ 255, 197, 101 },
        (Colour){ 73, 57, 38 },
        (Colour){ 102, 79, 47 },
        (Colour){ 108, 82, 47 },
        (Colour){ 73, 57, 38 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 193, 96 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 194, 98 },
        (Colour){ 226, 82, 82 },
        (Colour){ 255, 173, 94 },
        (Colour){ 255, 187, 94 },
        (Colour){ 232, 82, 82 },
        (Colour){ 226, 86, 79 },
        (Colour){ 232, 86, 86 },
        (Colour){ 219, 86, 79 },
        (Colour){ 239, 102, 86 },
        (Colour){ 229, 82, 82 },
        (Colour){ 229, 86, 82 }
    };

    // =================================== POOL_OF_TEARS ===================================
    emojiSignatures[POOL_OF_TEARS_UP] = (EmojiSignature){
        (Colour){ 242, 181, 92 },
        (Colour){ 159, 127, 66 },
        (Colour){ 86, 175, 207 },
        (Colour){ 89, 181, 213 },
        (Colour){ 86, 175, 204 },
        (Colour){ 255, 191, 97 },
        (Colour){ 191, 149, 76 },
        (Colour){ 255, 197, 100 },
        (Colour){ 251, 194, 102 },
        (Colour){ 255, 197, 100 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 196, 97 },
        (Colour){ 130, 66, 54 },
        (Colour){ 156, 111, 66 },
        (Colour){ 175, 130, 70 },
        (Colour){ 143, 117, 63 },
        (Colour){ 255, 208, 115 },
        (Colour){ 255, 202, 113 },
        (Colour){ 255, 204, 113 },
        (Colour){ 255, 193, 96 },
        (Colour){ 178, 140, 73 },
        (Colour){ 216, 219, 172 },
        (Colour){ 207, 223, 181 },
        (Colour){ 191, 216, 184 }
    };

    emojiSignatures[POOL_OF_TEARS_LEFT] = (EmojiSignature){
        (Colour){ 242, 181, 92 },
        (Colour){ 159, 127, 66 },
        (Colour){ 86, 175, 207 },
        (Colour){ 89, 181, 213 },
        (Colour){ 86, 175, 204 },
        (Colour){ 255, 191, 97 },
        (Colour){ 191, 149, 76 },
        (Colour){ 255, 197, 100 },
        (Colour){ 251, 194, 102 },
        (Colour){ 255, 197, 100 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 196, 97 },
        (Colour){ 130, 66, 54 },
        (Colour){ 156, 111, 66 },
        (Colour){ 175, 130, 70 },
        (Colour){ 143, 117, 63 },
        (Colour){ 255, 208, 115 },
        (Colour){ 255, 202, 113 },
        (Colour){ 255, 204, 113 },
        (Colour){ 255, 193, 96 },
        (Colour){ 178, 140, 73 },
        (Colour){ 216, 219, 172 },
        (Colour){ 207, 223, 181 },
        (Colour){ 191, 216, 184 }
    };

    emojiSignatures[POOL_OF_TEARS_DOWN] = (EmojiSignature){
        (Colour){ 95, 168, 184 },
        (Colour){ 82, 168, 194 },
        (Colour){ 98, 76, 47 },
        (Colour){ 194, 143, 76 },
        (Colour){ 255, 196, 99 },
        (Colour){ 213, 162, 86 },
        (Colour){ 255, 195, 100 },
        (Colour){ 133, 98, 57 },
        (Colour){ 255, 189, 96 },
        (Colour){ 255, 196, 98 },
        (Colour){ 143, 70, 60 },
        (Colour){ 255, 192, 97 },
        (Colour){ 255, 198, 99 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 196, 99 },
        (Colour){ 255, 206, 118 },
        (Colour){ 255, 207, 117 },
        (Colour){ 114, 89, 51 },
        (Colour){ 226, 178, 92 },
        (Colour){ 255, 196, 99 },
        (Colour){ 207, 210, 165 },
        (Colour){ 197, 210, 165 },
        (Colour){ 159, 114, 66 },
        (Colour){ 255, 189, 94 },
        (Colour){ 255, 198, 97 }
    };

    emojiSignatures[POOL_OF_TEARS_RIGHT] = (EmojiSignature){
        (Colour){ 76, 159, 191 },
        (Colour){ 165, 76, 63 },
        (Colour){ 207, 82, 79 },
        (Colour){ 95, 175, 194 },
        (Colour){ 255, 200, 103 },
        (Colour){ 86, 168, 200 },
        (Colour){ 210, 162, 86 },
        (Colour){ 168, 124, 70 },
        (Colour){ 95, 181, 204 },
        (Colour){ 255, 199, 102 },
        (Colour){ 79, 137, 156 },
        (Colour){ 162, 127, 66 },
        (Colour){ 219, 178, 92 },
        (Colour){ 89, 162, 178 },
        (Colour){ 210, 162, 86 },
        (Colour){ 216, 162, 82 },
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 195, 96 },
        (Colour){ 251, 194, 95 },
        (Colour){ 172, 124, 66 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 193, 98 },
        (Colour){ 255, 194, 95 }
    };

    // =================================== RED_CHEEKS ===================================
    emojiSignatures[RED_CHEEKS_UP] = (EmojiSignature){
        (Colour){ 255, 192, 96 },
        (Colour){ 226, 108, 105 },
        (Colour){ 255, 122, 122 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 198, 98 },
        (Colour){ 242, 184, 92 },
        (Colour){ 255, 192, 97 },
        (Colour){ 255, 196, 97 },
        (Colour){ 89, 73, 44 },
        (Colour){ 255, 198, 100 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 192, 97 },
        (Colour){ 255, 195, 97 },
        (Colour){ 146, 117, 63 },
        (Colour){ 255, 195, 98 },
        (Colour){ 207, 159, 82 },
        (Colour){ 255, 191, 97 },
        (Colour){ 255, 194, 99 },
        (Colour){ 82, 63, 41 },
        (Colour){ 255, 198, 97 },
        (Colour){ 255, 191, 94 },
        (Colour){ 216, 105, 98 },
        (Colour){ 248, 121, 121 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 197, 98 }
    };

    emojiSignatures[RED_CHEEKS_LEFT] = (EmojiSignature){
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 194, 95 },
        (Colour){ 232, 153, 92 },
        (Colour){ 117, 92, 51 },
        (Colour){ 105, 89, 51 },
        (Colour){ 255, 186, 97 },
        (Colour){ 219, 121, 98 },
        (Colour){ 229, 111, 108 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 145, 115 },
        (Colour){ 255, 124, 124 },
        (Colour){ 95, 79, 47 },
        (Colour){ 255, 193, 99 },
        (Colour){ 255, 195, 99 },
        (Colour){ 137, 114, 63 },
        (Colour){ 255, 170, 107 },
        (Colour){ 255, 199, 100 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 196, 102 },
        (Colour){ 255, 199, 99 },
        (Colour){ 255, 200, 100 }
    };

    emojiSignatures[RED_CHEEKS_DOWN] = (EmojiSignature){
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 194, 95 },
        (Colour){ 232, 153, 92 },
        (Colour){ 117, 92, 51 },
        (Colour){ 105, 89, 51 },
        (Colour){ 255, 186, 97 },
        (Colour){ 219, 121, 98 },
        (Colour){ 229, 111, 108 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 145, 115 },
        (Colour){ 255, 124, 124 },
        (Colour){ 95, 79, 47 },
        (Colour){ 255, 193, 99 },
        (Colour){ 255, 195, 99 },
        (Colour){ 137, 114, 63 },
        (Colour){ 255, 170, 107 },
        (Colour){ 255, 199, 100 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 196, 102 },
        (Colour){ 255, 199, 99 },
        (Colour){ 255, 200, 100 }
    };

    emojiSignatures[RED_CHEEKS_RIGHT] = (EmojiSignature){
        (Colour){255, 195, 99 },
        (Colour){149, 121, 63 },
        (Colour){140, 111, 60 },
        (Colour){255, 194, 100 },
        (Colour){255, 197, 100 },
        (Colour){197, 137, 82 },
        (Colour){255, 197, 100 },
        (Colour){255, 196, 98 },
        (Colour){239, 178, 95 },
        (Colour){248, 140, 117 },
        (Colour){242, 121, 114 },
        (Colour){255, 195, 99 },
        (Colour){255, 195, 97 },
        (Colour){251, 137, 114 },
        (Colour){242, 117, 114 },
        (Colour){111, 86, 51 },
        (Colour){95, 73, 44 },
        (Colour){140, 111, 60 },
        (Colour){149, 117, 63 },
        (Colour){255, 164, 102 },
        (Colour){255, 195, 96 },
        (Colour){255, 194, 95 },
        (Colour){255, 194, 95 },
        (Colour){255, 193, 95 },
        (Colour){255, 194, 95 }
    };

    // =================================== SAD ===================================
    emojiSignatures[SAD_UP] = (EmojiSignature){
        (Colour){ 146, 114, 60 },
        (Colour){ 255, 192, 97 },
        (Colour){ 255, 196, 97 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 198, 100 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 194, 95 },
        (Colour){ 108, 82, 51 },
        (Colour){ 255, 197, 102 },
        (Colour){ 255, 199, 99 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 197, 97 },
        (Colour){ 235, 184, 92 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 187, 95 },
        (Colour){ 255, 195, 97 },
        (Colour){ 111, 86, 51 },
        (Colour){ 255, 194, 100 },
        (Colour){ 255, 198, 100 },
        (Colour){ 162, 127, 66 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 201, 107 }
    };

    emojiSignatures[SAD_LEFT] = (EmojiSignature){
        (Colour){ 204, 143, 73 },
        (Colour){ 255, 191, 95 },
        (Colour){ 255, 191, 94 },
        (Colour){ 121, 92, 51 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 191, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 189, 94 },
        (Colour){ 76, 63, 41 },
        (Colour){ 89, 70, 44 },
        (Colour){ 108, 89, 54 },
        (Colour){ 86, 66, 44 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 198, 97 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 199, 98 },
        (Colour){ 255, 199, 99 },
        (Colour){ 255, 196, 100 },
        (Colour){ 255, 195, 100 },
        (Colour){ 255, 199, 100 },
        (Colour){ 255, 209, 110 }
    };

    emojiSignatures[SAD_DOWN] = (EmojiSignature){
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 190, 98 },
        (Colour){ 89, 73, 44 },
        (Colour){ 255, 192, 99 },
        (Colour){ 127, 98, 54 },
        (Colour){ 226, 175, 89 },
        (Colour){ 255, 194, 99 },
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 189, 99 },
        (Colour){ 127, 95, 54 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 192, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 196, 99 },
        (Colour){ 255, 191, 100 },
        (Colour){ 255, 186, 93 },
        (Colour){ 255, 199, 99 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 192, 99 },
        (Colour){ 255, 199, 98 },
        (Colour){ 255, 199, 97 },
        (Colour){ 255, 198, 100 },
        (Colour){ 102, 79, 47 },
        (Colour){ 255, 194, 97 }
    };

    emojiSignatures[SAD_RIGHT] = (EmojiSignature){
        (Colour){ 255, 198, 102 },
        (Colour){ 165, 130, 70 },
        (Colour){ 184, 143, 76 },
        (Colour){ 255, 198, 100 },
        (Colour){ 255, 197, 101 },
        (Colour){ 255, 197, 100 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 198, 99 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 199, 99 },
        (Colour){ 130, 102, 57 },
        (Colour){ 130, 102, 60 },
        (Colour){ 111, 89, 54 },
        (Colour){ 146, 114, 63 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 191, 94 },
        (Colour){ 255, 191, 94 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 195, 95 },
        (Colour){ 178, 140, 73 },
        (Colour){ 255, 191, 97 },
        (Colour){ 255, 193, 96 },
        (Colour){ 255, 194, 97 },
        (Colour){ 229, 165, 89 },
        (Colour){ 255, 194, 97 }
    };

    // =================================== SHADES ===================================
    emojiSignatures[SHADES_UP] = (EmojiSignature){
        (Colour){ 31, 31, 25 },
        (Colour){ 28, 31, 28 },
        (Colour){ 223, 165, 89 },
        (Colour){ 165, 133, 70 },
        (Colour){ 255, 197, 97 },
        (Colour){ 35, 35, 28 },
        (Colour){ 28, 31, 25 },
        (Colour){ 255, 193, 96 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 191, 97 },
        (Colour){ 54, 54, 35 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 197, 146, 79 },
        (Colour){ 35, 35, 28 },
        (Colour){ 31, 31, 28 },
        (Colour){ 255, 191, 97 },
        (Colour){ 255, 198, 99 },
        (Colour){ 255, 194, 97 },
        (Colour){ 31, 31, 28 },
        (Colour){ 31, 31, 28 },
        (Colour){ 255, 188, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 195, 99 }
    };

    emojiSignatures[SHADES_LEFT] = (EmojiSignature){
        (Colour){ 207, 156, 79 },
        (Colour){ 223, 165, 82 },
        (Colour){ 239, 178, 89 },
        (Colour){ 188, 146, 76 },
        (Colour){ 175, 140, 73 },
        (Colour){ 28, 31, 28 },
        (Colour){ 57, 51, 38 },
        (Colour){ 137, 117, 63 },
        (Colour){ 31, 31, 28 },
        (Colour){ 31, 35, 28 },
        (Colour){ 51, 47, 35 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 196, 98 },
        (Colour){ 44, 44, 35 },
        (Colour){ 51, 51, 35 },
        (Colour){ 255, 193, 96 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 196, 97 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 198, 97 },
        (Colour){ 255, 193, 99 },
        (Colour){ 76, 60, 41 },
        (Colour){ 76, 60, 41 },
        (Colour){ 255, 193, 99 },
        (Colour){ 255, 200, 101 }
    };

    emojiSignatures[SHADES_DOWN] = (EmojiSignature){
        (Colour){ 226, 172, 89 },
        (Colour){ 255, 195, 97 },
        (Colour){ 28, 31, 28 },
        (Colour){ 28, 28, 25 },
        (Colour){ 255, 194, 97 },
        (Colour){ 242, 178, 92 },
        (Colour){ 255, 193, 96 },
        (Colour){ 35, 35, 28 },
        (Colour){ 31, 31, 28 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 193, 96 },
        (Colour){ 255, 196, 97 },
        (Colour){ 255, 198, 99 },
        (Colour){ 60, 60, 38 },
        (Colour){ 255, 196, 98 },
        (Colour){ 219, 162, 86 },
        (Colour){ 255, 196, 98 },
        (Colour){ 31, 31, 28 },
        (Colour){ 31, 31, 28 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 195, 96 },
        (Colour){ 35, 35, 31 },
        (Colour){ 31, 31, 28 },
        (Colour){ 255, 196, 98 }
    };

    emojiSignatures[SHADES_RIGHT] = (EmojiSignature){
        (Colour){ 216, 165, 86 },
        (Colour){ 82, 63, 38 },
        (Colour){ 92, 70, 44 },
        (Colour){ 162, 124, 66 },
        (Colour){ 255, 198, 99 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 197, 97 },
        (Colour){ 255, 196, 99 },
        (Colour){ 31, 31, 28 },
        (Colour){ 242, 181, 95 },
        (Colour){ 255, 196, 99 },
        (Colour){ 31, 35, 28 },
        (Colour){ 35, 35, 28 },
        (Colour){ 28, 31, 25 },
        (Colour){ 44, 44, 31 },
        (Colour){ 82, 79, 47 },
        (Colour){ 31, 31, 28 },
        (Colour){ 28, 31, 28 },
        (Colour){ 255, 191, 94 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 194, 94 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 189, 96 }
    };

    // =================================== SMILE ===================================
    emojiSignatures[SMILE_UP] = (EmojiSignature){
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 195, 97 },
        (Colour){ 172, 137, 73 },
        (Colour){ 76, 60, 38 },
        (Colour){ 255, 195, 99 },
        (Colour){ 251, 188, 95 },
        (Colour){ 168, 127, 70 },
        (Colour){ 255, 195, 99 },
        (Colour){ 229, 255, 219 },
        (Colour){ 111, 86, 51 },
        (Colour){ 255, 191, 94 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 195, 99 },
        (Colour){ 226, 255, 219 },
        (Colour){ 76, 57, 38 },
        (Colour){ 213, 165, 82 },
        (Colour){ 76, 60, 38 },
        (Colour){ 255, 198, 100 },
        (Colour){ 227, 255, 214 },
        (Colour){ 181, 133, 73 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 196, 97 },
        (Colour){ 191, 156, 79 },
        (Colour){ 149, 111, 63 },
        (Colour){ 255, 197, 98 }
    };

    emojiSignatures[SMILE_LEFT] = (EmojiSignature){
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 192, 93 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 194, 94 },
        (Colour){ 79, 63, 38 },
        (Colour){ 255, 189, 94 },
        (Colour){ 255, 194, 95 },
        (Colour){ 76, 57, 38 },
        (Colour){ 255, 196, 95 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 197, 95 },
        (Colour){ 245, 255, 218 },
        (Colour){ 240, 255, 219 },
        (Colour){ 242, 255, 219 },
        (Colour){ 236, 255, 218 },
        (Colour){ 255, 192, 102 },
        (Colour){ 117, 95, 54 },
        (Colour){ 73, 54, 38 },
        (Colour){ 76, 57, 41 },
        (Colour){ 92, 73, 44 },
        (Colour){ 255, 200, 101 }
    };

    emojiSignatures[SMILE_DOWN] = (EmojiSignature){
        (Colour){ 105, 86, 47 },
        (Colour){ 102, 79, 47 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 191, 97 },
        (Colour){ 255, 194, 98 },
        (Colour){ 226, 229, 197 },
        (Colour){ 200, 146, 76 },
        (Colour){ 178, 140, 73 },
        (Colour){ 248, 181, 92 },
        (Colour){ 255, 194, 99 },
        (Colour){ 234, 255, 221 },
        (Colour){ 223, 162, 86 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 195, 97 },
        (Colour){ 181, 181, 153 },
        (Colour){ 181, 133, 73 },
        (Colour){ 98, 82, 47 },
        (Colour){ 184, 137, 73 },
        (Colour){ 255, 194, 97 },
        (Colour){ 165, 127, 70 },
        (Colour){ 124, 95, 54 },
        (Colour){ 255, 198, 99 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 195, 99 }
    };

    emojiSignatures[SMILE_RIGHT] = (EmojiSignature){
        (Colour){ 79, 63, 41 },
        (Colour){ 70, 57, 44 },
        (Colour){ 76, 63, 47 },
        (Colour){ 70, 54, 35 },
        (Colour){ 255, 196, 99 },
        (Colour){ 111, 111, 86 },
        (Colour){ 82, 79, 57 },
        (Colour){ 89, 82, 60 },
        (Colour){ 130, 137, 108 },
        (Colour){ 255, 201, 103 },
        (Colour){ 255, 195, 99 },
        (Colour){ 255, 196, 99 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 192, 97 },
        (Colour){ 255, 194, 98 },
        (Colour){ 92, 76, 44 },
        (Colour){ 255, 191, 95 },
        (Colour){ 255, 193, 93 },
        (Colour){ 76, 57, 38 },
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 194, 94 },
        (Colour){ 255, 194, 95 }
    };

    // =================================== SMILING_PILE_OF_POO ===================================
    emojiSignatures[SMILING_PILE_OF_POO_UP] = (EmojiSignature){
        (Colour){ 184, 124, 98 },
        (Colour){ 184, 114, 89 },
        (Colour){ 184, 102, 76 },
        (Colour){ 165, 95, 73 },
        (Colour){ 194, 108, 79 },
        (Colour){ 223, 172, 143 },
        (Colour){ 35, 38, 35 },
        (Colour){ 239, 207, 172 },
        (Colour){ 41, 41, 35 },
        (Colour){ 200, 117, 92 },
        (Colour){ 188, 102, 76 },
        (Colour){ 194, 114, 86 },
        (Colour){ 200, 111, 82 },
        (Colour){ 51, 47, 41 },
        (Colour){ 255, 183, 161 },
        (Colour){ 235, 191, 162 },
        (Colour){ 35, 38, 35 },
        (Colour){ 248, 219, 181 },
        (Colour){ 44, 41, 35 },
        (Colour){ 219, 143, 117 },
        (Colour){ 194, 111, 86 },
        (Colour){ 197, 117, 89 },
        (Colour){ 197, 111, 82 },
        (Colour){ 76, 57, 47 },
        (Colour){ 200, 111, 86 }
    };

    emojiSignatures[SMILING_PILE_OF_POO_LEFT] = (EmojiSignature){
        (Colour){ 175, 102, 76 },
        (Colour){ 172, 92, 70 },
        (Colour){ 181, 98, 73 },
        (Colour){ 181, 98, 73 },
        (Colour){ 226, 255, 223 },
        (Colour){ 226, 255, 221 },
        (Colour){ 239, 235, 200 },
        (Colour){ 239, 255, 217 },
        (Colour){ 230, 255, 221 },
        (Colour){ 235, 191, 156 },
        (Colour){ 241, 255, 221 },
        (Colour){ 235, 197, 162 },
        (Colour){ 255, 236, 200 },
        (Colour){ 247, 255, 218 },
        (Colour){ 197, 108, 82 },
        (Colour){ 175, 98, 73 },
        (Colour){ 188, 105, 79 },
        (Colour){ 184, 102, 76 },
        (Colour){ 191, 105, 79 },
        (Colour){ 194, 108, 79 },
        (Colour){ 159, 108, 95 },
        (Colour){ 255, 196, 180 },
        (Colour){ 255, 196, 178 },
        (Colour){ 184, 105, 79 },
        (Colour){ 197, 111, 82 }
    };

    emojiSignatures[SMILING_PILE_OF_POO_DOWN] = (EmojiSignature){
        (Colour){ 44, 41, 31 },
        (Colour){ 175, 98, 73 },
        (Colour){ 235, 200, 165 },
        (Colour){ 188, 105, 79 },
        (Colour){ 228, 255, 223 },
        (Colour){ 41, 41, 38 },
        (Colour){ 194, 117, 89 },
        (Colour){ 41, 51, 44 },
        (Colour){ 255, 242, 204 },
        (Colour){ 197, 111, 82 },
        (Colour){ 51, 54, 47 },
        (Colour){ 188, 105, 76 },
        (Colour){ 216, 143, 111 },
        (Colour){ 200, 108, 82 },
        (Colour){ 197, 108, 82 },
        (Colour){ 35, 35, 31 },
        (Colour){ 204, 130, 102 },
        (Colour){ 57, 70, 63 },
        (Colour){ 255, 252, 214 },
        (Colour){ 213, 140, 111 },
        (Colour){ 194, 108, 79 },
        (Colour){ 191, 105, 79 },
        (Colour){ 200, 114, 86 },
        (Colour){ 255, 227, 193 },
        (Colour){ 228, 255, 222 }
    };

    emojiSignatures[SMILING_PILE_OF_POO_RIGHT] = (EmojiSignature){
        (Colour){ 146, 86, 63 },
        (Colour){ 184, 140, 127 },
        (Colour){ 255, 194, 176 },
        (Colour){ 70, 66, 60 },
        (Colour){ 188, 105, 79 },
        (Colour){ 178, 98, 73 },
        (Colour){ 178, 98, 73 },
        (Colour){ 194, 108, 79 },
        (Colour){ 188, 105, 79 },
        (Colour){ 194, 108, 79 },
        (Colour){ 249, 255, 218 },
        (Colour){ 216, 232, 200 },
        (Colour){ 239, 184, 153 },
        (Colour){ 232, 255, 224 },
        (Colour){ 197, 111, 82 },
        (Colour){ 255, 233, 199 },
        (Colour){ 244, 255, 219 },
        (Colour){ 219, 153, 124 },
        (Colour){ 229, 255, 222 },
        (Colour){ 255, 210, 178 },
        (Colour){ 191, 105, 79 },
        (Colour){ 191, 105, 79 },
        (Colour){ 197, 108, 82 },
        (Colour){ 213, 130, 102 },
        (Colour){ 223, 255, 221 }
    };

    // =================================== TEETH ===================================
    emojiSignatures[TEETH_UP] = (EmojiSignature){
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 195, 99 },
        (Colour){ 228, 255, 221 },
        (Colour){ 251, 188, 95 },
        (Colour){ 255, 192, 96 },
        (Colour){ 82, 66, 38 },
        (Colour){ 255, 195, 97 },
        (Colour){ 222, 255, 222 },
        (Colour){ 255, 190, 98 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 195, 99 },
        (Colour){ 102, 98, 76 },
        (Colour){ 255, 189, 99 },
        (Colour){ 255, 194, 95 },
        (Colour){ 98, 76, 44 },
        (Colour){ 255, 195, 96 },
        (Colour){ 222, 255, 220 },
        (Colour){ 255, 190, 96 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 225, 255, 220 },
        (Colour){ 255, 193, 98 }
    };

    emojiSignatures[TEETH_LEFT] = (EmojiSignature){
        (Colour){ 255, 193, 93 },
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 193, 95 },
        (Colour){ 251, 188, 95 },
        (Colour){ 255, 193, 96 },
        (Colour){ 255, 189, 96 },
        (Colour){ 255, 195, 96 },
        (Colour){ 172, 127, 70 },
        (Colour){ 162, 130, 66 },
        (Colour){ 124, 102, 57 },
        (Colour){ 242, 184, 95 },
        (Colour){ 255, 196, 98 },
        (Colour){ 89, 79, 60 },
        (Colour){ 216, 229, 197 },
        (Colour){ 210, 216, 188 },
        (Colour){ 89, 82, 63 },
        (Colour){ 95, 79, 51 },
        (Colour){ 79, 63, 44 },
        (Colour){ 86, 76, 54 },
        (Colour){ 86, 76, 54 },
        (Colour){ 79, 66, 44 },
        (Colour){ 165, 124, 70 }
    };

    emojiSignatures[TEETH_DOWN] = (EmojiSignature){
        (Colour){ 230, 255, 222 },
        (Colour){ 210, 153, 79 },
        (Colour){ 255, 190, 98 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 196, 100 },
        (Colour){ 224, 255, 224 },
        (Colour){ 219, 159, 82 },
        (Colour){ 111, 92, 51 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 194, 98 },
        (Colour){ 130, 130, 108 },
        (Colour){ 235, 172, 89 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 196, 99 },
        (Colour){ 227, 255, 219 },
        (Colour){ 251, 184, 95 },
        (Colour){ 124, 102, 57 },
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 195, 99 },
        (Colour){ 230, 255, 222 },
        (Colour){ 255, 191, 97 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 207, 116 }
    };

    emojiSignatures[TEETH_RIGHT] = (EmojiSignature){
        (Colour){ 73, 63, 51 },
        (Colour){ 172, 178, 153 },
        (Colour){ 172, 172, 146 },
        (Colour){ 79, 70, 54 },
        (Colour){ 108, 86, 54 },
        (Colour){ 70, 57, 41 },
        (Colour){ 86, 82, 63 },
        (Colour){ 89, 86, 63 },
        (Colour){ 76, 63, 44 },
        (Colour){ 146, 111, 63 },
        (Colour){ 117, 92, 51 },
        (Colour){ 92, 79, 44 },
        (Colour){ 89, 76, 44 },
        (Colour){ 165, 137, 73 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 191, 94 },
        (Colour){ 255, 194, 95 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 191, 95 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 200, 108 }
    };

    // =================================== THINKING ===================================
    emojiSignatures[THINKING_UP] = (EmojiSignature){
        (Colour){ 255, 192, 94 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 184, 93 },
        (Colour){ 255, 149, 80 },
        (Colour){ 255, 142, 78 },
        (Colour){ 70, 51, 35 },
        (Colour){ 255, 196, 96 },
        (Colour){ 255, 187, 93 },
        (Colour){ 255, 186, 94 },
        (Colour){ 255, 143, 77 },
        (Colour){ 255, 190, 93 },
        (Colour){ 255, 194, 97 },
        (Colour){ 204, 146, 79 },
        (Colour){ 255, 155, 82 },
        (Colour){ 255, 145, 78 },
        (Colour){ 79, 63, 38 },
        (Colour){ 255, 194, 97 },
        (Colour){ 226, 172, 89 },
        (Colour){ 255, 141, 76 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 185, 94 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 195, 96 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 252, 192 }
    };

    emojiSignatures[THINKING_LEFT] = (EmojiSignature){
        (Colour){ 66, 54, 35 },
        (Colour){ 153, 114, 60 },
        (Colour){ 245, 181, 92 },
        (Colour){ 210, 153, 79 },
        (Colour){ 255, 190, 93 },
        (Colour){ 191, 143, 73 },
        (Colour){ 255, 191, 95 },
        (Colour){ 255, 191, 95 },
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 194, 94 },
        (Colour){ 255, 195, 99 },
        (Colour){ 226, 172, 89 },
        (Colour){ 117, 98, 54 },
        (Colour){ 255, 160, 83 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 183, 91 },
        (Colour){ 255, 188, 94 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 140, 77 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 198, 100 },
        (Colour){ 255, 190, 98 },
        (Colour){ 255, 144, 79 },
        (Colour){ 255, 143, 77 },
        (Colour){ 255, 172, 108 }
    };

    emojiSignatures[THINKING_DOWN] = (EmojiSignature){
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 193, 98 },
        (Colour){ 255, 197, 97 },
        (Colour){ 255, 189, 94 },
        (Colour){ 255, 193, 99 },
        (Colour){ 255, 143, 77 },
        (Colour){ 108, 89, 51 },
        (Colour){ 255, 197, 98 },
        (Colour){ 168, 127, 70 },
        (Colour){ 255, 195, 98 },
        (Colour){ 255, 152, 82 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 196, 97 },
        (Colour){ 255, 192, 95 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 176, 89 },
        (Colour){ 255, 164, 85 },
        (Colour){ 255, 196, 98 },
        (Colour){ 82, 63, 44 },
        (Colour){ 255, 193, 99 },
        (Colour){ 255, 152, 80 },
        (Colour){ 255, 196, 96 },
        (Colour){ 255, 199, 97 },
        (Colour){ 255, 193, 95 },
        (Colour){ 255, 196, 99 }
    };

    emojiSignatures[THINKING_RIGHT] = (EmojiSignature){
        (Colour){ 239, 133, 73 },
        (Colour){ 229, 127, 70 },
        (Colour){ 255, 164, 87 },
        (Colour){ 255, 195, 97 },
        (Colour){ 255, 206, 117 },
        (Colour){ 245, 137, 76 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 196, 97 },
        (Colour){ 255, 194, 97 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 184, 93 },
        (Colour){ 255, 191, 98 },
        (Colour){ 255, 194, 98 },
        (Colour){ 255, 196, 98 },
        (Colour){ 255, 197, 98 },
        (Colour){ 255, 191, 94 },
        (Colour){ 255, 192, 96 },
        (Colour){ 255, 193, 95 },
        (Colour){ 86, 70, 41 },
        (Colour){ 255, 190, 95 },
        (Colour){ 255, 193, 96 },
        (Colour){ 255, 188, 94 },
        (Colour){ 255, 192, 97 },
        (Colour){ 108, 82, 47 },
        (Colour){ 255, 191, 95 }
    };
}


static void loadEmojiNames() {
    emojiNames[CRYING_LAUGHTER_UP] = "cry_laugh_u";
    emojiNames[CRYING_LAUGHTER_LEFT] = "cry_laugh_l";
    emojiNames[CRYING_LAUGHTER_DOWN] = "cry_laugh_d";
    emojiNames[CRYING_LAUGHTER_RIGHT] = "cry_laugh_r";
    emojiNames[HEART_EYES_UP] = "heart_eyes_u";
    emojiNames[HEART_EYES_LEFT] = "heart_eyes_l";
    emojiNames[HEART_EYES_DOWN] = "heart_eyes_d";
    emojiNames[HEART_EYES_RIGHT] = "heart_eyes_r";
    emojiNames[POOL_OF_TEARS_UP] = "pool_of_tears_u";
    emojiNames[POOL_OF_TEARS_LEFT] = "pool_of_tears_l";
    emojiNames[POOL_OF_TEARS_DOWN] = "pool_of_tears_d";
    emojiNames[POOL_OF_TEARS_RIGHT] = "pool_of_tears_r";
    emojiNames[RED_CHEEKS_UP] = "red_cheeks_u";
    emojiNames[RED_CHEEKS_LEFT] = "red_cheeks_l";
    emojiNames[RED_CHEEKS_DOWN] = "red_cheeks_d";
    emojiNames[RED_CHEEKS_RIGHT] = "red_cheeks_r";
    emojiNames[SAD_UP] = "sad_u";
    emojiNames[SAD_LEFT] = "sad_l";
    emojiNames[SAD_DOWN] = "sad_d";
    emojiNames[SAD_RIGHT] = "sad_r";
    emojiNames[SHADES_UP] = "shades_u";
    emojiNames[SHADES_LEFT] = "shades_l";
    emojiNames[SHADES_DOWN] = "shades_d";
    emojiNames[SHADES_RIGHT] = "shades_r";
    emojiNames[SMILE_UP] = "smile_u";
    emojiNames[SMILE_LEFT] = "smile_l";
    emojiNames[SMILE_DOWN] = "smile_d";
    emojiNames[SMILE_RIGHT] = "smile_r";
    emojiNames[SMILING_PILE_OF_POO_UP] = "smiling_poo_u";
    emojiNames[SMILING_PILE_OF_POO_LEFT] = "smiling_poo_l";
    emojiNames[SMILING_PILE_OF_POO_DOWN] = "smiling_poo_d";
    emojiNames[SMILING_PILE_OF_POO_RIGHT] = "smiling_poo_r";
    emojiNames[TEETH_UP] = "teeth_u";
    emojiNames[TEETH_LEFT] = "teeth_l";
    emojiNames[TEETH_DOWN] = "teeth_d";
    emojiNames[TEETH_RIGHT] = "teeth_r";
    emojiNames[THINKING_UP] = "thinking_u";
    emojiNames[THINKING_LEFT] = "thinking_l";
    emojiNames[THINKING_DOWN] = "thinking_d";
    emojiNames[THINKING_RIGHT] = "thinking_r";
}


static void getDataFromPlatform() {
    const Vector3D platformDims = Motion_getPlatformDimensions();
    const Vector3D platformOrigin = Motion_getPlatformOrigin();

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_EMOJI; pointIdx++) {
        // 1. Fetch the emoji-space (-1.0, 1.0) critical point to be tested
        EmojiPoint* criticalPoint = &criticalPoints[pointIdx];

        // 2. Convert this point into platform coordinates and move the scan head there
        uint16_t x = platformOrigin.x + (int)((criticalPoint->x + 1.0f) * 0.5f * platformDims.x);
        uint16_t y = platformOrigin.y + (int)((criticalPoint->y + 1.0f) * 0.5f * platformDims.y);
        Motion_moveTo(x, y, 0);

        // 3. Store the colour at this point
        platformReading.criticalPointColours[pointIdx] = ColourSensor_read();
    }
}


static uint32_t calcErrorBetween(EmojiId emojiId) {
    uint32_t error = 0;

    uint8_t pointIdx = 0;
    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_EMOJI; pointIdx++) {
        EmojiPoint* criticalPoint = &criticalPoints[pointIdx];

        Colour colourReading = platformReading.criticalPointColours[pointIdx];
        Colour expectedColour = emojiSignatures[emojiId].criticalPointColours[pointIdx];

        error += pow(colourReading.r - expectedColour.r, 2) + pow(colourReading.g - expectedColour.g, 2) + pow(colourReading.b - expectedColour.b, 2);
    }

    return error;
}


void EmojiRecogniser_showDevMenu() {
    LCDMenu emojiSelectMenu = LCDMenu_create();
    LCDMenu_addItem(&emojiSelectMenu, "Gather emoji data", &printColoursAtCriticalPoints);
    LCDMenu_run(&emojiSelectMenu);
}


void printColoursAtCriticalPoints() {
    init();
    TextOutput_init();

    Motion_home();

    TextOutput_print("Emoji colours at critical points");

    uint8_t pointIdx = 0;
    const Vector3D platformDims = Motion_getPlatformDimensions();
    const Vector3D platformOrigin = Motion_getPlatformOrigin();

    for(pointIdx = 0; pointIdx < NUM_CRITICAL_POINTS_PER_EMOJI; pointIdx++) {
        // 1. Move the sensor to the critical point to be tested
        EmojiPoint* criticalPoint = &criticalPoints[pointIdx];

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