#include "FlagRecogniser.h"

#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>
#include <stdlib.h>


FlagId FlagRecogniser_run(ErrorFunction errorFunc) {
    Motion_init();
    ColourSensor_init();

    FlagId closestFlag = rand() % FLAG_COUNT;
    uint8_t minSqrError = 0;

    FlagId flagId = 0;
    for(flagId = BRITAIN; flagId < ITALY; flagId++) {
        uint32_t error = errorFunc(flagId);

        if(error < minSqrError || flagId == 0) {
            closestFlag = flagId;
            minSqrError = error;
        }
    }

    return closestFlag;
}