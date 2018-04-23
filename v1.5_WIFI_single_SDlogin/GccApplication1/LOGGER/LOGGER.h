/* 
* LOGGER.h
*
* Created: 7/8/2016 12:27:22 PM
* Author: Kris
*/


#define F_CPU 8000000UL  // this is the frequency of the

// include all libraries
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ctype.h>

#include "../ADC/ADCLIB.h"
#include "../USART/USART.h"
#include "../PIN/PIN.h"
#include "../I2C/I2C.h"
#include "../RTC/RTC.h"
#include "../TIMER/TIMER.h"
#include "../DHT/DHT.h"
#include "../SD/ff.h"
#include "../GPRS/GPRS.h"
#include "../WIFI/WIFI.h"
#include "../SD/SDMacro.h"
#include "../PIC/PIC.h"
#include "../TIMER/TIMER2.h"

#ifndef __LOGGER_H__
#define __LOGGER_H__


#define data_length 300 //default length of the data array


class LOGGER
{
//variables
public:
protected:
private:

//functions
public:
	LOGGER();
	~LOGGER();

	int readTime(RTC* pRTC, I2C* pI2C);
	int logDHT(DHT* pDHT, uint8_t address_DHT);
	int logMUX(ADCLIB* pADCLIB);
	int logADC(ADCLIB* pADCLIB, uint8_t address_ADC, uint8_t ctrl);
	int logTGS(ADCLIB* pADCLIB, uint8_t address_TGS);
	int logSINYEI(USART* pUSART, unsigned long lowocc_us, unsigned long sampletime_ms);

	int logALL(USART* pUSART, RTC* pRTC, I2C* pI2C, DHT* pDHT, ADCLIB* pADC);

	int send_to_USART(USART* pUSART);
	int send_to_SD(USART* pUSART, SDMacro* pSDMacro, FIL* file, char* filename);
	int send_to_WIFI(WIFI* pWIFI, USART* pUSART, char* HEADER, int HEADER_len);

	int resetBUFFER(void);
	int preSEND(USART* pUSART);


protected:
private:
	LOGGER( const LOGGER &c );
	LOGGER& operator=( const LOGGER &c );

	// function FLAGS
	uint8_t readTime_FLAG;
	uint8_t logDHT_FLAG;
	uint8_t logMUX_FLAG;
	uint8_t logADC_FLAG;
	uint8_t logTGS_FLAG;
	uint8_t logSINYEI_FLAG;
	uint8_t send_to_WIFI_FLAG;
	uint8_t send_to_SD_FLAG;
	uint8_t send_to_USART_FLAG;

	int sensors[16];
	char BUFFER [data_length]; // empty data char array that will be populated with data which will be sent over the UART
	char BUFFER_sd[data_length]; // this contains a newline

	char SINYEI[data_length];
	volatile uint8_t SINYEI_logged = 0;

	uint32_t sharp;
	uint32_t mux;

	volatile unsigned long sny_lowocc_us_main = 0; // sum of time spent LOW

	// set the device_id here
	int device_id = 24;

}; //LOGGER

#endif //__LOGGER_H__
