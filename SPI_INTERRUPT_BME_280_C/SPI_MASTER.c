#include "SPI_MASTER.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Select Master mode
void SPI2_MASTER_MODE(void){
	
	// Set MSTR in CR1 to select as master
	SPI2->CR1 |= SPI_CR1_MSTR;
}

// Serial Clock Baud Rate
void SPI2_BAUD_RATE_DIV_8(void){			// Div FPCLK by 8 to make BAUD RATE 5MHZ
	
	// Set BR[2:0] to 010: fPCLK/8
	SPI2->CR1 |= (1 << 4);
}

//LSBFIRST: Frame format : MSB transmitted first
void SPI2_MSB_FIRST(void){						
	
	// Set 0 in the LSBFIRST bit in CR1
	SPI2->CR1 &= ~(SPI_CR1_LSBFIRST);
}

// Enable Software Slave Management
void SPI2_SSM_Enable(void){						
	
	// Set SSM=1 and SSI=1
	SPI2->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;
}

// Enable Full Duplex mode SPI communication
void SPI2_FULL_DUPLEX_MODE(void){

	// RXONLY=0 means full duplex mode
	SPI2->CR1 &= ~(SPI_CR1_RXONLY);
}

// Data frame format Selection = 8 bit format
void SPI2_DFF_8BIT(void){							
	
	// DFF=0 means 8 bit format
	SPI2->CR1 &= ~(SPI_CR1_DFF);
}

// Enable TXEIE interrupt
void SPI2_TXEIE_INTERRUPT_ENABLE(void){
	
	// Set TXEIE in CR2 
	SPI2->CR2 |= SPI_CR2_TXEIE;
}

// Enable RXNEIE interrupt
void SPI2_RXNEIE_INTERRUPT_ENABLE(void){

	// Set RXNEIE in CR2
	SPI2->CR2 |= SPI_CR2_RXNEIE;
}

// Disable RXNEIE interrupt
void SPI2_RXNEIE_INTERRUPT_DISABLE(void){
	
	// Reset RXNEIE in CR2
	SPI2->CR2 &= ~(SPI_CR2_RXNEIE);
}

// Set Control Register2 to 0
void SPI2_CR2_REGISTER_RESET(void){
	
	SPI2->CR2 = 0;
}		

// SPI2 Enable 
void SPI2_ENABLE(void){
	
	// SPE:1 SPI Peripheral enabled
	SPI2->CR1 |= (SPI_CR1_SPE);
}

// SPI2 Disable
void SPI2_DISABLE(void){

	// SPE:0 SPI Peripheral disabled
	SPI2->CR1 &= ~(SPI_CR1_SPE);
}

// Chip Select Enable : Reset CSB Pin
void SPI2_CSB_ENABLE(void){
	
	// PB9 is the Chip Select Pin. Make PB9 Low
	GPIOB->BSRR |= GPIO_BSRR_BR9;
}

// Chip Select Disable : Set CSB Pin
void SPI2_CSB_DISABLE(void){

	// PB9 is the Chip Select Pin. Make PB9 High
	GPIOB->BSRR |= GPIO_BSRR_BS9;
}

// SPI Transmission
void SPI2_TRANSMIT_WRITE(uint8_t controlByte, uint8_t dataByte){
		
	GPIOA->BSRR |= GPIO_BSRR_BR9;		// Set CSB LOW
	TIMER7_Delay_us(5);
	
	// Wait for TXE bit to set which indicates data register is empty
	while(!(SPI2->SR & SPI_SR_TXE));
	
	// Set CONTROL BYTE i.e Register Address with RW bit (7th bit) as 0
	controlByte &= ~(1<<7);
	
	// SEND CONTROL BYTE i.e Register Address with RW bit (7th bit) as 0
	SPI2->DR = controlByte;
	TIMER7_Delay_us(5);
	
	// Wait for TXE bit to set and then wait for the BUSY FLag to RESET
	while(!(SPI2->SR & SPI_SR_TXE));
	// Wait for BSY Bit to Reset
	while((SPI2->SR & SPI_SR_BSY));
	
	// Clear Overrun bit by reading DR and SR
	uint32_t temp = SPI2->DR;
	temp = SPI2->SR;
	
	// Wait for TXE bit to set which indicates data register is empty
	while(!(SPI2->SR & SPI_SR_TXE));
	
	// SEND DATA BYTE we want to write into the register
	SPI2->DR = dataByte;
	TIMER7_Delay_us(5);
	
	// Wait for TXE bit to set and then wait for the BUSY FLag to RESET
	while(!(SPI2->SR & SPI_SR_TXE));
	// Wait for BSY Bit to Reset
	while((SPI2->SR & SPI_SR_BSY));
	
	// Clear Overrun bit by reading DR and SR
	temp = SPI2->DR;
	temp = SPI2->SR;
	
	GPIOA->BSRR |= GPIO_BSRR_BS9;		// Set CSB HIGH
}

