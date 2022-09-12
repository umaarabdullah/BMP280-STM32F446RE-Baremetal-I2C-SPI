#include "RCC_CLOCK_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Select Mode As Alternate function in the MODER REGISTER GPIOx_MODER
// GPIOA
void GPIOA_PA2_AF_Mode(void);				// set 10 at MODER2 bits pos to select Alternate function mode for pin PA2
void GPIOA_PA3_AF_Mode(void);				// set 10 at MODER3 bits pos to select Alternate function mode for pin PA3
// GPIOB
void GPIOB_PB6_AF_Mode(void);				// set 10 at MODER6 bits pos to select Alternate function mode for pin PB6
void GPIOB_PB7_AF_Mode(void);				// set 10 at MODER7 bits pos to select Alternate function mode for pin PB7
void GPIOB_PB8_AF_Mode(void);				// set 10 at MODER8 bits pos to select Alternate function mode for pin PB8
void GPIOB_PB9_AF_Mode(void);				// set 10 at MODER9 bits pos to select Alternate function mode for pin PB9


// Select Mode as OUTPUT MODE in the GPIOx_MODER
// GPIOA
void GPIOA_PA0_OUTPUT_MODE(void);			// set MODER0 to 01 select OUTPUT MODE
void GPIOA_PA1_OUTPUT_MODE(void);			// set MODER1 to 01 select OUTPUT MODE
void GPIOA_PA2_OUTPUT_MODE(void);			// set MODER2 to 01 select OUTPUT MODE
void GPIOA_PA3_OUTPUT_MODE(void);			// set MODER3 to 01 select OUTPUT MODE
void GPIOA_PA4_OUTPUT_MODE(void);			// set MODER4 to 01 select OUTPUT MODE
void GPIOA_PA5_OUTPUT_MODE(void);			// set MODER5 to 01 select OUTPUT MODE
void GPIOA_PA6_OUTPUT_MODE(void);			// set MODER6 to 01 select OUTPUT MODE
void GPIOA_PA7_OUTPUT_MODE(void);			// set MODER7 to 01 select OUTPUT MODE
void GPIOA_PA8_OUTPUT_MODE(void);			// set MODER8 to 01 select OUTPUT MODE
void GPIOA_PA9_OUTPUT_MODE(void);			// set MODER9 to 01 select OUTPUT MODE
void GPIOA_PA10_OUTPUT_MODE(void);		// set MODER10 to 01 select OUTPUT MODE
void GPIOA_PA11_OUTPUT_MODE(void);		// set MODER11 to 01 select OUTPUT MODE
void GPIOA_PA12_OUTPUT_MODE(void);		// set MODER12 to 01 select OUTPUT MODE
void GPIOA_PA13_OUTPUT_MODE(void);		// set MODER13 to 01 select OUTPUT MODE
void GPIOA_PA14_OUTPUT_MODE(void);		// set MODER14 to 01 select OUTPUT MODE
void GPIOA_PA15_OUTPUT_MODE(void);		// set MODER15 to 01 select OUTPUT MODE
// GPIOB
void GPIOB_PB0_OUTPUT_MODE(void);			// set MODER0 to 01 select OUTPUT MODE
void GPIOB_PB1_OUTPUT_MODE(void);			// set MODER1 to 01 select OUTPUT MODE
void GPIOB_PB2_OUTPUT_MODE(void);			// set MODER2 to 01 select OUTPUT MODE
void GPIOB_PB3_OUTPUT_MODE(void);			// set MODER3 to 01 select OUTPUT MODE
void GPIOB_PB4_OUTPUT_MODE(void);			// set MODER4 to 01 select OUTPUT MODE
void GPIOB_PB5_OUTPUT_MODE(void);			// set MODER5 to 01 select OUTPUT MODE
void GPIOB_PB6_OUTPUT_MODE(void);			// set MODER6 to 01 select OUTPUT MODE
void GPIOB_PB7_OUTPUT_MODE(void);			// set MODER7 to 01 select OUTPUT MODE
void GPIOB_PB8_OUTPUT_MODE(void);			// set MODER8 to 01 select OUTPUT MODE
void GPIOB_PB9_OUTPUT_MODE(void);			// set MODER9 to 01 select OUTPUT MODE
void GPIOB_PB10_OUTPUT_MODE(void);		// set MODER10 to 01 select OUTPUT MODE
void GPIOB_PB11_OUTPUT_MODE(void);		// set MODER11 to 01 select OUTPUT MODE
void GPIOB_PB12_OUTPUT_MODE(void);		// set MODER12 to 01 select OUTPUT MODE
void GPIOB_PB13_OUTPUT_MODE(void);		// set MODER13 to 01 select OUTPUT MODE
void GPIOB_PB14_OUTPUT_MODE(void);		// set MODER14 to 01 select OUTPUT MODE
void GPIOB_PB15_OUTPUT_MODE(void);		// set MODER15 to 01 select OUTPUT MODE
// GPIOC
void GPIOC_PC0_OUTPUT_MODE(void);			// set MODER0 to 01 select OUTPUT MODE
void GPIOC_PC1_OUTPUT_MODE(void);			// set MODER1 to 01 select OUTPUT MODE
void GPIOC_PC2_OUTPUT_MODE(void);			// set MODER2 to 01 select OUTPUT MODE
void GPIOC_PC3_OUTPUT_MODE(void);			// set MODER3 to 01 select OUTPUT MODE
void GPIOC_PC4_OUTPUT_MODE(void);			// set MODER4 to 01 select OUTPUT MODE
void GPIOC_PC5_OUTPUT_MODE(void);			// set MODER5 to 01 select OUTPUT MODE
void GPIOC_PC6_OUTPUT_MODE(void);			// set MODER6 to 01 select OUTPUT MODE
void GPIOC_PC7_OUTPUT_MODE(void);			// set MODER7 to 01 select OUTPUT MODE
void GPIOC_PC8_OUTPUT_MODE(void);			// set MODER8 to 01 select OUTPUT MODE
void GPIOC_PC9_OUTPUT_MODE(void);			// set MODER9 to 01 select OUTPUT MODE
void GPIOC_PC10_OUTPUT_MODE(void);		// set MODER10 to 01 select OUTPUT MODE
void GPIOC_PC11_OUTPUT_MODE(void);		// set MODER11 to 01 select OUTPUT MODE
void GPIOC_PC12_OUTPUT_MODE(void);		// set MODER12 to 01 select OUTPUT MODE
void GPIOC_PC13_OUTPUT_MODE(void);		// set MODER13 to 01 select OUTPUT MODE
void GPIOC_PC14_OUTPUT_MODE(void);		// set MODER14 to 01 select OUTPUT MODE
void GPIOC_PC15_OUTPUT_MODE(void);		// set MODER15 to 01 select OUTPUT MODE
// GPIOH
void GPIOC_PH0_OUTPUT_MODE(void);		// set MODER0 to 01 select OUTPUT MODE
void GPIOC_PH1_OUTPUT_MODE(void);		// set MODER1 to 01 select OUTPUT MODE


