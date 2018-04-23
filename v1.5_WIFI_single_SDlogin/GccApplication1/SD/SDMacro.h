/*
* SDMacro.h
*
* Created: 1/27/2016 12:00:17 PM
* Author: Kris
*/


#ifndef __SDMACRO_H__
#define __SDMACRO_H__

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "ff.h"
#include "../USART/USART.h"

#define LED_on |

class SDMacro
{
	//variables
	public:
	protected:
	private:
	char file[20];

	//functions
	public:
	SDMacro();
	~SDMacro();
	int CheckFile(FIL cFIL, char* filename);
	int OverWrite(FIL cFIL, char* filename);
	int DeleteFile(FIL cFIL, char* filename);
	
	int SendData(FIL* cFIL, char* BUFFER, char* filename);
	int ReadSD(FIL cFIL, USART* fUSART, char* filename, int location, int lines);
	int GetFileSize(FIL cFIL, char* filename);

	int getCredentials(FIL cFIL, char* BUFFER);
	
	//int ReadLine(char *buffer);
	
	protected:
	private:

	FATFS FF;
	UINT bw;

	SDMacro( const SDMacro &c );
	SDMacro& operator=( const SDMacro &c );

}; //SDMacro

#endif //__SDMACRO_H__
