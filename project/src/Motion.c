#include "Motion.h"
#include "LimitSwitch.h"

#include <common_utils/I2C.h>
#include <common_utils/Constants.h>
#include <common_utils/TextOutput.h>
#include <common_utils/LEDs.h>


#define SUB_STEP_COUNT 4

static const uint8_t subStepData[SUB_STEP_COUNT] = {
    0x09,
    0x05,
    0x06,
    0x0a
};

static Axis axes[3];

static inline void clampBelow(uint16_t* steps);
void stepForwards(uint8_t axis, uint16_t stepCount);
void stepBackwards(uint8_t axis, uint16_t stepCount);
uint8_t applySubStepPatternToMotor(uint8_t subStepPatternNibble, uint8_t existingByteContents, Motor* motor);
void neutralise(Motor* motor);
void neutraliseAll();
void delay();


void Motion_init() {
    // todo: Configure all axis (motor and switch) parameters
    axes[EMPR_X_AXIS].motor.deviceAddress = 0x3e;
    axes[EMPR_X_AXIS].motor.nibble = EMPR_LEFT;
    axes[EMPR_X_AXIS].limitSwitch.deviceAddress = 0x3c;
    axes[EMPR_X_AXIS].limitSwitch.stateBitPos = 0;
    axes[EMPR_X_AXIS].currentStepPos = 0;
    axes[EMPR_X_AXIS].maxSteps = 202; //todo: 202

    axes[EMPR_Y_AXIS].motor.deviceAddress = 0x3e;
    axes[EMPR_Y_AXIS].motor.nibble = EMPR_RIGHT;
    axes[EMPR_Y_AXIS].limitSwitch.deviceAddress = 0x3c;
    axes[EMPR_Y_AXIS].limitSwitch.stateBitPos = 1;
    axes[EMPR_Y_AXIS].currentStepPos = 0;
    axes[EMPR_Y_AXIS].maxSteps = 600; //todo

    axes[EMPR_Z_AXIS].motor.deviceAddress = 0x3f;
    axes[EMPR_Z_AXIS].motor.nibble = EMPR_RIGHT;
    axes[EMPR_Z_AXIS].limitSwitch.deviceAddress = 0x3c;
    axes[EMPR_Z_AXIS].limitSwitch.stateBitPos = 2;
    axes[EMPR_Z_AXIS].currentStepPos = 0;
    axes[EMPR_Z_AXIS].maxSteps = 600; //todo

    neutraliseAll();
    //Motion_home();
}

Axis Motion_getAxis(uint8_t axis)
{
    return axes[axis];
}

static inline void clampWithinAxis(Axis* axis, uint16_t* val) {
    if(*val > axis->maxSteps)
        *val = axis->maxSteps;
}


void Motion_moveAxisToPos(uint8_t axis, uint16_t targetStepPos) {
    Axis* a = &axes[axis];

    // Sanity check if we are going back to zero go to home
    if (targetStepPos==0){
    moveAxisToLimit(a);
    }
    else{

    clampWithinAxis(a, &targetStepPos);

    Motor* motor = &a->motor;
    neutralise(motor);

    uint16_t stepsRequired = 0;
    if(targetStepPos > a->currentStepPos) {
        stepsRequired = targetStepPos - a->currentStepPos;

        // Forward and backwards directions on the Z axis are inverted
        if(axis == EMPR_Z_AXIS)
            stepBackwards(axis, stepsRequired);
        else
            stepForwards(axis, stepsRequired);
    }
    else {
        stepsRequired = a->currentStepPos - targetStepPos;

        if(axis == EMPR_Z_AXIS)
            stepForwards(axis, stepsRequired);
        else
            stepBackwards(axis, stepsRequired);
    }

    neutralise(motor);
    }
}


void stepForwards(uint8_t axis, uint16_t stepCount) {
    Motor* motor = &axes[axis].motor;

    // Save the current contents of the byte being modified by this step sequence
    uint8_t existingData = 0;
    i2c_receiveDataFrom(motor->deviceAddress, &existingData, 1);

    uint16_t step = 0;
    for(step = 0; step < stepCount; step++) {

        uint8_t subStep = 0;
        for(subStep = 0; subStep < SUB_STEP_COUNT; subStep++) {
            uint8_t subStepPattern = subStepData[subStep];
            applySubStepPatternToMotor(subStepPattern, existingData, motor);
        }

        //axes[axis].currentStepPos += (axis != EMPR_Z_AXIS) * 2 - 1;
        axes[axis].currentStepPos++;
    }

}


