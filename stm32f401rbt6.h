/*

Filename:stm32f401rbt6.h
Description:Contains board specification details(Base address and physical address of device)

PHYSICAL ADDRESS OF REGISTER = BASE ADDRESS OF DEVICE + OFFSET ADDRESS OF REGISTER
*/

/***************************************BASE ADDRESS ZONE**************************************/
//BASE ADDRESS OF PERIPHERAL BUS
#define AHB1_BASEADDR           0X40020000
#define AHB2_BASEADDR           0X50000000

#define APB1_BASEADDR           0X40000000
#define APB2_BASEADDR           0X40010000

//BASE ADDRESSE OF RCC
#define RCC_BASEADDR            0X40023800
#define RCC_CR                  *(int *)(RCC_BASEADDR + 0X00)
#define RCC_CFGR                *(int *)(RCC_BASEADDR + 0X04)
#define RCC_CIR                 *(int *)(RCC_BASEADDR + 0X08)
#define RCC_AHB1RSTR            *(int *)(RCC_BASEADDR + 0X0C)
#define RCC_AHB2RSTR            *(int *)(RCC_BASEADDR + 0X10)
#define RCC_APB1RSTR            *(int *)(RCC_BASEADDR + 0X14)
#define RCC_APB2RSTR            *(int *)(RCC_BASEADDR + 0X18)	
#define RCC_AHB1ENR             *(int *)(RCC_BASEADDR + 0X30)
#define RCC_AHB2ENR             *(int *)(RCC_BASEADDR + 0X34)
#define RCC_APB1ENR             *(int *)(RCC_BASEADDR + 0X40)	
#define RCC_APB2ENR             *(int *)(RCC_BASEADDR + 0X44)		
#define RCC_BDCR                *(int *)(RCC_BASEADDR + 0X48)
#define RCC_CSR                 *(int *)(RCC_BASEADDR + 0X4C)

//GPIO BASE ADDRESSES
#define GPIOA_BASEADDR          AHB1_BASEADDR
#define GPIOB_BASEADDR          0X40020400
#define GPIOC_BASEADDR          0X40020800

//ADC BASE ADDRESS
#define ADC1_BASEADDR           0x40012000

//USART BASE ADDRESS
#define USART1_BASEADDR         0x40011000
#define USART2_BASEADDR         0x40004400
#define USART6_BASEADDR         0x40011400

//I2C BASE ADDRESS
#define I2C1_BASEADDR           0x40005400
#define I2C2_BASEADDR           0x40005800
#define I2C3_BASEADDR           0x40005C00

//SPI BASE ADDRESS
#define SPI1_BASEADDR           0x40013000
#define SPI2_BASEADDR           0x40003800
#define SPI3_BASEADDR           0x40003C00

/*****************************************PHYSICAL ADDRESS******************************************/

//PHYSICAL ADDRESS OF RCC AHB1ENR,APB1ENR,APB2ENR
#define RCC_AHB1ENR             *(int *)(RCC_BASEADDR + 0X30)   //OFFSET IS 0X30
#define RCC_APB1ENR             *(int *)(RCC_BASEADDR + 0X40)   //OFFSET IS 0X40
#define RCC_APB2ENR             *(int *)(RCC_BASEADDR + 0X44)   //OFFSET IS 0X44

//PHYSICAL ADDTRESS OF GPOIA MODER,ODR,IDR,PUPDR
#define GPIOA_MODER              *(int *)(GPIOA_BASEADDR)
#define GPIOA_OTYPER             *(int *)(GPIOA_BASEADDR + 0X04)

#define GPIOA_ODR                *(int *)(GPIOA_BASEADDR + 0X14)
#define GPIOA_IDR                *(int *)(GPIOA_BASEADDR + 0X10)
#define GPIOA_PUPDR              *(int *)(GPIOA_BASEADDR + 0X0C)
#define GPIOA_AFRL               *(int *)(GPIOA_BASEADDR + 0X20)
	


//PHYSICAL ADDTRESS OF GPOIB MODER,ODR,IDR,PUPDR
#define GPIOB_MODER              *(int *)(GPIOB_BASEADDR)
#define GPIOB_ODR                *(int *)(GPIOB_BASEADDR + 0X14)
#define GPIOB_OTYPER             *(int *)(GPIOB_BASEADDR + 0X04)

#define GPIOB_IDR                *(int *)(GPIOB_BASEADDR + 0X10)
#define GPIOB_PUPDR              *(int *)(GPIOB_BASEADDR + 0X0C)
#define GPIOB_AFRL               *(int *)(GPIOB_BASEADDR + 0X20)
#define GPIOB_AFRH               *(int *)(GPIOB_BASEADDR + 0X24)


//PHYSICAL ADDTRESS OF GPOIC MODER,ODR,IDR,PUPDR
#define GPIOC_MODER              *(int *)(GPIOC_BASEADDR)
#define GPIOC_OTYPER             *(int *)(GPIOC_BASEADDR + 0X04)

