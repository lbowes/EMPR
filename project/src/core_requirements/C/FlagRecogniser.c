#include "FlagRecogniser.h"

#include <stdlib.h>


FlagId FlagRecogniser_run(DataGatherFunction dataGatherFunc, ErrorFunction errorFunc) {
    dataGatherFunc();

    FlagId closestFlag = rand() % FLAG_COUNT;
    uint16_t minError = 0;

    FlagId flagId = 0;
    for(flagId = FIRST_FLAG; flagId <= LAST_FLAG; flagId++) {
        uint32_t error = errorFunc(flagId);

        if(error < minError || flagId == 0) {
            closestFlag = flagId;
            minError = error;
        }
    }

    return closestFlag;
}