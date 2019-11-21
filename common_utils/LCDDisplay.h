#ifndef EMPR_LDCDISPLAY_H_
#define EMPR_LDCDISPLAY_H_

#include <stdbool.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>


#define LINE_1 0
#define LINE_2 1


void LCDDisplay_init(void);

void LCDDisplay_clear(unsigned int line_number);

// This function returns 0 if successfully executed otherwise it will show -numbers for errors
int LCDDisplay_print(const char *msg, unsigned int line_number);

int LCDDisplay_progress_bar(unsigned int line_number, unsigned int progress_0_100);


#endif // EMPR_LDCDISPLAY_H_
