#ifndef EMPR_LED_UTILS_H_
#define EMPR_LED_UTILS_H_


#include <stdint.h>

#define NUMBER_OF_LEDS 4

// ----- Public functions -----
void LED_init(void);

void LED_turnOn(uint8_t led_num);
void LED_turnOff(uint8_t led_num);


#endif // EMPR_LED_UTILS_H_
