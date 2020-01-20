#include "common_utils/I2C.h"
#include "common_utils/RGBC.h"
#include "common_utils/TextOutput.h"

void Interrupts_handleAll() { }

void delay() {
    int i, j, count = 0;
    for(i = 0; i < 1000; i++) {
        for(j = 0; j < 1000; j++)
            count++;
    }
}

int main() {
    TextOutput_init();
    RGBC_init();
    Motion_init();

    while(1) {
        RGBC test = RGBC_SCAN();
        TextOutput_printInteger(test.c);
        delay();
    }

    return 0;
}