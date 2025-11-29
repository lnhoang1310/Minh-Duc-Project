#ifndef UART_H
#define UART_H

#include <stdint.h>

typedef struct{
	char* request;
	char* response;
}Command_t;

void uart_handle(void);
void uart_receive_data(uint8_t data);

#endif
