// Overview
// The second mini project requires that you understand how to use I/O devices
// connected to the MPU’s i2c bus.

// Stage 1:
// Write a program that determines how many devices are connected to the i2c bus. Your
// program should print out “X devices connected to i2c bus” on the terminal, where X
// is the number of devices and it should list thme i2c addresses at which devices are
// present.

// Stage 2:
// Write a program that writes “Hello World” on a single line on the
// small LCD display connected to the i2c bus. Modify your program to write
// each word on a separate line on the LCD display.

// Stage 3:
// Write a program that allows you to enter characters on your keypad
// and display the results on the small LCD. Try to develop your system so that
// it is responsive to key presses (no key presses missed) but also does not accept
// spurious multiple characters (eg. ‘22’ when only ‘2’was intended).

// Stage 4:
// Optional extra: Write a program that allows you to enter some
// numbers on the keypad and add, multiply, divide or subtract them, displaying
// the data entry and results on the LCD (i.e. a simple calculator).

// MP2 demonstration: Integrate your work into a single program that executes:
// • Stage 1, followed by a pause of 1 second.
// • Stage 2, with a pause of 1 second and a clear LCD screen after each of the two print operations.
// • Finally stage 3 above is executed.

#include <common_utils/I2CSniffer.h>
#include <common_utils/LCDDisplay.h>
#include <common_utils/Constants.h>
#include <common_utils/Keypad.h>
#include <common_utils/Interrupts.h>
#include <stdbool.h>
#include <RealTimeClock.h>

bool everySecond = false;

void Interrupts_handleAll()
{
    RUN_EVERY(1000)
    {
        everySecond = !everySecond;
    }
}

void aPauseOfOneSecond()
{
    bool previousSecond=everySecond;
    while (previousSecond==everySecond){} 
}

int main()
{
    // Stage 1
    I2CSniffer_run();

    aPauseOf1Second();

    // Stage 2
    LCDDisplay_init();
    LCDDisplay_print("Hello world", LINE_1);

    aPauseOf1Second();

    LCDDisplay_print("Hello", LINE_2);
    LCDDisplay_print("World", LINE_1);

    aPauseOf1Second();

    // Stage 3
    // Init the keypad
    Keypad_init();
    // Clear the LCD
    LCDDisplay_clear(LINE_1);
    LCDDisplay_clear(LINE_2);
    // Loop through keys
    uint8_t keys[] = {EMPR_KEY_0, EMPR_KEY_1, EMPR_KEY_2, EMPR_KEY_3, EMPR_KEY_4, EMPR_KEY_5, EMPR_KEY_6, EMPR_KEY_7, EMPR_KEY_8, EMPR_KEY_9, EMPR_KEY_A, EMPR_KEY_B, EMPR_KEY_C, EMPR_KEY_D};
    // While loop it
    while (true)
    {
        for (int index = 0; index < sizeof(keys); index++)
        {
            if (Keypad_isKeyDown(keys[index]))
            {
                aPauseOf1Second();
                char string[4];
                sprintf(string, "%d", index);
                LCDDisplay_print(string, LINE_1);
            }
        }
    }

    return 0;
}