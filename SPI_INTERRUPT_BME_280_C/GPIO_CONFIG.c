#include "GPIO_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/


// GPIOx MODER REGISTER CONFIGURATION
// ALTERNATE FUNCTION MODES
void GPIOA_PA2_AF_Mode(){
	GPIOA->MODER |= GPIO_MODER_MODE2_1;		// set 10 at MODER2 bit pos to select Alternate function mode for pin PA2 in the GPIOA_MODER
}
void GPIOA_PA3_AF_Mode(){
	GPIOA->MODER |= GPIO_MODER_MODE3_1;		// set 7 at MODER3 bit pos to select Alternate function mode for pin PA3 in the GPIOA_MODER
}
// GPIOB
void GPIOB_PB6_AF_Mode(void){
	GPIOB->MODER |= GPIO_MODER_MODE6_1;		// set 13 at MODER6 bit pos to select Alternate function mode for pin PB6
}
void GPIOB_PB7_AF_Mode(void){
	GPIOB->MODER |= GPIO_MODER_MODE7_1;		// set 15 at MODER7 bit pos to select Alternate function mode for pin PB7
}
void GPIOB_PB9_AF_Mode(void){				// set 10 at MODER9 bit pos to select Alternate function mode for pin PB9
	GPIOB->MODER |= GPIO_MODER_MODE9_1;
}
// GPIOC
void GPIOC_PC1_AF_Mode(void){				// set 10 at MODER1 bit pos to select Alternate function mode for pin PC1
	GPIOC->MODER |= GPIO_MODER_MODE1_1;
}
void GPIOC_PC2_AF_Mode(void){				// set 10 at MODER2 bit pos to select Alternate function mode for pin PC2
	GPIOC->MODER |= GPIO_MODER_MODE2_1;
}
void GPIOC_PC7_AF_Mode(void){				// set 10 at MODER7 bit pos to select Alternate function mode for pin PC17
	GPIOC->MODER |= GPIO_MODER_MODE7_1;
}

// Select Mode as OUTPUT MODE in the GPIOx_MODER
// GPIOA
void GPIOA_PA5_OUTPUT_MODE(void){		// set MODER5 to select OUTPUT MODE
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
}
void GPIOA_PA6_OUTPUT_MODE(void){		// set MODER6 to select OUTPUT MODE
	GPIOA->MODER |= GPIO_MODER_MODER6_0;
}
void GPIOA_PA7_OUTPUT_MODE(void){		// set MODER7 to select OUTPUT MODE
	GPIOA->MODER |= GPIO_MODER_MODER7_0;
}
void GPIOA_PA8_OUTPUT_MODE(void){		// set MODER8 to 01 select OUTPUT MODE
	GPIOA->MODER |= GPIO_MODER_MODER8_0;
}
void GPIOA_PA9_OUTPUT_MODE(void){		// set MODER9 to select OUTPUT MODE
	GPIOA->MODER |= GPIO_MODER_MODER9_0;
}
void GPIOA_PA10_OUTPUT_MODE(void){	// set MODER10 to select OUTPUT MODE
	GPIOA->MODER |= GPIO_MODER_MODER10_0;
}
// GPIOB
void GPIOB_PB3_OUTPUT_MODE(void){		// set MODER3 to select OUTPUT MODE
	GPIOB->MODER |= GPIO_MODER_MODE3_0;		// 1 in bit 6
	GPIOB->MODER &= (uint32_t)~(1<<7);							// 0 in bit 7
}
void GPIOB_PB4_OUTPUT_MODE(void){		// set MODER4 to select OUTPUT MODE
	GPIOB->MODER |= GPIO_MODER_MODE4_0;		// 1 in bit 8
	GPIOB->MODER &= (uint32_t)~(1<<9);							// 0 in bit 9
}
void GPIOB_PB5_OUTPUT_MODE(void){		// set MODER5 to select OUTPUT MODE
	GPIOB->MODER |= GPIO_MODER_MODE5_0;		// 1 in bit 10
	GPIOB->MODER &= (uint32_t)~(1<<11);							// 0 in bit 11
}
void GPIOB_PB6_OUTPUT_MODE(void){		// set MODER6 to select OUTPUT MODE
	GPIOB->MODER |= GPIO_MODER_MODE6_0;
}
void GPIOB_PB8_OUTPUT_MODE(void){		// set MODER8 to select OUTPUT MODE
	GPIOB->MODER |= GPIO_MODER_MODE8_0;
}
void GPIOB_PB9_OUTPUT_MODE(void){	// set MODER9 to select OUTPUT MODE
	GPIOB->MODER |= GPIO_MODER_MODE9_0;
}
void GPIOB_PB10_OUTPUT_MODE(void){	// set MODER10 to select OUTPUT MODE
	GPIOB->MODER |= GPIO_MODER_MODE10_0;
}

