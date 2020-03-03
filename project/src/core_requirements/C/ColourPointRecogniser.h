#ifndef EMPR_COLOURPOINTRECOGNITION_H_
#define EMPR_COLOURPOINTRECOGNITION_H_

#include "FlagRecogniser.h"


void ColourPointRecogniser_init();
void ColourPointRecogniser_gatherData();
uint32_t ColourPointRecogniser_errorFunc(FlagId flagId);

void temp_ColourSensor_gatherData();


#endif // EMPR_COLOURPOINTRECOGNITION_H_
