/*
* USART.h
*
* Created: 27/08/2015 12:19:45 PM
* Author: Aluminum
*/

#define F_CPU 8000000UL  // this is the frequency of the
#define FOSC 8000000UL

#ifndef __USART_H__
#define __USART_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

class USART {
	public:
		USART();
		int Initialize1(unsigned int ubrr);
		int Initialize0(unsigned int ubrr);
		
		int Transmit1(unsigned char data);
		int Transmit0(unsigned char data);
		
		int available1(void);
		int available0(void);
		
		int sendToUSART1(char* BUFFER);
		int sendToUSART0(char* BUFFER);
		
		char Receive1(void);
		char Receive0(void);
	
};

#endif //__USART_H__
