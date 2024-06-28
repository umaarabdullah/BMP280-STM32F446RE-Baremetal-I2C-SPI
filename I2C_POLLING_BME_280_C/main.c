#include "main.h"

uint8_t RXBuf[50];
int RXBufIndex;

uint8_t calib[40];
int calibIndex;

// t_fine carries fine temperature as global value
BME280_S32_t t_fine;

// Raw and Calibrated Reading variables
int temp;
int press;
int hum;
double calibratedTemp;
double calibratedPress;
double calibratedAlt;

// Flags for measurement button for LCD Display
uint8_t tempButton = 1; 			// By default LCD will show Temp
uint8_t pressButton;
uint8_t altButton;

// Flag for title
uint8_t title;

// Refernce Pressure - Average of measured pressure values. Suppose 100 samples.
double p_reference;

// Trimming Parameters
// For Temperature
unsigned short dig_T1;
signed short dig_T2;
signed short dig_T3;
// For Pressure
unsigned short dig_P1;
signed short dig_P2;
signed short dig_P3;
signed short dig_P4;
signed short dig_P5;
signed short dig_P6;
signed short dig_P7;
signed short dig_P8;
signed short dig_P9;
// For Humidity
unsigned char dig_H1;
signed short dig_H2;
unsigned char dig_H3;
signed short dig_H4;
signed short dig_H5;
signed char dig_H6;

uint8_t trimming;


int main(){
	
	// Clock
	SysClockConfig();
	GPIOB_CLOCK_ENABLE();
	GPIOA_CLOCK_ENABLE();
	GPIOC_CLOCK_ENABLE();
	USART2_CLOCK_ENABLE();
	I2C1_CLOCK_ENABLE();
	TIM6_CLOCK_ENABLE();
	TIM7_CLOCK_ENABLE();
	
	// PB7 SDA
	GPIOB_PB7_AF_Mode();
	GPIOB_PB7_AF4_I2C1();
	GPIOB_PB7_OTYPE_Open_Drain();
	GPIOB_PB7_Pull_Up();
	GPIOB_PB7_Output_Speed_HIGH();
	
	// PB8 SCL
	GPIOB_PB8_AF_Mode();
	GPIOB_PB8_AF4_I2C1();
	GPIOB_PB8_OTYPE_Open_Drain();
	GPIOB_PB8_Pull_Up();
	GPIOB_PB8_Output_Speed_HIGH();
	
	// I2C1 MASTER 
	I2C1_Software_Reset();
	I2C1_MASTER_CLK_FREQ_45MHZ();
	I2C1_MASTER_CCR_Sm_THigh_FREQ_45();
	I2C1_MASTER_Sm_TRISE_FREQ_45();
	//I2C1_MASTER_BUFFER_INTERRUPT_ENABLE();
	//I2C1_MASTER_EVENT_INTERRUPT_ENABLE();
	//NVIC_EnableIRQ(I2C1_ER_IRQn);
	I2C1_MASTER_ENABLE();
	
	/*********************/
	/*	Problem interfacing with usart2 
	**	Weird I2C start condition doesnt get generated if USART Clock is enabled or USART GPIO pins are configured for RX and TX
	*/
	/*********************/
	// UART
	USART2_GPIO_CONFIG();
	USART2_Enable();
	USART2_Baud_Rate_115200();
	USART2_Word_Length_8();
	USART2_Enable_RE();
	USART2_Enable_TE();
	
	// TIMER
	// TIM6
	TIMER6_PSC_90();
	TIMER6_ARR_MAX();
	Enable_TIMER6();
	// TIM7
	Timer7_PSC_9000();		// Each Count is at 1/10ms
	TIMER7_ARR_5000();		// 10000 so each update interrupt will be generated after 0.5 second
	//TIMER7_ARR_10000();	// 10000 so each update interrupt will be generated after 1 second
	Timer7_Interrupt_Enable();
	NVIC_EnableIRQ(TIM7_IRQn);
	
	// LCD Control
	LCD_GPIO_CONFIG();
	LCD_INIT();
	LCD_FUNCTION_SET_8BIT_INTERFACE();
	LCD_RETURN_HOME();
	LCD_CLEAR_DISPLAY();
	//LCD_DISPLAY_ON();								// LCD Display with no cursor and no cursor blink
	LCD_CURSOR_ON();								// LCD Display with cursor and no cursor blink
	//LCD_DISPLAY_AND_CURSOR_ON();		// LCD Display with cursor and cursor blink
	LCD_ENTRY_MODE_CURSOR_RIGHT();
	
	READ_SENSOR_ID();
	
	trimming = 1;
	readTrimmingParameters();
	BME280Config();
	
	p_reference = BMP_SetRefPressure(100,50);					// Assigning p_reference
	
	// Clear display to clear the Displayed CHIP ID
	LCD_CLEAR_DISPLAY();

	Enable_TIMER7();
	
	while(1){
		
	}
}