// SPI Reception
void SPI2_TRANSMIT_READ(uint8_t data, uint8_t *receivedByteData){
	
	// Wait for TXE bit to set which indicates data register is empty
	while(!(SPI2->SR & SPI_SR_TXE));
	
	// Write Data
	SPI2->DR = data;
	
	// Wait for RXNE bit to set
	while(!(SPI2->SR & SPI_SR_RXNE));	
	//uint8_t receivedByteData[10]
	receivedByteData[0] = (uint8_t) SPI2->DR;
	receivedByteData[1] = (uint8_t) SPI2->DR;
	receivedByteData[2] = (uint8_t) SPI2->DR;
	receivedByteData[3] = (uint8_t) SPI2->DR;
	receivedByteData[4] = (uint8_t) SPI2->DR;
	receivedByteData[5] = (uint8_t) SPI2->DR;
	receivedByteData[6] = (uint8_t) SPI2->DR;
	receivedByteData[7] = (uint8_t) SPI2->DR;
	
	// Wait for TXE bit to set and then wait for the BUSY FLag to RESET
	while(!(SPI2->SR & SPI_SR_TXE));
	
	// Wait for BSY Bit to Reset
	while((SPI2->SR & SPI_SR_BSY));
	
	// Clear Overrun bit by reading DR and SR
	uint32_t temp = SPI2->DR;
	temp = SPI2->SR;
	
	//return receivedByteData;
}

// SPI Control Byte transmission with RW as 1
uint8_t SPI2_TRANSMIT_CONTROL_BYTE_SINGLE_BYTE_READ(uint8_t contByte){

	GPIOA->BSRR |= GPIO_BSRR_BR9;		// Set CSB LOW
	TIMER7_Delay_us(5);
	
	// Set 1 in 7th bit RW bit 
	contByte |= (1<<7);
	
	// Wait for TXE bit to set to indicate Data Register is empty
	while(!(SPI2->SR & SPI_SR_TXE));		
	
	SPI2->DR = contByte;
	TIMER7_Delay_us(5);
	
	// Dummy read
	uint8_t tmpp;
	tmpp = (uint8_t)SPI2->DR;
	
	// Wait for TXE bit to set and then wait for the BUSY FLag to RESET
	while(!(SPI2->SR & SPI_SR_TXE));
	
	// Wait for BSY Bit to Reset
	while((SPI2->SR & SPI_SR_BSY));
	
	SPI2->DR = 0x00;			// an xtra byte
	TIMER7_Delay_us(5);
	
	uint8_t slaveData = (uint8_t)SPI2->DR;
	
	GPIOA->BSRR |= GPIO_BSRR_BS9;		// Set CSB HIGH
	
	return slaveData;
}

// SPI Multiple Byte readout
void SPI2_TRANSMIT_MULTI_BYTE_READ(uint8_t contByte, uint8_t *RXBuffer, int size){

	GPIOA->BSRR |= GPIO_BSRR_BR9;		// Set CSB LOW
	TIMER7_Delay_us(5);
	
	// Set 1 in 7th bit RW bit to indicate read of control byte (Register address)
	contByte |= (1<<7);
	
	// Wait for TXE bit to set to indicate Data Register is empty
	while(!(SPI2->SR & SPI_SR_TXE));		
	
	SPI2->DR = contByte;
	TIMER7_Delay_us(5);
	
	// Dummy read
	uint8_t tmpp;
	tmpp = (uint8_t)SPI2->DR;
	
	// Wait for TXE bit to set and then wait for the BUSY FLag to RESET
	while(!(SPI2->SR & SPI_SR_TXE));
	// Wait for BSY Bit to Reset
	while((SPI2->SR & SPI_SR_BSY));
	
	// Read Data bytes and store in buffer
	int i;
	for(i=0; i<size; i++){
		SPI2->DR = 0x00;			// an extra byte
		TIMER7_Delay_us(5);
		uint8_t tmp;
		tmp = (uint8_t)SPI2->DR;
		RXBuffer[i] = (uint8_t)SPI2->DR;
	}
	
	GPIOA->BSRR |= GPIO_BSRR_BS9;		// Set CSB HIGH
}

// SPI BMP Config Control Byte transmission with RW as 1 and with interrupt disabled
uint8_t SPI2_BMP_CONFIG_TRANSMIT_CONTROL_BYTE(uint8_t contByte){
	
	// Set 1 in 7th bit RW bit 
	contByte |= (1<<7);

	// Wait for TXE bit to set to indicate Data Register is empty
	while(!(SPI2->SR & SPI_SR_TXE));
	
	SPI2->DR = 0;
	SPI2->DR = 0;
	SPI2->DR = 0;
	SPI2->DR = 0;
	SPI2->DR = 0;
	SPI2->DR = 0;
	SPI2->DR = 0;
	SPI2->DR = 0;
	SPI2->DR = 0;
	SPI2->DR = contByte;
	SPI2->DR = 0;
	
	// Wait for TXE bit to set and then wait for the BUSY FLag to RESET
	while(!(SPI2->SR & SPI_SR_TXE));
	
	// Wait for BSY Bit to Reset
	while((SPI2->SR & SPI_SR_BSY));
	
	return (uint8_t)SPI2->DR;
}


