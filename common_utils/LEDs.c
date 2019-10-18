#include "LEDs.h"
#include "Constants.h"

#include <lpc17xx_gpio.h>


#define LED_PORT_NUM 1


static uint32_t LEDBitStates[NUMBER_OF_LEDS] = {
    0x00040000,
    0x00100000,
    0x00200000,
    0x00800000
};


void LEDs_init(void) {
    uint8_t ledIdx = 0;
    for(ledIdx = 0; ledIdx < NUMBER_OF_LEDS; ledIdx++)
        GPIO_SetDir(LED_PORT_NUM, LEDBitStates[ledIdx], OUTPUT);
}


void LEDs_turnOn(uint8_t led_num) {
    GPIO_SetValue(LED_PORT_NUM, LEDBitStates[led_num]);
}


void LEDs_turnOff(uint8_t led_num) {
    GPIO_ClearValue(LED_PORT_NUM, LEDBitStates[led_num]);
}


void LEDs_debug(uint32_t debugValue) {
    uint32_t led_val = 0;
    debugValue = debugValue << 18;
    led_val = LEDBitStates[0] & (debugValue);
    led_val += LEDBitStates[1] & (debugValue << 1);
    led_val += LEDBitStates[2] & (debugValue << 1);
    led_val += LEDBitStates[3] & (debugValue << 2);
    GPIO_SetValue(LED_PORT_NUM, led_val);
}