// Tim7 Update Interrupt. An update event is set to occur when CNT=ARR
void TIM7_IRQHandler(void){
	
	if((TIM7->SR & TIM_SR_UIF)){
		
		// Must be synchronized
		// Button Selection to Select type of Output - temp/press/alt
		// PB0 - TEMPBUTTON			PB1 - PRESSBUTTON			PB2 ALTBUTTON
		if(GPIOB->IDR & GPIO_IDR_ID0){			// PB0
			LCD_CLEAR_DISPLAY();
			title = 0;
			tempButton = 1;
			pressButton = 0;
			altButton = 0;
			TIMER6_Delay_s(1);
		}
		if(GPIOB->IDR & GPIO_IDR_ID1){			// PB1
			LCD_CLEAR_DISPLAY();
			title = 0;
			tempButton = 0;
			pressButton = 1;
			altButton = 0;
			TIMER6_Delay_s(1);
		}
		if(GPIOB->IDR & GPIO_IDR_ID2){			// PB2
			LCD_CLEAR_DISPLAY();
			title = 0;
			tempButton = 0;
			pressButton = 0;
			altButton = 1;
			TIMER6_Delay_s(1);
		}
		
		// Record Raw Measurement from sensor
		BMPMeasure();
		
		// Use Compensation Algorithms
		calibratedTemp 		= (BME280_compensate_T_int32(temp)/100.0);
		calibratedPress 	= (BME280_compensate_P_int64(press)/256.0);
		if(p_reference > 0){
			calibratedAlt = (double)(1.0 - pow(((calibratedPress)/(p_reference)), 0.1903)) * (double)4433076.0;
			calibratedAlt = (calibratedAlt/10)*(-1);
		}
	
		
		/*** Result shown in Terminal ***/
		// buffer to store the data to be showed in UART Terminal
		char str[50];
		UART2_SendString((uint8_t *)"Sensor Reading :");
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		// Temperature Measurement
		// Calibrated Reading
		sprintf(str, "%.2lf", calibratedTemp);
		UART2_SendString((uint8_t *)"TEMP  : ");
		UART2_SendString((uint8_t *)str);
		UART2_SendString((uint8_t *)" DegC");
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		// Pressure Measurement
		// Calibrated Reading
		sprintf(str, "%.2lf", calibratedPress);
		UART2_SendString((uint8_t *)"PRESS : ");
		UART2_SendString((uint8_t *)str);
		UART2_SendString((uint8_t *)" Pa");
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		// p_refernce 
		sprintf(str, "%.2lf", p_reference);
		UART2_SendString((uint8_t *)"P_REF : ");
		UART2_SendString((uint8_t *)str);
		UART2_SendString((uint8_t *)" Pa"); 
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		// Altitude Measurement
		// Reading
		sprintf(str, "%.2lf", calibratedAlt);
		UART2_SendString((uint8_t *)"ALT   : ");
		UART2_SendString((uint8_t *)str);
		UART2_SendString((uint8_t *)" m");
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		/**** Send Data to LCD according to button pressed ***/
		// Temperature
		if(tempButton){
			if(!title){
				title = 1;
				LCD_SEND_STRING("TEMP: ");
			}
			// Send Temperature Measurement to the LCD Display
			LCD_SEND_FLOAT_NUM(calibratedTemp);
		}
		// Pressure
		else if(pressButton){
			if(!title){
				title = 1;
				LCD_SEND_STRING("PRES: ");
			}
			// Send Pressure Measurement to the LCD Display
			LCD_SEND_FLOAT_NUM(calibratedPress);
		}
		// Altitude
		else if(altButton){
			if(!title){
				title = 1;
				LCD_SEND_STRING("ALT: ");
			}
			// Send Alitude Measurement to the LCD Display
			LCD_SEND_FLOAT_NUM(calibratedAlt);
		}
		else{
			LCD_SEND_STRING("PRESS BUTTON");
			TIMER6_Delay_s(2);
			LCD_CLEAR_DISPLAY();
		}
		
		// Clear UIF FLag
		TIM7->SR &= ~(TIM_SR_UIF);
	}
}

