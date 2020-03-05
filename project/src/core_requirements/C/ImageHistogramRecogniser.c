#include "ImageHistogramRecogniser.h"

#include <scanner/Image.h>

//temp - for data gathering
#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>
#include <mbed/TextOutput.h>
#include <mbed/LCDMenu.h>
#include <mbed/Constants.h>
//


void ImageHistogramRecogniser_init() {

}


void ImageHistogramRecogniser_gatherData() {

}


uint32_t ImageHistogramRecogniser_errorFunc(FlagId flagId) {
    uint32_t error = 0;

    return error;
}


// =================== DATA GATHERING UTILITY FUNCTIONS ======================
static void scanFlagFull(FlagId flagId) {
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

    const Vector3D platformDims = Motion_getPlatformDimensions();
    const Vector3D platformOrigin = Motion_getPlatformOrigin();

    uint16_t xi = 0;
    uint16_t yi = 0;

#define FULL_RES 1
#if FULL_RES
    for(xi = 0; xi < platformDims.x; xi++) {
        for(yi = 0; yi < platformDims.y; yi++) {
#else
    for(xi = 0; xi < platformDims.x; xi += 29) {
        for(yi = 0; yi < platformDims.y; yi += 29) {
#endif
            Motion_moveTo(platformOrigin.x + xi, platformOrigin.y + yi, 0);
            Colour reading = ColourSensor_read();
            TextOutputUtils_printColour(reading);
        }

        Motion_moveAxisToLimit(EMPR_Y_AXIS);
    }

    TextOutput_println("");

    Motion_neutraliseAllAxes();
}


static void scanUnitedKingdomFull() { scanFlagFull(UNITED_KINGDOM); }
static void scanFranceFull() { scanFlagFull(FRANCE); }
static void scanSyriaFull() { scanFlagFull(SYRIA); }
static void scanIcelandFull() { scanFlagFull(ICELAND); }
static void scanSudanFull() { scanFlagFull(SUDAN); }
static void scanNorthMacedoniaFull() { scanFlagFull(NORTH_MACEDONIA); }
static void scanCzechiaFull() { scanFlagFull(CZECHIA); }
static void scanBurkinaFasoFull() { scanFlagFull(BURKINA_FASO); }
static void scanAfricanRepublicFull() { scanFlagFull(CENTRAL_AFRICAN_REBUBLIC); }
static void scanBurundiFull() { scanFlagFull(BURUNDI); }


void gatherImageHistogramData() {
    // This function should allow the user to collect all flag data necessary at the critical points
    Motion_init();
    ColourSensor_init();
    TextOutput_init();

    LCDMenu flagSelectMenu = LCDMenu_create();

    LCDMenu_addItem(&flagSelectMenu, "United Kingom", &scanUnitedKingdomFull);
    LCDMenu_addItem(&flagSelectMenu, "France", &scanFranceFull);
    LCDMenu_addItem(&flagSelectMenu, "Syria", &scanSyriaFull);
    LCDMenu_addItem(&flagSelectMenu, "Iceland", &scanIcelandFull);
    LCDMenu_addItem(&flagSelectMenu, "Sudan", &scanSudanFull);
    LCDMenu_addItem(&flagSelectMenu, "North Macedonia", &scanNorthMacedoniaFull);
    LCDMenu_addItem(&flagSelectMenu, "Czechia", &scanCzechiaFull);
    LCDMenu_addItem(&flagSelectMenu, "Burkina Faso", &scanBurkinaFasoFull);
    LCDMenu_addItem(&flagSelectMenu, "Cent.Africa.Rep.", &scanAfricanRepublicFull);
    LCDMenu_addItem(&flagSelectMenu, "Burundi", &scanBurundiFull);

    LCDMenu_run(&flagSelectMenu);
}