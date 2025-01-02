#include "stm32f401rbt6.h"

/**
 * @brief  Configure the magnetic sensor pins
 *
 * This function is used to configure the GPIO pins for the magnetic sensor.
 * It sets the GPIOA pin 0 and GPIOC pin 0 as input with pull-up.
 * It also sets the GPIOB pin 13 and 14 as output for the red and green LEDs.
 *
 * @param  None
 * @retval None
 */
void SENSOR_config()
{
	GPIOA_PUPDR&=0XFFFFFFF0;//CLEAR 0,1 TH BITS(PC0)
	GPIOA_PUPDR|=0X00000001;//LOAD 01 TO THE 1-0 BITS FOR ENABLE PULLUP FOR PC0
	GPIOC_PUPDR&=0XF0FFFFFF;//CLEAR 0,1 TH BITS(PC0)
	GPIOC_PUPDR|=0X04000000;//LOAD 01 TO THE 1-0 BITS FOR ENABLE PULLUP FOR PC0
	GPIOB_MODER|=0X01<<26;//RED LED   
  GPIOB_MODER|=0X01<<28;//green LED    	
}
/**
 * @brief  Initialize sensor clocks
 *
 * This function enables the clocks for AHB1 and APB2 buses
 * for the sensor peripheral.
 *
 * @param  None
 * @retval None
 */

void SENSOR_intit()
{
	// Enable clocks for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE
	RCC_AHB1ENR |= 0X07;
	// Enable clock for SYSCFG
	RCC_APB2ENR |= 0X01 << 14;
}
/**
 * @brief  Configure interrupts for magnetic sensor
 *
 * This function is used to configure interrupts for the magnetic sensor.
 * It sets the SYSCFG_EXTICR4 register to select PA13 as the source of EXTI13
 * It also sets the EXTI_IMR register to unmask the interrupt and the
 * EXTI_FTSR register to configure the interrupt as falling edge triggered.
 * Finally, it enables the EXTI13 interrupt in NVIC.
 *
 * @param  None
 * @retval None
 */
void SENSEOR_INTERRRUPT_config()
{
	
	// Select PA13 as the source of EXTI13
	SYSCFG_EXTICR4|=0X02<<4;
	// Clear SYSCFG_EXTICR1 register to select PA13 as source
	SYSCFG_EXTICR1|=0X00;
	// Unmask EXTI13 interrupt
	//SYSCFG_EXTICR1|=0X10;
	EXTI_IMR |=0X01<<13;
	// Configure interrupt as falling edge triggered
	EXTI_FTSR|=0x01<<13;
	// Unmask EXTI0 interrupt
	
	
	EXTI_IMR |=0X01;
	// Configure interrupt as rising edge triggered
	EXTI_RTSR|=0x01;
	// Enable EXTI0 interrupt in NVIC
	NVIC_ISER0 |= 0x01<<6;
	NVIC_ISER1 |= (0x01 << 8); // Enable EXTI13 interrupt in NVIC
	//NVIC_ISER0|=0x03<<6;
}



	