#define GPIOC_ODR                *(int *)(GPIOC_BASEADDR + 0X14)
#define GPIOC_IDR                *(int *)(GPIOC_BASEADDR + 0X10)
#define GPIOC_PUPDR              *(int *)(GPIOC_BASEADDR + 0X0C)
#define GPIOC_AFRL               *(int *)(GPIOC_BASEADDR + 0X20)
	
//BASE ANDPHYSICAL ADDRESS OF SYSCNG
#define SYSCFG_BASEADDR         0x40013800
#define SYSCFG_EXTICR1   *(int *)(SYSCFG_BASEADDR + 0X08)
#define SYSCFG_EXTICR2   *(int *)(SYSCFG_BASEADDR + 0X0C)
#define SYSCFG_EXTICR3   *(int *)(SYSCFG_BASEADDR + 0X10)
#define SYSCFG_EXTICR4   *(int *)(SYSCFG_BASEADDR + 0X14)

//BASE AND PHYSICAL ADDRESS OF EXTI
#define EXTI_BASEADDR     0x40013C00
#define EXTI_IMR          *(int *)(EXTI_BASEADDR)
#define EXTI_EMR          *(int *)(EXTI_BASEADDR + 0X04)
#define EXTI_FTSR         *(int *)(EXTI_BASEADDR + 0X0C)
	#define EXTI_RTSR         *(int *)(EXTI_BASEADDR + 0X08)
#define EXTI_PR          *(int *)(EXTI_BASEADDR + 0X14)

//system timer(stk) Base and physical address
#define STK_CTRL       *(int *)0xE000E010 
#define STK_LOAD       *(int *)0xE000E014
#define STK_VAL       *(int *)0xE000E018
#define STK_CALIB       *(int *)0xE000E01C
#define NVIC_ISER0      *(int *)(0xe000e000+0x100)
#define NVIC_ISER1      *(int *)(0xe000e000+0x104)
	#define NVIC_ISER2      *(int *)(0xe000e000+0x108)
//ADC BASE ADDRES AND PHYSICAL ADDRESS
#define  ACD1_BASEADDR     0x40012000
#define  ADC_SR         *(int *)(ADC1_BASEADDR)
#define  ADC_CR1         *(int *)(ADC1_BASEADDR + 0X04)
#define  ADC_CR2         *(int *)(ADC1_BASEADDR + 0X08)
#define  ADC_SMPR1         *(int *)(ADC1_BASEADDR + 0X0C)
#define  ADC_SMPR2         *(int *)(ADC1_BASEADDR + 0X10)
#define  ADC_JOFR1         *(int *)(ADC1_BASEADDR + 0X14)
#define  ADC_JOFR2        *(int *)(ADC1_BASEADDR + 0X18)
#define  ADC_JOFR3         *(int *)(ADC1_BASEADDR + 0X1C)
#define  ADC_JOFR4        *(int *)(ADC1_BASEADDR + 0X20)
#define  ADC_HTR        *(int *)(ADC1_BASEADDR + 0X24)
#define  ADC_LTR        *(int *)(ADC1_BASEADDR + 0X28)
#define  ADC_SQR1        *(int *)(ADC1_BASEADDR + 0X2C)
#define  ADC_SQR2        *(int *)(ADC1_BASEADDR + 0X30)
#define  ADC_SQR3        *(int *)(ADC1_BASEADDR + 0X34)
#define  ADC_JSQR        *(int *)(ADC1_BASEADDR + 0X38)
#define  ADC_JDR1        *(int *)(ADC1_BASEADDR + 0X3C)
#define  ADC_JDR2        *(int *)(ADC1_BASEADDR + 0X40)
#define  ADC_JDR3        *(int *)(ADC1_BASEADDR + 0X44)
#define  ADC_JDR4        *(int *)(ADC1_BASEADDR + 0X48)
#define  ADC_DR        *(int *)(ADC1_BASEADDR + 0X4C)

//USART BASE ADDRESS AND PHYSICAL ADDRESS

