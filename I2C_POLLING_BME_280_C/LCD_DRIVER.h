#include "I2C_MASTER.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "math.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

//Configure GPIO Pins to be used for LCD
void LCD_GPIO_CONFIG(void);

// Initialize LCD
void LCD_INIT(void);

// Turn on LCD Display and Turn on Cursor and Turn on Cursor Blink
void LCD_DISPLAY_AND_CURSOR_ON(void);

// Turn on LCD Display with no Cursor and no Cursor Blink
void LCD_DISPLAY_ON(void);

// Turn on LCD Display with Cursor and no Cursor Blink
void LCD_CURSOR_ON(void);


// Set Entry Mode 
// Increment cursor to the right 
void LCD_ENTRY_MODE_CURSOR_RIGHT(void);

// Shift Display One Character right
void LCD_SHIFT_DISPLAY_RIGHT(void);

// Shift Display One Character left
void LCD_SHIFT_DISPLAY_LEFT(void);

// Shift Entry Entire Display right
void LCD_ENTRY_SHIFT_DISPLAY_RIGHT(void);

// Shift Entry Entire Display left
void LCD_ENTRY_SHIFT_DISPLAY_LEFT(void);

// Shift Cursor left 
void LCD_SHIFT_CURSOR_LEFT(void);

// Clear Display
void LCD_CLEAR_DISPLAY(void);

// Return home i.e return cursor to it's original site and return display to it's original status
void LCD_RETURN_HOME(void);

// Set LCD to 8-bit bus mode with MPU
void LCD_FUNCTION_SET_8BIT_INTERFACE(void);

// Set LCD to 2-Line Display Mode
void LCD_FUNCTION_SET_8BIT_INTERFACE_2Line_DISPLAY_MODE(void);

// Write data to LCD
void LCD_8BIT_WRITE(uint8_t data);

// Send 8bit Command to the LCD while RS is low
void LCD_SEND_CMD(uint8_t data);

// LCD enable
void LCD_ENABLE(void);

// Send Space to LCD
void LCD_SEND_SPACE(void);

// Send a Character to LCD
void LCD_SEND_CHAR(char charData);

// Send String to LCD
void LCD_SEND_STRING(char *stringData);

// Send whole number to LCD
void LCD_SEND_WHOLE_NUM(int num);

// Send Floating point number to LCD
void LCD_SEND_FLOAT_NUM(double floatNum);

// Shift Display 16 Character
void LCD_SHIFT_DISPLAY_16_CHAR(void);

// Shift Cursor to Next Screen that is 16 characters
void LCD_SHIFT_CURSOR_16_CHAR(void);

