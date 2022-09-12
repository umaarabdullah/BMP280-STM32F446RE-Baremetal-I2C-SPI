#include "main.h"

uint8_t RXBuf[50];
int RXBufIndex;

uint8_t calib[40];
int calibIndex;

// Status Flag
int statusFlag = 0;

int temp = 0;
int press = 0;

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

BME280_S32_t t_fine;


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
	GPIOA_CLOCK_ENABLE();
	GPIOB_CLOCK_ENABLE();
	GPIOC_CLOCK_ENABLE();
	TIM6_CLOCK_ENABLE();
	TIM7_CLOCK_ENABLE();
	USART2_CLOCK_ENABLE();
	SPI2_CLOCK_ENABLE();
	
	// Enabling FPU (From PM)
	__asm volatile("LDR.W R0, =0xE000ED88");
	__asm volatile("LDR R1, [R0]");
	__asm volatile("MOV R2, #0xF");
	__asm volatile("ORR R1, R1, R2, LSL #20");
	__asm volatile("STR R1, [R0]");
	__asm volatile("DSB");
	__asm volatile("ISB");
	float f = 1.2303f;
	f = f + 0.2343f;
	
	// Timer
	// Basic Timer TIM7
	TIMER7_PSC_90();
	TIMER7_ARR_MAX();
	Enable_TIMER7();
	
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
	
	// USART Alternate Function
	GPIOA_PA2_AF_Mode();
	GPIOA_PA2_AF7_USART2();
	GPIOA_PA2_Output_Speed_HIGH();
	GPIOA_PA3_AF_Mode();
	GPIOA_PA3_AF7_USART2();
	GPIOA_PA3_Output_Speed_HIGH();
	
	// SPI2 GPIO and Alternate Function config
	// PC1 - MOSI - SDA
	GPIOC_PC1_AF_Mode();
	GPIOC_PC1_Output_Speed_HIGH();
	GPIOC_PC1_AF7_SPI2();
	// PC2 - MISO - SDO
	GPIOC_PC2_AF_Mode();
	GPIOC_PC2_Output_Speed_HIGH();
	GPIOC_PC2_AF5_SPI2();
	// PC7 - SCK - SCL
	GPIOC_PC7_AF_Mode();
	GPIOC_PC7_Output_Speed_HIGH();
	GPIOC_PC7_AF5_SPI2();
	// PA9 - CSB
	GPIOA_PA9_OUTPUT_MODE();
	
	// UART
	USART2_Enable();
	USART2_Baud_Rate_115200();
	USART2_Word_Length_8();
	USART2_Enable_RE();
	USART2_Enable_TE();
	
	// Timer
	// Basic Timer TIM6
	Timer6_PSC_9000();	// Each Count is at 1/10ms
	TIMER6_ARR_5000();	// 10000 so each update interrupt will be generated after 0.5 second
	//TIMER6_ARR_10000();	// 10000 so each update interrupt will be generated after 1 second
	Timer6_Interrupt_Enable();
	NVIC_EnableIRQ(TIM6_DAC_IRQn);			
	
	// SPI Master Config
	SPI2_MASTER_MODE();
	SPI2_BAUD_RATE_DIV_8();
	SPI2_MSB_FIRST();
	SPI2_SSM_Enable();
	SPI2_FULL_DUPLEX_MODE();
	SPI2_DFF_8BIT();
	SPI2_CR2_REGISTER_RESET();
	SPI2_ENABLE();
	
	// SPI2 Interrupt Enable
	//SPI2_RXNEIE_INTERRUPT_ENABLE();
	//NVIC_EnableIRQ(SPI2_IRQn);
	
	// Read the Trimming Parameters and store in an array
	trimming = 1;
	GPIOA->BSRR |= GPIO_BSRR_BS9;		// Set CSB HIGH
	trimmingParameterReadout();			// Trimming Parameters will be stored in the calib Array
	trimming = 0;
	
	BME280_INDOOR_NAVIGATION();
	
	//p_reference = BMP_SetRefPressure(100, 50);
	p_reference = 101325.0;
	
	LCD_CLEAR_DISPLAY();
	
	// Enable Timer6 
	Enable_TIMER6();
	
	/*** It is supposed to auto-increment from the Register address 
	why isnt it auto-incrementing ???????? ***/
	
	while(1){
		
	}
}

