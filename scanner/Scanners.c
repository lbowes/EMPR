#include "mbed/I2C.h"
#include "mbed/TextOutput.h"
#include "stdlib.h"
#include "Motion.h"
#include "PcSender.h"
#include "Scanners.h"
#include "RGBC.h"
#include "mbed/Interrupts.h"
#include "mbed/Delay.h"
#include "mbed/RealTimeClock.h"
void SetupScan()
{
    // Enable text output
    TextOutput_init();
    // Enable RGBC
    RGBC_init();

    // Go home
    Motion_init();
}

void MoveAndWaitAndSend(uint8_t x,uint8_t y,uint8_t z,uint8_t delayMs)
{
    Motion_toPoint(x, y, z);
    Delay_ms(delayMs);
    RGBC result = RGBC_SCAN();

    PCSender_sendRGBAndPos(x, y, z, result.r, result.g, result.b, result.c);
}

void DelayScanTestSettings()
{
    SetupScan();
    Real_Time_Clock_init();
    uint8_t delayState = 0xFF;
    while (delayState>=0x00){
    
    uint8_t aTimeTx[] = {0x81,delayState};
    i2c_send_data(RGBC_I2C_SENSOR_ADDRESS,aTimeTx, sizeof(aTimeTx));

    uint32_t amountOfDelay = 3 * (abs(0xFF-delayState)+1);
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    // TextOutput_println("New Scan");
    // TextOutput_printInteger(delayState);
    // TextOutput_println("Time Start");
    // RTC_TIME_Type time = Real_Time_Clock_Get_Time();
    // TextOutput_printInteger(time.HOUR);
    // TextOutput_printInteger(time.MIN);
    // TextOutput_printInteger(time.SEC);
    TextOutput_println("Output");
    while (y < 200)
    {
        while (x < 200)
        {
            MoveAndWaitAndSend(x,y,z,amountOfDelay);
            x += 1;
        }
        MoveAndWaitAndSend(x,y,z,amountOfDelay);
        y += 1;

        while (x > 0)
        {
            MoveAndWaitAndSend(x,y,z,amountOfDelay);
            x -= 1;
        }
        MoveAndWaitAndSend(x,y,z,amountOfDelay);
        y += 1;
    }
    delayState-=1;
    // TextOutput_println("End");
    // TextOutput_println("Time End");
    // time = Real_Time_Clock_Get_Time();
    // TextOutput_printInteger(time.HOUR);
    // TextOutput_printInteger(time.MIN);
    // TextOutput_printInteger(time.SEC);
    Motion_neutraliseAll();
    Delay_ms(15000);
    }
}

// Simple Scan line by line with delay
void SimpleScan(void)
{
    SetupScan();
    uint32_t x = 100;
    uint32_t y = 100;
    uint32_t z = 0;
    RGBC result;
    while (x < 200)
    {
        while (y < 237)
        {
            Motion_toPoint(x, y, z);
            Delay_ms(5);
            result = RGBC_SCAN();
            PCSender_sendRGBAndPos(x, y, 0, result.r, result.g, result.b, result.c);
            y += 1;
        }
        y = y - 1;

        Motion_toPoint(x, y, z);
        Delay_ms(5);
        x += 1;
        result = RGBC_SCAN();
        PCSender_sendRGBAndPos(x, y, 0, result.r, result.g, result.b, result.c);
        while (y > 0)
        {

            Motion_toPoint(x, y, 0);
            Delay_ms(5);
            result = RGBC_SCAN();
            PCSender_sendRGBAndPos(x, y, 0, result.r, result.g, result.b, result.c);
            y -= 1;
        }
        Motion_toPoint(x, y, 0);
        Delay_ms(5);
        result = RGBC_SCAN();
        PCSender_sendRGBAndPos(x, y, 0, result.r, result.g, result.b, result.c);
        x += 1;
    }
}

