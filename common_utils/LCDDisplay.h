#ifndef EMPR_LDCDISPLAY_H_
#define EMPR_LDCDISPLAY_H_

// TODO
// #include <lpkdjfx_lcddriver.h>
// #include <someOtherDriverHeader.h>

void LCDDisplay_init(void); // TODO: might pass in more options

void LCDDisplay_clear(void);
void LCDDisplay_print(const char* msg);

#endif // EMPR_LDCDISPLAY_H_
