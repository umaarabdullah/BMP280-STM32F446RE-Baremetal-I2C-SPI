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
void TIMER6_PSC_9000(void){		// set prescaler to (9000 - 1) to divide by 9000.

	TIM6->PSC = (9000 - 1);
}

void Timer7_PSC_9000(void){		// // set prescaler to (9000 - 1) to divide by 9000. So APB1 bus clock becomes 10khz. Each Count is at 1/10ms
	
	TIM7->PSC = (9000 - 1);
}


// Set the ARR TIMx_ARR
void TIMER6_ARR_MAX(void){		// set max value for TIM6_ARR
	
	TIM6->ARR = 0xffff;
}
void TIMER6_ARR_98(void){		// set 98 For TIM6 ARR
	
	TIM6->ARR = 98;
}

void TIMER7_ARR_10000(void){		// 10000 so each update interrupt will be generated after 1 second
	
	TIM7->ARR = 10000;
}

void TIMER7_ARR_5000(void){			// 5000 so each update interrupt will be generated after 0.5 second
	
	TIM7->ARR = 5000;
}
	

// Enable the Timer and wait for update flag to ready TIMx_CR1
void Enable_TIMER6(void){		// Enable TIMER 6 

	TIM6->CR1 |= TIM_CR1_CEN;
	
	// Wait for the update flag UIF to set in TIM6_SR
	while(!(TIM6->SR & (1<<0)));
}

void Enable_TIMER7(void){		// Enable TIMER 7
	
	TIM7->CR1 |= TIM_CR1_CEN;
	
	// Wait for the update flag UIF to set in TIM7_SR
	while(!(TIM7->SR & (1<<0)));
}

// Enable TIMx Update Interrupt
void Timer7_Interrupt_Enable(void){
	
	// Set bit 0 of TIM7_DIER Register
	TIM7->DIER |= TIM_DIER_UIE;
}

// Set precise Delay
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

