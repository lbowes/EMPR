// Overview
// The final mini project requires you to become familiar with the system’s analogue-to-digital
// (ADC) and digital-to-analogue (DAC) converter facilities and its PWM controllers.

// Stage 1:
// Write a program that can read in and print out the value of a small DC voltage applied to the
// input of an ADC. This input voltage can be derived from the 3.3V power pin on the mbed board and
// varied through the use of various voltage divider arrangements. Use of 10kΩ resistors is
// suggested so that not too much current is drawn from the voltage supply.

// Stage 2:
// Write a program that can generate a sine wave and output it via the system DAC. The amplitude and
// frequency should be parameters to your waveform generation function and these should be changed
// periodically, for example, at 10 second intervals. You should observe the waveforms generated on
// an oscilloscope.

// Stage 3:
// Write a program that can take a sine wave input from a signal generator and mirror this onto the
// output of the DAC. Be careful to set the allowable ADC input levels correctly (0-3V) by checking
// them on an oscilloscope before applying to the ADC input.

// Stage 4:
// Write a program to output a PWM wave from the MCU using one of the the dedicated PWM controllers.
// Use single edge mode and cycle through the full range of changes in pulse width 5 times. A single
// cycle from minimum pulse width to maximum should take 5 seconds and should be displayed on the
// oscillscope. You should use some form of timer on the MCU to change the pulse width at regular
// intervals, not a delay loop.

// Stage 5:
// Optional extra: Build a distance measuring device, using a Sharp GP2Y0A21YK0F infra-red range
// sensor (datasheet online). Print the sensors output voltage and/or measured distance to the LCD
// screen. Note that you will need a calibration procedure before converting input voltage to
// distance. Modes for ‘calibration’ and ‘distance measurement’ should be selectable on the keypad.

// MP3 demonstration:
// Integrate your work into a single program that executes:
// • Stage 2 above until any key is pressed on the keypad.
// • Stage 3 above until any key is pressed on the keypad.
// • Stage 4 above and then terminates.

// If you have attempted stage 5, demonstrate this as a separate program. Fill in the mini project
// review sheet and then request formative feedback and sign-off from the lecturer (Nick Pears).


int main() {
    return 0;
}