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


void delay() {
    uint32_t count = 0;
    uint32_t i = 0;
    uint32_t j = 0;

    for(i = 0xFFFFF000; i < 0xFFFFFFFF; i++) {
        for(j = 0XFFFFFF00; j < 0xFFFFFFFF; j++)
            count++;
    }
}

int main() {
    initGPIO();

    while(1) {
        delay();
        turnOnLED(LED_0);

        delay();
        turnOnLED(LED_1);

        delay();
        turnOnLED(LED_2);

        delay();
        turnOnLED(LED_3);
    }

    return 0;
}
