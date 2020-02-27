#ifndef EMPR_COLOURSENSOR_H_
#define EMPR_COLOURSENSOR_H_

#include "Colour.h"

#include <stdint.h>


void ColourSensor_init();
Colour ColourSensor_read();
Colour ColourSensor_seq();

#endif // EMPR_COLOURSENSOR_H_
