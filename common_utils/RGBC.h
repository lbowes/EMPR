#ifndef EMPR_RGBC_H_
#define EMPR_RGBC_H_

#include <stdint.h>

//Struct
typedef struct
{
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t c;
} RGBC;

//initialises the 7segment display
void RGBC_init(void);

// Scan 
RGBC RGBC_SCAN(void);
#endif // EMPR_I2C7SEG_H_