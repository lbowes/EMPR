#include "TextOutputUtils.h"

#include <mbed/TextOutput.h>

#include <stdio.h>


void TextOutputUtils_printColour(Colour colour) {
    char buf[32];
    sprintf(buf, "rgb(%i, %i, %i)", colour.r, colour.g, colour.b);
    TextOutput_print(&buf[0]);
}


void TextOutputUtils_printVector3D(Vector3D vec) {
    char buf[32];
    sprintf(buf, "rgb(%i, %i, %i)\n", vec.x, vec.y, vec.z);
    TextOutput_print(&buf[0]);
}