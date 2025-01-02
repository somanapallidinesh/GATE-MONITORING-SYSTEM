/*********************************************************************************************************
*    File: LCD.C                                                                 
*    Description: This file contain the functions related to the lcd
*                 a. write data                                      
*                 b. write command                                                                          
*    Board: Raayan Mini                                                                                  
*    Version: 4.0                                                                                        
*    Controller: STM32F4011RBT6                                                                          
*                                                                                                        
*    Pins Used: PB1,PB2,PB3,PB4,PB5,PB8                                                                         
*                                                                                      
*                                                                                                                                                                                         
**********************************************************************************************************/
/*
This file contain all address of the core registers and peripheras
*/
#include "stm32f401rbt6.h"
/*
This file contain delay function using systicktimer core peripheral
*/
#include "SysTickTimer.h"
/*
This file contains the functions related to the lcd
*/
#include "LCD.h"
/*
This function contain the clock initilization of requred registers and peripherals
*/

void devices_init()
{
	RCC_AHB1ENR|=(0X01<<1);//ENABLE CLOCK TO GPIOB
	GPIOB_MODER&=0XFFFcf000;//CLEAR THE PORTB0,1,2,3,4,5,8
	GPIOB_MODER|=0X00010555;//ENABLE THESE PORTS ARE OUTPUT PORTS
}
/*
This function contain the lcd initilization like clear,curser etc..
*/
void km_lcd_init()
{
	devices_init();
	KM_Delay_ms(20);
	GPIOB_ODR&=~(0X01<<4);//CLEAR THE 4TH TO COMMAND MODE 
	km_lcd_write_cmd(0x33);//
		KM_Delay_ms(1);

	km_lcd_write_cmd(0x32);
	km_lcd_write_cmd(0x0c);
	km_lcd_write_cmd(0x01);//CLEAR THE SCREEN
	km_lcd_write_cmd(0x80);
	}
/*
This function contain the implementation write command of Lcd 
*/
void km_lcd_write_cmd(char data)
{
	char str=(data>>4);//HIGHER NIBBLE IS SHIFFTED TO LOWER NIBBLE BITS
	GPIOB_ODR&=~(0X01<<4);//CLEAR THE 4TH TO COMMAND MODE 
	GPIOB_ODR&=0XFFFFFFF0;//CLEAR THE FIRST FOUR BITS
	str&=0x0f;//CLEAR THE HIGHER NIBBLE
	GPIOB_ODR|=str;//LOAD THE HIGER NIBBLE OF ACTUAL DATA 
	GPIOB_ODR|=(0X01<<8);//SET ENABLE PIN OF THE LCD
		KM_Delay_ms(20);

	GPIOB_ODR&=~(0X01<<8);//CLEAR THE ENABLE PIN
	
	GPIOB_ODR&=0XFFFFFFF0;//CLEAR THE FIRST FOUR BITS
	data&=0x0f;//CLEAR THE HIGHER NIBBLE
	GPIOB_ODR|=data;//LOAD THE LOWER NIBBLE OF ACTUAL DATA 
	GPIOB_ODR|=(0X01<<8);//SET ENABLE PIN OF THE LCD
		KM_Delay_ms(20);

	GPIOB_ODR&=~(0X01<<8);//CLEAR THE ENABLE PIN
	}
/*
This function contain the implementation write data of Lcd 
*/
void KM_LCD_Write_Data(unsigned char str)
{
	int i=0;
	GPIOB_ODR&=(0X00000000);//CLEAR THE ENABLE PIN
 GPIOB_ODR|=(0X01<<4);	//SET THE 4TH TO DATA MODE 
	
	//while(str[i]!='\0')
	{

	km_lcd_write_higher_data(str);
	km_lcd_write_lower_data(str);

	}
}
/*
This function contain the implementation higher nibble data write into a Lcd 
*/
void km_lcd_write_higher_data(unsigned char data)
{
	//GPIOB_ODR|=(0X01<<4);//SET THE 4TH TO DATA MODE 
	GPIOB_ODR&=0XFFFFFFF0;//CLEAR THE FIRST FOUR BITS
	data>>=4;//SHIFT HIGHER NIBBLE TO LOWER NIBBLE
	data&=0x0f;//CLEAR THE HIGHER NIBBLE
	GPIOB_ODR|=data;//LOAD HIGHER NIBBLE DATA 
	GPIOB_ODR|=(0X01<<8);//SET ENABLE PIN OF THE LCD
		KM_Delay_ms(10);

	GPIOB_ODR&=~(0X01<<8);//SET ENABLE PIN OF THE LCD
	
}
/*
This function contain the implementation lower nibble data write into a Lcd 
*/
void km_lcd_write_lower_data(unsigned char data)
{
	//GPIOB_ODR|=(0X01<<4);//SET THE 4TH TO DATA MODE 
	GPIOB_ODR&=0XFFFFFFF0;//CLEAR THE FIRST FOUR BITS
	data&=0x0f;//CLEAR THE HIGHER NIBBLE
	GPIOB_ODR|=data;//LOAD LOWER NIBBLE DATA
	GPIOB_ODR|=(0X01<<8);//SET ENABLE PIN OF THE LCD
		KM_Delay_ms(10);

	GPIOB_ODR&=~(0X01<<8);//SET ENABLE PIN OF THE LCD
}
/*
This function contain the implementation string is converted into characters and sending into write data function
*/
void lcd(unsigned char *str)
{
	int i=0;//local variable
	//km_lcd_init();
	while(str[i]!='\0')//loop will set to iterate upto null character is found
	{
		KM_LCD_Write_Data(str[i]);//write each character in lcd
		i++;//increment
	}
	
		
}