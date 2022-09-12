#include "USART_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// I2C Peripheral Reset
void I2C1_Software_Reset(void);

// Peripheral Input Clock to generate correct timings
void I2C1_MASTER_CLK_FREQ_45MHZ(void);										// Set FREQ to 45 in CR2

// Configure Clock Control Registers (CCR)
// I2C1 Sm Mode CCR = ((tr(SCL) + tw(SCLH))/tPCLK1)
void I2C1_MASTER_CCR_Sm_THigh_FREQ_45(void);							// In Standard Mode (Sm) using THigh with FREQ as 45 the CCR is set to 225 in CRR[11:0]
// I2C1 Sm Mode CCR = ((tf(SCL) + tw(SCLL))/tPCLK1)
void I2C1_MASTER_CCR_Sm_TLow_BME280_Tf140ns_Tw210ns_FREQ_45(void);			// In Standard Mode (Sm) using TLow with FREQ as 45 the CCR is set to 16 in CRR[11:0]

// Rise Time Register Configuration
// I2C1 Rise time Tr(SCL)/TPCLK1
void I2C1_MASTER_Sm_TRISE_FREQ_45(void);									// Set 45+1 = 46 to TRISE Register
// I2C1 Rise time Tr(SCL)/TPCLK1
void I2C1_MASTER_Sm_TRISE_Tr6_FREQ_45(void);							// Set 7+1 = 8 to TRISE Register

// Enable I2C Reception Interrupt
void I2C1_MASTER_BUFFER_INTERRUPT_ENABLE(void);
void I2C1_MASTER_EVENT_INTERRUPT_ENABLE(void);

// Enable I2C1
void I2C1_MASTER_ENABLE(void);																		// Set PE bit in CR1

// Disable I2C1
void I2C1_MASTER_DISABLE(void);																		// Reset PE bit in CR1

// Enable Acknowledgement
void I2C1_MASTER_ACK_ENABLE(void);

// Disable Acknowledgement (NOACKM) (NACK)
void I2C1_MASTER_ACK_DISABLE(void);

// Generate Start Condition and Switch to MASTER mode 
void I2C1_MASTER_START(void);																		// set bit 8 START to 1 in CR1 and wait for START FLAG in SR1

// Slave Address Transmission
void I2C1_MASTER_SLAVEADDRESS_TRANSMIT(uint8_t slaveAddress, uint8_t LSB);		// send slave address and wait for ADDR flag bit to set 
																																							// and then clear ADDR by a read to SR1 followed by a read to SR2
// Slave Address Transmission for single byte readout
void I2C1_MASTER_SLAVEADDRESS_TRANSMIT_SINGLE_BYTE_READ(uint8_t slaveAddress, uint8_t LSB);

// Slave Address Transmission for Multi Byte readout
void I2C1_MASTER_SLAVEADDRESS_TRANSMIT_MULTIPLE_BYTE_READ(uint8_t slaveAddress, uint8_t *RXTXBuffer, int size);

// Master Transmission
void I2C1_MASTER_TRANSMIT(uint8_t byteData);							// transmit a byte of data by writing to the DR Register when shfit register empty and data register empty

// Receive Data 
uint8_t I2C1_MASTER_RECEIVE_DATA(void);

// Generate Stop Condition and thus return to SLAVE MODE
void I2C1_MASTER_STOP(void);

// Enable Acknowledgement
void I2C1_MASTER_ACK_ENABLE(void);
