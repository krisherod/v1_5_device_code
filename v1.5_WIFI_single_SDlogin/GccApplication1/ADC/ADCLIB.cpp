/*
* ADCLIB.cpp
*
* Created: 27/08/2015 12:15:03 PM
* Author: Aluminum
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "ADCLIB.h"
#include "../PIN/PIN.h"

// default constructor
ADCLIB::ADCLIB()
{
} //ADCLIB


int ADCLIB::Initialize(void)
{
	ADCSRA |= (1<<ADPS1) | (1<<ADPS2) | (0<<ADPS0) | (1<<ADATE); //set the prescaler to 64
	ADMUX |= (1<<REFS0); //set the reference voltage to 5v
	ADMUX |= 0b00000001; //set the ADC channel to 1
	
	//ADCSRB = 0; // free running mode
	ADCSRB |= (1<<ADTS0); // free running mode

	//ADMUX |= (1<<ADLAR); //set the adlar to high
	ADCSRA |= (1<<ADEN); //enable ADC
	ADCSRA |= (1<<ADSC); //start ADC
	return 0;
}


int ADCLIB::choose_ADC(uint8_t num_adc)
{
	// select ADC Channel
	ADMUX &= 0xf0;
	ADMUX |= num_adc;
	//ADCSRA |= (1<<ADSC);

	return 0;
}

uint32_t ADCLIB::read_mux_sensors(int select)
{
	//ADMUX = 0b01000011;

	(select & 0b0001) ? PORTA |= (1 << MUX0_S0) : PORTA &= ~(1 << MUX0_S0);
	(select & 0b0010) ? PORTA |= (1 << MUX0_S1) : PORTA &= ~(1 << MUX0_S1);
	(select & 0b0100) ? PORTA |= (1 << MUX0_S2) : PORTA &= ~(1 << MUX0_S2);
	(select & 0b1000) ? PORTA |= (1 << MUX0_S3) : PORTA &= ~(1 << MUX0_S3);
	_delay_ms(10);	// Let digital values propagate
	
	//PORTA |= (select<<SS0);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	
	uint32_t sensor_value = ADCL;
	sensor_value |= (ADCH << 8);
	
	return sensor_value;
}


uint32_t ADCLIB::read_sharp(int ADC_pin, int pin)
{
	//first the sharp output is set to output using the direction register
	//the voltage is initially set to low
	//then before reading the ADC, the pin is set to low
	//ADMUX = 0b01000000;
	
	PORTA &= ~(1 << pin); //set the TGS2600_SNS pin to low

	ADCSRA |= (1<<ADSC);
	_delay_us(280);
	while (ADCSRA & (1<<ADSC));
	//ADMUX = ADC_pin;
	uint32_t dust_value = ADCL;
	dust_value |= (ADCH << 8);
	
	_delay_us(40);
	
	PORTA |= (1 << pin); //set the TGS2600_SNS pin to high
	
	_delay_ms(10);
	
	return dust_value;
}


uint32_t ADCLIB::read_tgs(int ADC_pin)
{
	// select ADC Channel
	//ADMUX &= 0xF8;
	//ADMUX |= (ADC_pin);
	//ADMUX = 0b01000010;
	
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));

	uint32_t tgs_value = ADCL;
	tgs_value |= (ADCH <<8);
	_delay_ms(10);
	
	return tgs_value;
}