#define  USART1_SR          *(int *)(USART1_BASEADDR + 0x00)
#define  USART2_SR          *(int *)(USART2_BASEADDR + 0x00)
#define  USART6_SR          *(int *)(USART6_BASEADDR + 0x00)
#define  USART1_DR          *(int *)(USART1_BASEADDR + 0x04)
#define  USART2_DR          *(int *)(USART2_BASEADDR + 0x04)
#define  USART6_DR          *(int *)(USART6_BASEADDR + 0x04)
#define  USART1_BRR         *(int *)(USART1_BASEADDR + 0x08)
#define  USART2_BRR         *(int *)(USART2_BASEADDR + 0x08)
#define  USART6_BRR         *(int *)(USART6_BASEADDR + 0x08)
#define  USART1_CR1         *(int *)(USART1_BASEADDR + 0x0C)
#define  USART2_CR1         *(int *)(USART2_BASEADDR + 0x0C)
#define  USART6_CR1         *(int *)(USART6_BASEADDR + 0x0C)
#define  USART1_CR2         *(int *)(USART1_BASEADDR + 0x10)
#define  USART2_CR2         *(int *)(USART2_BASEADDR + 0x10)
#define  USART6_CR2         *(int *)(USART6_BASEADDR + 0x10)
#define  USART1_CR3         *(int *)(USART1_BASEADDR + 0x14)
#define  USART2_CR3         *(int *)(USART2_BASEADDR + 0x14)
#define  USART6_CR3         *(int *)(USART6_BASEADDR + 0x14)
#define  USART1_GPTR        *(int *)(USART1_BASEADDR + 0x18)
#define  USART2_GPTR        *(int *)(USART2_BASEADDR + 0x18)
#define  USART6_GPTR        *(int *)(USART6_BASEADDR + 0x18)

//spi base address and physical address
#define SPI2_BASEADDR        0x40003800 
#define SPI2_CR1          *(int *)(SPI2_BASEADDR + 0X00)
#define SPI2_CR2          *(int *)(SPI2_BASEADDR + 0X04)
#define SPI2_SR           *(int *)(SPI2_BASEADDR + 0X08)
#define SPI2_DR           *(int *)(SPI2_BASEADDR + 0X0C)


//I2C BASE ADDRESS AND OFFSET ADDRESS
#define I2C1_BASEADDR       0x40005400
#define I2C1_CR1            *(int *)(I2C1_BASEADDR + 0x00)
#define I2C1_CR2            *(int *)(I2C1_BASEADDR + 0x04)
#define I2C1_OAR1           *(int *)(I2C1_BASEADDR + 0x08)
#define I2C1_OAR2           *(int *)(I2C1_BASEADDR + 0x0C)
#define I2C1_DR             *(int *)(I2C1_BASEADDR + 0x10)
#define I2C1_SR1            *(int *)(I2C1_BASEADDR + 0x14)
#define I2C1_SR2            *(int *)(I2C1_BASEADDR + 0x18)
#define I2C1_CCR            *(int *)(I2C1_BASEADDR + 0x1C)
#define I2C1_TRISE          *(int *)(I2C1_BASEADDR + 0x20)
#define I2C1_FLTR           *(int *)(I2C1_BASEADDR + 0x24)

#define I2C2_BASEADDR       0x40005800
#define I2C2_CR1            *(int *)(I2C2_BASEADDR + 0x00)
#define I2C2_CR2            *(int *)(I2C2_BASEADDR + 0x04)
#define I2C2_OAR1           *(int *)(I2C2_BASEADDR + 0x08)
#define I2C2_OAR2           *(int *)(I2C2_BASEADDR + 0x0C)
#define I2C2_DR             *(int *)(I2C2_BASEADDR + 0x10)
#define I2C2_SR1            *(int *)(I2C2_BASEADDR + 0x14)
#define I2C2_SR2            *(int *)(I2C2_BASEADDR + 0x18)
#define I2C2_CCR            *(int *)(I2C2_BASEADDR + 0x1C)
#define I2C2_TRISE          *(int *)(I2C2_BASEADDR + 0x20)
#define I2C2_FLTR           *(int *)(I2C2_BASEADDR + 0x24)

#define RTC_BASEADDR        0x40002800
#define RTC_TR              *(int *)(RTC_BASEADDR + 0X00)
#define RTC_DR              *(int *)(RTC_BASEADDR + 0X04)
#define RTC_CR              *(int *)(RTC_BASEADDR + 0X08)
#define RTC_ISR             *(int *)(RTC_BASEADDR + 0X0C)
#define RTC_PRER            *(int *)(RTC_BASEADDR + 0X10)
#define RTC_ALRMAR          *(int *)(RTC_BASEADDR + 0X14)
#define RTC_ALRMBR          *(int *)(RTC_BASEADDR + 0X18)
#define RTC_WPR             *(int *)(RTC_BASEADDR + 0X1C)
#define RTC_SSR             *(int *)(RTC_BASEADDR + 0X20)
#define RTC_SHIFTR          *(int *)(RTC_BASEADDR + 0X24)
#define RTC_TSTR            *(int *)(RTC_BASEADDR + 0X28)
#define RTC_TSDR            *(int *)(RTC_BASEADDR + 0X2C)
#define RTC_TSSSR           *(int *)(RTC_BASEADDR + 0X30)
#define RTC_CALIBR          *(int *)(RTC_BASEADDR + 0X34)
#define RTC_ALRMASSR        *(int *)(RTC_BASEADDR + 0X38)
#define RTC_ALRMBSSR        *(int *)(RTC_BASEADDR + 0X3C)	

	






	









	

	



	

