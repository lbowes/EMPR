#include "common_utils/I2C.h"
#include "common_utils/RGBC.h"
#include "common_utils/TextOutput.h"
#include "Motion.h"
#include "PcSender.h"
#include "Scanners.h"

void SetupScan()
{
    // Enable text output
    TextOutput_init();
    // Enable RGBC
    RGBC_init();

    // Go home
    Motion_init();
    Motion_home();
}

// Simple Scan line by line with delay
void SimpleScan(void)
{
    SetupScan();

    //  Setup axis
    // TODO can make more efficient
    Axis xAxis = Motion_getAxis(EMPR_X_AXIS);
    Axis yAxis = Motion_getAxis(EMPR_Y_AXIS);
    Axis zAxis = Motion_getAxis(EMPR_Z_AXIS);

    // Todo refer to xAxis.max & yAxis
    while (xAxis.currentStepPos != 202)
    {
        while (yAxis.currentStepPos != 202)
        {
            // Get the updated Axis results
            xAxis = Motion_getAxis(EMPR_X_AXIS);
            yAxis = Motion_getAxis(EMPR_Y_AXIS);
            zAxis = Motion_getAxis(EMPR_Z_AXIS);

            // Get the RGBC scan
            RGBC result = RGBC_SCAN();
            // Send to interface
            PCSender_sendRGBAndPos(xAxis.currentStepPos, yAxis.currentStepPos, zAxis.currentStepPos, result.r, result.g, result.b, result.c);
            // Move to our next point
            Motion_toPoint(xAxis.currentStepPos, yAxis.currentStepPos + 2, zAxis.currentStepPos);
            // Use the motor delay to hold on
            delay();
        }
        // Update the axis
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // Move to the next point down
        Motion_toPoint(xAxis.currentStepPos + 2, 0, zAxis.currentStepPos);
    }
}

// Simple Scan line by line with no delay and no gap
void StreamSimpleScan(void)
{
    SetupScan();

    //  Setup axis
    // TODO can make more efficient
    Axis xAxis = Motion_getAxis(EMPR_X_AXIS);
    Axis yAxis = Motion_getAxis(EMPR_Y_AXIS);
    Axis zAxis = Motion_getAxis(EMPR_Z_AXIS);

    // Todo refer to xAxis.max & yAxis
    while (xAxis.currentStepPos != 202)
    {
        while (yAxis.currentStepPos != 202)
        {
            // Get the updated Axis results
            xAxis = Motion_getAxis(EMPR_X_AXIS);
            yAxis = Motion_getAxis(EMPR_Y_AXIS);
            zAxis = Motion_getAxis(EMPR_Z_AXIS);

            // Get the RGBC scan
            RGBC result = RGBC_SCAN();
            // Send to interface
            PCSender_sendRGBAndPos(xAxis.currentStepPos, yAxis.currentStepPos, zAxis.currentStepPos, result.r, result.g, result.b, result.c);
            // Move to our next point
            Motion_toPoint(xAxis.currentStepPos, yAxis.currentStepPos + 1, zAxis.currentStepPos);
        }
        // Update the axis
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // Move to the next point down
        Motion_toPoint(xAxis.currentStepPos + 1, 0, zAxis.currentStepPos);
    }
}

// Scans in both directions with no delay
void BetterSimpleScan(void)
{
    SetupScan();

    //  Setup axis
    // TODO can make more efficient
    Axis xAxis = Motion_getAxis(EMPR_X_AXIS);
    Axis yAxis = Motion_getAxis(EMPR_Y_AXIS);
    Axis zAxis = Motion_getAxis(EMPR_Z_AXIS);
    int backwards = 0;
    // Todo refer to xAxis.max & yAxis
    while (xAxis.currentStepPos != 202)
    {
        if (!backwards)
        {
            while (yAxis.currentStepPos != 202)
            {
                // Get the updated Axis results
                xAxis = Motion_getAxis(EMPR_X_AXIS);
                yAxis = Motion_getAxis(EMPR_Y_AXIS);
                zAxis = Motion_getAxis(EMPR_Z_AXIS);

                // Get the RGBC scan
                RGBC result = RGBC_SCAN();
                // Send to interface
                PCSender_sendRGBAndPos(xAxis.currentStepPos, yAxis.currentStepPos, zAxis.currentStepPos, result.r, result.g, result.b, result.c);
                // Move to our next point
                Motion_toPoint(xAxis.currentStepPos, yAxis.currentStepPos + 1, zAxis.currentStepPos);
            }
            backwards = 1;
        }
        else
        {
            while (yAxis.currentStepPos != 0)
            {
                // Get the updated Axis results
                xAxis = Motion_getAxis(EMPR_X_AXIS);
                yAxis = Motion_getAxis(EMPR_Y_AXIS);
                zAxis = Motion_getAxis(EMPR_Z_AXIS);

                // Get the RGBC scan
                RGBC result = RGBC_SCAN();
                // Send to interface
                PCSender_sendRGBAndPos(xAxis.currentStepPos, yAxis.currentStepPos, zAxis.currentStepPos, result.r, result.g, result.b, result.c);
                // Move to our next point
                Motion_toPoint(xAxis.currentStepPos, yAxis.currentStepPos - 1, zAxis.currentStepPos);
            }
            backwards = 0;
        }
        // Update the axis
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // Move to the next point down
        Motion_toPoint(xAxis.currentStepPos + 1, yAxis.currentStepPos, zAxis.currentStepPos);
    }
}

void PointScanner(Point points[])
{
    SetupScan();
    int index;
    for (index = 0; index < sizeof(points) / sizeof(Point); index++)
    {
        Motion_toPoint(points[index].x, points[index].y, points[index].z);
        // Get the RGBC scan
        RGBC result = RGBC_SCAN();
        // Send to interface
        PCSender_sendRGBAndPos(xAxis.currentStepPos, yAxis.currentStepPos, zAxis.currentStepPos, result.r, result.g, result.b, result.c);
    }
}