void SPI2_IRQHandler(void){
	
	// RXNE Interrupt Handling
	if(SPI2->SR & SPI_SR_RXNE){
		
		UART2_SendString((uint8_t *)"In Interrupt");
		UART2_SendChar(NL);
		
		if(trimming == 1){
			uint8_t registerDataByte = (uint8_t) SPI2->DR;
			calib[calibIndex++] = registerDataByte;	
		}
		else if(statusFlag == 1){
			statusFlag = 0;
			LCD_SEND_STRING("STATUS: ");
			LCD_SEND_WHOLE_NUM((int)SPI2->DR);
			TIMER7_Delay_s(5);
			LCD_CLEAR_DISPLAY();
		}
		else{
		
			// Read Received Data from Data Register
			uint8_t registerDataByte = (uint8_t) SPI2->DR;
			RXBuf[RXBufIndex++] = registerDataByte;
		}
		
		// Clear flag
		SPI2->SR &= ~(SPI_SR_RXNE);
	}
}

// Tim6 Update Interrupt. An update event is set to occur when CNT=ARR
void TIM6_DAC_IRQHandler(void){
	
	if((TIM6->SR & TIM_SR_UIF)){
			
		// Button Selection to Select type of Output - temp/press/alt
		// PB0 - TEMPBUTTON			PB1 - PRESSBUTTON			PB2 ALTBUTTON
		if(GPIOB->IDR & GPIO_IDR_ID0){			// PB0
			LCD_CLEAR_DISPLAY();
			title = 0;
			tempButton = 1;
			pressButton = 0;
			altButton = 0;
		}
		if(GPIOB->IDR & GPIO_IDR_ID1){			// PB1
			LCD_CLEAR_DISPLAY();
			title = 0;
			tempButton = 0;
			pressButton = 1;
			altButton = 0;
		}
		if(GPIOB->IDR & GPIO_IDR_ID2){			// PB2
			LCD_CLEAR_DISPLAY();
			title = 0;
			tempButton = 0;
			pressButton = 0;
			altButton = 1;
		}
		if((GPIOB->IDR & GPIO_IDR_ID0) && (GPIOB->IDR & GPIO_IDR_ID1)){
			LCD_CLEAR_DISPLAY();
			title = 1;
			tempButton = 1;
			pressButton = 1;
			altButton = 0;
		}
		
		BMPMeasure();
		
		// Applying compensation formula
		calibratedTemp = (BMP_Temp_Compensation(temp) /100.0);			// Calibrated Reading
		calibratedPress = (BMP_Press_Compensation(press)/256.0);		// Calibrated Reading
		
		// Calculating Altitude from sea level considering sea-level pressure p0 = 101325;
		calibratedAlt = (((double)(pow((p_reference/calibratedPress), 0.1903)) - 1.0) * (calibratedTemp + 273.15)) / 0.0065;
		
		/*
		if(p_reference > 0){
			calibratedAlt = (double)(1.0 - pow(((calibratedPress)/(p_reference)), 0.1903)) * (double)4433076.0;
			calibratedAlt = (calibratedAlt/10)*(1);
			//calibratedAlt = ;
		}*/
		
		// buffer to store the data to be shown Via UART in Terminal
		char str[50];
		UART2_SendString((uint8_t *)"Sensor Reading :");
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		sprintf(str, "%.2lf", calibratedTemp);
		UART2_SendString((uint8_t *)"TEMP  : ");
		UART2_SendString((uint8_t *)str);
		UART2_SendString((uint8_t *)" DegC");
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		sprintf(str, "%.2lf", calibratedPress);
		UART2_SendString((uint8_t *)"PRESS : ");
		UART2_SendString((uint8_t *)str);
		UART2_SendString((uint8_t *)" Pa");
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		sprintf(str, "%.2lf", calibratedAlt);
		UART2_SendString((uint8_t *)"ALT   : ");
		UART2_SendString((uint8_t *)str);
		UART2_SendString((uint8_t *)" m");
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		UART2_SendChar(NL);		// 10 is the ASCII for newline
		
		
		/**** Send Data to LCD according to button pressed ***/
		/*// Temperature
		if(tempButton && !pressButton && !altButton){
			if(!title){
				title = 1;
				LCD_SEND_STRING("TEMP: ");
			}
			// Send Temperature Measurement to the LCD Display
			LCD_SEND_FLOAT_NUM(calibratedTemp);
		}
		// Pressure
		else if(pressButton && !tempButton && !altButton){
			if(!title){
				title = 1;
				LCD_SEND_STRING("PRES: ");
			}
			// Send Pressure Measurement to the LCD Display
			LCD_SEND_FLOAT_NUM(calibratedPress);
		}
		// Altitude
		else if(altButton && !tempButton && !pressButton){
			if(!title){
				title = 1;
				LCD_SEND_STRING("ALT: ");
			}
			// Send Alitude Measurement to the LCD Display
			LCD_SEND_FLOAT_NUM(calibratedAlt);
		}
		else if(tempButton && pressButton && !altButton){					// Send Data to LCD Periodically
			LCD_SEND_STRING("TEMP: ");
			LCD_SEND_FLOAT_NUM(calibratedTemp);
			TIMER7_Delay_ms(300);
			LCD_CLEAR_DISPLAY();
			LCD_SEND_STRING("PRESS : ");
			LCD_SEND_FLOAT_NUM(calibratedPress);
			TIMER7_Delay_ms(300);
			LCD_CLEAR_DISPLAY();
			LCD_SEND_STRING("ALT: ");
			LCD_SEND_FLOAT_NUM(calibratedAlt);
			TIMER7_Delay_ms(300);
			LCD_CLEAR_DISPLAY();
		}
		else{
			LCD_SEND_STRING("PRESS BUTTON");
			TIMER7_Delay_s(1);
			LCD_CLEAR_DISPLAY();
		}*/
		
		// Clear UIF FLag
		TIM6->SR &= ~(TIM_SR_UIF);
	}
}

