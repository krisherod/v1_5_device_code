/* 
* TIMER.cpp
*
* Created: 31/08/2015 5:10:48 PM
* Author: Aluminum
*/

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "TIMER.h"
#include "../PIN/PIN.h"

volatile uint16_t TIMER_COUNT;

// default constructor
TIMER::TIMER()
{
} //TIMER

/*
ISR(TIMER1_COMPA_vect)
{
	TIMER_COUNT++;
}
*/



int TIMER::TIMER1_init(void)
{
	// here i want to use the CTC mode which means capture and compare mode
	// I need waveform generation mode  and a clock prescaler of 8
	// note: i dont need TCCR1A because for ctc mode everything is 0
	TCCR1A |= 0;
	TCCR1B |= (1<<CS10) | (1<<CS12) | (1<<WGM12);

	
	//there is also a noise canceller but it requires 4 successive equal valued samples of the icpn pin for changing its output
	// TCCR1A |= (1<<ICNC1);
	
	//this is the value used to compare
	OCR1A = F_CPU/1024;
	
	//enamble compare interrupt
	TIMSK |= (1<<OCIE1A);
	return 0;
}