void stepBackwards(uint8_t axis, uint16_t stepCount) {
    Motor* motor = &axes[axis].motor;

    // Save the current contents of the byte being modified by this step sequence
    uint8_t existingData = 0;
    i2c_receiveDataFrom(motor->deviceAddress, &existingData, 1);

    TextOutput_print("Backwards from: ");
    TextOutput_printInteger(axes[axis].currentStepPos);

    uint32_t step = 0;
    for(step = 0; step < stepCount; step++) {

        uint8_t subStep = 0;
        for(subStep = 0; subStep < SUB_STEP_COUNT; subStep++) {
            uint8_t subStepPattern = subStepData[SUB_STEP_COUNT - subStep - 1];
            applySubStepPatternToMotor(subStepPattern, existingData, motor);
        }

        //axes[axis].currentStepPos += (axis != EMPR_Z_AXIS) * 2 - 1;
        axes[axis].currentStepPos--;
    }
}


void delay() {
    int i, j, count = 0;
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 1000; j++)
            count++;
    }
}


uint8_t applySubStepPatternToMotor(uint8_t subStepPatternNibble, uint8_t existingByteContents, Motor* motor) {
    // 1. Get the next motor substep pattern subStepData[subStep] e.g 00001001
    //                                                                    ^^^^

    // 2. Shift these four bits into the nibble used by the motor     10010000
    //                                                                ^^^^ <--

    // 3. Create a variable representing 00001111 (15):               00001111

    // 4. Shift these four bits into the nibble NOT used by the motor 
    //    Note: This means simply leaving them in place if the motor
    //    uses the left nibble, since they are already on the right.  00001111

    // 5. We've previously fetched the existing data at the target
    //    byte                                                    e.g 10101010

    // 6. AND the result of steps 4 and the existing byte (step 5)    00001010

    // 7. OR the result of steps 6 and step 2                         10011010

    // This inserts 1001 into the left nibble of 10101010, giving 10011010
    uint8_t newByteContents = (subStepPatternNibble << motor->nibble * 4) | (existingByteContents & (0x0f << (1 - motor->nibble) * 4));
    i2c_send_data(motor->deviceAddress, &newByteContents, 1);
    delay();
}


void neutralise(Motor* motor) {
    // Get the existing contents of the byte for this motors state
    uint8_t existingByteContents = 0;
    i2c_receiveDataFrom(motor->deviceAddress, &existingByteContents, 1);

    // Create a stop command byte that, when ANDed with, will zero the left or right nibble
    uint8_t stopCmd = motor->nibble == EMPR_LEFT ? 0x0f : 0xf0;

    // Apply the stop command to the existing byte contents
    existingByteContents &= stopCmd;
    uint8_t stop = 0x00;
    i2c_send_data(motor->deviceAddress, &stop, 1);
}


void neutraliseAll() {
    uint8_t axisIdx = 0;
    for(axisIdx = EMPR_X_AXIS; axisIdx <= EMPR_Z_AXIS; axisIdx++)
        neutralise(&axes[axisIdx].motor);
}


void Motion_toPoint(uint16_t x, uint16_t y, uint16_t z) {
    Motion_moveAxisToPos(EMPR_X_AXIS, x);
    Motion_moveAxisToPos(EMPR_Y_AXIS, y);
    Motion_moveAxisToPos(EMPR_Z_AXIS, z);
}


void moveAxisToLimit(uint8_t axis) {
    Axis* a = &axes[axis];

    Motor* motor = &a->motor;
    LimitSwitch* lSwitch = &a->limitSwitch;
    uint32_t steps = 0;

    // Number of steps required is bounded by the maximum number of steps possible on this axis
    if(axis == EMPR_Z_AXIS) {
        while(!LimitSwitch_isDown(lSwitch))
            stepForwards(axis, 1);

        while(LimitSwitch_isDown(lSwitch))
            stepBackwards(axis, 1);
    }
    else {
        while(!LimitSwitch_isDown(lSwitch))
            stepBackwards(axis, 1);

        while(LimitSwitch_isDown(lSwitch))
            stepForwards(axis, 1);
    }

    neutralise(motor);
}


void Motion_home() {
    neutraliseAll();

    uint8_t axisIdx = 0;
    for(axisIdx = EMPR_X_AXIS; axisIdx <= EMPR_Z_AXIS; axisIdx++)
        moveAxisToLimit(axisIdx);

    neutraliseAll();
}
