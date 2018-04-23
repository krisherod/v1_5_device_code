/*
* USART.cpp
*
* Created: 27/08/2015 12:19:45 PM
* Author: Aluminum
*/

#include "USART.h"




// default constructor
USART::USART()
{
} //USART


int USART::Initialize1(unsigned int ubrr)
{
	UBRR1H = (unsigned char) (ubrr>>8); //last 4 values of the baud rate
	UBRR1L = (unsigned char) ubrr; // first 8 values of the baud rate
	
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);// | (1 << RXCIE1); // initialize tx and rx in the register
	UCSR1C = (1 << USBS1) | (3 << UCSZ10); // set the number of stop bits to 2 and the number of data bits to 8
	return 0;
}

int USART::Initialize0(unsigned int ubrr)
{
	UBRR0H = (unsigned char) (ubrr>>8); //last 4 values of the baud rate
	UBRR0L = (unsigned char) ubrr; // first 8 values of the baud rate
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);// | (1<<RXCIE0); // initialize tx and rx in the register
	//UCSR0B |= (1 << RXCIE0);
	
	UCSR0C = (1 << USBS0) | (3 << UCSZ00); // set the number of stop bits to 2 and the number of data bits to 8
	return 0;
}



int USART::Transmit1(unsigned char data)
{
	//if (!isalnum(data) || data != ',' || data != '\n' || data != '"' || data != ':' || data != '-') return 0;
	
	while (!(UCSR1A & (1 << UDRE1))); //wait for status flag to say that it is ready to send
	UDR1 = data; // make the UDR pin set to the data so that it will send - has to be 8 bits
	
	//UCSR0B |= (1<<UDRIE0);
	return 0;
}

int USART::Transmit0(unsigned char data)
{
	//if (!isalnum(data) || data != ',' || data != '\n' || data != '"' || data != ':' || data != '-') return 0;
	
	while (!(UCSR0A & (1 << UDRE0))); //wait for status flag to say that it is ready to send
	UDR0 = data; // make the UDR pin set to the data so that it will send - has to be 8 bits
	
	//UCSR0B |= (1<<UDRIE0);
	return 0;
}



char USART::Receive1(void)
{
	char ReceivedByte;
	
	while (!(UCSR1A & (1 << RXC1))); // do nothing until the data has been recieved
	ReceivedByte = UDR1; // put the byte into the variable
	
	return ReceivedByte;
	
}

char USART::Receive0(void)
{
	char ReceivedByte;
	
	while (!(UCSR0A & (1 << RXC0))); // do nothing until the data has been recieved
	ReceivedByte = UDR0; // put the byte into the variable
	
	return ReceivedByte;
	
}



int USART::available1(void)
{
	return (UCSR1A & (1 << RXC1));
}

int USART::available0(void)
{
	return (UCSR0A & (1 << RXC0));
}



int USART::sendToUSART1(char* BUFFER)
{
	//memset(BUFFER, 0, data_length);
	int index = 0;
	while (BUFFER[index] != 0)
	{
		Transmit1(BUFFER[index]);
		index++;
	}
	return 0;
	//memset(BUFFER, 0, data_length);
}

int USART::sendToUSART0(char* BUFFER)
{
	//memset(BUFFER, 0, data_length);
	int index = 0;
	while (BUFFER[index] != 0)
	{
		Transmit0(BUFFER[index]);
		index++;
	}
	return 0;
	//memset(BUFFER, 0, data_length);
}


//ISR(USART0_UDRE_vect)
//{
//	UCSR0B &= ~(1<<UDRIE0);
//}

