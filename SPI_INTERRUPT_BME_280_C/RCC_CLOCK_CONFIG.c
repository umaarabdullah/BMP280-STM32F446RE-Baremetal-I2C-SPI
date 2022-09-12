#include "RCC_CLOCK_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// configure HSE (High Speed External Clock)
void SysClockConfig(void){

		// Enable HSE (High Speed External Clock) and wait for HSE to become ready
		RCC->CR |= RCC_CR_HSEON;		// writing a 1 in bit 16 of the control register
		
		// wait until there is a 1 in the bit 17 of the Control register
		while(!(RCC->CR & RCC_CR_HSERDY));
		
		// Set the power enable clock and volatge regulator
		// the power management system is connected to the APB1 bus 
		// so the APB1 bus register's bit 28 PWREN: Power interface clock enable is set to 1
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		// Voltage regular has to set to scale 1 to achieve 180MHZ in the clock
		// 15th and 16th bit of the PWR power control register (PWR_CR) corresponds to voltage regular settings
		PWR->CR |= PWR_CR_VOS;		// writing 11 in bit 14 and 15 of the power control register
		
		// Configure the FLASH PREFETCH and the LATENCY Related Settings
		// bit 9 is set to 1 to enable instruction cache 
		// bit 10 is set to 1 to enable data cache
		// Bit 8 is set to 1 to enable Prefetch 
		// Set FLash Latency to 5 WS (Wait states)
		FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
		
		// Configure the Prescalers for HCLK, PCLK1, PCLK2
		// AHB prescaler bits 4 to 7
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;		// divide by nothing
		// APB1 prescaler bits 12:10
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;		// HCLK divided by 4
		// APB2 prescaler bits 15:13
		RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;		// HCLK divided by 2
		
		// Configugure the main PLL
		// PLLM, PLLN, PLLP
		// pllm starts from bit 0, plln starts from bit 6, pllp starts from bit 16
		// PLLM is 4 as dividing by 4, PLLN is 180 as multiplying by 180, PLLP is 0 as we are dividing by 2
		RCC->PLLCFGR = (PLL_M << 0) | (PLL_N << 6) | (PLL_P << 16) | RCC_PLLCFGR_PLLSRC_HSE;
		
		// Enable PLL and wait for it to become ready
		RCC->CR |= RCC_CR_PLLON;
		
		// wait until the bit 25 PLLRDY is 1
		while(!(RCC->CR & RCC_CR_PLLRDY));
		
		// Select clock source and wait for it to be set
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		// wait until the status bit updates to 1 in bit 3 and 0 in bit 2
		while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
		
}


// All GPIO Ports are connected to the AHB1 Bus
// Give Clocks to the GPIO PORTS
void GPIOA_CLOCK_ENABLE(){
	
	// set GPIOAEN in RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}
void GPIOB_CLOCK_ENABLE(){
	
	// set GPIOBEN in RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
}
void GPIOC_CLOCK_ENABLE(){
	
	// set GPIOCEN in RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
}
void GPIOD_CLOCK_ENABLE(){
	
	// set GPIODEN in RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
}
void GPIOE_CLOCK_ENABLE(){
	
	// set GPIOEEN in RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
}
void GPIOF_CLOCK_ENABLE(){
	
	// set GPIOFEN in RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
}
void GPIOG_CLOCK_ENABLE(){
	
	// set GPIOGEN in RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
}
void GPIOH_CLOCK_ENABLE(){
	
	// set GPIOHEN in RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
}


// Enable USART2 Clock in the RCC APB1 peripheral clock enable register 
void USART2_CLOCK_ENABLE(void){
	
	// set bit 17 USART2EN in RCC_APB1ENR
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}


// Enable Timer Clock in the RCC APB1 peripheral clock enable register 
void TIM6_CLOCK_ENABLE(void){			// Enable Basic Timer 6 Clock
	
	// Set bit 4 TIM6EN in RCC_APB1ENR
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
}
void TIM7_CLOCK_ENABLE(void){			// Enable Basic Timer 7 Clock
	
	// Set bit 5 TIM7EN in RCC_APB1ENR
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
}


// Enable I2C1 Clock in the RCC APB1 Peripheral Clock enable register
void I2C1_CLOCK_ENABLE(void){
	
	// Set bit 21 I2C1EN in RCC_APB1ENR
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
}

// Enable SPI2 Clock in the RCC_APB1
void SPI2_CLOCK_ENABLE(void){
	
	// Set bit 14 SPI2EN in the RCC_APB1ENR
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
}
