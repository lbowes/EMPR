#include "I2CSniffer.h"

#include <mbed/TextOutput.h>
#include <mbed/I2C.h>
#include <stdio.h>
#include <stdbool.h>

static bool I2CSniffer_deviceExistsAt(int address)
{
    uint8_t dummyData[1] = {0x00};
    return i2c_send_data(address, &dummyData[0], 1) == SUCCESS;
}

static void I2CSniffer_reportDeviceFoundAt(uint8_t address)
{
    char notifcation[128];
    sprintf(notifcation, "Device found at address %d", address);
    TextOutput_print(notifcation);
}

void I2CSniffer_run(void)
{
    TextOutput_init();
    i2c_init();

    uint8_t queryAddress = 0;
    uint8_t numDevicesFound = 0;
    for (queryAddress = 0; queryAddress < 128; queryAddress++)
    {
        if (I2CSniffer_deviceExistsAt(queryAddress))
        {
            I2CSniffer_reportDeviceFoundAt(queryAddress);

            numDevicesFound++;
        }
    }

    char foundDevicesMsg[128];
    sprintf(foundDevicesMsg, "%d devices connected to i2c bus", numDevicesFound);
    TextOutput_print(foundDevicesMsg);
}