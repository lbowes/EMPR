#include "FlagRecogniser.h"

#include <stdlib.h>

// temp
#include <mbed/TextOutput.h>
//


FlagId FlagRecogniser_run(DataGatherFunction dataGatherFunc, ErrorFunction errorFunc) {
    dataGatherFunc();

    FlagId closestFlag = rand() % FLAG_COUNT;
    uint8_t minSqrError = 0;

    FlagId flagId = 0;
    for(flagId = FIRST_FLAG; flagId <= LAST_FLAG; flagId++) {
        uint32_t error = errorFunc(flagId);

        TextOutput_printInteger(error);

        if(error < minSqrError || flagId == 0) {
            closestFlag = flagId;
            minSqrError = error;
        }
    }

    return closestFlag;
}