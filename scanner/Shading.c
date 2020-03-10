#include <scanner/Shading.h>
#include <mbed/Constants.h>
#include <scanner/ColourSensor.h>
#include <scanner/Drawing.h>
#include <scanner/Motion.h>
#include <mbed/TextOutput.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#define IMAGE_HEIGHT 6
#define IMAGE_WIDTH 11
#define Y_PENOFFSET 36
#define X_OFFSET 29
#define Y_OFFSET 0
#define Z_OFFSET 0
Grid Image[169];
uint8_t Shading_calc(Colour Point);

Colour Shade;
typedef struct {
    uint8_t grid; // 0 to 168
    uint8_t row; // 0, 1, 2
    uint8_t block; // 0 , 1 , 2
} local;
//void Shading_CheckEndBlock(local curPos) {
//    Image[curPos.grid.row[curPos.row] 

//}

void Shading_writeBlock(uint16_t value, local* curPos) {
    Image[curPos->grid].row[curPos->row] = (Image[curPos->grid].row[curPos->row] & ~(0xF << (4 * curPos->block)));
    Image[curPos->grid].row[curPos->row] = (Image[curPos->grid].row[curPos->row] | (value << (4 * curPos->block)));
}

int Shading_readBlock(local* curPos) {
    uint8_t value = 0;
    value = ((Image[curPos->grid].row[curPos->row] >> (curPos->block * 4)) & 0xF);
    return value;
    }


uint8_t Shading_calc(Colour Point) {
    uint16_t grayScale = Point.clear;
    if(grayScale < 100){
        return 1;
    }
    else if(grayScale < 120) {
        return 2;
    }
    else  if(grayScale < 140) {
        return 4;
    }
    else if(grayScale < 150) {
        return 8;
    }
    return 0;
}

void Shading_scanShade() {
    Shading_init();
    local myPos;
    myPos.grid = 0;
    myPos.row = 0;
    myPos.block = 0;
    TextOutput_init();
    TextOutput_println("Begin");
    for(myPos.grid=0; myPos.grid<((IMAGE_WIDTH * IMAGE_HEIGHT));myPos.grid++){
        myPos.block = 0;
        myPos.row = 0;
        Shading_position(&myPos);
        Shading_scanGrid(&myPos);
   }
}
void Shading_init() {
    Motion_init();
    ColourSensor_init();
}

void Shading_position(local* ImagePos) {
    uint16_t x_working = X_OFFSET + (18 * (ImagePos->grid % IMAGE_HEIGHT));
    uint16_t y_working = Y_OFFSET + (18 * floor((float)((float)ImagePos->grid / IMAGE_HEIGHT)));
    uint16_t z_working = Z_OFFSET;
    Vector3D Pos;
    Pos = Motion_getCurrentPos();
    Motion_moveTo(x_working, y_working, Pos.z);
    Motion_neutraliseAllAxes();
}


void Shading_scanGrid(local* gridPos) {
    uint16_t i, j, k, sum = 0;
    for (gridPos->row=0;gridPos->row<3; gridPos->row++){
        Motion_moveBy(0, 3, 0);
        Motion_neutraliseAllAxes();
        for (gridPos->block=0; gridPos->block<3; gridPos->block++) {
            Motion_moveBy(3, 0, 0);
            Motion_neutraliseAllAxes();
            Shade = ColourSensor_seq(); // Must be repeated after every movement.
            if ((sum/4) > Shade.clear) {
                Shade.clear = (Shade.clear/2);
            }
            Shading_writeBlock(Shading_calc(Shade), gridPos);
            Shading_displayBlock(gridPos);
            TextOutput_printInteger(Shading_readBlock(gridPos));
            //TextOutput_printInteger(gridPos->grid);
            //TextOutput_printInteger(gridPos->row);
            //TextOutput_printInteger(gridPos->block);
            Motion_moveBy(3, 0, 0);
            Motion_neutraliseAllAxes();
            if (gridPos->block == 0) {
                i = Shade.clear;
            }
            else if (gridPos->block == 1) {
                j = Shade.clear;
            }
            else {
                k = Shade.clear;
            }
        }
        sum=i+j+k;
        TextOutput_print("Block");
        Shading_displayBlock(gridPos);
        Motion_moveBy(-18, 3, 0);
        Motion_neutraliseAllAxes();
    }
}

