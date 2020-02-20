#include "Image.h"

#include <stdbool.h>
#include <stdlib.h>


static bool isInside(Image* img, uint16_t x, uint16_t y);


Image Image_create(uint16_t width, uint16_t height) {
    Image image;

    image.width = width;
    image.height = height;
    image.data = (Colour*)calloc(width * height, sizeof(Colour));

    return image;
}


void Image_setColourAt(Image* dest, uint16_t x, uint16_t y, Colour c) {
    if(!isInside(dest, x, y))
        return;

    dest->data[y * dest->width + x] = c;
}


Colour Image_getColourAt(Image* source, uint16_t x, uint16_t y) {
    if(!isInside(source, x, y)) {
        Colour errorColour;
        errorColour.r = 0;
        errorColour.g = 0;
        errorColour.b = 0;
        errorColour.clear = 0;
        return errorColour;
    }

    return source->data[y * source->width + x];
}


void Image_destroy(Image* img) {
    free(img->data);
}


static bool isInside(Image* img, uint16_t x, uint16_t y) {
    return x < img->width && y < img->height;
}