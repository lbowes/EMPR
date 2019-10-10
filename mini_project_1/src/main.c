#include <lpc17xx_gpio.h>

#define OUTPUT 1
#define INPUT 0

#define LED_PORT_NUM 1
#define LED_0 0x00040000 // (bit 20)
#define LED_1 0x00100000 // (bit 23)
#define LED_2 0x00200000 // (bit 24)
#define LED_3 0x00800000 // (bit 25)


void initGPIO() {
    // Set all LED GPIO pins as output
    GPIO_SetDir(LED_PORT_NUM, LED_0, OUTPUT);
    GPIO_SetDir(LED_PORT_NUM, LED_1, OUTPUT);
    GPIO_SetDir(LED_PORT_NUM, LED_2, OUTPUT);
    GPIO_SetDir(LED_PORT_NUM, LED_3, OUTPUT);
}


void turnOnLED(uint32_t led_num) {
	GPIO_SetValue(LED_PORT_NUM, led_num);
}


void turnOffLED(uint32_t led_num) {
    GPIO_ClearValue(LED_PORT_NUM, led_num);
}


void TEMP_delay1Second() {
    uint32_t count = 0;
    uint32_t i = 0;
    uint32_t j = 0;

    for(i = 0xFFFFF000; i < 0xFFFFFFFF; i++) {
        for(j = 0XFFFFF900; j < 0xFFFFFFFF; j++)
            count++;
    }
}


void cycleAllLEDsOn() {
    turnOnLED(LED_0);
    TEMP_delay1Second();
    turnOffLED(LED_0);

    turnOnLED(LED_1);
    TEMP_delay1Second();
    turnOffLED(LED_1);

    turnOnLED(LED_2);
    TEMP_delay1Second();
    turnOffLED(LED_2);

    turnOnLED(LED_3);
    TEMP_delay1Second();
    turnOffLED(LED_3);
}


int main() {
    initGPIO();

    uint8_t i = 0;
    for(i = 0; i < 2; i++)
        cycleAllLEDsOn();

    return 0;
}
