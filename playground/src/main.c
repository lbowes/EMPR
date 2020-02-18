/***********************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include "scanner/Motion.h"
#include "mbed/Interrupts.h"
#include "mbed/LEDs.h"
#include "mbed/Delay.h"

#define c3 7634
#define d3 6803
#define e3 6061
#define f3 5714
#define g3 5102
#define a3 4545
#define b3 4049
#define c4 3816 // 261 Hz
#define d4 3401 // 294 Hz
#define e4 3030 // 329 Hz
#define f4 2865 // 349 Hz
#define g4 2551 // 392 Hz
#define a4 2272 // 440 Hz
#define a4s 2146
#define b4 2028 // 493 Hz
#define c5 1912 // 523 Hz
#define d5 1706
#define d5s 1608
#define e5 1517 // 659 Hz
#define f5 1433 // 698 Hz
#define g5 1276
#define a5 1136
#define a5s 1073
#define b5 1012
#define c6 955

#define R 0 // Define a special note, 'R', to represent a rest

// MELODIES and TIMING //
//  melody[] is an array of notes, accompanied by beats[],
//  which sets each note's relative length (higher #, longer note)

// Melody 1: Star Wars Imperial March
int melody1[] = {a4, R, a4, R, a4, R, f4, R, c5, R, a4, R, f4, R, c5, R, a4, R, e5, R, e5, R, e5, R, f5, R, c5, R, g5, R, f5, R, c5, R, a4, R};
int beats1[] = {50, 20, 50, 20, 50, 20, 40, 5, 20, 5, 60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5, 60, 10, 40, 5, 20, 5, 60, 40};

// Melody 2: Star Wars Theme
int melody2[] = {f4, f4, f4, a4s, f5, d5s, d5, c5, a5s, f5, d5s, d5, c5, a5s, f5, d5s, d5, d5s, c5};
int beats2[] = {21, 21, 21, 128, 128, 21, 21, 21, 128, 64, 21, 21, 21, 128, 64, 21, 21, 21, 128};

long timePerBeat = 100; // Set time per beat set this faster to increase tempo

// int pause = 1000; // Set length of pause between notes

// int rest_count = 50; // Loop variable to increase Rest length (BLETCHEROUS HACK; See NOTES)

int location = 0;
int direction = 1;
void playFrequency(int frequency, int beats)
{
    int timePeriod = (int)1.0f / frequency;
    if (timePeriod == 0)
    {
        timePeriod = 1;
    }
    for (int counter = 0; counter < beats; counter++)
    {
        int delayCount = 0;
        while (delayCount < timePerBeat)
        {
            if (location==199)
            {
                direction=0;
            }
            if (location==1)
            {
                direction=1;
            }

            Motion_toPoint(location,0,0);
            Delay_ms(timePeriod);
            location+= direction ? 1 : -1;
            Motion_toPoint(location,0,0);
            delayCount+=timePeriod;
            
        }
    }
}

int main()
{
    Motion_init();
    for (int index=0; index<sizeof(melody1);index++)
    {
        playFrequency(melody1[index],beats1[index]);
    }
    Motion_home();
    for (int index=0; index<sizeof(melody2);index++)
    {
        playFrequency(melody2[index],beats2[index]);
    }
}