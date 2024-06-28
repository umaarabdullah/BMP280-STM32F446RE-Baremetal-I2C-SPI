#include "I2C_MASTER.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// I2C Peripheral Reset
void I2C1_Software_Reset(void){
	I2C1->CR1 |= I2C_CR1_SWRST;
	I2C1->CR1 &= ~(I2C_CR1_SWRST);
}

// Peripheral Input Clock to generate correct timings
void I2C1_MASTER_CLK_FREQ_45MHZ(void){										// Set FREQ[5:0] to 45 in CR2
	I2C1->CR2 |= (45 << 0);
}

// Configure Clock Control Registers (CCR)
// I2C1 Sm Mode CCR = ((tr(SCL) + tw(SCLH))/tPCLK1)
void I2C1_MASTER_CCR_Sm_THigh_FREQ_45(void){							// In Standard Mode (Sm) using THigh with FREQ as 45 the CCR is set to 225 in CRR[11:0]
	// Standard Mode (SM)
	I2C1->CCR |= (225 << 0);
}
// I2C1 Sm Mode CCR = ((tf(SCL) + tw(SCLL))/tPCLK1)
void I2C1_MASTER_CCR_Sm_TLow_BME280_Tf140ns_Tw210ns_FREQ_45(void){			// In Standard Mode (Sm) using TLow with FREQ as 45 the CCR is set to 16 in CRR[11:0]
	/**** 
				CCR = ((tf(SCL) + tw(SCLL))/tPCLK1) 
				CCR = (((140ns) + (210ns))/(1/45MHZ)) = 15.75
	****/
	// Standard Mode (SM)
	I2C1->CCR |= (16 << 0);
}

// Rise Time Register Configuration
// I2C1 Rise time Tr(SCL)/TPCLK1
void I2C1_MASTER_Sm_TRISE_FREQ_45(void){									// Set 45+1 = 46 to TRISE Register
	I2C1->TRISE = 46;
}
// I2C1 Rise time Tr(SCL)/TPCLK1
void I2C1_MASTER_Sm_TRISE_Tr6_FREQ_45(void){							// Set 7+1 = 8 to TRISE Register
	I2C1->TRISE = 8;
}

// Enable I2C Reception Interrupt
void I2C1_MASTER_BUFFER_INTERRUPT_ENABLE(void){
	I2C1->CR2 |= I2C_CR2_ITBUFEN;
}
void I2C1_MASTER_EVENT_INTERRUPT_ENABLE(void){
	I2C1->CR2 |= I2C_CR2_ITEVTEN;
}

// Enable I2C1
void I2C1_MASTER_ENABLE(void){																		// Set PE bit in CR1
	I2C1->CR1 |= I2C_CR1_PE;
}

// Disable I2C1
void I2C1_MASTER_DISABLE(void){																		// Reset PE bit in CR1
	I2C1->CR1 &= ~(I2C_CR1_PE);
}

void I2C1_MASTER_ACK_ENABLE(void){
	
	// Set ACK bit in CR1
	I2C1->CR1 |= I2C_CR1_ACK;
}

// Disable Acknowledgement (NOACKM) (NACK)
void I2C1_MASTER_ACK_DISABLE(void){

	// Reset ACK bit in CR1
	I2C1->CR1 &= ~(I2C_CR1_ACK);
}

// Generate Start Condition and Switch to MASTER mode
void I2C1_MASTER_START(void){																		// set bit 8 START to 1 in CR1 and wait for START FLAG in SR1
	
	// Enable ACK
	I2C1->CR1 |= I2C_CR1_ACK;
	
	// Set Start Bit
	I2C1->CR1 |= I2C_CR1_START;
	// wait until SB bit is 1 (1 : start condition generated)
	while(!(I2C1->SR1 & I2C_SR1_SB));
}

