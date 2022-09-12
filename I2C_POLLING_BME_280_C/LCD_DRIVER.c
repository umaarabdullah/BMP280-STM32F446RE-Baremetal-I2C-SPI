#include "LCD_DRIVER.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

//Configure GPIO Pins to be used for LCD
void LCD_GPIO_CONFIG(void){
	
	// GPIO Pins PC0,PB9, PA5, PA6, PA7, PA8, PB10, PB4, PB5, PB3, PA10 as LCD pins
	// GPIO PIN  PA5 as E bit
	// GPIO PINS PC0, PB9 as RS and RW respectively
	/* GPIO PINS PA6, PA7, PA8, PB10, PB4, PB5, PB3, PA10 as Data pins Respectively
	** DATA PINS D0,	D1,	 D2,	D3,		D4,	 D5,	D6,	 D7		Data pins Respectively
	*/
	// Set Output Mode
	GPIOC_PC0_OUTPUT_MODE();
	GPIOB_PB9_OUTPUT_MODE();
	GPIOA_PA5_OUTPUT_MODE();
	GPIOA_PA6_OUTPUT_MODE();
	GPIOA_PA7_OUTPUT_MODE();
	GPIOA_PA8_OUTPUT_MODE();
	GPIOB_PB10_OUTPUT_MODE();
	GPIOB_PB4_OUTPUT_MODE();
	GPIOB_PB5_OUTPUT_MODE();
	GPIOB_PB3_OUTPUT_MODE();
	GPIOA_PA10_OUTPUT_MODE();
	// Enable all Pins Pull Down Resistor
	GPIOC_PC0_Pull_Down();
	GPIOB_PB9_Pull_Down();
	GPIOA_PA5_Pull_Down();
	GPIOA_PA6_Pull_Down();
	GPIOA_PA7_Pull_Down();
	GPIOA_PA8_Pull_Down();
	GPIOB_PB10_Pull_Down();
	GPIOB_PB4_Pull_Down();
	GPIOB_PB5_Pull_Down();
	GPIOB_PB3_Pull_Down();
	GPIOA_PA10_Pull_Down();
	
}

// Initialize LCD
void LCD_INIT(void){
	
	TIMER6_Delay_ms(50);
	LCD_SEND_CMD(0x30);
	TIMER6_Delay_ms(20);
	LCD_SEND_CMD(0x30);
	TIMER6_Delay_ms(20);
	LCD_SEND_CMD(0x30);
	TIMER6_Delay_ms(20);
	
}

// Turn on LCD Display and Turn on Cursor and Turn on Cursor Blink
void LCD_DISPLAY_AND_CURSOR_ON(void){

	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  1,  D,  C,  B
	// D = HIGH, Entire display is turned on
	// C = HIGH, Cursor is turned on
	// B = HIGH, Cursor blink is turned on
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  1,  1,  1,  1
	// CMD 0xF
	LCD_SEND_CMD(0xF);
}

// Turn on LCD Display with no cursor and no blink
void LCD_DISPLAY_ON(void){
	
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  1,  D,  C,  B
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  1,  1,  0,  0
	LCD_SEND_CMD(0xC);
}

// Turn on LCD Display with cursor and no blink
void LCD_CURSOR_ON(void){
	
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  1,  D,  C,  B
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  1,  1,  1,  0
	LCD_SEND_CMD(0xE);
}

// Set Entry Mode 
// Increment cursor to the right 
void LCD_ENTRY_MODE_CURSOR_RIGHT(void){
	
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  1,  I/D, S
	// I/D = HIGH cursor moves right
	// S, I/D = High , Low = shift the display to the right
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  1,  1, 0
	LCD_SEND_CMD(0x6);
}

// Shift Display One Character right
void LCD_SHIFT_DISPLAY_RIGHT(void){

	// RS, RW, D7, D6, D5, D4, D3, D2,  D1, D0
	// 0 , 0,  0,  0,  0,  1, S/C, R/L, x,  x
	// RS, RW, D7, D6, D5, D4, D3, D2,  D1, D0
	// 0 , 0,  0,  0,  0,  1,  1,  1,   0,  0
	LCD_SEND_CMD(0x1C);
}

// Shift Display One Character left
void LCD_SHIFT_DISPLAY_LEFT(void){
	
	// RS, RW, D7, D6, D5, D4, D3, D2,  D1, D0
	// 0 , 0,  0,  0,  0,  1, S/C, R/L, x,  x
	// RS, RW, D7, D6, D5, D4, D3, D2,  D1, D0
	// 0 , 0,  0,  0,  0,  1,  1,  0,   0,  0
	LCD_SEND_CMD(0x18);
}

// Shift Entry Entire Display right
void LCD_ENTRY_SHIFT_DISPLAY_RIGHT(void){

	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  1, I/D, S
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  1,  0,  1
	LCD_SEND_CMD(0x5);
}

// Shift Entry Entire Display left
void LCD_ENTRY_SHIFT_DISPLAY_LEFT(void){
	
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  1, I/D, S
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  1,  1,  1
	LCD_SEND_CMD(0x7);
}

// Shift Cursor left 
void LCD_SHIFT_CURSOR_LEFT(void){

	// RS, RW, D7, D6, D5, D4, D3, D2,  D1, D0
	// 0 , 0,  0,  0,  0,  1, S/C, R/L, x,  x
	// RS, RW, D7, D6, D5, D4, D3, D2,  D1, D0
	// 0 , 0,  0,  0,  0,  1,  0,  0,   0,  0
	LCD_SEND_CMD(0x10);
}

// Clear Display
void LCD_CLEAR_DISPLAY(void){

	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  0,  0,  1
	LCD_SEND_CMD(0x1);
}

