#include <common_utils/RealTimeClock.h>


// Init rtc
void Real_Time_Clock_init(){
    RTC_Init(LPC_RTC);
    RTC_Cmd(LPC_RTC,ENABLE);
}

// return time
RTC_TIME_Type Real_Time_Clock_Get_Time(){
        RTC_TIME_Type rtc;
        RTC_GetFullTime(LPC_RTC,&rtc);
        return rtc;
}