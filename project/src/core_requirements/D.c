#include "D.h"


/*
 * PC DATA LOGGER
 * The PC will be able to receive RGB data from the mbed board, along with 
 * tracking of coordinate data.
 * • The way coordinates are tracked may vary, you can send X,Y for every
 * pixel, or use tags to indicate new line and number of pixels per line, for
 * example.
 * • You may choose not to transmit coordinates but track them on the PC.
*/
void D1() {

}


/*
 * PC Move and Measure:
 * The PC will be able to send commands to MBED to move axes, and then receive
 * a color data measurement from the new location.
 * • Minimum requirement is for a 16x16 grid resolution.
 * • Color data should be displayed as RGB values on the PC.
*/
void D2() {

}


/*
 * PC Imager
 * The PC will display an image of the scanned item on the screen.
 * • Data is read from the mbed board in whatever way you wish
 * • Data is displayed by your PC code in a suitable visual format*.
 * *If data is only viewable by creating a file (e.g. bmp) and then the user opening it
 * manually with a standard utility then some partial marks will still be available. 
*/
void D3() {

}