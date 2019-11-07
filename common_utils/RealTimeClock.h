#ifndef EMPR_REALTIME_CLOCK_H_
#define EMPR_REALTIME_CLOCK_H_
#include "lpc17xx_rtc.h"
void Real_Time_Clock_init(void);
RTC_TIME_Type Real_Time_Clock_Get_Time(void);
#endif