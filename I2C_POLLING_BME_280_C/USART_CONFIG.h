#include "TIMER_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Configure GPIO Pins for RX and TX
void USART2_GPIO_CONFIG(void);

// Enable USARTx
void USART2_Enable(void);		// Set UE bit in USART2_CR1

// Program the M bit in USARTx_CR1 to define the word length
void USART2_Word_Length_8(void);		// Set 0 at bit 12 (M bit) pos to set 1 Start bit, 8 Data bits, n Stop bit

// Select the desired baud rate using the baud rate register USARTx_BRR
void USART2_Baud_Rate_115200(void);		// set baud rate to 115200 by configuring the div and mantissa bits in the USART2_BRR 

// Enable USARTx Transmitter
void USART2_Enable_TE(void);		// set 1 to TE bit in the USART2_CR1 register

// Enable USARTx Receiver
void USART2_Enable_RE(void);		// set 1 to RE bit in the USART2_CR1 register

// Transmission
void UART2_SendChar(uint8_t byteData);				// Transmit an unsigned char Character using USART2 port in UART POLL METHOD
void UART2_SendString(uint8_t *stringData);		// Transmit a string using USART2 port in UART POLL METHOD

// Reception
uint8_t UART2_ReceiveChar(void);														// Receive an unsigned char character using USART2 port in UART POLL METHOD
void UART2_ReceiveString(uint8_t *stringData);							// receive a string of characters until a (.) is detected POLL METHOD

// Enable Receive RXNE interrupt 
void USART2_Enable_RECEIVE_INTERRUPT_RXNEIE(void);		// set bit 5 RXNEIE in USART2_CR1

// Enable Transmission TXEIE interrupt 
void USART2_Enable_TRANSMIT_INTERRUPT_TXEIE(void);		// set bit 7 TXEIE in USART2_CR

// Enable Transmission TCIE interrupt 
void USART2_Enable_TRANSMIT_COMPLETE_INTERRUPT_TCIE(void);		// set bit 6 TCIE in USART2_CR