// Select Alternate function in the ALTERNATE FUNCTION LOW/HIGH REGISTER GPIOx_AFRL/GPIOx_AFRH
// GPIOA
void GPIOA_PA2_AF7_USART2(void);		// Set 7 = 0111 at AFRL2 bit positions to select AF7 AKA USART2 for pin PA2 in the AFRL Register
void GPIOA_PA3_AF7_USART2(void);		// Set 7 = 0111 at AFRL3 bit positions to select AF7 AKA USART2 for pin PA3 in the AFRL Register
// GPIOB
void GPIOB_PB6_AF4_I2C1(void);			// Set 4 = 0100 at AFRL6 bit positions to select AF4 AKA I2C1 for pin PB6 in the AFRL Register
void GPIOB_PB7_AF4_I2C1(void);			// Set 4 = 0100 at AFRL7 bit positions to select AF4 AKA I2C1 for pin PB7 in the AFRL Register
void GPIOB_PB8_AF4_I2C1(void);			// set 4 = 0100 at AFRH8 bit positions to select AF4 to Select I2C for pin PB8 (PB8 will be the SCL)
void GPIOB_PB9_AF4_I2C1(void);			// set 4 = 0100 at AFRH9 bit positions to select AF4 to select I2C for pin PB9 (PB9 will be the SDA)


// Select Output Type Push-Pull/Open-Drain in the GPIOx_OTYPER
// Open Drain Output Type
// GPIOB
void GPIOB_PB7_OTYPE_Open_Drain(void);		// set 1 at bit pos OT7 to configure open drain for PB7 pin
void GPIOB_PB8_OTYPE_Open_Drain(void);		// set 1 at bit pos OT8 to configure open drain for PB8 pin
void GPIOB_PB9_OTYPE_Open_Drain(void);		// set 1 at bit pos OT9 to configure open drain for PB9 pin