// Simple Scan line by line with no delay and no gap
void StreamSimpleScan(void)
{
    SetupScan();

    //  Setup axis
    // TODO can make more efficient
    Axis *xAxis = Motion_getAxis(EMPR_X_AXIS);
    Axis *yAxis = Motion_getAxis(EMPR_Y_AXIS);
    Axis *zAxis = Motion_getAxis(EMPR_Z_AXIS);

    // Todo refer to xAxis.max & yAxis
    while (xAxis->currentStepPos != 202)
    {
        while (yAxis->currentStepPos != 202)
        {
            // Get the updated Axis results
            xAxis = Motion_getAxis(EMPR_X_AXIS);
            yAxis = Motion_getAxis(EMPR_Y_AXIS);
            zAxis = Motion_getAxis(EMPR_Z_AXIS);

            // Get the RGBC scan
            RGBC result = RGBC_SCAN();
            // Send to interface
            PCSender_sendRGBAndPos(xAxis->currentStepPos, yAxis->currentStepPos, zAxis->currentStepPos, result.r, result.g, result.b, result.c);
            // Move to our next point
            Motion_toPoint(xAxis->currentStepPos, yAxis->currentStepPos + 1, zAxis->currentStepPos);
        }
        // Update the axis
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // Move to the next point down
        Motion_toPoint(xAxis->currentStepPos + 1, 0, zAxis->currentStepPos);
    }
}

// Scans in both directions with no delay
void BetterSimpleScan(void)
{
    SetupScan();

    //  Setup axis
    // TODO can make more efficient
    Axis *xAxis = Motion_getAxis(EMPR_X_AXIS);
    Axis *yAxis = Motion_getAxis(EMPR_Y_AXIS);
    Axis *zAxis = Motion_getAxis(EMPR_Z_AXIS);
    int backwards = 0;
    // Todo refer to xAxis.max & yAxis
    while (xAxis->currentStepPos != 202)
    {
        if (!backwards)
        {
            while (yAxis->currentStepPos != 202)
            {
                // Get the updated Axis results
                xAxis = Motion_getAxis(EMPR_X_AXIS);
                yAxis = Motion_getAxis(EMPR_Y_AXIS);
                zAxis = Motion_getAxis(EMPR_Z_AXIS);

                // Get the RGBC scan
                RGBC result = RGBC_SCAN();
                // Send to interface
                PCSender_sendRGBAndPos(xAxis->currentStepPos, yAxis->currentStepPos, zAxis->currentStepPos, result.r, result.g, result.b, result.c);
                // Move to our next point
                Motion_toPoint(xAxis->currentStepPos, yAxis->currentStepPos + 1, zAxis->currentStepPos);
            }
            backwards = 1;
        }
        else
        {
            while (yAxis->currentStepPos != 0)
            {
                // Get the updated Axis results
                xAxis = Motion_getAxis(EMPR_X_AXIS);
                yAxis = Motion_getAxis(EMPR_Y_AXIS);
                zAxis = Motion_getAxis(EMPR_Z_AXIS);

                // Get the RGBC scan
                RGBC result = RGBC_SCAN();
                // Send to interface
                PCSender_sendRGBAndPos(xAxis->currentStepPos, yAxis->currentStepPos, zAxis->currentStepPos, result.r, result.g, result.b, result.c);
                // Move to our next point
                Motion_toPoint(xAxis->currentStepPos, yAxis->currentStepPos - 1, zAxis->currentStepPos);
            }
            backwards = 0;
        }
        // Update the axis
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // Move to the next point down
        Motion_toPoint(xAxis->currentStepPos + 1, yAxis->currentStepPos, zAxis->currentStepPos);
    }
}

// void PointScanner(Point points[])
// {
//     SetupScan();
//     int index;
//     for (index = 0; index < sizeof(points) / sizeof(Point); index++)
//     {
//         Motion_toPoint(points[index].x, points[index].y, points[index].z);
//         // Get the RGBC scan
//         RGBC result = RGBC_SCAN();
//         // Send to interface
//         PCSender_sendRGBAndPos(xAxis.currentStepPos, yAxis.currentStepPos, zAxis.currentStepPos, result.r, result.g, result.b, result.c);
//     }
// }