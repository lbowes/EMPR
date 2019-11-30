#ifndef EMPR_INTERRUPTS_H_
#define EMPR_INTERRUPTS_H_

#include <stdint.h>
#include <stdbool.h>

#define RUN_EVERY(x) if (Interrupts_every(x))

void Interrupts_start(void);
void Interrupts_stop(void);
bool Interrupts_every(uint32_t ms);

// User defined
void Interrupts_handleAll(void);

#endif //EMPR_INTERRUPTS_H_