// Select Pull-up/pull-down register
// Select Pull-up
// GPIOB
void GPIOB_PB7_Pull_Up(void);				// set 01 at PUPDR7 bit postions to Select Pull-up for Pin PB7
void GPIOB_PB8_Pull_Up(void);				// set 01 at PUPDR8 bit postions to Select Pull-up for Pin PB8
void GPIOB_PB9_Pull_Up(void);				// set 01 at PUPDR9 bit postions to Select Pull-up for Pin PB9
// Select Pull-Down
// GPIOA
void GPIOA_PA1_Pull_Down(void);			// set 10 at PUPDR1 bit postions to Select Pull-down for Pin PA1
void GPIOA_PA2_Pull_Down(void);			// set 10 at PUPDR2 bit postions to Select Pull-down for Pin PA2
void GPIOA_PA3_Pull_Down(void);			// set 10 at PUPDR3 bit postions to Select Pull-down for Pin PA3
void GPIOA_PA4_Pull_Down(void);			// set 10 at PUPDR4 bit postions to Select Pull-down for Pin PA4
void GPIOA_PA5_Pull_Down(void);			// set 10 at PUPDR5 bit postions to Select Pull-down for Pin PA5
void GPIOA_PA6_Pull_Down(void);			// set 10 at PUPDR6 bit postions to Select Pull-down for Pin PA6
void GPIOA_PA7_Pull_Down(void);			// set 10 at PUPDR7 bit postions to Select Pull-down for Pin PA7
void GPIOA_PA8_Pull_Down(void);			// set 10 at PUPDR8 bit postions to Select Pull-down for Pin PA8
void GPIOA_PA10_Pull_Down(void);			// set 10 at PUPDR10 bit postions to Select Pull-down for Pin PA10
// GPIOB
void GPIOB_PB3_Pull_Down(void);			// set 10 at PUPDR3 bit postions to Select Pull-down for Pin PB3
void GPIOB_PB4_Pull_Down(void);			// set 10 at PUPDR4 bit postions to Select Pull-down for Pin PB4
void GPIOB_PB5_Pull_Down(void);			// set 10 at PUPDR5 bit postions to Select Pull-down for Pin PB5
void GPIOB_PB9_Pull_Down(void);			// set 10 at PUPDR9 bit postions to Select Pull-down for Pin PB9
void GPIOB_PB10_Pull_Down(void);			// set 10 at PUPDR10 bit postions to Select Pull-down for Pin PB10
// GPIOC
void GPIOC_PC0_Pull_Down(void);			// set 10 at PUPDR0 bit postions to Select Pull-down for Pin PC0
void GPIOC_PC1_Pull_Down(void);			// set 10 at PUPDR1 bit postions to Select Pull-down for Pin PC1
void GPIOC_PC1_Pull_Up(void);				// set 01 at PUPDR1 bit postions to Select Pull-up for Pin PC1
void GPIOC_PC2_Pull_Up(void);				// set 01 at PUPDR2 bit postions to Select Pull-up for Pin PC2
void GPIOC_PC7_Pull_Up(void);				// set 01 at PUPDR7 bit postions to Select Pull-up for Pin PC7



// Select Output Speed in the OUTPUT SPEED REGISTER GPIOx_OSPEEDR 
// GPIOA
void GPIOA_PA2_Output_Speed_HIGH(void);		// set 11 at OSPEEDR2 bit pos to select High output speed for pin PA2
void GPIOA_PA3_Output_Speed_HIGH(void);		// set 11 at OSPEEDR3 bit pos to select High output speed for pin PA3
// GPIOB
void GPIOB_PB6_Output_Speed_HIGH(void);		// set 11 at OSPEEDR6 bit pos to select High output speed for pin PB6
void GPIOB_PB7_Output_Speed_HIGH(void);		// set 11 at OSPEEDR7 bit pos to select High output speed for pin PB7
void GPIOB_PB8_Output_Speed_HIGH(void);		// set 11 at OSPEEDR8 bit pos to select High output speed for pin PB8
void GPIOB_PB9_Output_Speed_HIGH(void);		// set 11 at OSPEEDR9 bit pos to select High output speed for pin PB9