// BMP measure
void BMPMeasure(void){
	
	// Control Byte holding the Register Address and RW bit (1)
	uint8_t controlByte = 0xF7;
	
	/*** Trying to Read the measurement Registers From 0xF7 to 0xFC ***/
	SPI2_TRANSMIT_MULTI_BYTE_READ(controlByte, RXBuf, 6);
	
	temp = (RXBuf[3] << 12) | (RXBuf[4] << 4) | (RXBuf[5] >> 4);			// MSB part [19:12] // LSB part [11:4] // XLSB part [3:0]
	press = (RXBuf[0] << 12) | (RXBuf[1] << 4) | (RXBuf[2] >> 4);			// MSB part [19:12] // LSB part [11:4]
	
}

// Calculating p_reference: use few samples of pressure and calculate the average. Assuming delay_ms is delay between each measurement.
double BMP_SetRefPressure(int samples, int delay_ms){
	
	double sum = 0.0;
	
	for(int i=0; i<samples; i++){
		BMPMeasure();
		calibratedTemp = (BMP_Temp_Compensation(temp)/100.0);
		calibratedPress = (BMP_Press_Compensation(press)/256.0);
		if(calibratedPress < 100000){
			--i;
			continue;
		}
		sum += calibratedPress;
		TIMER7_Delay_ms((uint16_t)delay_ms);
	}
	return (sum/samples);
}

