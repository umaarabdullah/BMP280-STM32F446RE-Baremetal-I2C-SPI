#include "LCD_DRIVER.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// CPHA AND CPOL as 0 and 0

// Select Master mode
void SPI2_MASTER_MODE(void);

// Serial Clock Baud Rate
void SPI2_BAUD_RATE_DIV_8(void);			// Div FPCLK by 8 to make BAUD RATE 5MHZ

//LSBFIRST: Frame format : MSB transmitted first
void SPI2_MSB_FIRST(void);						// Set 0 in the LSBFIRST bit in CR1

// Enable Software Slave Management
void SPI2_SSM_Enable(void);						// SSM=1 and SSI=1

// Enable Full Duplex mode SPI communication
void SPI2_FULL_DUPLEX_MODE(void);			// RXONLY=0 means full duplex mode

// Data frame format Selection = 8 bit format
void SPI2_DFF_8BIT(void);							// DFF=0 means 8 bit format

// Enable TXEIE interrupt
void SPI2_TXEIE_INTERRUPT_ENABLE(void);

// Enable RXNEIE interrupt
void SPI2_RXNEIE_INTERRUPT_ENABLE(void);

// Disable RXNEIE interrupt
void SPI2_RXNEIE_INTERRUPT_DISABLE(void);

// Set Control Register2 to 0
void SPI2_CR2_REGISTER_RESET(void);		

// SPI2 Enable 
void SPI2_ENABLE(void);

// SPI2 Disable
void SPI2_DISABLE(void);

// Chip Select Enable : Reset CSB Pin
void SPI2_CSB_ENABLE(void);

// Chip Select Disable : Set CSB Pin
void SPI2_CSB_DISABLE(void);

// SPI Transmission
void SPI2_TRANSMIT_WRITE(uint8_t controlByte, uint8_t dataByte); 

// SPI Reception
void SPI2_TRANSMIT_READ(uint8_t data, uint8_t *receivedByteData); 

// SPI Control Byte transmission with RW as 1 for single byte read
uint8_t SPI2_TRANSMIT_CONTROL_BYTE_SINGLE_BYTE_READ(uint8_t contByte);

// SPI Multiple Byte readout
void SPI2_TRANSMIT_MULTI_BYTE_READ(uint8_t contByte, uint8_t *RXBuffer, int size);

// SPI BMP Config Control Byte transmission with RW as 1 and with interrupt disabled
uint8_t SPI2_BMP_CONFIG_TRANSMIT_CONTROL_BYTE(uint8_t contByte);

// Configure BME280
int BME280_Config(uint8_t osrs_t, uint8_t isrs_p, uint8_t mode, uint8_t t_sb, uint8_t filter);

