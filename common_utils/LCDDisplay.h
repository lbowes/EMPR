#include <stdbool.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#ifndef EMPR_LDCDISPLAY_H_
#define EMPR_LDCDISPLAY_H_
#define LINE_1 0
#define LINE_2 1
// TODO
// #include <lpkdjfx_lcddriver.h>
// #include <someOtherDriverHeader.h>

void LCDDisplay_init(void); // TODO: might pass in more options
// Takes in a line number of what you want to clear
void LCDDisplay_clear(unsigned int line_number);
// This function returns 0 if successfully executed otherwise it will show -numbers for errors
int LCDDisplay_print(const char* msg, unsigned int line_number);
// Outputs a progress bar on a line takes between 0 and 100
int LCDDisplay_progress_bar(unsigned int line_number, unsigned int progress);
#endif // EMPR_LDCDISPLAY_H_
