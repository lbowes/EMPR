#include <stdint.h>


typedef struct point {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} Point;

void SetupScan();
void SimpleScan(void);
void StreamSimpleScan(void);
void BetterSimpleScan(void);
void delayScanner(uint8_t ms);
//void PointScanner(Point points[])