// GPIOC
void GPIOC_PC0_OUTPUT_MODE(void){		// set MODER0 to 01 select OUTPUT MODE
	GPIOC->MODER |= GPIO_MODER_MODE0_0;
}
void GPIOC_PC7_OUTPUT_MODE(void){		// set MODER7 to select OUTPUT MODE
	GPIOC->MODER |= GPIO_MODER_MODE7_0;
}


// Select Alternate function in the ALTERNATE FUNCTION LOW/HIGH REGISTER GPIOx_AFRL/GPIOx_AFRH
// GPIOA
void GPIOA_PA2_AF7_USART2(){
	GPIOA->AFR[0] |= (7 << 8);		// Set 7 = 0111 at AFRL2 bit positions to select AF7 AKA USART2 for pin PA2 in the AFRL Register
}
void GPIOA_PA3_AF7_USART2(){
	GPIOA->AFR[0] |= (7 << 12);		// Set 7 = 0111 at AFRL3 bit positions to select AF7 AKA USART2 for pin PA3 in the AFRL Register
}
// GPIOB
void GPIOB_PB6_AF4_I2C1(void){
	
	GPIOB->AFR[0] |= (1 << 26);				// Set bit 26 to 0100 (4) at AFRL6 bit positions to select AF4 AKA I2C1 for pin PB6 in the AFRL Register
}
void GPIOB_PB7_AF4_I2C1(void){
	GPIOB->AFR[0] |= (1 << 30);				// Set bit 30 = 0100 at AFRL7 bit positions to select AF4 AKA I2C1 for pin PB7 in the AFRL Register
}
void GPIOB_PB9_AF5_SPI2(void){			// Set 5 = 0101 at AFRH9 bit positions to select AF5 as SPI2_NSS for pin PB9 in the AFRH Register
	GPIOB->AFR[1] |= (5 << 4);
}
// GPIOC
void GPIOC_PC1_AF7_SPI2(void){			// Set 7 = 0111 at AFRL1 bit positions to select AF7 as SPI2_MOSI for pin PC1 in the AFRL Register
	GPIOC->AFR[0] |= (7 << 4);
}
void GPIOC_PC2_AF5_SPI2(void){			// Set 5 = 0101 at AFRL2 bit positions to select AF5 as SPI2_MISO for pin PC2 in the AFRL Register
	GPIOC->AFR[0] |= (5 << 8);
}
void GPIOC_PC7_AF5_SPI2(void){			// Set 5 = 0101 at AFRL7 bit positions to select AF5 as SPI2_SCK for pin PC7 in the AFRL Register
	GPIOC->AFR[0] |= (5 << 28);
}


