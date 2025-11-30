#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

/* ==========================
   FUNCTION PROTOTYPES
========================== */

void Flash_Erase_Page(uint32_t address);

void Flash_Write(uint32_t address, uint8_t data);
void Flash_Read(uint32_t address, uint8_t* data);

void Flash_Write_Array(uint32_t address, uint8_t* array, uint16_t len);
void Flash_Read_Array(uint32_t address, uint8_t* array, uint16_t len);

void Flash_Write_Matrix(uint32_t address, uint8_t data[][5], uint32_t size);
void Flash_Read_Matrix(uint32_t address, uint8_t data[][5], uint32_t size);

#endif