// Measurement of Temperature and Pressure values
void BMPMeasure(void){
	
	// read - start, send slave address, control byte, start, slave address, reception data byte, NOACKM, stop
	I2C1_MASTER_START();
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT(BME280_Chip_Address, 0);
	I2C1_MASTER_TRANSMIT(0xF7);						// Control Byte
	I2C1_MASTER_START();
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT_MULTIPLE_BYTE_READ(BME280_Chip_Address, RXBuf, 6);
	
	// Measurements
	press		= ((RXBuf[0] << 12) | (RXBuf[1] << 4) | (RXBuf[2] >> 4));
	temp 		= ((RXBuf[3] << 12) | (RXBuf[4] << 4) | (RXBuf[5] >> 4));

}

// Calculating p_reference: use few samples of pressure and calculate the average. Assuming delay_ms is delay between each measurement.
double BMP_SetRefPressure(int samples, int delay_ms){
	
	double sum = 0.0;
	
	for(int i=0; i<samples; i++){
		BMPMeasure();
		calibratedTemp 		= (BME280_compensate_T_int32(temp)/100.0);
		calibratedPress = (BME280_compensate_P_int64(press)/256.0);
		if(calibratedPress < 100000){
			--i;
			continue;
		}
		sum += calibratedPress;
		TIMER6_Delay_ms((uint16_t)delay_ms);
	}
	return (sum/samples);
}

void I2C1_EV_IRQHandler(void){
	/*
	if(I2C1->SR1 & I2C_SR1_RXNE){
		
		if(trimming == 1){
			
			trimming = 0;
			
			// Trimming Parameters Readout
		}
		
		uint8_t id = (uint8_t)I2C1->DR;
		char strID[20];
		sprintf(strID, "%x", id);
		
		LCD_SEND_STRING(strID);
		TIMER6_Delay_s(5);
		LCD_CLEAR_DISPLAY();
		
		// Clear Flag 
		I2C1->SR1 &= ~(I2C_SR1_RXNE);
	}*/
}


void readTrimmingParameters(void){

	// read - start, send slave address, control byte, start, slave address, reception data byte, NOACKM, stop
	I2C1_MASTER_START();
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT(BME280_Chip_Address, 0);
	I2C1_MASTER_TRANSMIT(0x88);						// Control Byte
	I2C1_MASTER_START();
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT_MULTIPLE_BYTE_READ(BME280_Chip_Address, calib, 24);		// Size = 24

	/* Assigning Trimming Parameter from the calib Array
	// dig_T1 to dig_T3 maps to 0x88 to 0x8D (array index 0-5)
	// dig_P1 to dig_P9 maps to 0x8E to 0x9F (array index 6-23)
	// dig_H1 to dig_H6 maps to 0xA1 (array index 24) and 0xE1 to 0xE7 (array index 25-32)
	*/
	dig_T1 = (unsigned short) ((calib[0] << 0) | (calib[1] << 8));
	dig_T2 = (signed short) 	((calib[2] << 0) | (calib[3] << 8));
	dig_T3 = (signed short) 	((calib[4] << 0) | (calib[5] << 8));
	
	dig_P1 = (unsigned short) ((calib[6] << 0) | (calib[7] << 8));
	dig_P2 = (signed short) 	((calib[8] << 0) | (calib[9] << 8));
	dig_P3 = (signed short) 	((calib[10] << 0) | (calib[11] << 8));
	dig_P4 = (signed short) 	((calib[12] << 0) | (calib[13] << 8));
	dig_P5 = (signed short) 	((calib[14] << 0) | (calib[15] << 8));
	dig_P6 = (signed short) 	((calib[16] << 0) | (calib[17] << 8));
	dig_P7 = (signed short) 	((calib[18] << 0) | (calib[19] << 8));
	dig_P8 = (signed short) 	((calib[20] << 0) | (calib[21] << 8));
	dig_P9 = (signed short) 	((calib[22] << 0) | (calib[23] << 8));
	
	
}