// Slave Address Transmission
void I2C1_MASTER_SLAVEADDRESS_TRANSMIT(uint8_t slaveAddress, uint8_t LSB){			// send slave address and wait for ADDR flag bit to set and 
																																								// then clear ADDR by a read to SR1 followed by a read to SR2
	uint8_t slaveAddressWithLSB = 0;
	slaveAddressWithLSB |= (slaveAddress << 1);
	
	// If LSB is 0 indicates that the master will transmit data
	// If LSB is 1 indicates that the master will receive data
	slaveAddressWithLSB |= (LSB << 0);
	
	// Write Slave Address in the Data register here we write the address of the SLAVE
	I2C1->DR = slaveAddressWithLSB;
	
	// Wait for ADDR bit to set in SR1 which indicates that the slave address has matched and end of SLAVE Address Transmission
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	
	// Clear ADDR Bit by a Read to SR1 followed by a Read to SR2
	uint32_t tempRead = I2C1->SR1;
	tempRead = I2C1->SR2;
	(void) tempRead;
}
// Slave Address Transmission for single byte readout
void I2C1_MASTER_SLAVEADDRESS_TRANSMIT_SINGLE_BYTE_READ(uint8_t slaveAddress, uint8_t LSB){
	
	uint8_t slaveAddressWithLSB = 0;
	slaveAddressWithLSB |= (slaveAddress << 1);
	
	// If LSB is 0 indicates that the master will transmit data
	// If LSB is 1 indicates that the master will receive data
	slaveAddressWithLSB |= (LSB << 0);
	
	// Write Slave Address in the Data register here we write the address of the SLAVE
	I2C1->DR = slaveAddressWithLSB;
	
	uint8_t tmp;
	tmp = (uint8_t) I2C1->DR;		// Tmp read
	(void) tmp;
	
	// Wait for ADDR bit to set in SR1 which indicates that the slave address has matched and end of SLAVE Address Transmission
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	
	// Clear ACK bit 
	I2C1->CR1 &= ~(I2C_CR1_ACK);
	UART2_SendString((uint8_t *)" Got here6\n");

	// Clear ADDR Bit by a Read to SR1 followed by a Read to SR2
	uint32_t tempRead = I2C1->SR1;
	tempRead = I2C1->SR2;
	(void) tempRead;
	
	// Wait for RXNE Flag bit to set in the status register
	while(!(I2C1->SR1 & I2C_SR1_RXNE));
	UART2_SendString((uint8_t *)" Got here7\n");
	tmp = (uint8_t) I2C1->DR;		// Tmp read
}

// Slave Address Transmission for Multi Byte readout
void I2C1_MASTER_SLAVEADDRESS_TRANSMIT_MULTIPLE_BYTE_READ(uint8_t slaveAddress, uint8_t *RXTXBuffer, int size){
	
	uint8_t slaveAddressWithLSB = 0;
	slaveAddressWithLSB |= (slaveAddress << 1);
	
	// If LSB is 0 indicates that the master will transmit data
	// If LSB is 1 indicates that the master will receive data
	slaveAddressWithLSB |= (1 << 0);
	
	// Write Slave Address in the Data register here we write the address of the SLAVE
	I2C1->DR = slaveAddressWithLSB;
	
	// Wait for ADDR bit to set in SR1 which indicates that the slave address has matched and end of SLAVE Address Transmission
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	
	// Clear ADDR Bit by a Read to SR1 followed by a Read to SR2
	uint32_t tempRead = I2C1->SR1;
	tempRead = I2C1->SR2;
	(void) tempRead;
	
	// READING MULTIPLE BYTES UPTO 3RD LAST BYTE
	int i;
	for(i=0; i<size-2; i++){
		
		// Wait for RXNE Flag bit to set in the status register
		while(!(I2C1->SR1 & I2C_SR1_RXNE));
		
		// Read Data from Data Register
		RXTXBuffer[i] = (uint8_t) I2C1->DR;
		
		// Set ACK bit to Acknowledge the data received
		I2C1->CR1 |= I2C_CR1_ACK;
		
	}
	
	/*** Reading 2nd Last Byte ***/
	// Wait for RXNE Flag bit to set in the status register
	while(!(I2C1->SR1 & I2C_SR1_RXNE));
	
	// Read Data from Data Register
	RXTXBuffer[i++] = (uint8_t) I2C1->DR;
	
	// Reset ACK bit to NoAcknowledge (NACK)
	I2C1->CR1 &= ~(I2C_CR1_ACK);
	
	// Stop I2C
	//I2C1_MASTER_DISABLE();
	
	I2C1_MASTER_STOP();
	
	/*** Reading Last Byte ***/
	// Wait for RXNE Flag bit to set in the status register
	while(!(I2C1->SR1 & I2C_SR1_RXNE));
	
	// Read Data from Data Register
	RXTXBuffer[i] = (uint8_t) I2C1->DR;
	
}

// Master Transmission
void I2C1_MASTER_TRANSMIT(uint8_t byteData){							// transmit a byte of data by writing to the DR Register when shfit register empty and data register empty
		
	// Wait for the data register to be empty
	while(!(I2C1->SR1 & I2C_SR1_TXE));
	
	// Write data in the data register
	I2C1->DR = byteData;
	
	// Wait for the BTF bit to set in SR1 to indicate the byte transfer has completed
	while(!(I2C1->SR1 & I2C_SR1_BTF));
	
}

// Receive Data 
uint8_t I2C1_MASTER_RECEIVE_DATA(void){

	// wait for RXNE bit to set
	while(!(I2C1->SR1 & I2C_SR1_RXNE));
	
	// Read Data
	uint8_t byteData = (uint8_t) I2C1->DR;
	
	return byteData;
}

// Generate Stop Condition and thus return to SLAVE MODE
void I2C1_MASTER_STOP(void){
	
	I2C1->CR1 |= I2C_CR1_STOP;
	
	/*// wait for the stop generation that is Wait for STOPF bit to set
	while(!(I2C1->SR1 & I2C_SR1_STOPF));
	
	uint32_t temp;
	temp = I2C1->SR1;
	I2C1->CR1 |= (I2C_CR1_PE);*/
}
