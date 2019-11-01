#ifndef EMPR_KEYPAD_UTILS_H_
#define EMPR_KEYPAD_UTILS_H_

// TODO
#include <stdint.h>
#include <stdbool.h>

void keypad_init(void);

bool keypad_isKeyPressed(uint8_t character);

#endif // EMPR_KEYPAD_UTILS_H_