// Select Output Speed in the OUTPUT SPEED REGISTER GPIOx_OSPEEDR 
// GPIOA
void GPIOA_PA2_Output_Speed_HIGH(){	
	GPIOA->OSPEEDR |= (3 << 4);		// set 11 at OSPEEDR2 bit pos to select High output speed for pin PA2
}
void GPIOA_PA3_Output_Speed_HIGH(){
	GPIOA->OSPEEDR |= (3 << 6);		// set 11 at OSPEEDR3 bit pos to select High output speed for pin PA3
}
// GPIOB
void GPIOB_PB6_Output_Speed_HIGH(void){
	GPIOB->OSPEEDR |= (3 << 12);		// set 11 at OSPEEDR6 bit pos to select High output speed for pin PB6
}
void GPIOB_PB7_Output_Speed_HIGH(void){
	GPIOB->OSPEEDR |= (3 << 14);		// set 11 at OSPEEDR7 bit pos to select High output speed for pin PB7
}
void GPIOB_PB9_Output_Speed_HIGH(void){		// set 11 at OSPEEDR9 bit pos to select High output speed for pin PB9
	GPIOB->OSPEEDR |= (3 << 18);
}
// GPIOC
void GPIOC_PC1_Output_Speed_HIGH(void){ 	// set 11 at OSPEEDR1 bit pos to select High output speed for pin PC1
	GPIOC->OSPEEDR |= (3 << 2);
}
void GPIOC_PC2_Output_Speed_HIGH(void){ 	// set 11 at OSPEEDR2 bit pos to select High output speed for pin PC2
	GPIOC->OSPEEDR |= (3 << 4);
}
void GPIOC_PC7_Output_Speed_HIGH(void){ 	// set 11 at OSPEEDR7 bit pos to select High output speed for pin PC7
	GPIOC->OSPEEDR |= (3 << 14);
}


// Select Pull-up/pull-down register
// GPIOA
void GPIOA_PA1_Pull_Down(void){			// set 10 at PUPDR1 bit postions to Select Pull-down for Pin PA1
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_1;
}
void GPIOA_PA2_Pull_Down(void){			// set 10 at PUPDR2 bit postions to Select Pull-down for Pin PA2
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR2_1;
}
void GPIOA_PA3_Pull_Down(void){			// set 10 at PUPDR3 bit postions to Select Pull-down for Pin PA3
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_1;
}
void GPIOA_PA4_Pull_Down(void){			// set 10 at PUPDR4 bit postions to Select Pull-down for Pin PA4
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR4_1;
}
void GPIOA_PA5_Pull_Down(void){			// set 10 at PUPDR5 bit postions to Select Pull-down for Pin PA5
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR5_1;
}
void GPIOA_PA6_Pull_Down(void){			// set 10 at PUPDR6 bit postions to Select Pull-down for Pin PA6
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR6_1;
}
void GPIOA_PA7_Pull_Down(void){			// set 10 at PUPDR7 bit postions to Select Pull-down for Pin PA7
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR7_1;
}
void GPIOA_PA8_Pull_Down(void){			// set 10 at PUPDR8 bit postions to Select Pull-down for Pin PA8
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR8_1;
}
void GPIOA_PA10_Pull_Down(void){		// set 10 at PUPDR10 bit postions to Select Pull-down for Pin PA10
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_1;
}
// GPIOB
void GPIOB_PB3_Pull_Down(void){			// set 10 at PUPDR3 bit postions to Select Pull-down for Pin PB3
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR3_1;
}
void GPIOB_PB4_Pull_Down(void){			// set 10 at PUPDR4 bit postions to Select Pull-down for Pin PB4
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR4_1;
}
void GPIOB_PB5_Pull_Down(void){			// set 10 at PUPDR5 bit postions to Select Pull-down for Pin PB5
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR5_1;
}
void GPIOB_PB9_Pull_Down(void){			// set 10 at PUPDR9 bit postions to Select Pull-down for Pin PB9
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR9_1;
}
void GPIOB_PB10_Pull_Down(void){		// set 10 at PUPDR10 bit postions to Select Pull-down for Pin PB10
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR10_1;
}
// GPIOC
void GPIOC_PC0_Pull_Down(void){			// set 10 at PUPDR0 bit postions to Select Pull-down for Pin PC0
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR0_1;
}
void GPIOC_PC1_Pull_Down(void){			// set 10 at PUPDR1 bit postions to Select Pull-down for Pin PC1
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR1_1;
}

