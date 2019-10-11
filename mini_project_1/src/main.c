#include <lpc17xx_gpio.h>

#define OUTPUT 1
#define INPUT 0

#define LED_PORT_NUM 1
#define NUMBER_OF_LEDS 4


uint32_t LEDBitStates[NUMBER_OF_LEDS] = {
    0x00040000,
    0x00100000,
    0x00200000,
    0x00800000
};


void setAllLEDGPIOsToOutput() {
    uint8_t ledIdx = 0;
    for(ledIdx = 0; ledIdx < NUMBER_OF_LEDS; ledIdx++)
        GPIO_SetDir(LED_PORT_NUM, LEDBitStates[ledIdx], OUTPUT);
}


void turnOnLED(uint8_t led_num) {
    GPIO_SetValue(LED_PORT_NUM, LEDBitStates[led_num]);
}


void turnOffLED(uint8_t led_num) {
    GPIO_ClearValue(LED_PORT_NUM, LEDBitStates[led_num]);
}


void TEMP_delay1Second() {
    uint32_t count = 0;
    uint32_t i = 0;

    for(i = 0xFFFFF000; i < 0xFFFFFFFF; i++) {
        uint32_t j = 0;
        for(j = 0XFFFFF900; j < 0xFFFFFFFF; j++)
            count++;
    }
}


void TEMP_cycleAllLEDsOn() {
    uint8_t ledIdx = 0;
    for(ledIdx = 0; ledIdx < NUMBER_OF_LEDS; ledIdx++) {
        turnOnLED(ledIdx);
        TEMP_delay1Second();
        turnOffLED(ledIdx);
    }
}


int main() {
    setAllLEDGPIOsToOutput();

    uint8_t i = 0;
    const uint8_t cycleCount = 2;
    for(i = 0; i < cycleCount; i++)
        TEMP_cycleAllLEDsOn();

    return 0;
}
