#include "LCD_DRIVER.h"

#define NL 10
#define BME280_Chip_Address 0x76

// “BME280_S32_t” should define a 32 bit signed integer variable type and can usually be defined as “long signed int”
typedef long signed int BME280_S32_t;
// “BME280_U32_t” should define a 32 bit unsigned integer variable type and can usually be defined as “long unsigned int”
typedef long unsigned int BME280_U32_t;
// “BME280_S64_t” should define a 64 bit signed integer variable type, which on most supporting platforms can be defined as “long long signed int”
typedef long long signed int BME280_S64_t;

// t_fine carries fine temperature as global value
extern BME280_S32_t t_fine;

// Raw and Calibrated Reading variables
extern int temp;
extern int press;
extern int hum;
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

// Tim7 Update Interrupt. An update event is set to occur every 1 second
void TIM7_IRQHandler(void);

// Measurement of Temperature and Pressure values
void BMPMeasure(void);

// Calculating p_reference: use few samples of pressure and calculate the average. Assuming delay_ms is delay between each measurement.
double BMP_SetRefPressure(int samples, int delay_ms);

// I2C1 Reception Interrupt Handler
void I2C1_EV_IRQHandler(void);

// Trimming Parameter Readout
void trimmingParameterReadout(void);

// Read ChipID on register 0xD0
void READ_SENSOR_ID(void);

// Compensation Formulas
BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T);
BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P);
BME280_U32_t bme280_compensate_H_int32(BME280_S32_t adc_H);

// RXBuf is the Reception Buffer and RXBufIndex is the index
extern uint8_t RXBuf[50];
extern int RXBufIndex;

void readTrimmingParameters(void);			// Read trimming parameters
void BME280Config(void);								// Set Indoor Navigation as Mode of Operation 
