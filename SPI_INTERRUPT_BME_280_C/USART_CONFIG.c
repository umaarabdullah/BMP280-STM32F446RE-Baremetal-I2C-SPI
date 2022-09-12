#include "USART_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Enable USARTx in CR1 Register
// Enable USART2
void USART2_Enable(){
	
	USART2->CR1 = 0x00;		// Clears the CR1 Register
	USART2->CR1 |= USART_CR1_UE;		// Set UE bit in USART2_CR1
}

// Program the M bit in USARTx_CR1 to define the word length
// Configure M bit in USART2_CR1
void USART2_Word_Length_8(void){
	
	USART2->CR1 &= (unsigned int)~(1 << 12);		// Set 0 at bit 12 (M bit) pos to set 1 Start bit, 8 Data bits, n Stop bit
}

// Select the desired baud rate using the baud rate register USARTx_BRR
// Set Baud rate of USART2 to 115200
void USART2_Baud_Rate_115200(void){
	
	// set baud rate to 115200 by configuring the div and mantissa bits in the USART2_BRR 
	// For baud rate 115200, 7 in the Div part 24 in the mantissa part
	USART2->BRR |= (7 << 0);		// DIV part
	USART2->BRR |= (24 << 4);		// Mantissa part
}

// Enable USARTx Transmitter
void USART2_Enable_TE(void){
	
	USART2->CR1 |= USART_CR1_TE;		// set 1 to TE bit in the USART2_CR1 register
}

// Enable USARTx Receiver
void USART2_Enable_RE(void){
	
	USART2->CR1 |= USART_CR1_RE;		// set 1 to RE bit in the USART2_CR1 register
}

// Transmission
void UART2_SendChar(uint8_t byteData){
	
	// Transmit an unsigned char Character using USART2 port
	// Write the data to send in the USART_DR register (this clears the TXE bit)
	USART2->DR = byteData;
	// After writing data into the USART_DR register 
	// wait until TC=1. This indicates that the transmission of the last frame is complete
	while(!(USART2->SR & USART_SR_TC));
	
}
// Transmit a string using USART2 port in UART Communication mode
// DURING FIRST BYTE TRANSMISSION IT GETS LOST
void UART2_SendString(uint8_t *stringData){
	
	while(*stringData)
		UART2_SendChar(*stringData++);
}

// Reception
// Receive an unsigned char character using USART2 port in UART POLL METHOD	
uint8_t UART2_ReceiveChar(void){
	
	// When the RXNE bit is set. It indicates data has been received and can be read
	// Wait for the RXNE bit to be 1
	while(!(USART2->SR & USART_SR_RXNE));
	// In single buffer mode, software read to the USART_DR register clears the RXNE bit
	// read data from DR Register
	uint8_t byteData = (uint8_t) USART2->DR;
	
	return byteData;
}
// Recieve a string of characters until a (.) is detected UART POLL METHOD
void UART2_ReceiveString(uint8_t *stringData){
	
	uint8_t byteCharData;
	byteCharData = UART2_ReceiveChar();
	// recieve a character from UART2 port unitl a newline or carriage return character is detected
	// store the character in an array of characters i.e a string using it's base address pointer stringdata
	// '.' period character is used to detect input string end
	while(byteCharData != '.'){
		*(stringData++) = byteCharData;
		byteCharData = UART2_ReceiveChar();
	}
	*stringData = '\0';		// String Null Terminator
}

// Enable Receive RXNE interrupt 
void USART2_Enable_RECEIVE_INTERRUPT_RXNEIE(void){		// set bit 5 RXNEIE in USART2_CR1
	
	USART2->CR1 |= USART_CR1_RXNEIE;
}

// Enable Transmission TXEIE interrupt 
void USART2_Enable_TRANSMIT_INTERRUPT_TXEIE(void){		// set bit 7 TXEIE in USART2_CR
	
	USART2->CR1 |= USART_CR1_TXEIE;
}

// Enable Transmission TCIE interrupt

void USART2_Enable_TRANSMIT_COMPLETE_INTERRUPT_TCIE(void){		// set bit 6 TCIE in USART2_CR
	
	USART2->CR1 |= USART_CR1_TCIE;
}


