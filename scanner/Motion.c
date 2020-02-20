#include "Motion.h"
#include "LimitSwitch.h"

#include <mbed/I2C.h>
#include <mbed/Constants.h>
#include <mbed/TextOutput.h>
#include <mbed/LEDs.h>
#include <mbed/Delay.h>

#include <stdbool.h>


typedef struct {
    uint32_t deviceAddress;    // I2C device address of the motor
    bool nibble;               // The nibble of `deviceAddress` that corresponds to this motor, EMPR_<LEFT|RIGHT>
} Motor;

typedef struct {
    Motor motor;
    LimitSwitch limitSwitch;
    uint16_t currentPos_steps; // Current number of 'motor steps' away from the limit switch (0 - EMPR_<axis>_MOTOR_MAX_STEPS inc)
    uint16_t maxPos_steps;     // Maximum number of 'motor steps' that can be moved from the limit switch
} Axis;

static Axis axes[3];

typedef struct {
    uint16_t xPos_steps;
    uint16_t yPos_steps;
    uint16_t xDims_steps;
    uint16_t yDims_steps;
} Platform;

static Platform platform;

#define SUB_STEP_COUNT 4

static const uint8_t subStepData[SUB_STEP_COUNT] = {
    0x09,
    0x05,
    0x06,
    0x0a
};

static void stepForwards(uint8_t axis, uint16_t stepCount);
static void stepBackwards(uint8_t axis, uint16_t stepCount);
static void applySubStepPatternToMotor(uint8_t subStepPatternNibble, uint8_t existingByteContents, Motor* motor);
static void neutraliseAxis(uint8_t axis);
static void substepDelay();
static void initAxes();
static void neutraliseAxis(uint8_t axis);
static void clampWithinAxis(Axis* axis, int* val);
static void moveAxisToLimit(uint8_t axis);
static void moveAxisToPos(uint8_t axis, int targetStepPos);
static void initPlatform();


void Motion_init() {
    i2c_init();

    initAxes();
    initPlatform();

    Motion_home();
}


static void initAxes() {
    axes[EMPR_X_AXIS].motor.deviceAddress = 0x3e;
    axes[EMPR_X_AXIS].motor.nibble = EMPR_LEFT;
    axes[EMPR_X_AXIS].limitSwitch.deviceAddress = 0x3c;
    axes[EMPR_X_AXIS].limitSwitch.stateBitPos = 0;
    axes[EMPR_X_AXIS].currentPos_steps = 0;
    axes[EMPR_X_AXIS].maxPos_steps = EMPR_X_LIMIT;

    axes[EMPR_Y_AXIS].motor.deviceAddress = 0x3e;
    axes[EMPR_Y_AXIS].motor.nibble = EMPR_RIGHT;
    axes[EMPR_Y_AXIS].limitSwitch.deviceAddress = 0x3c;
    axes[EMPR_Y_AXIS].limitSwitch.stateBitPos = 1;
    axes[EMPR_Y_AXIS].currentPos_steps = 0;
    axes[EMPR_Y_AXIS].maxPos_steps = EMPR_Y_LIMIT;

    axes[EMPR_Z_AXIS].motor.deviceAddress = 0x3f;
    axes[EMPR_Z_AXIS].motor.nibble = EMPR_RIGHT;
    axes[EMPR_Z_AXIS].limitSwitch.deviceAddress = 0x3c;
    axes[EMPR_Z_AXIS].limitSwitch.stateBitPos = 2;
    axes[EMPR_Z_AXIS].currentPos_steps = 0;
    axes[EMPR_Z_AXIS].maxPos_steps = EMPR_Z_LIMIT;
}


static void initPlatform() {
    // Before `Motion_localisePlatform()` is called, the platform should inherit the boundaries of
    // the complete movement space. After it is called, the variables below will be correctly initialised
    // and represent a smaller movement volume.
    platform.xPos_steps = 0;
    platform.yPos_steps = 0;
    platform.xDims_steps = EMPR_X_LIMIT;
    platform.yDims_steps = EMPR_Y_LIMIT;
}


void Motion_home() {
    uint8_t axisIdx = 0;

    for(axisIdx = EMPR_X_AXIS; axisIdx <= EMPR_Z_AXIS; axisIdx++)
        moveAxisToLimit(axisIdx);

    Motion_neutraliseAllAxes();
}


static void moveAxisToLimit(uint8_t axis) {
    Axis* a = &axes[axis];
    LimitSwitch* lSwitch = &a->limitSwitch;


    // Number of steps required is bounded by the maximum number of steps possible on this axis
    if(axis == EMPR_Z_AXIS) {
        while(!LimitSwitch_isDown(lSwitch))
            stepForwards(axis, 1);

        while(LimitSwitch_isDown(lSwitch))
            stepBackwards(axis, 1);
    }
    else {
        // TextOutput_println("start");
        while(!LimitSwitch_isDown(lSwitch)) {
            stepBackwards(axis, 1);
            // TextOutput_println("running");
        }
        // TextOutput_println("end");

        while(LimitSwitch_isDown(lSwitch))
            stepForwards(axis, 1);
    }


    a->currentPos_steps = 0;
}


static void stepForwards(uint8_t axis, uint16_t stepCount) {
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

        axes[axis].currentPos_steps += (axis != EMPR_Z_AXIS) * 2 - 1;
    }
}


static void applySubStepPatternToMotor(uint8_t subStepPatternNibble, uint8_t existingByteContents, Motor* motor) {
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
    substepDelay();
    //Delay_ms(16);
}


