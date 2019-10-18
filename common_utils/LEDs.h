#ifndef EMPR_LED_UTILS_H_
#define EMPR_LED_UTILS_H_


#include <stdint.h>

#define NUMBER_OF_LEDS 4


// ----- Public functions -----
//
void LEDs_init(void);
void LEDs_turnOn(uint8_t led_num);
void LEDs_turnOff(uint8_t led_num);
void LEDS_debug(uint32_t message);

#endif // EMPR_LED_UTILS_H_
