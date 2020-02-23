#include "ImageHistogramRecogniser.h"

#include <scanner/Image.h>


// TODO: Define the data required required for this method of flag recognition
// ...

void ImageHistogramRecogniser_init() {

}


uint32_t ImageHistogramRecogniser_errorFunc(FlagId flagId) {
    uint32_t error = 0;

    // TODO: Calculate the error between the flag on the platform and that with ID `flagId`, using
    // image histograms.

    // 1. Scan the flag on the platform first and store the result in an `Image`.
    // Image platformContents = someScanFunction();

    return error;
}