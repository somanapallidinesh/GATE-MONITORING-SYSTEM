/**
 * @file    system_config.c
 * @author  Somanapalli Dinesh
 * @brief   This file contains the functions related to the system configuration
 * @date    22-Jan-2020
 * @version 4.0
 * @compiler Keil ARM MDK 5
 * @target  STM32F4011RBT6
 * @details This file contains the functions related to the system configuration
 *          a. Configure interrupts for PC8 and PC9
 *          b. Configure the time 
 *          c. Configure the volume
 *          d. Convert decimal to hexadecimal
 */
#include "stm32f401rbt6.h" // Include the STM32F401RBT6 specific header file

#include "i2c.h"
/**
 * @brief   I2C communication header file
 */
#include "LCD.h"
/**
 * @brief   LCD display header file
 */
#include "SysTickTimer.h"
/**
 * @brief   System tick timer header file
 */
#include "magnetic.h"
/**
 * @brief   Magnetic sensor header file
 */
#include "itoa.h"
/**
 * @brief   Integer to ASCII conversion functions header file
 */
#include "SYSTEM_CONFIG.h"
/**
 * @brief   System configuration functions header file
 */

unsigned char rtc1_data[100]; // Buffer for RTC data
int start = 1;                // Start flag
int g1 = 0, g2 = 0, g3 = 0,   // General purpose counters
    g4 = 0, g5 = 0, g6 = 0, g7 = 0;
int rtc;                      // RTC variable

/**
 * @brief  Convert decimal to hexadecimal
 * This function takes an integer as input and returns the same value in
 * hexadecimal. It does this by taking the remainder of the number when divided
 * by 10, which gives the units digit. The number is then divided by 10 and
 * multiplied by 16, which shifts the digits to the left by 4 bits. The two
 * values are then added together to give the hexadecimal equivalent of the
 * input number.
 * @param  x   The number to be converted to hexadecimal
 * @return     The hexadecimal equivalent of the input number
 */
int dectohex(int x)
{
	// Take the remainder of the number when divided by 10, which gives the units digit
	int y=0;
	y=x%10;
	// Divide the number by 10 and multiply by 16, which shifts the digits to the left by 4 bits
	x = (x / 10) * 16;
	// Add the two values together to give the hexadecimal equivalent of the input number
	return (x + y);
	
}
/**
 * @brief  Configure interrupts for PC8 and PC9
 * This function is used to configure interrupts for PC8 and PC9. It sets the
 * 8th and 9th bits of SYSCFG_EXTICR3 to 01 for triggering interrupts on
 * falling edge. It also sets the 8th and 9th bits of EXTI_FTSR to 1 for
 * configuring the interrupts as falling edge triggered. The 8th and 9th bits
 * of EXTI_IMR are also set to 1 to unmask the interrupts. Finally, the 23rd bit
 * of NVIC_ISER0 is set to 1 to enable the 23rd pin in NVIC of the
 * microprocessor.
 */

//void interrupt_config()
//{
//	SYSCFG_EXTICR3|=0X00000022;//ADDING 8 TH AND 9 TH PORTS
//	EXTI_FTSR|=0X00000300;//SET 8TH AND 9TH BITS ARE FALLING EDGE
//	EXTI_IMR|=0X00000300;//MASK IS ENABLE FOR 8TH AND 9TH BITS 
//	NVIC_ISER0|=(0x01<<23);//SET 23 BIT FOR ENABLE THE 23RD PIN IN NVIC OF MICROPROCESSER
//	
//}		




/**
 * @brief  Configure the device for USART operation.
 *
 * This function is used to configure the device for USART operation. It
 * configures the GPIOA pins as alternate function, sets the baud rate to 115200
 * and enables the USART.
 */




