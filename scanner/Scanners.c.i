#include "mbed/I2C.h"
#include "mbed/TextOutput.h"

#include "Motion.h"
#include "PcSender.h"
#include "Scanners.h"
#include "RGBC.h"
#include "mbed/Interrupts.h"
void SetupScan()
{
    // Enable text output
    TextOutput_init();
    // Enable RGBC
    RGBC_init();

    // Go home
    Motion_init();
}



// Simple Scan line by line with delay
void SimpleScan(void)
{
    SetupScan();
<<<<<<< HEAD:scanner/Scanners.c.i

    //  Setup axis
    // TODO can make more efficient
    Axis* xAxis = Motion_getAxis(EMPR_X_AXIS);
    Axis* yAxis = Motion_getAxis(EMPR_Y_AXIS);
    Axis* zAxis = Motion_getAxis(EMPR_Z_AXIS);

    // Todo refer to xAxis.max & yAxis
    while (xAxis->currentPos_steps != 202)
    {
        while (yAxis->currentPos_steps != 202)
=======
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    RGBC result;
    while (x < 200)
    {
        while (y < 237)
>>>>>>> 059ef79615ea109312fa59f14a9b0c219330fa8b:scanner/Scanners.c
        {
            Motion_toPoint(x, y, z);
            result = RGBC_SCAN();
            // PCSender_sendRGBAndPos(x,y,0, result.r, result.g, result.b, result.c);
            TextOutput_printInteger(y);
            y += 1;
        }
        y = y - 1;

<<<<<<< HEAD:scanner/Scanners.c.i
            // // Get the RGBC scan
            // RGBC result = RGBC_SCAN();
            // // Send to interface
            // PCSender_sendRGBAndPos(xAxis.currentPos_steps, yAxis.currentPos_steps, zAxis.currentPos_steps, result.r, result.g, result.b, result.c);
            // Move to our next point
            Motion_moveTo(xAxis->currentPos_steps, yAxis->currentPos_steps + 2, zAxis->currentPos_steps);
            // Use the motor delay to hold on
            //delay();
        }
        // Update the axis
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // Move to the next point down
        Motion_moveTo(xAxis->currentPos_steps + 2, 0, zAxis->currentPos_steps);
=======
        Motion_toPoint(x, y, z);
        x += 1;
        result = RGBC_SCAN();
        PCSender_sendRGBAndPos(x, y, 0, result.r, result.g, result.b, result.c);
        while (y > 0)
        {
            TextOutput_printInteger(y);
            Motion_toPoint(x, y, 0);
            result = RGBC_SCAN();
            PCSender_sendRGBAndPos(x, y, 0, result.r, result.g, result.b, result.c);
            y -= 1;
        }
        Motion_toPoint(x, y, 0);
        result = RGBC_SCAN();
        PCSender_sendRGBAndPos(x, y, 0, result.r, result.g, result.b, result.c);
        x += 1;
>>>>>>> 059ef79615ea109312fa59f14a9b0c219330fa8b:scanner/Scanners.c
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
    while (xAxis->currentPos_steps != 202)
    {
        while (yAxis->currentPos_steps != 202)
        {
            // Get the updated Axis results
            xAxis = Motion_getAxis(EMPR_X_AXIS);
            yAxis = Motion_getAxis(EMPR_Y_AXIS);
            zAxis = Motion_getAxis(EMPR_Z_AXIS);

            // Get the RGBC scan
            RGBC result = RGBC_SCAN();
            // Send to interface
            PCSender_sendRGBAndPos(xAxis->currentPos_steps, yAxis->currentPos_steps, zAxis->currentPos_steps, result.r, result.g, result.b, result.c);
            // Move to our next point
            Motion_moveTo(xAxis->currentPos_steps, yAxis->currentPos_steps + 1, zAxis->currentPos_steps);
        }
        // Update the axis
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // Move to the next point down
        Motion_moveTo(xAxis->currentPos_steps + 1, 0, zAxis->currentPos_steps);
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
    while (xAxis->currentPos_steps != 202)
    {
        if (!backwards)
        {
            while (yAxis->currentPos_steps != 202)
            {
                // Get the updated Axis results
                xAxis = Motion_getAxis(EMPR_X_AXIS);
                yAxis = Motion_getAxis(EMPR_Y_AXIS);
                zAxis = Motion_getAxis(EMPR_Z_AXIS);

                // Get the RGBC scan
                RGBC result = RGBC_SCAN();
                // Send to interface
                PCSender_sendRGBAndPos(xAxis->currentPos_steps, yAxis->currentPos_steps, zAxis->currentPos_steps, result.r, result.g, result.b, result.c);
                // Move to our next point
                Motion_moveTo(xAxis->currentPos_steps, yAxis->currentPos_steps + 1, zAxis->currentPos_steps);
            }
            backwards = 1;
        }
        else
        {
            while (yAxis->currentPos_steps != 0)
            {
                // Get the updated Axis results
                xAxis = Motion_getAxis(EMPR_X_AXIS);
                yAxis = Motion_getAxis(EMPR_Y_AXIS);
                zAxis = Motion_getAxis(EMPR_Z_AXIS);

                // Get the RGBC scan
                RGBC result = RGBC_SCAN();
                // Send to interface
                PCSender_sendRGBAndPos(xAxis->currentPos_steps, yAxis->currentPos_steps, zAxis->currentPos_steps, result.r, result.g, result.b, result.c);
                // Move to our next point
                Motion_moveTo(xAxis->currentPos_steps, yAxis->currentPos_steps - 1, zAxis->currentPos_steps);
            }
            backwards = 0;
        }
        // Update the axis
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // Move to the next point down
        Motion_moveTo(xAxis->currentPos_steps + 1, yAxis->currentPos_steps, zAxis->currentPos_steps);
    }
}

// void PointScanner(Point points[])
// {
//     SetupScan();
//     int index;
//     for (index = 0; index < sizeof(points) / sizeof(Point); index++)
//     {
//         Motion_moveTo(points[index].x, points[index].y, points[index].z);
//         // Get the RGBC scan
//         RGBC result = RGBC_SCAN();
//         // Send to interface
//         PCSender_sendRGBAndPos(xAxis.currentPos_steps, yAxis.currentPos_steps, zAxis.currentPos_steps, result.r, result.g, result.b, result.c);
//     }
// }