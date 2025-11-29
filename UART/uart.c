#include "uart.h"
#include "string.h"
#include "stm32f1xx.h"

extern UART_HandleTypeDef huart1;
uint8_t uart_buffer[20];
uint8_t buffer_index = 0;
uint8_t flag_cplt = 0;

Command_t list_command[] = 
{
	{"GROUP_NAME", ""},
	{"MEMBERS", ""},
	{"PROJECT_NAME", ""},
	{"HARDWARE_USED", ""},
	{"SOFTWARE_USED", ""},
	{"DATE", ""}
};

void uart_receive_data(uint8_t data){
	if(data == '\n'){
		uart_buffer[buffer_index] = '\0';
		flag_cplt = 1;
		buffer_index = 0;
		return;
	}
	uart_buffer[buffer_index++] = data;
	if(buffer_index >= 20) buffer_index = 0;
}

void uart_handle(void){
	if(flag_cplt){
		for(uint8_t i=0; i<sizeof(list_command)/sizeof(Command_t); i++){
			if(strcmp((char*)uart_buffer, list_command[i].request)){
				HAL_UART_Transmit_DMA(&huart1, (uint8_t*)list_command[i].response, strlen(list_command[i].response));
				return;
			}
		}
	}
}
