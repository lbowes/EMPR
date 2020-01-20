#include "common_utils/I2C.h"
#include "common_utils/RGBC.h"
#include "common_utils/TextOutput.h"
#include "Motion.h"
#include "PcSender.h"
void Interrupts_handleAll() { }

int main() {
    TextOutput_init();
    RGBC_init();

    Motion_init();
    Motion_home();
    Axis xAxis = Motion_getAxis(EMPR_X_AXIS);
    Axis yAxis = Motion_getAxis(EMPR_Y_AXIS);
    Axis zAxis = Motion_getAxis(EMPR_Z_AXIS);
    while (xAxis.currentStepPos!=xAxis.maxSteps){
        while (yAxis.currentStepPos!=yAxis.maxSteps){
            RGBC result= RGBC_SCAN();
            // Send to interface
            PCSender_sendRGBAndPos(xAxis.currentStepPos,yAxis.currentStepPos,zAxis.currentStepPos,result.r,result.g,result.b);
            // Move to our next point
            Motion_toPoint(xAxis.currentStepPos,yAxis.currentStepPos+1,zAxis.currentStepPos);
        }
        // Start our new line
        Motion_toPoint(xAxis.currentStepPos+1,0,zAxis.currentStepPos);
    }

    return 0;
}