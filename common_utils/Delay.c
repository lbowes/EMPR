#include "Delay.h"
#define STCTRL 0xE000E010

#define STRELOAD 0xE000E014
#define STCURR 0xE000E018
#define STCALIB 0xE000E01C
#define tenMS 0xF234F
/*
#define DISABLE 0
#define ENABLE 1
#define TOGGLE 2
#define CLOCK_SOURCE 4
#define COUNTFLAG 0x10000
#define TIME 1000
*/
#define TIME 1000
int delayLoop

//void systick
// Systick is in main
void Delay_tenMS() {
    STCTRL = 7;
    STRELOAD = tenMS; 
} 
void Delay_varyingMS(uint32_t value)
{


}
