/*
* GPRS.h
*
* Created: 1/25/2016 2:22:23 PM
* Author: Kris
*/

#define F_CPU 8000000UL  // this is the frequency of the

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "../USART/USART.h"

#define data_length 100 //default length of the data array

#ifndef __GPRS_H__
#define __GPRS_H__

#include "../USART/USART.h"
#include "../SD/SDMacro.h"

class GPRS
{
	//variables
	public:

	protected:
	private:



	//functions
	public:
	GPRS();
	int setupGPRS(USART *fUSART);
	int setupWifi(USART *fUSART);
	
	int connect(USART *fUSART);
	
	int checknetwork(USART *fUSART, char *network_name, int network_len); // this function is to check if there are any networks are around
	
	int sendGPRS(SDMacro* fSDMacro, USART* fUSART, char* BUFFER);
	
	//int SendToUSARTGPRS(USART* fUSART, char command[100]);
	int sendSpecial(USART* fUSART);
	
	int sendGPRS_multipart(FIL cFIL, SDMacro* fSDMacro, USART* fUSART, char* filename, int lines, int FILE_len[100]);
	int POST(FIL cFIL, SDMacro* fSDMacro, USART* fUSART, char* filename, char *post_len, char *body_len, int file_index, int remainder);
	
	int receive(USART* fUSART);
	int checkRX(USART* fUSART, char *substring, int string_length, int TIMEOUT);
	
	private:
	

	//USART fUSART;
	//SDMacro fSDMacro;
	
	//GPRS( const GPRS &c );
	//GPRS& operator=( const GPRS &c );

}; //GPRS

#endif //__GPRS_H__
