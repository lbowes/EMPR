#define IN_LAB 1
#include "ColourSensor.h"

#if IN_LAB
#include <mbed/I2C.h>
#include <mbed/Delay.h>
#include <mbed/Constants.h>
#else
static void i2c_init(void) { }
static void i2c_send_data(uint8_t address, uint8_t *dataSource, uint32_t dataLength) { }
static void i2c_receiveDataFrom(uint8_t address, uint8_t *dataDest, uint32_t dataLength) { }
static void Delay_ms() { }
#endif

#include <math.h>


// CODE LIFTED FROM
// https://github.com/adafruit/Adafruit_TCS34725

#define TCS34725_ADDRESS     (0x29)
#define TCS34725_COMMAND_BIT (0x80)
#define TCS34725_ATIME       (0x01)
#define TCS34725_ID          (0x12)
#define TCS34725_CONTROL     (0x0F)
#define TCS34725_ENABLE      (0x00)
#define TCS34725_ENABLE_PON  (0x01)
#define TCS34725_ENABLE_AEN  (0x02)
#define TCS34725_CDATAL      (0x14)
#define TCS34725_CDATAH      (0x15)
#define TCS34725_RDATAL      (0x16)
#define TCS34725_RDATAH      (0x17)
#define TCS34725_GDATAL      (0x18)
#define TCS34725_GDATAH      (0x19)
#define TCS34725_BDATAL      (0x1A)
#define TCS34725_BDATAH      (0x1B)

#define MAX_COLOUR_VALUE     10240

/** Integration time settings for TCS34725 */
typedef enum {
    TCS34725_INTEGRATIONTIME_2_4MS = 0xFF, /**<  2.4ms - 1 cycle    - Max Count: 1024  */
    TCS34725_INTEGRATIONTIME_24MS = 0xF6,  /**<  24ms  - 10 cycles  - Max Count: 10240 */
    TCS34725_INTEGRATIONTIME_50MS = 0xEB,  /**<  50ms  - 20 cycles  - Max Count: 20480 */
    TCS34725_INTEGRATIONTIME_101MS = 0xD5, /**<  101ms - 42 cycles  - Max Count: 43008 */
    TCS34725_INTEGRATIONTIME_154MS = 0xC0, /**<  154ms - 64 cycles  - Max Count: 65535 */
    TCS34725_INTEGRATIONTIME_700MS = 0x00  /**<  700ms - 256 cycles - Max Count: 65535 */
} tcs34725IntegrationTime_t;

/** Gain settings for TCS34725  */
typedef enum {
    TCS34725_GAIN_1X = 0x00,  /**<  No gain  */
    TCS34725_GAIN_4X = 0x01,  /**<  4x gain  */
    TCS34725_GAIN_16X = 0x02, /**<  16x gain */
    TCS34725_GAIN_60X = 0x03  /**<  60x gain */
} tcs34725Gain_t;

static uint8_t sIntegrationTime = 0;

static void initIntegrationTime();
static void integrationDelay();
static void initGain();
static void enable();
static void write8(uint8_t reg, uint8_t value);
static uint16_t read16(uint8_t reg);
static void postProcess(Colour* rawData);


void ColourSensor_init() {
    i2c_init();

    initIntegrationTime();
    initGain();

    enable();
}


static void initIntegrationTime() {
    sIntegrationTime = TCS34725_INTEGRATIONTIME_2_4MS;
    write8(TCS34725_ATIME, sIntegrationTime);
}


static void write8(uint8_t reg, uint8_t value) {
    uint8_t cmd = TCS34725_COMMAND_BIT | reg;
    i2c_send_data(TCS34725_ADDRESS, &cmd, 1);

    uint8_t data = value & 0xFF;
    i2c_send_data(TCS34725_ADDRESS, &data, 1);
}


static void initGain() {
    uint8_t gain = TCS34725_GAIN_1X;
    write8(TCS34725_CONTROL, gain);
}


static void enable() {
    write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
    Delay_ms(3);
    write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);

    integrationDelay();
}


static void integrationDelay() {
    switch (sIntegrationTime) {
    case TCS34725_INTEGRATIONTIME_2_4MS:
        Delay_ms(3);
        break;
    case TCS34725_INTEGRATIONTIME_24MS:
        Delay_ms(24);
        break;
    case TCS34725_INTEGRATIONTIME_50MS:
        Delay_ms(50);
        break;
    case TCS34725_INTEGRATIONTIME_101MS:
        Delay_ms(101);
        break;
    case TCS34725_INTEGRATIONTIME_154MS:
        Delay_ms(154);
        break;
    case TCS34725_INTEGRATIONTIME_700MS:
        Delay_ms(700);
        break;
    }
}


Colour ColourSensor_read() {
    Colour reading;

    reading.r = read16(TCS34725_RDATAL);
    reading.g = read16(TCS34725_GDATAL);
    reading.b = read16(TCS34725_BDATAL);
    reading.clear = read16(TCS34725_CDATAL);

    postProcess(&reading);

    return reading;
}


static void postProcess(Colour* rawData) {
    // Get the maximum value to use when scaling all components
    uint16_t max = MAX_COLOUR_VALUE;

    if(rawData->r > max)
        max = rawData->r;
    else if(rawData->g > max)
        max = rawData->r;
    else if(rawData->b > max)
        max = rawData->r;

    float maxF = (float)max;

    // Convert integer colour readings into floats for post processing
    float r = rawData->r;
    float g = rawData->g;
    float b = rawData->b;

    // Normalise all components between 0 and 1
    r = r / maxF;
    g = g / maxF;
    b = b / maxF;

    // Apply non-linear 'S' shape to make light colours darker
    // and darker colours lighter
    r -= 0.2f * (0.5f * (1.0f + sin(2.0f * M_PI * r)) - 0.5f);
    g -= 0.2f * (0.5f * (1.0f + sin(2.0f * M_PI * g)) - 0.5f);
    b -= 0.2f * (0.5f * (1.0f + sin(2.0f * M_PI * b)) - 0.5f);

    // Scale all components by 255
    r *= 255;
    g *= 255;
    b *= 255;

    // Complete the process by modifying the input rawData
    rawData->r = r;
    rawData->g = g;
    rawData->b = b;
}

static uint16_t read16(uint8_t reg) {
    uint8_t writeData = TCS34725_COMMAND_BIT | reg;
    i2c_send_data(TCS34725_ADDRESS, &writeData, 1);

    uint16_t result = 0;
    i2c_receiveDataFrom(TCS34725_ADDRESS, &result, 2);

    return result;
}
