#include "A.h"


/*
 * A scanning API should be written, to permit control of all three stepper motors.
 * It should be possible to demonstrate its functionality by performing test
 * patterns as defined below,
 * • The stepper motors should be operated via the I2C ports provided,
 * • Care should be taken to ensure that microswitch end-stops prevent motor
 * overun and belt-strain at the edges of the scanning platform.
 * • The X-Y functional test will include scan patterns:
 * • (a) A full-size circle
 * • (b) A square at the boundaries of the platform
 * • (c) You should be able to demonstrate that Z axis can be moved up and
 * down.
 * • Tests should be selectable via a user interface on the MBED board.
*/
void A1() {

}


/*
 * The X-Y Platform should perform a boundary detection setup procedure, such
 * that the edges of the platform are determined automatically by stepping the
 * motors and monitoring the microswitches.
 * • The platform will explore the edge boundaries
 * • The edge boundaries will be displayed on LCD at the end of the search.
 * • Stepping resolution should be at least 16 distinct positions per X/Yaxis.
*/
void A2() {

}


/*
 * 'Manual Move Mode,' : the user should be able to use the keypad or another
 * input device to move all three axes back and forth, whilst the position of each axis
 * is displayed on the LCD panel.
 * • The user can move the x-y position using suitable inputs
 * • The Z-axis can be controlled to at least two positions (Up/Down)
 * • Response times should be fast enough for reasonable user interaction.
*/
void A3() {

}