/*********************************************************************************************************
*    File: KM_Systick_Timer.c                                                                  
*    Description: This file contains functions related to generate own delay functions using both        
*                 a. Polling                                                                             
*                 b. Interrupt                                                                           
*    Board: Raayan Mini                                                                                  
*    Version: 4.0                                                                                        
*    Controller: STM32F4011RBT6                                                                          
*                                                                                                        
*    Pins Used:      Null                                                                                    
*                                                                                      
*                                                                                                        
*    Core Peripherals:Systick Timer                                                                                    
**********************************************************************************************************/


/**********************************************************************
*                     PERIPHERAL ADDRESSES                            
***********************************************************************/

#include "SysTickTimer.h"

/*
*    AHB1_BASEADDR:      Base address of AHB1 Peripheral Bus
*    GPIOB_BASEADDR:     Base address of GPIOB Peripheral
*    RCC_BASEADDR:       Base address of Reset and Clock Control (RCC) Peripheral
*/

#define     AHB1_BASEADDR      0x40020000
#define     GPIOB_BASEADDR     0x40020400
#define     RCC_BASEADDR       0x40023800

/*
*    GPIOB_MODER:        GPIOB Mode Register
*    GPIOB_ODR:          GPIOB Output Data Register
*/

#define     GPIOB_MODER        *(int*)(GPIOB_BASEADDR)
#define     GPIOB_ODR          *(int*)(GPIOB_BASEADDR + 0x14)

/*
*    RCC_AHB1ENR:        AHB1 Peripheral Clock Enable Register
*/

#define     RCC_AHB1ENR       *(int*)(RCC_BASEADDR + 0x30)
    
/*
*    STK_CTRL:           System Tick Timer Control Register
*    STK_LOAD:           System Tick Timer Load Register
*    STK_VAL:            System Tick Timer Current Value Register
*/

#define     STK_CTRL          *(int*)0xE000E010
#define     STK_LOAD          *(int*)0xE000E014
#define     STK_VAL           *(int*)0xE000E018

    

    


/**********************************************************************
*                   FUNCTION DECLARATIONS                             
***********************************************************************/

void GPIOB_INIT(void);
void RED_LED_CONFIG(void);

void SYSTICK_INIT(void);

/*
    Generic Delay functions using Polling
*/
void km_mdelay(int );
void km_udelay(int );

/*
    Generic Delay functions using Interrupt
*/
void km_mdelay_it(int );
void km_udelay_it(int );

/**********************************************************************
*                   GLOBAL VARIABLES                                  
***********************************************************************/

int count1= 0;
int temp_count = 0;

/********************************************************************************
*                    SYSTICK_INIT()                                   
* Description : Here all initialization of systick timer is done      
* Arguments   : none                                                  
* Return Type : none                                                  
* Notes :  STK_CTRL value is 7 for interrupt mode / 5 for Polling 
*          STK_VAL  value is anything to clear the current value in register
*          STK_LOAD value is 16000 for 1msec                             
*********************************************************************************/


void SYSTICK_INIT(void)
{
    // Enable SysTick timer with interrupt
    STK_CTRL |= 0x07;
    // Clear current value register
    STK_VAL = 0x123;
    // Load value for 1ms delay
    STK_LOAD = 16000;
}



void GPIOB_INIT(void)
{

    // Enable clock to GPIOB
    RCC_AHB1ENR |= (1 << 1);
   
}




/**************************************************************************
*           KM_MDELAY_IT(int ) , KM_MDELAY(int )                   
* Description : Functions to generate MILLI Seconds Delay 
*               It will take int input and loads value into STK_LOAD                                              
* Arguments   : int                                                   
* Return Type : none                                                  
* Notes :  STK_LOAD value is 16000 for 1msec                                                       
****************************************************************************/

void KM_Delay_ms(int n)
{
    //Phase 1
    SYSTICK_INIT();
   // GPIOB_INIT();
    STK_VAL = 0x123;
   // STK_LOAD = 16000 * n;

    // add 'n' to current counter value
    temp_count = n + count1;
    // wait until the counter value exceeds the current counter value
    while((temp_count)  >= count1);
}


/**************************************************************************
*           KM_DELAY(int n)                   
* Description : Function to generate delay in milliseconds
*               using the SysTick timer with polling.
* Arguments   : int n - Number of milliseconds to delay
* Return Type : none                                                  
* Notes :  - Initializes and configures the SysTick timer.
*          - STK_LOAD value is calculated as 16000 * n for n milliseconds.
*          - Waits until the COUNTFLAG bit is set, indicating the delay is complete.
****************************************************************************/

void KM_Delay(int n)
{
	  //Phase 1
    // Initialize SysTick timer and GPIOB
    SYSTICK_INIT();
    GPIOB_INIT();

    // Clear current value register
    STK_VAL = 0x123;

    // Load value for n milliseconds delay
    STK_LOAD = 16000 * n;

    // Wait until the COUNTFLAG bit is set
    while(!(STK_CTRL & (0x1 << 16)));
}

/**************************************************************************
*           KM_uDELAY_IT(int ) , KM_uDELAY_IT(int )                   
* Description : Function to generate MICRO Seconds Delay 
*               It will take int input and loads value into STK_LOAD                                              
* Arguments   : int                                                   
* Return Type : none                                                  
* Notes : STK_LOAD value is 16 for 1usec                             
****************************************************************************/



void km_udelay_it(int n)
{
	int temp_count = 0;
	   //Phase 1
    SYSTICK_INIT();
   GPIOB_INIT();
	
    
//    STK_VAL = 0x123;
//    STK_LOAD = 16 * n;
    temp_count = n + count1;
    while(temp_count  >= count1);
}

void km_udelay(int n)
{
	   //Phase 1
    SYSTICK_INIT();
   GPIOB_INIT();
    //int temp_count = 0;
    STK_VAL = 0x123;
    STK_LOAD = 16 * n;
    
    temp_count = n + count1;
    while(temp_count  > count1);
    while(!(STK_CTRL & (0x1 << 16)));
}


/**********************************************************************
*                    SysTick_Handler( )
***********************************************************************
* Description : HANDLER FINCTION
* Arguments   : none
* Return Type : none
* Notes :  STK_LOAD value is 0 then Handler will execute
***********************************************************************/

/**
 * @brief SysTick interrupt handler
 * 
 * Increments the global counter variable 'count1' each time the SysTick interrupt occurs.
 * This function is called at every SysTick interrupt, typically every 1 millisecond
 * if configured correctly. It is used for time-keeping or delay generation in the
 * system.
 * 
 * @note Ensure that SysTick is properly initialized and enabled for this handler
 * to be executed.
 */

void SysTick_Handler(void)
{
    count1++;
}




