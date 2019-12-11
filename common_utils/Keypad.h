#ifndef EMPR_KEYPAD_UTILS_H_
#define EMPR_KEYPAD_UTILS_H_

#include <stdint.h>
#include <stdbool.h>
#include <common_utils/Constants.h>

void Keypad_init(void);

bool Keypad_isKeyDown(uint8_t character);

#endif // EMPR_KEYPAD_UTILS_H_