// NOW WORKS
void Shading_displayBlock(local* Pos){
    TextOutput_printInteger(Pos->grid);
    TextOutput_printInteger(Pos->row);
    TextOutput_printInteger(Pos->block);
    TextOutput_printInteger(Shading_readBlock(Pos));
}

void Shading_shadeGrid(local* penPos) {
    uint16_t scanVal;
    int8_t penDepth;
    int8_t drawDepth;
    for(penPos->row=0; penPos->row<3; penPos->row++) {
        penDepth = 0;
        for(penPos->block=0; penPos->block<3; penPos->block++) {
            scanVal = Shading_readBlock(penPos);
            TextOutput_print("Block");
            Shading_displayBlock(penPos);
            TextOutput_print("Val:");
            TextOutput_printInteger(scanVal);
            /*TextOutput_printInteger(penDepth);
            TextOutput_printInteger(drawDepth);*/
            switch (scanVal) 
            {
                case 0:
                    TextOutput_print("Case 0");
                    Drawing_penUp();
                    Motion_moveBy(6, 0, 0);
                    break;

                case 1:
                    TextOutput_print("Case 1");
                    if (penDepth == 6) {
                        penDepth = 6;
                        drawDepth = 6;
                    } else {
                        penDepth = 0;
                        drawDepth = -6;
                    }
                    Drawing_penDownDark();
                    Motion_neutraliseAllAxes();
                    Motion_moveBy(6, -drawDepth, 0);
                    Motion_moveBy(-6, 0, 0);
                    Motion_moveBy(6, drawDepth, 0);
                    Motion_neutraliseAllAxes();
                    break;

                case 2:
                    TextOutput_print("Case 2");
                    if (penDepth == 6) {
                        drawDepth = -6;
                        penDepth = 0;
                    }
                    else {
                        drawDepth = 6;
                        penDepth = 6;
                    }
                    Drawing_penDownDark();
                    Motion_neutraliseAllAxes();
                    Motion_moveBy(2, drawDepth, 0);
                    Motion_moveBy(2, -drawDepth, 0);
                    Motion_moveBy(2, drawDepth, 0);
                    Motion_neutraliseAllAxes();
                    break;
                    /*
                    TextOutput_print("Case 2");
                    if (penDepth == 6) {
                        drawDepth = -6;
                        penDepth = 6;
                    }
                    else { 
                        drawDepth = 6;
                        penDepth = 0;
                    }
                    Drawing_penDownDark();
                    Motion_neutraliseAllAxes();
                    Motion_moveBy(3, drawDepth, 0);
                    Motion_neutraliseAllAxes();
                    Motion_moveBy(3, -drawDepth, 0);
                    Motion_neutraliseAllAxes();
                    break;*/

                case 4:
                    TextOutput_print("Case 4");
                    if (penDepth == 6) {
                        drawDepth = -6;
                        penDepth = 0;
                    } 
                    else {
                        drawDepth = 6;
                        penDepth = 6;
                    }
                    Motion_neutraliseAllAxes();
                    Drawing_penDownDark();
                    Motion_moveBy(6, drawDepth, 0);
                    Motion_neutraliseAllAxes();
                    break;

                case 8: 
                    TextOutput_print("Case 8");
                    if (penDepth == 6) {
                        drawDepth = -6;
                        penDepth = 0;
                    } 
                    else {
                        drawDepth = 6;
                        penDepth = 6;
                    }
                    Motion_neutraliseAllAxes();
                    Drawing_penDownLight();
                    Motion_moveBy(6, drawDepth, 0);
                    Motion_neutraliseAllAxes();
                    break;
    
            }
        }
        Drawing_penUp();
        if (penDepth == 6){
            Motion_moveBy(-18, 0, 0);
            penDepth = 0;
        } 
        else{
            Motion_moveBy(-18, 6, 0);
            penDepth = 0;
        } 
        penDepth = 0;
        Motion_neutraliseAllAxes();
    }   
}

void Shading_shade() {
    local penPos;
    penPos.grid = 0;
    penPos.row = 0;
    penPos.block = 0;
    Drawing_penUp();
    for(penPos.grid=0; penPos.grid<((IMAGE_WIDTH * IMAGE_HEIGHT));penPos.grid++){
        if((penPos.grid % IMAGE_HEIGHT) == 0) {
            Motion_moveAxisToLimit(0);
            Motion_moveAxisToLimit(1);
        }
        Drawing_penUp();
        penPos.block = 0;
        penPos.row = 0;
        Shading_position(&penPos);
        Drawing_penToHead();
        Shading_shadeGrid(&penPos);
}
}
