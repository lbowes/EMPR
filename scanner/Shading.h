#ifndef EMPR_SHADING_H_
#define EMPR_SHADING_H_
#include <stdint.h>
typedef struct {
    uint16_t row[3]; // Packed 4 bit values corresponding to shades of 3 squares within the row. These are known as blocks
} Grid;

void Shading_shade();
void Shading_scanShade();
#endif // EMPR_SHADING_H_