void READ_SENSOR_ID(void){
	
	/***
	1. If only 1 BYTE needs to be Read
		a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
		b) the Acknowledge disable is made during EV6 (before ADDR flag is cleared) and the STOP condition generation is made after EV6
		c) Wait for the RXNE (Receive Buffer not Empty) bit to set
		d) Read the data from the DR 
	***/
	
	UART2_SendString((uint8_t *)" Got here1\n");
	I2C1_MASTER_START();
	UART2_SendString((uint8_t *)" Got here2\n");
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT(BME280_Chip_Address, 0);
	UART2_SendString((uint8_t *)" Got here3\n");
	I2C1_MASTER_TRANSMIT(0xD0);
	UART2_SendString((uint8_t *)" Got here4\n");
	I2C1_MASTER_START();
	UART2_SendString((uint8_t *)" Got here5\n");
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT_SINGLE_BYTE_READ(BME280_Chip_Address, 1);
	//I2C1_MASTER_STOP();
	//I2C1_MASTER_DISABLE();
	UART2_SendString((uint8_t *)" Got here!!\n");

	uint8_t id = (uint8_t)I2C1->DR;
	char strID[20];
	sprintf(strID, "%x", id);
	UART2_SendString((uint8_t *)"CHIP ID : ");
	UART2_SendString((uint8_t *)strID);
	UART2_SendChar(NL);
	
	LCD_SEND_STRING("CHIP ID: 0x");
	LCD_SEND_STRING(strID);
	TIMER6_Delay_ms(50);
}


void BME280Config(void){
	
	/**** 
	*	write - start, send slave address, control byte , data byte, stop 
	* ****/
	
	// Reset Register Address : 0xE0, DataByte : 0xB6
	I2C1_MASTER_START();
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT(BME280_Chip_Address, 0);
	I2C1_MASTER_TRANSMIT(0xE0);						// Control Byte Reset Register 0xE0
	I2C1_MASTER_TRANSMIT(0xB6);						// Data Byte to write 
	TIMER6_Delay_ms(100);
	
	// Set humidity Oversampling as x1 in ctrl_hum register Address : 0xF2 , Databyte : 1
	I2C1_MASTER_START();
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT(BME280_Chip_Address, 0);
	I2C1_MASTER_TRANSMIT(0xF2);						// Control Byte 
	I2C1_MASTER_TRANSMIT(0x1);					  // Data Byte to write 
	TIMER6_Delay_ms(100);
	
	// Set filter coefficient as 16 and t_sb as 0.5 in config register Address : 0xF5, Databyte : 0x10
	I2C1_MASTER_START();
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT(BME280_Chip_Address, 0);
	I2C1_MASTER_TRANSMIT(0xF5);						// Control Byte 
	I2C1_MASTER_TRANSMIT(0x10);					  // Data Byte to write
	TIMER6_Delay_ms(100);
	
	/** 
	* Set Pressure oversampling as x16 and Temperature Oversampling as x2 and Select Normal Mode in 
	* ctrl_meas register Address : 0xF4, Databyte : 0x57
	**/
	I2C1_MASTER_START();
	I2C1_MASTER_SLAVEADDRESS_TRANSMIT(BME280_Chip_Address, 0);
	I2C1_MASTER_TRANSMIT(0xF4);						// Control Byte 
	I2C1_MASTER_TRANSMIT(0x57);					  // Data Byte to write
	TIMER6_Delay_ms(100);

}


// Returns temperature in DegC, resolution is 0.01 DegC. Output value of �5123� equals 51.23 DegC.
// t_fine carries fine temperature as global value
BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T){

	BME280_S32_t var1, var2, T;
	var1 = ((((adc_T>>3) - ((BME280_S32_t)dig_T1<<1))) * ((BME280_S32_t)dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((BME280_S32_t)dig_T1)) * ((adc_T>>4) - ((BME280_S32_t)dig_T1))) >> 12) * ((BME280_S32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}


// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of �24674867� represents 24674867/256 = 96386.2 Pa = 963.862 hPa
BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P){
	
	BME280_S64_t var1, var2, p;
	var1 = ((BME280_S64_t)t_fine) - 128000;
	var2 = var1 * var1 * (BME280_S64_t)dig_P6;
	var2 = var2 + ((var1*(BME280_S64_t)dig_P5)<<17);
	var2 = var2 + (((BME280_S64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (BME280_S64_t)dig_P3)>>8) + ((var1 * (BME280_S64_t)dig_P2)<<12);
	var1 = (((((BME280_S64_t)1)<<47)+var1))*((BME280_S64_t)dig_P1)>>33;
	if (var1 == 0){
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((BME280_S64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((BME280_S64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((BME280_S64_t)dig_P7)<<4);
	return (BME280_U32_t)p;
}

