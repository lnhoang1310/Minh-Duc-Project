#include "flash.h"

void Flash_Erase_Page(uint32_t address)
{
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef erase;
    uint32_t error;

    erase.TypeErase    = FLASH_TYPEERASE_PAGES;
    erase.PageAddress  = address;
    erase.NbPages      = 1;

    HAL_FLASHEx_Erase(&erase, &error);

    HAL_FLASH_Lock();
}

void Flash_Write(uint32_t address, uint8_t data)
{
    uint16_t half = data;

    Flash_Erase_Page(address);   // *** Quan tr?ng ***

    HAL_FLASH_Unlock();
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, half);
    HAL_FLASH_Lock();
}

void Flash_Read(uint32_t address, uint8_t* data)
{
    uint16_t half = *(__IO uint16_t*)address;
    *data = (uint8_t)(half & 0x00FF);
}

void Flash_Write_Array(uint32_t address, uint8_t* array, uint16_t len)
{
    Flash_Erase_Page(address);
    HAL_FLASH_Unlock();

    uint16_t half;
    uint16_t i = 0;

    while (i < len)
    {
        if(i + 1 < len)
            half = (array[i+1] << 8) | array[i];
        else
            half = array[i];

        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, half);

        address += 2;
        i += 2;
    }

    HAL_FLASH_Lock();
}

void Flash_Read_Array(uint32_t address, uint8_t* array, uint16_t len)
{
    uint16_t half;
    uint16_t i = 0;

    while (i < len)
    {
        half = *(__IO uint16_t*)address;

        array[i] = (uint8_t)(half & 0x00FF);

        if(i + 1 < len)
            array[i+1] = (uint8_t)((half >> 8) & 0xFF);

        address += 2;
        i += 2;
    }
}

void Flash_Write_Matrix(uint32_t address, uint8_t data[][5], uint32_t size)
{
    Flash_Erase_Page(address);
    HAL_FLASH_Unlock();

    uint8_t* ptr = (uint8_t*)data;
    uint16_t half;

    for(uint32_t i = 0; i < size; i += 2)
    {
        if(i + 1 < size)
            half = (ptr[i+1] << 8) | ptr[i];
        else
            half = ptr[i];

        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address + i, half);
    }

    HAL_FLASH_Lock();
}

void Flash_Read_Matrix(uint32_t address, uint8_t data[][5], uint32_t size)
{
    uint16_t half;
    uint8_t* ptr = (uint8_t*)data;

    for(uint32_t i = 0; i < size; i += 2)
    {
        half = *(__IO uint16_t*)(address + i);

        ptr[i] = (uint8_t)(half & 0x00FF);

        if(i + 1 < size)
            ptr[i+1] = (uint8_t)((half >> 8) & 0xFF);
    }
}
