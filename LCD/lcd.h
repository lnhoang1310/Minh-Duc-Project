#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f1xx_hal.h"

#define LCD_ADDRESS 0x27 << 1

typedef struct{
	I2C_HandleTypeDef *hi2c;
	uint16_t address;
}I2C_LCD_HandleTypedef;

void lcd_clear(I2C_LCD_HandleTypedef* lcd);
void lcd_gotoxy(I2C_LCD_HandleTypedef* lcd, uint8_t col, uint8_t row);
void lcd_init(I2C_LCD_HandleTypedef* lcd, I2C_HandleTypeDef* _hi2c, uint16_t _address);
void lcd_send_string(I2C_LCD_HandleTypedef* lcd, char* str);
void lcd_send_char(I2C_LCD_HandleTypedef* lcd, char c);
void lcd_create_char(I2C_LCD_HandleTypedef* lcd, uint8_t location, uint8_t charmap[]);

#endif /* INC_LCD_H_ */