// Return home i.e return cursor to it's original site and return display to it's original status
void LCD_RETURN_HOME(void){

	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  0,  1,  x
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  0,  0,  0,  0,  1,  0
	LCD_SEND_CMD(0x2);
}

// Set LCD to 8-bit bus mode with MPU
void LCD_FUNCTION_SET_8BIT_INTERFACE(void){
	
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  1,  DL,  N,  F,  x,  x
	// DL = HIGH = 8-bit bus mode
	// N 	= High = 2 Line Mode
	// F 	= low = 5x8 dots format display
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  1,  1,  0,  0,  0,  0
	LCD_SEND_CMD(0x30);
}

// Set LCD to 2-Line Display Mode
void LCD_FUNCTION_SET_8BIT_INTERFACE_2Line_DISPLAY_MODE(void){

	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  1,  DL,  N,  F,  x,  x
	// DL = HIGH = 8-bit bus mode
	// N 	= High = 2 Line Mode
	// F 	= low = 5x8 dots format display
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 0 , 0,  0,  0,  1,  1,  1,  0,  0,  0
	LCD_SEND_CMD(0x38);
}

// Write data to LCD
void LCD_8BIT_WRITE(uint8_t data){
	
	// GPIO PINS PC0 as RS 
	// RS, RW, D7, D6, D5, D4, D3, D2, D1, D0
	// 1 , 0,  D7, D6, D5, D4, D3, D2, D1, D0
	GPIOC->BSRR |= GPIO_BSRR_BS0; 		// RS = High to select Data Register
	TIMER6_Delay_ms(20);
	LCD_SEND_CMD(data);
	GPIOC->BSRR |= GPIO_BSRR_BR0; 		// Reset RS	
	TIMER6_Delay_ms(20);
}

// Send 8bit Command to the LCD while RS is low
void LCD_SEND_CMD(uint8_t data){
	
	/* GPIO PINS PA6, PA7, PA8, PB10, PB4, PB5, PB3, PA10 as Data pins Respectively
	** DATA PINS D0,	D1,	 D2,	D3,		D4,	 D5,	D6,	 D7		Data pins Respectively
	*/
	
	if(data & 1<<0)				// D0
		GPIOA->BSRR |= GPIO_BSRR_BS6;
	if(data & 1<<1)
		GPIOA->BSRR |= GPIO_BSRR_BS7;
	if(data & 1<<2)
		GPIOA->BSRR |= GPIO_BSRR_BS8;
	if(data & 1<<3)
		GPIOB->BSRR |= GPIO_BSRR_BS10;
	if(data & 1<<4)
		GPIOB->BSRR |= GPIO_BSRR_BS4;
	if(data & 1<<5)
		GPIOB->BSRR |= GPIO_BSRR_BS5;
	if(data & 1<<6)
		GPIOB->BSRR |= GPIO_BSRR_BS3;
	if(data & 1<<7)
		GPIOA->BSRR |= GPIO_BSRR_BS10;
	TIMER6_Delay_ms(20);
	
	// E enable
	LCD_ENABLE();
	
	// Reset	
	GPIOA->BSRR |= GPIO_BSRR_BR6;
	GPIOA->BSRR |= GPIO_BSRR_BR7;
	GPIOA->BSRR |= GPIO_BSRR_BR8;
	GPIOB->BSRR |= GPIO_BSRR_BR10;
	GPIOB->BSRR |= GPIO_BSRR_BR4;
	GPIOB->BSRR |= GPIO_BSRR_BR5;
	GPIOB->BSRR |= GPIO_BSRR_BR3;
	GPIOA->BSRR |= GPIO_BSRR_BR10;
	TIMER6_Delay_ms(20);
}

// LCD enable
void LCD_ENABLE(void){

	// GPIO PIN  PA5 as E bit
	// E Enable Bit
	GPIOA->BSRR |= GPIO_BSRR_BS5;
	TIMER6_Delay_ms(20);
	GPIOA->BSRR |= GPIO_BSRR_BR5;
	TIMER6_Delay_ms(20);
}

// Send Space to LCD
void LCD_SEND_SPACE(void){
	LCD_8BIT_WRITE(' ');
}

// Send a Character to LCD
void LCD_SEND_CHAR(char charData){
	LCD_8BIT_WRITE(charData);
}

// Send String to LCD
void LCD_SEND_STRING(char *stringData){
	
	while(*stringData){
		LCD_SEND_CHAR(*stringData++);
	}
}

// Send whole number to LCD
void LCD_SEND_WHOLE_NUM(int num){
	
	char numString[50];
	sprintf(numString, "%d", num);
	LCD_SEND_STRING(numString);
}

// Send Floating point number to LCD
void LCD_SEND_FLOAT_NUM(double floatNum){
	
	char floatNumString[50];
	sprintf(floatNumString, "%.2lf", floatNum);
	LCD_SEND_STRING(floatNumString);
	
	// Move cursor back to starting position to overwrite the next data
	uint32_t len = strlen(floatNumString);
	for(uint32_t i=0; i<len; i++)
		LCD_SHIFT_CURSOR_LEFT();
}

// Shift Display 16 Character
void LCD_SHIFT_DISPLAY_16_CHAR(void){
	
	for(int i=0; i<16; i++){
		LCD_SHIFT_DISPLAY_LEFT();
	}
}

// Shift Cursor to Next Screen that is 16 characters
void LCD_SHIFT_CURSOR_16_CHAR(void){

	for(int i=0; i<16; i++){
		LCD_ENTRY_SHIFT_DISPLAY_RIGHT();
	}
}






