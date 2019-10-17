#ifndef EMPR_UART_UTILS_H_
#define EMPR_UART_UTILS_H_


#include <stdint.h>


void UART_init(void);

void UART_clearScreen();
void UART_print(const char* msg);
void UART_debugMsg(const char* functionName, const char* msg);
void UART_memeText();


#endif // EMPR_UART_UTILS_H_
