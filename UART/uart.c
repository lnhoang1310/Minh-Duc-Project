#include "uart.h"
#include "string.h"
#include "stm32f1xx.h"

extern UART_HandleTypeDef huart1;
uint8_t uart_buffer[20];
uint8_t buffer_index = 0;
uint8_t flag_cplt = 0;

Command_t list_command[] = 
{
	{"GROUP_NAME", "NHOM 13\n"},
	{"MEMBERS", "Nhu Ngoc Hoang, Vu Van Tuong, Tran Dinh Huy Anh, Nguyen Duy Thanh\n"},
	{"PROJECT_NAME", "He thong quan ly ra vao voi RFID va LCD\n"},
	{"HARDWARE_USED", "STM32F103C8T6, RFID RC522, LCD1602 I2C, UART CP2102, ST LINK V2\n"},
	{"SOFTWARE_USED", "KEIL C, HAL Library\n"},
	{"DATE", "2025-12-01\n"}
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
		flag_cplt = 0;
		for(uint8_t i=0; i<sizeof(list_command)/sizeof(Command_t); i++){
			if(!strcmp((char*)uart_buffer, list_command[i].request)){
				HAL_UART_Transmit_DMA(&huart1, (uint8_t*)list_command[i].response, strlen(list_command[i].response));
				return;
			}
		}
	}
}
