#include "common_utils/I2C.h"
#include "common_utils/RGBC.h"
#include "common_utils/TextOutput.h"
#include "Motion.h"
#include "PcSender.h"
void Interrupts_handleAll() {}

int main()
{
    // Enable text output
    TextOutput_init();
    // Enable RGBC
    RGBC_init();

    // Go home
    Motion_init();
    Motion_home();

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

    return 0;
}