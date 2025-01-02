#include "stm32f401rbt6.h"
/**
 * @file    LCD.h
 * @author  Somanapalli Dinesh
 * @brief   lcd functions
 * @date    22-DEC-2024
 */
void device_init();/*!< Initialize the devices */
void km_lcd_init();/*!< Initialize the lcd */
void km_lcd_write_cmd(char data);/*!< Write command to lcd */
void KM_LCD_Write_Data(unsigned char str);/*!< Write data to lcd */
void km_lcd_write_higher_data(unsigned char data);/*!< Write higher nibble of data to lcd */
void km_lcd_write_lower_data(unsigned char data);/*!< Write lower nibble of data to lcd */
void lcd(unsigned char *str);/*!< Write the string to lcd */
