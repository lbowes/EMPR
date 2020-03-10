#ifndef EMPR_IMAGEHISTOGRAMRECOGNISER_H
#define EMPR_IMAGEHISTOGRAMRECOGNISER_H

#include "FlagRecogniser.h"


void ImageHistogramRecogniser_init();
void ImageHistogramRecogniser_gatherData();
uint32_t ImageHistogramRecogniser_errorFunc(FlagId flagId);

//temp
void gatherImageHistogramData();
//


#endif // EMPR_IMAGEHISTOGRAMRECOGNISER_H
