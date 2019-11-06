#ifndef EMPR_KEYPAD_UTILS_H_
#define EMPR_KEYPAD_UTILS_H_

// TODO
#include <stdint.h>
#include <stdbool.h>


void Keypad_init(void);

bool Keypad_isKeyPressed(uint8_t character);


#endif // EMPR_KEYPAD_UTILS_H_
