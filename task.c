#include "stm32f401rbt6.h"
#include "i2c.h"
#include "LCD.h"
#include "SysTickTimer.h"
#include "magnetic.h"
#include "SYSTEM_CONFIG.h"
#include "config.h"
#include "task.h"
#include "itoa.h"
int in=0,out=0;
unsigned char str[]="Gate Announces..";
unsigned char rtc_data[100];
extern int flag11;
extern int flag12;
extern int time_out;
extern int total;
extern int count;

/**
 * @brief  Convert higher nibble of BCD to decimal
 * @param  p   Higher nibble of BCD data
 * @return     Decimal equivalent of the higher nibble of BCD
 */
char bcd_dec1(char p)
{
	p=(((p>>4)+48));
	return p;
}
/**
 * @brief  Convert lower nibble of BCD to decimal
 * @param  p   Lower nibble of BCD data
 * @return     Decimal equivalent of the lower nibble of BCD
 */


char bcd_dec2(char p) 
{
	p=(((p&0x0f)+48));
	return p;
}


/**
 * @brief  Configure PC8,PC9 as input with pull-up.
 * This function is used to configure the pins PC8 and PC9 as input with pull-up
 * so that they can be used as switches.
 */
void switch_config()
{
	GPIOC_PUPDR&=0XFFC0FFFF;
	GPIOC_PUPDR|=0X00150000;
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

void interrupt_config()
{
	SYSCFG_EXTICR3|=0X00000200;
	EXTI_FTSR|=0X00000400;
	EXTI_IMR|=0X00000400;
	NVIC_ISER1|=(0x01<<8);
	SYSCFG_EXTICR3|=0X00000022;//ADDING 8 TH AND 9 TH PORTS
	EXTI_FTSR|=0X00000300;//SET 8TH AND 9TH BITS ARE FALLING EDGE
	EXTI_IMR|=0X00000300;//MASK IS ENABLE FOR 8TH AND 9TH BITS 
	NVIC_ISER0|=(0x01<<23);//SET 23 BIT FOR ENABLE THE 23RD PIN IN NVIC OF MICROPROCESSER
	
}		

/**
 * @brief  Initialize the device.
 *
 * This function is used to initialize the device. It enables the clock to
 * GPIOA, GPIOB, GPIOC, GPIOH and USART2. It is called in the main function
 * to initialize the device before performing any other operations.
 */

void device_init()
{
	RCC_AHB1ENR|=(0X07);
	RCC_APB2ENR|=(0X00004000); 
	RCC_APB1ENR|=(0X01<<17);//ENABLE CLOCK TO USART
	
}

/**
 * @brief  Configure the device for USART operation.
 *
 * This function is used to configure the device for USART operation. It
 * configures the GPIOA pins as alternate function, sets the baud rate to 115200
 * and enables the USART.
 */

void device_config()
{
	GPIOA_MODER&=0XFFFFFF0F;//CLEAR THE 7-6 BITS
	GPIOA_MODER|=0X000000A0;//LOAD 1010 FOR TO ENABLE ALTERNATIVE MODE
	GPIOA_AFRL|=0X00007700;//CONFIGURE THE ATRNATIVE MODE
	USART2_BRR=0X680;//BAUD RATE
	USART2_CR1|=0X0000200C;//ENABLE THE USART
	USART2_SR&=0X00000000;

}

/**
 * @brief  Transmit a character via USART.
 * 
 * This function waits until the USART data register is empty, then loads
 * the specified character into the data register for transmission.
 *
 * @param  x  The character to be transmitted.
 */


void usart_outchar(char x)
{
	while(!(USART2_SR&(0X01<<7)))//RETURN THE RECEIVED VALUE

	{
		;
	}
	USART2_DR=x;//LOAD THE TRANSMITTING VALUE
	
}

/**
 * @brief  Transmit a string via USART.
 * 
 * This function transmits each character of the string via USART by calling
 * usart_outchar() for each character. It iterates until it encounters a null
 * character.
 *
 * @param  str  The string to be transmitted.
 */

void usart_out_string(char str[])
{
	int i=0;
	while(str[i]!='\0')
	{
		usart_outchar(str[i]);
		i++;
	}
	
}
void total_count()
{
	unsigned char st[]="TOTALMEMBERS:";
	 km_lcd_write_cmd(0x01);
	lcd(st);
	myitoa2(total);
	KM_Delay_ms(300);
	
	
}


/**
 * @brief  Read the time from the RTC.
 *
 * This function reads the time from the RTC and displays it on the LCD in the
 * format HH:MM:SS. It also displays the date in the format DD/MM/YY.
 *
 * @note   This function is called in the main loop of the program to
 *         display the time and date on the LCD.
 */
void rtc_read_1sec()
{
	int ret=0;

	 ret = KM_I2C_Mem_Read( 0x68, 0x00, 0x01, rtc_data, 0x07); 
	if(ret==1)
	{
		
		//lcd(rt3);
		// Display time in the format HH:MM:SS
		km_lcd_write_cmd(0x81);
		KM_LCD_Write_Data(bcd_dec1(rtc_data[2]));
		KM_LCD_Write_Data(bcd_dec2(rtc_data[2]));
		KM_LCD_Write_Data(':');
		
//		lcd(rt2);
		KM_LCD_Write_Data(bcd_dec1(rtc_data[1]));
		KM_LCD_Write_Data(bcd_dec2(rtc_data[1]));
	//	lcd(rt1);
		KM_LCD_Write_Data(':');
	  KM_LCD_Write_Data(bcd_dec1(rtc_data[0]));
		KM_LCD_Write_Data(bcd_dec2(rtc_data[0]));
	//	km_lcd_write_cmd(0x01);
		km_lcd_write_cmd(0xc1);
		 KM_LCD_Write_Data(bcd_dec1(rtc_data[4]));
		KM_LCD_Write_Data(bcd_dec2(rtc_data[4]));
		KM_LCD_Write_Data('/');
		
		 KM_LCD_Write_Data(bcd_dec1(rtc_data[5]));
		KM_LCD_Write_Data(bcd_dec2(rtc_data[5]));
		KM_LCD_Write_Data('/');
		//km_lcd_write_cmd(0xcb);
		 KM_LCD_Write_Data(bcd_dec1(rtc_data[6]));
		KM_LCD_Write_Data(bcd_dec2(rtc_data[6]));
		//KM_LCD_Write_Data('-');
		
	}
}
/**
 * @brief  This function is used to close the gate. It displays a message on
 *         the LCD and sends a command through USART to close the gate.
 *         It waits until the gate is closed and then displays a "Thank You"
 *         message on the LCD.
 * @note   This function is called in main loop of the program to control the
 *         gate.
 */

void gate_close()
{ 
	// Display "Please close" on the first line of the LCD
	// and "gate" on the second line.
	unsigned char str1[]="please close";
	unsigned char str2[]="gate";
	km_lcd_write_cmd(0x01);
	  lcd(str1);
	km_lcd_write_cmd(0xc9);
	  lcd(str2);
	

	// Wait until the gate is closed. When the gate is closed, the
	// signal from the sensor will be high. The loop will continue
	// until the gate is closed.
	while(GPIOA_IDR&(0X01))
	{
		char gm[]={0x7E,0X04,0X03,0X00,0X03,0XEF};
		int i=0;
		// Send the command to close the gate through USART.
		for(i=0;i<6;i++)
		{
		usart_outchar(gm[i]);	
		}
	

		// Wait for 4 seconds before sending the command again.
		KM_Delay_ms(4000);
	
		
	}
{	// Send the command to open the gate through USART
	// and display "Thank You" on the LCD.
	char gm[]={0x7E,0X04,0X03,0X00,0X04,0XEF};
	int i=0;
	
	unsigned char str3[]="Thank You";
	
	
		if(in==1)
	{
		in=0;
		flag11=0,flag12=0;
		total=total+count;
		count=0;
	}
	if(out==1)
	{
		out=0;
		flag11=0,flag12=0;
		total=total-count;
		count=0;
	}
	km_lcd_write_cmd(0x01);
	lcd(str);
	km_lcd_write_cmd(0xc0);
	 lcd(str3);
	
	// Send the command to open the gate through USART.
	for(i=0;i<6;i++)
	{
		
		usart_outchar(gm[i]);	
	}
	
	// Wait for 1 second before clearing the LCD.
	KM_Delay_ms(1000);
	total_count();
	// Clear the LCD.
	
	km_lcd_write_cmd(0x01);
}
	}
/**
 * @brief  This function is used to check the time and day and display an
 *         appropriate greet message on the LCD. If the time is between the
 *         set time interval, it will send a command through USART to open
 *         the gate. It waits until the gate is closed and then displays a
 *         "Thank You" message on the LCD.
 * @note   This function is called in main loop of the program to control the
 *         gate.
 */
void task2_check_sensor()
{
	/* Variables to store the return value of the I2C read function
	   and the data read from the RTC. */
	int ret=0;
	unsigned char t_read[100];
	/* Variable to store the time set by the user. */
	unsigned char time_set[100];

	// Reset the time_out counter to 0 if it reaches 50
	// and reset flag12 to 0
	
if(time_out==50)
    {
		flag12=0;
		time_out=0;
	  }
    time_out++;    
	 /* Check if the flag11 is set. If it is, read the memory of the I2C device
	   and reset the flag11 to 0. */
	 if(flag11==1)
         {
					 ret=KM_I2C_Mem_Read(0x50,0x00,0x01,time_set,0x07);
					// flag11=0;
          if(flag12==1)
           {

						 unsigned char x[]="ThankYou";
						 /* Send the command to open the gate through USART. */
						
						 char gm[]={0x7E,0X04,0X03,0X00,0X06,0XEF};
		         int i=0;
						 out=1;
						 	 	km_lcd_write_cmd(0x01);
	              lcd(str);
	               km_lcd_write_cmd(0xc0);
						      lcd(x);
			// Send the command to open the gate through USART.
			// 0X7E is the start byte.
			// 0X03 is the command to open the gate.
			// 0X06 is the address of the slave device.
			// time_set[6] is the time set by the user.
			// 0XEF is the end byte.
			usart_outchar(0X7E);
			usart_outchar(0X03);
			usart_outchar(0X06);
			usart_outchar(time_set[6]);
			usart_outchar(0XEF);
		for(i=0;i<6;i++)
			{
			usart_outchar(gm[i]);
			}
						 // Reset the flag12 to 0
						// flag12=0;

		  // Wait for 900ms before clearing the LCD
		  KM_Delay_ms(900);
		   // Clear the LCD
		   km_lcd_write_cmd(0x01);
			 // Call the gate_close() function to close the gate
			 gate_close();

           

	  }
    else
	 {
		 in=1;
		km_lcd_write_cmd(0x01);
				// Read the memory of the I2C device
				ret=KM_I2C_Mem_Read(0x68,0x00,0x01,t_read,0x07);
				ret=KM_I2C_Mem_Read(0x50,0x00,0x01,time_set,0x07);
			  // Check the hour and display an appropriate greet
			usart_outchar(0X7E);
			usart_outchar(0X03);
			usart_outchar(0X06);
			usart_outchar(time_set[6]);
			usart_outchar(0XEF);
				if(t_read[2]>=time_set[0]&&t_read[2]<time_set[1])
		{
			
			// Morning
			unsigned char x[]="Good Morning";
			// Send USART commands for morning
			char gm[]={0x7E,0X04,0X03,0X00,0X05,0XEF,0x7E,0X04,0X03,0X00,0X07,0XEF};
		int i=0;
				km_lcd_write_cmd(0x01);
	       lcd(str);
	       km_lcd_write_cmd(0xc0);
			lcd(x);
		for(i=0;i<12;i++)
			{
			usart_outchar(gm[i]);
			}
			
			// Wait for 1 second before closing the gate
			KM_Delay_ms(1000);
			// Call the gate_close() function to close the gate
			gate_close();
				
			

		}

    // Check the time and display appropriate messages
		else if(t_read[2]>=time_set[2]&&t_read[2]<time_set[3]) // Afternoon
		{
			// Display "Good Afternoon" on the LCD
			unsigned char x[]="Good Afternoon";
			// Send USART commands for afternoon
			char gm[]={0x7E,0X04,0X03,0X00,0X01,0XEF,0x7E,0X04,0X03,0X00,0X07,0XEF};
		int i=0;
				km_lcd_write_cmd(0x01);
	lcd(str);
	km_lcd_write_cmd(0xc0);
			lcd(x);
		for(i=0;i<12;i++)
			{
			usart_outchar(gm[i]);
			}
			
			// Wait for 1 second before closing the gate
			KM_Delay_ms(1000);
			// Call the gate_close() function to close the gate
			gate_close();
		}
		else if(t_read[2]>=time_set[4])//&&t_read[2]<time_set[5]) // Evening
		
		{
			
			// Display "Good Evening" on the LCD
			unsigned char x[]="Good Evening";
			
			// Send USART commands for evening
			char gm[]={0x7E,0X04,0X03,0X00,0X02,0XEF,0x7E,0X04,0X03,0X00,0X07,0XEF};
		int i=0;
				km_lcd_write_cmd(0x01);
	lcd(str);
	km_lcd_write_cmd(0xc0);
			lcd(x);
		for(i=0;i<12;i++)
			{
			usart_outchar(gm[i]);
			}
			
			// Wait for 1 second before closing the gate
			KM_Delay_ms(1000);
			// Call the gate_close() function to close the gate
			gate_close();
		
				}


		// Wait for 300ms before clearing the LCD
		KM_Delay_ms(300);
		
		// Clear the LCD
		km_lcd_write_cmd(0x01);
		
		// Clear the LCD again
		km_lcd_write_cmd(0x01);
	
	}
	
	
				
						
		}
	
}
void starting_message()
{
	 unsigned char stli[]="GATE MONITORING";
	unsigned char stli2[]="V 1.0";
	km_lcd_write_cmd(0x01);
	km_lcd_write_cmd(0x80);
	lcd(stli);
	km_lcd_write_cmd(0xc5);
	lcd(stli2);
	KM_Delay_ms(1000);
	km_lcd_write_cmd(0x01);
	
	
	
}


	
	