static void substepDelay() {
    int i, j, count = 0;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 1000; j++)
            count++;
    }
}


static void stepBackwards(uint8_t axis, uint16_t stepCount) {
    Motor* motor = &axes[axis].motor;

    // Save the current contents of the byte being modified by this step sequence
    uint8_t existingData = 0;
    i2c_receiveDataFrom(motor->deviceAddress, &existingData, 1);

    uint32_t step = 0;
    for(step = 0; step < stepCount; step++) {

        uint8_t subStep = 0;
        for(subStep = 0; subStep < SUB_STEP_COUNT; subStep++) {
            uint8_t subStepPattern = subStepData[SUB_STEP_COUNT - subStep - 1];
            applySubStepPatternToMotor(subStepPattern, existingData, motor);
        }

        axes[axis].currentPos_steps -= (axis != EMPR_Z_AXIS) * 2 - 1;
    }
}


void Motion_neutraliseAllAxes() {
    uint8_t axisIdx = 0;
    for(axisIdx = EMPR_X_AXIS; axisIdx <= EMPR_Z_AXIS; axisIdx++)
        neutraliseAxis(axisIdx);
}


static void neutraliseAxis(uint8_t axis) {
    // Get the existing contents of the byte for this motors state
    uint8_t existingByteContents = 0;
    Motor* motor = &axes[axis].motor;
    i2c_receiveDataFrom(motor->deviceAddress, &existingByteContents, 1);

    // Create a stop command byte that, when ANDed with, will zero the left or right nibble
    uint8_t stopCmd = motor->nibble == EMPR_LEFT ? 0x0f : 0xf0;

    // TODO: Get this to neutralise only the motor passed in,
    // it currently zeros the whole byte. There's a branch that fixes this. Where's it gone?

    // Apply the stop command to the existing byte contents
    existingByteContents &= stopCmd;
    uint8_t stop = 0x00;
    i2c_send_data(motor->deviceAddress, &stop, 1);
}


void Motion_moveTo(int x, int y, int z) {
    Vector3D currentPos = Motion_getCurrentPos();

    clampWithinAxis(&axes[EMPR_X_AXIS], &x);
    clampWithinAxis(&axes[EMPR_Y_AXIS], &y);
    clampWithinAxis(&axes[EMPR_Z_AXIS], &z);

    while(currentPos.x != x || currentPos.y != y || currentPos.z != z) {
        currentPos = Motion_getCurrentPos();

        if(currentPos.x != x) {
            if(currentPos.x < x)
                moveAxisToPos(EMPR_X_AXIS, currentPos.x + 1);
            else
                moveAxisToPos(EMPR_X_AXIS, currentPos.x - 1);
        }

        if(currentPos.y != y) {
            if(currentPos.y < y)
                moveAxisToPos(EMPR_Y_AXIS, currentPos.y + 1);
            else
                moveAxisToPos(EMPR_Y_AXIS, currentPos.y - 1);
        }

        if(currentPos.z != z) {
            if(currentPos.z < z)
                moveAxisToPos(EMPR_Z_AXIS, currentPos.z + 1);
            else
                moveAxisToPos(EMPR_Z_AXIS, currentPos.z - 1);
        }
    }
}


static void moveAxisToPos(uint8_t axis, int targetStepPos) {
    Axis* a = &axes[axis];

    clampWithinAxis(a, &targetStepPos);

    Motor* motor = &a->motor;

    uint16_t stepsRequired = 0;
    if(targetStepPos > a->currentPos_steps) {
        stepsRequired = targetStepPos - a->currentPos_steps;

        // Forward and backwards directions on the Z axis are inverted
        if(axis == EMPR_Z_AXIS)
            stepBackwards(axis, stepsRequired);
        else
            stepForwards(axis, stepsRequired);
    }
    else {
        stepsRequired = a->currentPos_steps - targetStepPos;

        if(axis == EMPR_Z_AXIS)
            stepForwards(axis, stepsRequired);
        else
            stepBackwards(axis, stepsRequired);
    }
}


static void clampWithinAxis(Axis* axis, int* val) {
    if(*val < 0)
        *val = 0;
    else if(*val > axis->maxPos_steps)
        *val = axis->maxPos_steps;
}


void Motion_localisePlatform() {
    // 1. Move the scan head to a position roughly in the centre of the platform (keep hold of this position)

    // 2. Move the scan head in one direction along one axis until either:
    //  - a platform edge is detected (when the distance between the colour currently under the cursor
    //    and the colour under the sensor during the last step is greater than some threshold), keeping
    //    track of the number of steps moved.
    //  - the internal limit of the motion range along this axis reached.

    // 3. If an edge is detected, somehow the number of steps it took to reach this edge in this direction
    //    from the (roughly) central start position and repeat this process in the other direction, returning
    //    to the original start position.

    // 4. Repeat the process outlined above for the other axis.
}


void Motion_moveBy(int deltaX, int deltaY, int deltaZ) {
    Vector3D currentPos = Motion_getCurrentPos();

    Vector3D targetPos = {
        currentPos.x + deltaX,
        currentPos.y + deltaY,
        currentPos.z + deltaZ
    };

    Motion_moveTo(targetPos.x, targetPos.y, targetPos.z);
}


Vector3D Motion_getCurrentPos() {
    Vector3D output;

    output.x = axes[EMPR_X_AXIS].currentPos_steps;
    output.y = axes[EMPR_Y_AXIS].currentPos_steps;
    output.z = axes[EMPR_Z_AXIS].currentPos_steps;

    return output;
}


