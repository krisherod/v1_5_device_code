/*
	SOCAAR Project
	ATMEGA64 Timer Library for AVR
	
	Created by: Tae Young Goh
	Date: August 28, 2014
	Comment:
	- Timing counter for millis()
	- Timing counter for pulsewidth() for Shinyei sensors
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "TIMER2.h"

#define F_CPU 8000000UL
// Calculate the value needed for
// the CTC match value in OCR1A.
//#define CTC_MATCH_OVERFLOW (2*F_CPU / 1024) - 1
#define CTC_MATCH_OVERFLOW ((F_CPU / 1024) / 8)


volatile int flag2 = 0;
volatile uint16_t fall_edge = 0;
volatile uint16_t rise_edge = 0;

unsigned long sny_lowocc_us = 0; // sum of time spent LOW

volatile unsigned long timer1_millis;
unsigned long millis_return;




ISR (TIMER1_COMPA_vect)
{
	timer1_millis++;
}


ISR(TIMER1_CAPT_vect)
{
	if (flag2 == 0)  //falling edge
	{
		fall_edge = ICR1; //save fall edge time to input capture register
		TCCR1B |= (1<<ICES1); //change input capture edge select on rising edge
	}
	if (flag2 == 1) //rising edge
	{
		rise_edge = ICR1; //save rise edge time to input capture register
		TCCR1B &= ~(1<<ICES1); //change input capture edge select on falling edge
		TIMSK &= ~(1<<TICIE1); //disable input capture interrupt
	}
	
	flag2++; //increment flag
	
	if (flag2 >= 2)
	{
		//	PORTE ^= (1 << 2);
		unsigned long sny_duration = 0;
		
		sny_duration = rise_edge - fall_edge;
		sny_lowocc_us += sny_duration;
		
		flag2 = 0;
		TIFR = (1 << ICF1);
		TIMSK |= (1 << TICIE1);
		TCCR1B |= (1 << ICNC1);
		TCCR1B &= ~(1 << ICES1);
	}
}




TIMER2::TIMER2()
{
	
}


unsigned long TIMER2::get_sample()
{
	unsigned long temp = sny_lowocc_us;
	sny_lowocc_us = 0;
	return temp;
}



int TIMER2::initialize(void)
{
	// Timer1 Enable
	// CTC mode, Clock/8
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << ICNC1); //taes way
	//TCCR1B |= (1<<CS10) | (1<<CS12) | (1<<WGM12) | (1 << ICNC1);
	
	TCCR1B &= ~(1 << ICES1);	// Falling Edge
	
	// Load the high byte, then the low byte
	// into the output compare
	OCR1AH = (CTC_MATCH_OVERFLOW >> 8);
	OCR1AL = CTC_MATCH_OVERFLOW;

	// Enable the compare match interrupt and input capture
	TIMSK |= (1 << OCIE1A) | (1 << TICIE1);

	// Input capture interrupt enable
	TIFR |= (1 << ICF1);
	
	return 0;
}



unsigned long TIMER2::millis(void)
{
	// Ensure this cannot be disrupted
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		millis_return = timer1_millis;
	}
		
	return millis_return;
}


unsigned long TIMER2::check_ICP(void)
{
	unsigned long sny_duration = 0;
	if (flag2 >= 2)
	{
	//	PORTE ^= (1 << 2);
		sny_duration = rise_edge - fall_edge;
		flag2 = 0;
		TIFR = (1 << ICF1);
		TIMSK |= (1 << TICIE1);
		TCCR1B |= (1 << ICNC1);
		TCCR1B &= ~(1 << ICES1);
	}	
	return sny_duration;
}
