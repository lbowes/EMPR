#include "B.h"


/*
 * A second manual move mode (Manual Scan Mode) will be implemented, which
 * displays the RGB values instead of XYZ positions during manual movements.
 * • Operates as per A3 but readout shows RGB values on LCD.
*/
void B1() {

}


/*
 * Raster Scan Mode: your platform will scan the X-Y grid using a raster scan
 * pattern, and display the RGB data.
 * • RGB data will be displayed on LCD during scanning
 * • RGB data will be sent to PC via USB (this needs to be able to be turned on
 * or off by the user).
 * • Note that you only have to show here that data is being sent. D1 deals with
 * what happens to the data later.
*/
void B2() {

}


/*
* Color Search: Allows a point in an image of a certain colour specification to be
* located.
* • A raster scan will be performed,
* • The highest reading for R, G or B (as selected by user) will be located.
* • The head will move to that final position once it has been identified.
* For the demonstration you can scan a smaller region than the whole bed, a minimum
* of 2x2 inches, if a full scan may take an inconveniently long time. 
*/
void B3() {

}