#include "GPIO_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Set the prescaler TIMx_PSC 
void TIMER6_PSC_90(void);			// set prescaler to (90 - 1) to divide by 90. So the APB1 bus Clock of 90MHZ gets divided by 90 and becomes 1MHZ
void TIMER6_PSC_9000(void);		// set prescaler to (9000 - 1) to divide by 9000. 
void Timer7_PSC_9000(void);				// Each Count is at 1/10ms

// Set the ARR TIMx_ARR
void TIMER6_ARR_MAX(void);	// set max value for TIM6_ARR
void TIMER6_ARR_98(void);		// set 98 For TIM6 ARR
void TIMER7_ARR_10000(void);		// 10000 so each update interrupt will be generated after 1 second
void TIMER7_ARR_5000(void);			// 5000 so each update interrupt will be generated after 0.5 second
	

// Enable the Timer and wait for update flag to ready TIMx_CR1
void Enable_TIMER6(void);
void Enable_TIMER7(void);

// Enable TIMx Update Interrupt
void Timer7_Interrupt_Enable(void);

// Set precise Delay
void TIMER6_Delay_us(uint16_t timeMicroSec);		// x micro seconds delay
void TIMER6_Delay_ms(uint16_t timeMilliSec);		// x milli second delay
void TIMER6_Delay_s(uint16_t timeSec);					// x second delay
