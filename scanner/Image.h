#ifndef EMPR_IMAGE_H_
#define EMPR_IMAGE_H_

#include "Colour.h"

#include <stdint.h>


typedef struct {
    uint16_t width;
    uint16_t height;
    Colour* data;
} Image;

Image Image_create(uint16_t width, uint16_t height);
void Image_setColourAt(Image* dest, uint16_t x, uint16_t y, Colour c);
Colour Image_getColourAt(Image* source, uint16_t x, uint16_t y);
void Image_destroy(Image* img);


#endif // EMPR_IMAGE_H_
