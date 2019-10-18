#ifndef EMPR_UART_UTILS_H_
#define EMPR_UART_UTILS_H_


#include <stdint.h>


void UART_init(void);

int UART_print(const char* msg);
void UART_debugMsg(const char* functionName, const char* msg);
void UART_memeText(void);


#endif // EMPR_UART_UTILS_H_
