#ifndef EMPR_LDCDISPLAY_H_
#define EMPR_LDCDISPLAY_H_
#define LINE_1 0
#define LINE_2 1
// TODO
// #include <lpkdjfx_lcddriver.h>
// #include <someOtherDriverHeader.h>

void LCDDisplay_init(void); // TODO: might pass in more options
// Takes in a line number of what you want to clear
void LCDDisplay_clear(unsigned int line_number);
// This function returns 0 if successfully executed otherwise it will show -numbers for errors
int LCDDisplay_print(const char* msg, unsigned int line_number);
// Sends data
void sendData(I2C_M_SETUP_Type* setup, uint32_t Address,uint8_t* Data, uint32_t dataLength);
// sets up pins
void setupPins(void);
#endif // EMPR_LDCDISPLAY_H_
