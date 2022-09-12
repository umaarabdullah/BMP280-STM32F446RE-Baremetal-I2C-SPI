#include "GPIO_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Set the prescaler TIMx_PSC 
void TIMER6_PSC_90(void);		// set prescaler to (90 - 1) to divide by 90. So the APB1 bus Clock of 90MHZ gets divided by 90 and becomes 1MHZ
void Timer6_PSC_9000(void);	// set prescaler to (9000 - 1) to divide by 9000. So APB1 bus clock becomes 10khz.
void TIMER7_PSC_90(void);		// set prescaler to (90 - 1) to divide by 90. So the APB1 bus Clock of 90MHZ gets divided by 90 and becomes 1MHZ

// Set the ARR TIMx_ARR
void TIMER6_ARR_MAX(void);		// set max value for TIM6_ARR
void TIMER6_ARR_5000(void);		// Set 5000 for TIM6_ARR
void TIMER6_ARR_10000(void);	// set 10000 for TIM6_ARR
void TIMER6_ARR_50000(void);	// set 50000 for TIM6_ARR
void TIMER7_ARR_MAX(void);		// set max value for TIM6_ARR

// Tim6 Update interrupt Enable/Disable
void Timer6_Interrupt_Enable(void);
void Timer6_Interrupt_Disable(void);

// Enable the Timer and wait for update flag to ready TIMx_CR1
void Enable_TIMER6(void);
void Enable_TIMER7(void);

// Set precise Delay
// TIM6
void TIMER6_Delay_us(uint16_t timeMicroSec);		// x micro seconds delay
void TIMER6_Delay_ms(uint16_t timeMilliSec);		// x milli second delay
void TIMER6_Delay_s(uint16_t timeSec);					// x second delay
// TIM7
void TIMER7_Delay_us(uint16_t timeMicroSec);		// x micro seconds delay
void TIMER7_Delay_ms(uint16_t timeMilliSec);		// x milli second delay
void TIMER7_Delay_s(uint16_t timeSec);					// x second delay
