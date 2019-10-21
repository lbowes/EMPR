#ifndef EMPR_UART_UTILS_H_
#define EMPR_UART_UTILS_H_


#include <stdint.h>


void TextOutput_init(void);

// screen /dev/ttyACM0
void TextOutput_print(const char* msg);
void TextOutput_println(const char* msg);
void TextOutput_debugMsg(const char* functionName, const char* msg);
void TextOutput_memeText(void);

void TextOutput_shutdown(void);


#endif // EMPR_UART_UTILS_H_
