
// STM32F401RBT6 specific header file
#include "stm32f401rbt6.h"

// I2C communication header file
#include "i2c.h"

// LCD display header file
#include "LCD.h"

// SysTick Timer for delay functions
#include "SysTickTimer.h"

// Integer to ASCII conversion functions
#include "itoa.h"

// System configuration functions
#include "SYSTEM_CONFIG.h"



/**
 * This function is used to reset the device configuration to the default values.
 */
void device_reset()
{
   // variables to store the RTC data
   unsigned char rtc_data2[7];
   

   // dummy strings for display
	int check=0x00,hur=0x00,min=0x00,sec=0x00,date=0x00,mon=0x00,year=0x00;
		
		
		unsigned char dummy1[]="HH:MM:SS";
		unsigned char dummy2[]="DD/MM/YY";
		
		
		// reset the RTC to the default values
	  EXTI_IMR&=~(0X00000300);//MASK IS DISABLE FOR 8TH AND 9TH BITS 
		// Disable 8th and 9th bits in EXTI_IMR
		EXTI_IMR&=(0Xfffffbff);
		// Clear the LCD
		km_lcd_write_cmd(0x01);
		// Move the curser to line 1, position 1
        km_lcd_write_cmd(0x81);
		
		// display dummy strings for hour, minute, second, date, month, year
		lcd(dummy1);
		km_lcd_write_cmd(0xC1);	
		lcd(dummy2);
		
		// wait for the user to enter the time		
		// check variable to move to next configuration
		if(check==0)
		{
			// display dummy strings for hour, minute, second, date, month, year

			km_lcd_write_cmd(0x81);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			while(1)
			{
				// display hour
				if(hur<9)
				{
					km_lcd_write_cmd(0x81);
					KM_LCD_Write_Data('0');
					myitoa2(hur);
					km_lcd_write_cmd(0x82);
					
				}
				else
				{
					km_lcd_write_cmd(0x81);
				}
					
				// increment hour
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					hur++;
					KM_Delay_ms(300);
					if(hur>24)
					{
						hur=0;
			 km_lcd_write_cmd(0x81);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(hur);
					}
				}
        // decrement hour
				if(!(GPIOC_IDR&(0x01<<9)))
      
				{
					hur--;
					KM_Delay_ms(300);
					if(hur==9)
				{
					km_lcd_write_cmd(0x81);
					KM_LCD_Write_Data('0');
					myitoa2(hur);
					km_lcd_write_cmd(0x82);
					
				}
			else if(hur<=0)
			{
       hur=0;
			 km_lcd_write_cmd(0x81);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
					myitoa2(hur);
				}
				}				
				// move to minute configuration
				if(!(GPIOC_IDR&(0x01<<10)))
				{

					check=1;
					hur=dectohex(hur);
					rtc_data2[2]=hur;
					KM_Delay_ms(300);
					break;
				}
			
      				
			
				
			}
		}
		if(check==1)
		{
			// display dummy strings for hour, minute, second, date, month, year
			km_lcd_write_cmd(0x84);
				km_lcd_write_cmd(0x84);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			while(1)
			{
				// display minute
				if(min<9)
				{
					//km_lcd_write_cmd(0x85);
					km_lcd_write_cmd(0x84);
					KM_LCD_Write_Data('0');
					myitoa2(min);
					km_lcd_write_cmd(0x85);
				}
				else
				{
					km_lcd_write_cmd(0x84);
				}
		
				// increment minute
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					min++;
					KM_Delay_ms(300);
					if(min>60)
					{
						min=0;
			 km_lcd_write_cmd(0x84);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(min);
					}
									
				}
        // decrement minute
				if(!(GPIOC_IDR&(0x01<<9)))
       
				{
					min--;
					KM_Delay_ms(300);
					if(min==9)
				{
					km_lcd_write_cmd(0x84);
					KM_LCD_Write_Data('0');
					myitoa2(min);
					km_lcd_write_cmd(0x85);
					
				}
			else if(min<=0)
			{
       min=0;
			 km_lcd_write_cmd(0x84);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
									myitoa2(min);
				}	
			}				
				// move to second configuration
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					check=2;
					min=dectohex(min);
					rtc_data2[1]=min;
					KM_Delay_ms(300);
					break;
				}
				
				
				
			}
		}
		
		if(check==2)
		{
			// Initialize the display for second configuration
			km_lcd_write_cmd(0x87);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
		while(1)
		{
				// Display single-digit seconds with a leading zero
				if(sec<9)
				{
					//km_lcd_write_cmd(0x88);
					km_lcd_write_cmd(0x87);
					KM_LCD_Write_Data('0');
					myitoa2(sec);
					km_lcd_write_cmd(0x88);
				}
				else
				{
					km_lcd_write_cmd(0x87);
				}
				// Increment seconds
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					sec++;
					KM_Delay_ms(300);
					if(sec>60)
					{
						sec=0;
			 km_lcd_write_cmd(0x87);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(sec);
					}
									
				}
        // Decrement seconds
				if(!(GPIOC_IDR&(0x01<<9)))
        if(!(GPIOC_IDR&(0x01<<9)))
				{
					sec--;
					KM_Delay_ms(300);
					if(sec==9)
				{
					km_lcd_write_cmd(0x87);
					KM_LCD_Write_Data('0');
					myitoa2(sec);
					km_lcd_write_cmd(0x88);
					
				}
			else if(sec<=0)
			{
       sec=0;
			 km_lcd_write_cmd(0x87);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
									myitoa2(sec);
				}	
			}				
					
									
				
				// Move to date configuration
								
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					check=3;
					sec=dectohex(sec);
					rtc_data2[0]=sec;
					KM_Delay_ms(300);
					break;
				}
				
			
				
			}
		}
	if(check==3)
		{
			km_lcd_write_cmd(0xc1);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			while(1)
			{
				if(date<9)
				{
					km_lcd_write_cmd(0xC1);
					KM_LCD_Write_Data('0');
					myitoa2(date);
					km_lcd_write_cmd(0xC2);
					
				}
				else
				{
					km_lcd_write_cmd(0xC1);
				}
					
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					date++;
					KM_Delay_ms(300);
					if(date>31)
					{
						date=0;
			 km_lcd_write_cmd(0xC1);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(date);
					}
				}
        if(!(GPIOC_IDR&(0x01<<9)))
				{
					date--;
					KM_Delay_ms(300);
					if(date==9)
				{
					km_lcd_write_cmd(0xC1);
					KM_LCD_Write_Data('0');
					myitoa2(date);
					km_lcd_write_cmd(0xC2);
					
				}
			else if(date<=0)
			{
       date=0;
			 km_lcd_write_cmd(0xC1);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
					myitoa2(date);
				}
				}				
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					check=4;
					date=dectohex(date);
					rtc_data2[4]=date;
					KM_Delay_ms(300);
					break;
				}
			}
		}
		// configure the month
		if(check==4)
		{
			km_lcd_write_cmd(0xc4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			while(1)
			{
				if(mon<9)
				{
					km_lcd_write_cmd(0xC4);
					KM_LCD_Write_Data('0');
					myitoa2(mon);
					km_lcd_write_cmd(0xC5);
					
				}
				else
				{
					km_lcd_write_cmd(0xC4);
				}
					
				// increase the month
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					mon++;
					KM_Delay_ms(300);
					if(mon>12)
					{
						mon=0;
			 km_lcd_write_cmd(0xC4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(mon);
					}
				}
        // decrease the month
        if(!(GPIOC_IDR&(0x01<<9)))
				{
					mon--;
					KM_Delay_ms(300);
					if(mon==9)
				{
					km_lcd_write_cmd(0xc4);
					KM_LCD_Write_Data('0');
					myitoa2(mon);
					km_lcd_write_cmd(0xC5);
					
				}
			else if(mon<=0)
			{
       mon=0;
			 km_lcd_write_cmd(0xC4);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					
					myitoa2(mon);
				}
				}				
				// save the month
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					check=5;
					mon=dectohex(mon);
					rtc_data2[5]=mon;
					KM_Delay_ms(300);
					break;
				}
			
      				
			
				
			}
		}
		// configure the year
		if(check==5)
		{
			km_lcd_write_cmd(0xc7);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			while(1)
			{
				if(year<9)
				{
					km_lcd_write_cmd(0xC7);
					KM_LCD_Write_Data('0');
					myitoa2(year);
					km_lcd_write_cmd(0xC8);
					
				}
				else
				{
					km_lcd_write_cmd(0xC7);
				}
				// check the year
					
				if(!(GPIOC_IDR&(0x01<<8)))
				{
					year++;
					KM_Delay_ms(300);
					if(year>99)
					{
						year=0;
			 km_lcd_write_cmd(0xC7);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
					}
					else
					{
									myitoa2(year);
					}
				}
        if(!(GPIOC_IDR&(0x01<<9)))
				{
					year--;
					KM_Delay_ms(300);
					if(year==9)
				{
					km_lcd_write_cmd(0xC7);
					KM_LCD_Write_Data('0');
					myitoa2(year);
					km_lcd_write_cmd(0xC8);
					
				}
			else if(year<=0)
			{
       year=0;
			 km_lcd_write_cmd(0xC7);
			KM_LCD_Write_Data('0');
			KM_LCD_Write_Data('0');
			}
				else
				{
					//display the year
					
					myitoa2(year);
				}
				}				
				if(!(GPIOC_IDR&(0x01<<10)))
				{
					//save the year
					check=6;
					year=dectohex(year);
					rtc_data2[6]=year;
					KM_Delay_ms(300);
					break;

				}
			}
		}
		if(check==6)
		{
int ret1;			
//unsigned char T_Date[]={sec,min,hur,0x1,date,mon,year};
			rtc_data2[3]=0x01;
		
		ret1= KM_I2C_Mem_Write(0x68, 0x00, 0x01, rtc_data2, 0x07);	
		}
	
	EXTI_IMR|=0X00000400;
	
 }
	