void time_config(int check11)
{
	if(check11==1)
	{
		// Reset check11 and disable specific interrupts
		check11 = 0;
		EXTI_IMR &= 0Xfffffbff;
		EXTI_IMR &= ~0X00000300; // Disable 8th and 9th bits

		// Clear LCD and display configuration messages
		km_lcd_write_cmd(0x01);
		lcd("time config:");
		KM_Delay_ms(300);
		km_lcd_write_cmd(0x01);
		lcd("morning time:");
		km_lcd_write_cmd(0xc0);
		lcd("SS::EE");

		// Initialize the time display with zeros
		km_lcd_write_cmd(0xc0);
		KM_LCD_Write_Data('0');
		KM_LCD_Write_Data('0');
		if(start==1)
		{
			while(1)
		  {
				if(g1<9)
				{
					// Display the hours
					//km_lcd_write_cmd(0x85);
					km_lcd_write_cmd(0xc0);
					KM_LCD_Write_Data('0');
					myitoa2(g1);
					km_lcd_write_cmd(0xc1);// Move the cursor to the next field

				}
				else
				{
					km_lcd_write_cmd(0xc0);// Move the cursor to the next field

				}
		    if(!(GPIOC_IDR&(0x01<<8)))
				{
					// Increment the hours if the button is pressed

					g1++;
					KM_Delay_ms(300);
					// Wrap around to 0 if the hours exceeds 23

					if(g1>23)
				{
						g1=0;
						km_lcd_write_cmd(0xc0);
						KM_LCD_Write_Data('0');
						KM_LCD_Write_Data('0');
				}
				else
				{
						myitoa2(g1);
				}
									
				}
        if(!(GPIOC_IDR&(0x01<<9)))
				{
					// Decrement the hours if the button is pressed

					g1--;
					KM_Delay_ms(300);
					// Wrap around to 0 if the hours exceeds 23
					if(g1==9)
				  {
						km_lcd_write_cmd(0xc0);
						KM_LCD_Write_Data('0');
						myitoa2(g1);
						km_lcd_write_cmd(0xc1);
					}
			    else if(g1<=0)
					{
						// If the hours is 0, wrap around to 23
						g1=0;
						km_lcd_write_cmd(0xc0);
						KM_LCD_Write_Data('0');
						KM_LCD_Write_Data('0');
			    }
					else
					{		
							// If the hours is not 0, display the hours
						myitoa2(g1);
				  }	
			  }				
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					// If the button is pressed, set the start flag to 2
					// and break the loop

					start=2;
					// Convert the hours from decimal to BCD
					g1=dectohex(g1);
					// Store the hours in the first element of the array
					rtc1_data[0]=g1;
					KM_Delay_ms(300);
					break;
				}
			}
				
		}
 if(start==2)
		{
			km_lcd_write_cmd(0xc4);
		KM_LCD_Write_Data('0');
		KM_LCD_Write_Data('0');
		while(1)
		{
			// Increment the hours if the button is pressed
		
	   	if(g2<9)
				{
					//km_lcd_write_cmd(0x85);
					km_lcd_write_cmd(0xc4);
					KM_LCD_Write_Data('0');
					myitoa2(g2);
					km_lcd_write_cmd(0xc5);
				}
				else
				{
					km_lcd_write_cmd(0xc4);
				}
		    // Increment the hours if the button is pressed
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					g2++;
					KM_Delay_ms(300);
					if(g2>23)
					{
						g2=0;
			 km_lcd_write_cmd(0xc4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
							myitoa2(g2);
					}
									
				}
				// Decrement the hours if the button is pressed
        if(!(GPIOC_IDR&(0x01<<9)))
				{
					g2--;
					KM_Delay_ms(300);
					if(g2==9)
				{
					km_lcd_write_cmd(0xc4);
					KM_LCD_Write_Data('0');
					myitoa2(g2);
					km_lcd_write_cmd(0xc5);
					
				}
			else if(g2<=0)
			{
       g2=0;
			 km_lcd_write_cmd(0xc4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
									myitoa2(g2);
				}	
			}	
			
				// If the button is pressed, set the start flag to 3
				// and break the loop
				
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					start=3;
					g3=g2;
					g2=dectohex(g2);
					rtc1_data[1]=g2;
					KM_Delay_ms(300);
					break;
				}
				
				
				
			}
				
			}
		km_lcd_write_cmd(0x01);
		lcd("afernoon time:");
		km_lcd_write_cmd(0xc0);
		lcd("SS::EE");
		km_lcd_write_cmd(0xc0);
			KM_LCD_Write_Data('0');
		KM_LCD_Write_Data('0');
				km_lcd_write_cmd(0xc0);
			
			if(g3<9)
				{
					//km_lcd_write_cmd(0x85);
					km_lcd_write_cmd(0xc0);
					KM_LCD_Write_Data('0');
					myitoa2(g3);
					
				}
				else
				{
					// Display the hours in the correct format

					km_lcd_write_cmd(0xc0);
					myitoa2(g3);
				}
		g3=dectohex(g3);
					rtc1_data[2]=g3;
	/* Display the morning time in the correct format */
		 if(start==3)
		{
				km_lcd_write_cmd(0xc4);
		KM_LCD_Write_Data('0');
		KM_LCD_Write_Data('0');
		while(1)
		{
		
		
	   	if(g4<9)
				{
					//km_lcd_write_cmd(0x85);
					km_lcd_write_cmd(0xc4);
					KM_LCD_Write_Data('0');
					myitoa2(g4);
					km_lcd_write_cmd(0xc5);
				}
				else
				{
					km_lcd_write_cmd(0xc4);
				}
		/* Increment the hours if the button is pressed */
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					g4++;
					KM_Delay_ms(300);
					if(g4>23)
					{
						g4=0;
			 km_lcd_write_cmd(0xc4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(g4);
					}
									
				}
				/* Decrement the hours if the button is pressed */
        if(!(GPIOC_IDR&(0x01<<9)))
				{
					g4--;
					KM_Delay_ms(300);
					if(g4==9)
				{
					km_lcd_write_cmd(0xc4);
					KM_LCD_Write_Data('0');
					myitoa2(g4);
					km_lcd_write_cmd(0xc5);
					
				}
			else if(g4<=0)
			{
       g4=0;
			 km_lcd_write_cmd(0xc4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
									myitoa2(g4);
				}	
			}		
/* If the button is pressed, set the start flag to 4
				 * and break the loop
				 */
				
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					start=4;
					g5=g4;
					g4=dectohex(g4);
					rtc1_data[3]=g4;
					KM_Delay_ms(300);
					break;
				}
				
				
				
			}
				
			}
		// Clear the LCD
		km_lcd_write_cmd(0x01);
		// Display "evening time:"
		lcd("evening time:");
		// Move the cursor to the second line
		km_lcd_write_cmd(0xc0);
		// Display "SS:EE"
		lcd("SS::EE");
		// Move the cursor to the second line
		km_lcd_write_cmd(0xc0);
		// Display "00"
		
		KM_LCD_Write_Data('0');
		KM_LCD_Write_Data('0');
		// Move the cursor to the second line
		km_lcd_write_cmd(0xc0);
		

			
			if(g5<9)
				{
					//km_lcd_write_cmd(0x85);
					// Display the hours in the correct format
					km_lcd_write_cmd(0xc0);
					KM_LCD_Write_Data('0');
					myitoa2(g5);
					
				}
				else
				{
					km_lcd_write_cmd(0xc0);
					myitoa2(g5);
				}
				g5=dectohex(g5);
					rtc1_data[4]=g5;
	
		
 if(start==4)
		{
				km_lcd_write_cmd(0xc4);
		KM_LCD_Write_Data('0');
		KM_LCD_Write_Data('0');
		while(1)
		{
		/* Display the hours in the correct format
			 * and configure the minutes
			 */

		
	   	if(g6<9)
				{
					//km_lcd_write_cmd(0x85);
					km_lcd_write_cmd(0xc4);
					KM_LCD_Write_Data('0');
					myitoa2(g6);
					km_lcd_write_cmd(0xc5);
				}
				else
				{
					km_lcd_write_cmd(0xc4);
				}
		     /* If the button is pressed, increment the minutes
				 * and break the loop
				 */

				if(!(GPIOC_IDR&(0x01<<8)))
				{
					g6++;
					KM_Delay_ms(300);
					if(g6>23)
					{
						g6=0;
			 km_lcd_write_cmd(0xc4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(g6);
					}
									
				}
				 /* If the button is pressed, decrement the minutes
         * and break the loop
         */

        if(!(GPIOC_IDR&(0x01<<9)))
				{
					g6--;
					KM_Delay_ms(300);
					if(g6==9)
				{
					km_lcd_write_cmd(0xc4);
					KM_LCD_Write_Data('0');
					myitoa2(g6);
					km_lcd_write_cmd(0xc5);
					
				}
			else if(g6<=0)
			{
       g6=0;
			 km_lcd_write_cmd(0xc4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
									myitoa2(g6);
				}	
			}		
/* If the button is pressed, set the start flag to 1
				 * and break the loop
				 */
				
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					start=1;
					g6=dectohex(g6);
					rtc1_data[5]=g6;
					KM_Delay_ms(300);
					break;
				}
				
				
				
			}
				
			}
		// write the data to EEPROM
		rtc=KM_I2C_Mem_Write( 0x50, 0x00, 0x01, rtc1_data, 0x06); 
		 km_lcd_write_cmd(0x01);
		EXTI_IMR|=0X00000300;//MASK IS ENABLE FOR 8TH AND 9TH BITS 
			EXTI_IMR|=0X00000400;
			
		}
		
		
		
		
		
	}
	
	void volume_config(int check12)
	{
		if(check12==1)
		{
			check12=0;
		 EXTI_IMR&=(0Xfffffbff);
		EXTI_IMR&=~(0X00000300);
		km_lcd_write_cmd(0x01);
		lcd("volume config:");
		KM_Delay_ms(300);
		km_lcd_write_cmd(0x01);
		lcd("set volume:");
		km_lcd_write_cmd(0xc0);
		lcd("ss");
		km_lcd_write_cmd(0xc0);
		KM_LCD_Write_Data('0');
		KM_LCD_Write_Data('0');
			while(1)
		{
			
		
        if(g7<9)
				{
					//km_lcd_write_cmd(0x85);
					km_lcd_write_cmd(0xc0);
					KM_LCD_Write_Data('0');
					myitoa2(g7);
					km_lcd_write_cmd(0xc1);
				}
				else
				{
					km_lcd_write_cmd(0xc0);
				}
		
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					g7++;
					KM_Delay_ms(300);
					if(g7>30)
					{
						g7=0;
			 km_lcd_write_cmd(0xc0);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(g7);
					}
									
				}
        if(!(GPIOC_IDR&(0x01<<9)))
				{
					g7--;
					KM_Delay_ms(300);
					if(g7==9)
				{
					km_lcd_write_cmd(0xc0);
					KM_LCD_Write_Data('0');
					myitoa2(g7);
					km_lcd_write_cmd(0xc1);
					
				}
			else if(g7<=0)
			{
       g7=0;
			 km_lcd_write_cmd(0xc0);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
									myitoa2(g7);
				}	
			}				
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					unsigned char st_link[1];
					start=2;
					g7=dectohex(g7);
					st_link[0]=g7;
					KM_Delay_ms(300);
					KM_I2C_Mem_Write( 0x50, 0x06, 0x01, st_link, 0x01); 
		      km_lcd_write_cmd(0x01);
		      EXTI_IMR|=0X00000300;//MASK IS ENABLE FOR 8TH AND 9TH BITS 
			    EXTI_IMR|=0X00000400;
					break;
				}
				
				
				
			}
		
				
			}
		
		}
		
	

	
	
  
	

	
