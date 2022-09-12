#include "stm32f446xx.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

#define PLL_M 4
#define PLL_N 180
#define PLL_P 0

// Configure System Clock Using External Crystal as HSE and PLL as clock source
void SysClockConfig(void);

// Enable CLocks for GPIOx Ports
void GPIOA_CLOCK_ENABLE(void);		// Enable GPIOA Clock
void GPIOB_CLOCK_ENABLE(void);		// Enable GPIOB Clock
void GPIOC_CLOCK_ENABLE(void);		// Enable GPIOC Clock
void GPIOD_CLOCK_ENABLE(void);		// Enable GPIOD Clock
void GPIOE_CLOCK_ENABLE(void);		// Enable GPIOE Clock
void GPIOF_CLOCK_ENABLE(void);		// Enable GPIOF Clock
void GPIOG_CLOCK_ENABLE(void);		// Enable GPIOG Clock
void GPIOH_CLOCK_ENABLE(void);		// Enable GPIOH Clock

// Enable Clocks for USARTx
void USART2_CLOCK_ENABLE(void);		// Enable USART2 Clock

// Enable Timer Clock
void TIM6_CLOCK_ENABLE(void);			// Enable Basic Timer 6 Clock
void TIM7_CLOCK_ENABLE(void);			// Enable Basic Timer 7 Clock

// Enable I2C1 Clock
void I2C1_CLOCK_ENABLE(void);			// Enable I2C1 Clock