// Trimming Parameter Readout
void trimmingParameterReadout(){
	
	/*** Trying to Read the Calibration Registers From 0x88 to 0x9F ***/
	// Control Byte holding the Register Address and RW bit (1)
	SPI2_TRANSMIT_MULTI_BYTE_READ(0x88, calib, 24);			// size = 24
	
	// dig_T1 to dig_T3 maps to 0x88 to 0x8D (array index 0-5)
	// dig_P1 to dig_P9 maps to 0x8E to 0x9F (array index 6-23)
	// dig_H1 to dig_H6 maps to 0xA1 (array index 24) and 0xE1 to 0xE7 (array index 25-32)
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
	
	/*
	dig_H1 = (unsigned char) 	(calib[24] << 0); 
	dig_H2 = (signed short) 	((calib[25] << 0) | (calib[26] << 8));
	dig_H3 = (unsigned char) 	(calib[27] << 0);
	dig_H4 = (signed short) 	((calib[28] << 4) | (calib[29] << 0));
	dig_H5 = (signed short) 	((calib[30] << 0) | (calib[31] >> 4));
	dig_H6 = (signed char) 		(calib[32] << 0);*/
	
}


// BME280 Mode of Operation
void BME280_INDOOR_NAVIGATION(void){			// Indoor Navigation Mode
	
	/*****
				Sensor mode = normal mode, tStandby = 0.5 ms
				Oversampling settings = pressure ×16, temperature ×2, humidity ×1
				IIR filter settings = filter coefficient 16
	*****/
	
	// Read id register
	uint8_t idRead = SPI2_TRANSMIT_CONTROL_BYTE_SINGLE_BYTE_READ(id);
	// Display the Chip id
	char idBuf[5];
	sprintf(idBuf, "%x", idRead);
	UART2_SendString((uint8_t *)" CHIP ID : 0x");
	UART2_SendString((uint8_t *)idBuf);
	UART2_SendChar(0xA);
	UART2_SendChar(0xA);
	LCD_SEND_STRING("CHIP ID : 0x");
	LCD_SEND_STRING(idBuf);

	// Power On Reset write 0xB6 in register reset (0xE0)
	SPI2_TRANSMIT_WRITE(0xE0, 0xB6);			// write 0xB6 in the reset_register 0xE0
	TIMER7_Delay_ms(1);
	
	// IIR Filter settings in the 0xF5 config register ( t_sb[2:0] (standby time), filter[2:0], spi3w_en[0](3 wire spi) )  
	SPI2_TRANSMIT_WRITE(0xF5, 0x10);			// write 0x10 in the config register 0xF5 to set filter coefficient 16 and standby time 0.5
	
	// Control Byte 0x74 to write in the ctrl_meas Register (0xF4 register contains osrs__t and osrs_p)
	SPI2_TRANSMIT_WRITE(0xF4, 0x57);			// 0x57 to select mode as normal mode and select oversampling of pressure x16 and temperature measurement as x2
	
	// READING BACK THE REGISTER 0xF4 THERE SHOULD CHANGES IN THE FIRST TWO BITS, THEY SHOULD BE ONE AS WE ARE WRITING 3 TO THE REGISTER
	//SPI2_TRANSMIT_CONTROL_BYTE_SINGLE_BYTE_READ(0xF4);
	
	TIMER7_Delay_ms(300);
}


// Defined in data sheet
// Temperature Compensation Function return 32 bit value
int32_t BMP_Temp_Compensation(int32_t adc_T){
	int32_t var1, var2,T;
	var1 = ((((adc_T>>3) - ((int32_t) dig_T1<<1))) * ((int32_t) dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((int32_t)dig_T1))*((adc_T>>4) -
	((int32_t)dig_T1)))>>12)*((int32_t)dig_T3))>>14;
	t_fine =var1+var2;
	T = (t_fine*5+128)>>8;
	return T;
}


// Defined in data sheet
// Pressure Compensation -- return 64-bit value
uint32_t BMP_Press_Compensation(int32_t adc_P){
	int64_t var1,var2,p;
	var1 = (int64_t) t_fine - 128000;
	var2 = var1 * var1 * (int64_t) dig_P6;
	var2 = var2 + ((var1*(int64_t)dig_P5)<<17);
	var2 = var2 + (((int64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (int64_t)dig_P3)>>8)+((var1 * (int64_t)dig_P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
	if(var1 == 0 ) return 0;
	p = 1048576 - adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)dig_P8) * p)>>19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
	return (uint32_t)p;
}




