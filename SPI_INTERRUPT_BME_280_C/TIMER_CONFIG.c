#include "TIMER_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Set the prescaler TIMx_PSC 
void TIMER6_PSC_90(void){		// set prescaler to (90 - 1) to divide by 90. So APB1 bus Clock of 90MHZ gets divided by 90 and becomes 1MHZ
	
	TIM6->PSC = (90 - 1);
}
void Timer6_PSC_9000(void){	// set prescaler to (9000 - 1) to divide by 9000. So APB1 bus clock becomes 10khz.
	
	TIM6->PSC = (9000 - 1);
}
void TIMER7_PSC_90(void){		// set prescaler to (90 - 1) to divide by 90. So the APB1 bus Clock of 90MHZ gets divided by 90 and becomes 1MHZ
	
	TIM7->PSC = (90 - 1);
}

// Set the ARR TIMx_ARR
void TIMER6_ARR_MAX(void){		// set max value for TIM6_ARR
	
	TIM6->ARR = 0xffff;
}
void TIMER6_ARR_5000(void){		// Set 5000 for TIM6_ARR
	
	TIM6->ARR = 5000;
}
void TIMER6_ARR_10000(void){	// set 10000 for TIM6_ARR
	
	TIM6->ARR = 10000;
}
void TIMER6_ARR_50000(void){	// set 50000 for TIM6_ARR

	TIM6->ARR = 50000;
}
void TIMER7_ARR_MAX(void){		// set max value for TIM7_ARR
	
	TIM7->ARR = 0xffff;
}

// Tim6 Update interrupt Enable/Disable
void Timer6_Interrupt_Enable(void){
	
	// Set bit 0 of TIM6_DIER Register
	TIM6->DIER |= TIM_DIER_UIE;
}
void Timer6_Interrupt_Disable(void){

	// Reset bit 0 of TIM6_DIER Register
	TIM6->DIER &= ~(TIM_DIER_UIE);
}

// Enable the Timer and wait for update flag to ready TIMx_CR1
void Enable_TIMER6(void){		// Enable TIMER 6 

	TIM6->CR1 |= TIM_CR1_CEN;
	
	// Wait for the update flag UIF to set in TIM6_SR
	//while(!(TIM6->SR & (1<<0)));
}
// Enable the Timer and wait for update flag to ready TIMx_CR1
void Enable_TIMER7(void){		// Enable TIMER 7

	TIM7->CR1 |= TIM_CR1_CEN;
	
	// Wait for the update flag UIF to set in TIM7_SR
	while(!(TIM7->SR & (1<<0)));
}

// Set precise Delay
// TIM6
void TIMER6_Delay_us(uint16_t timeMicroSec){		// x micro seconds delay
	
	// Reset the counter
	TIM6->CNT = 0;
	
	// wait for the counter to reach the given timer delay value
	// Each count of the timer takes exactly 1us as the timer clock is 1MHZ
	while(TIM6->CNT < timeMicroSec);
}
void TIMER6_Delay_ms(uint16_t timeMilliSec){		// x milli second delay
	
	for(int i=0; i<timeMilliSec; i++)
		TIMER6_Delay_us(1000);											// as 1ms = 1000us
}
void TIMER6_Delay_s(uint16_t timeSec){					// x second delay
	
	for(int i=0; i<timeSec; i++)
		TIMER6_Delay_ms(1000);											// as 1s = 1000ms
}
// TIM7
void TIMER7_Delay_us(uint16_t timeMicroSec){		// x micro seconds delay
	
	// Reset the counter
	TIM7->CNT = 0;
	
	// wait for the counter to reach the given timer delay value
	// Each count of the timer takes exactly 1us as the timer clock is 1MHZ
	while(TIM7->CNT < timeMicroSec);
}
void TIMER7_Delay_ms(uint16_t timeMilliSec){		// x milli second delay
	
	for(int i=0; i<timeMilliSec; i++)
		TIMER7_Delay_us(1000);											// as 1ms = 1000us
}
void TIMER7_Delay_s(uint16_t timeSec){					// x second delay
	
	for(int i=0; i<timeSec; i++)
		TIMER7_Delay_ms(1000);											// as 1s = 1000ms
}

