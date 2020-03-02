#include <scanner/Motion.h>
#include <scanner/ColourSensor.h>


int main() {
    Motion_init();
    ColourSensor_init();

    Motion_moveTo(0, 100, 10);

    return 0;
}