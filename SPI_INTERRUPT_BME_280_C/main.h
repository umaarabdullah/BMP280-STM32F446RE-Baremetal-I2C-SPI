#include "SPI_MASTER.h"
#include "math.h"

#define NL 10

/********** BME280 Register Read Addresses *********/

#define hum_lsb 		0xFE
#define hum_msb 		0xFD
#define temp_xlsb 	0xFC
#define temp_lsb 		0xFB
#define temp_msb 		0xFA
#define press_xlsb 	0xF9
#define press_lsb 	0xF8
#define press_msb 	0xF7
#define config 			0xF5
#define ctrl_meas 	0xF4
#define status 			0xF3
#define ctrl_hum 		0xF2
#define reset 			0xE0
#define id 					0xD0

/********** BME280 Register write Addresses *********/

/********** BME Register Settings Data To Write *********/

// “BME280_S32_t” should define a 32 bit signed integer variable type and can usually be defined as “long signed int”
typedef long signed int BME280_S32_t;
// “BME280_U32_t” should define a 32 bit unsigned integer variable type and can usually be defined as “long unsigned int”
typedef long unsigned int BME280_U32_t;
// “BME280_S64_t” should define a 64 bit signed integer variable type, which on most supporting platforms can be defined as “long long signed int”
typedef long long signed int BME280_S64_t;

// t_fine carries fine temperature as global value
extern BME280_S32_t t_fine;

// Status Flag
extern int statusFlag;

// Raw and Calibrated Reading variables
extern int temp;
extern int press;
extern double calibratedTemp;
extern double calibratedPress;
extern double calibratedAlt;

// Flags for measurement button for LCD Display
extern uint8_t tempButton; 			// By default LCD will show Temp
extern uint8_t pressButton;
extern uint8_t altButton;

// Flag for title
extern uint8_t title;

// Refernce Pressure - Average of measured pressure values. Suppose 100 samples.
extern double p_reference;

// Trimming Parameters
// For Temperature
extern unsigned short dig_T1;
extern signed short dig_T2;
extern signed short dig_T3;
// For Pressure
extern unsigned short dig_P1;
extern signed short dig_P2;
extern signed short dig_P3;
extern signed short dig_P4;
extern signed short dig_P5;
extern signed short dig_P6;
extern signed short dig_P7;
extern signed short dig_P8;
extern signed short dig_P9;
// For Humidity
extern unsigned char dig_H1;
extern signed short dig_H2;
extern unsigned char dig_H3;
extern signed short dig_H4;
extern signed short dig_H5;
extern signed char dig_H6;

// Trimming Flag
extern uint8_t trimming;

// Array to store the Trimming Parameters
extern uint8_t calib[40];
// Index for calib array
extern int calibIndex;

// Trimming Parameter Readout
void trimmingParameterReadout(void);

// Compensation Formulas
int32_t BMP_Temp_Compensation(int32_t adc_T);
uint32_t BMP_Press_Compensation(int32_t adc_P);

// BME280 Mode of Operation
void BME280_INDOOR_NAVIGATION(void);

// BMP measure
void BMPMeasure(void);

// Calculating p_reference: use few samples of pressure and calculate the average. Assuming delay_ms is delay between each measurement.
double BMP_SetRefPressure(int samples, int delay_ms);

// RXBuf is the Reception Buffer and RXBufIndex is the index
extern uint8_t RXBuf[50];
extern int RXBufIndex;

// Interrupt Service Routines
void SPI2_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);

