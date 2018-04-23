/*
* ADCLIB.h
*
* Created: 27/08/2015 12:15:03 PM
* Author: Aluminum
*/

//#define F_CPU 8000000  // this is the frequency of the
#define FOSC 8000000

#include <avr/io.h>

#ifndef __ADCLIB_H__
#define __ADCLIB_H__

//#define M0 3
//#define M1 4
//#define M2 5
//#define M3 6

class ADCLIB
{
	public:
	ADCLIB();
	int	Initialize(void);
	int choose_ADC(uint8_t num_adc);
	uint32_t read_mux_sensors(int select);
	uint32_t read_sharp(int ADC_pin, int pin);
	uint32_t read_tgs(int ADC_pin);

};

#endif //__ADCLIB_H__
