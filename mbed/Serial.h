#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t serial_read(uint8_t *buffer, int length);

void serial_sendRGB (uint8_t raw_r,uint8_t raw_g,uint8_t raw_b,uint8_t raw_c);

void serial_init(void);