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
    // LOOK HERE THIS IS PROBABLY THE CAUSE OF THE PROBLEMS IF THERE ARE ANY THESE NEED TO REFERNCE THE ARRAY
    Axis xAxis = Motion_getAxis(EMPR_X_AXIS);
    Axis yAxis = Motion_getAxis(EMPR_Y_AXIS);
    Axis zAxis = Motion_getAxis(EMPR_Z_AXIS);
    // Motion_toPoint(xAxis.currentStepPos,yAxis.currentStepPos,zAxis.currentStepPos);
    // TextOutput_printInteger(xAxis.currentStepPos);
    // TextOutput_printInteger(yAxis.currentStepPos);
    
    while (xAxis.currentStepPos!=120){
        while (yAxis.currentStepPos!=120){
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
            RGBC result= RGBC_SCAN();
            // Send to interface
            PCSender_sendRGBAndPos(xAxis.currentStepPos,yAxis.currentStepPos,zAxis.currentStepPos,result.r,result.g,result.b, result.c);
            
            // Move to our next point
            Motion_toPoint(xAxis.currentStepPos,yAxis.currentStepPos+3,zAxis.currentStepPos);
            delay(); 
            delay(); 
            delay(); 
            delay(); 
            delay();      
            delay(); 
            delay(); 
            delay(); 
            delay(); 
        }
        xAxis = Motion_getAxis(EMPR_X_AXIS);
        yAxis = Motion_getAxis(EMPR_Y_AXIS);
        zAxis = Motion_getAxis(EMPR_Z_AXIS);
        // TextOutput_printInteger(xAxis.currentStepPos);
        // Start our new line
        Motion_toPoint(xAxis.currentStepPos+3,0,zAxis.currentStepPos);
    }

    return 0;
}