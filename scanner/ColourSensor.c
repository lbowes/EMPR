#include "ColourSensor.h"

#include <mbed/I2C.h>
#include <mbed/Delay.h>
#include <mbed/Constants.h>

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

#define MAX_COLOUR_VALUE     20480

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
static void initWait();
static void initIntegrationTime();
static void integrationDelay();
static void initGain();
static void enable();
static void write8(uint8_t reg, uint8_t value);
static uint16_t read16(uint8_t reg);
static void postProcess(Colour* rawData);
static void write16(uint8_t reg, uint8_t value);
uint8_t * readAuto16(uint8_t reg);


void ColourSensor_init() {
    i2c_init();
    Delay_ms(3);
    Delay_ms(3);
    initIntegrationTime();
    Delay_ms(3);
    initGain();
    Delay_ms(3);
    initWait();
    Delay_ms(3);
    write16(0x0D, 0X00);
    Delay_ms(3);
    enable();
}


static void initWait() {
    uint8_t WTIME = 0X03;
    write16(WTIME, 0XFF);
}


static void initIntegrationTime() {
    sIntegrationTime = 0XFF;
    write16(TCS34725_ATIME, 0XFF);
}


static void write16(uint8_t reg, uint8_t value) {
    uint8_t cmd = (TCS34725_COMMAND_BIT | reg);
    uint8_t data = value;
    uint8_t package = {cmd, data};
    i2c_send_data(TCS34725_ADDRESS, &package, 2);

}


static void write8(uint8_t reg, uint8_t value) {
    uint8_t cmd = (TCS34725_COMMAND_BIT | reg);
    i2c_send_data(TCS34725_ADDRESS, &cmd, 1);

   // Very confused what the point of this is?
   uint8_t data = value; // & 0xFF;
   i2c_send_data(TCS34725_ADDRESS, &data, 1);
}


static void initGain() {
    uint8_t gain = TCS34725_GAIN_1X;
    write16(TCS34725_CONTROL, gain);
}


static void enable() {
    write16(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
    //integrationDelay();
}


static void integrationDelay() {
    switch (sIntegrationTime) {
    case TCS34725_INTEGRATIONTIME_2_4MS:
        Delay_ms(8);
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


Colour ColourSensor_seq() {
    Colour seq_read;
    uint8_t *vals;
    vals = readAuto16(TCS34725_CDATAL);
    seq_read.clear = ((*(vals+1)<<8) | *(vals));
    seq_read.r = ((*(vals+3)<<8) | *(vals+2));
    seq_read.g = ((*(vals+5)<<8) | *(vals+4));
    seq_read.b = ((*(vals+7)<<8) | *(vals+6));
    return seq_read;
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
    uint16_t max = 0;

    if(rawData->r > max)
        max = rawData->r;
    if(rawData->g > max)
        max = rawData->g;
    if(rawData->b > max)
        max = rawData->b;

    rawData->r = (int)((float)rawData->r / max * 255);
    rawData->g = (int)((float)rawData->g / max * 255);
    rawData->b = (int)((float)rawData->b / max * 255);
}


uint8_t * readAuto16(uint8_t reg) {
    static uint8_t list_result[8];
    uint8_t writeData = TCS34725_COMMAND_BIT | 0x10 | reg; // 0X10 AUTO INC MODE
    i2c_send_data(TCS34725_ADDRESS, &writeData, 1);
    i2c_receiveDataFrom(TCS34725_ADDRESS, &list_result, 8);
    return list_result;
}


static uint16_t read16(uint8_t reg) {
    uint8_t writeData = TCS34725_COMMAND_BIT | reg;
    i2c_send_data(TCS34725_ADDRESS, &writeData, 1);

    uint16_t result = 0;
    i2c_receiveDataFrom(TCS34725_ADDRESS, &result, 2);

    return result;
}