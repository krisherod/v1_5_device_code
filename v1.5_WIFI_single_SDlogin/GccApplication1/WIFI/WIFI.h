/* 
* WIFI.h
*
* Created: 5/5/2016 4:26:56 PM
* Author: Kris
*/


#define F_CPU 8000000UL  // this is the frequency of the
#define data_length 100 //default length of the data array

// controls for the usart0 power
#define USART0_OFF PORTE |= (1 << USART0_PWR_EN)
#define USART0_ON PORTE &= ~(1 << USART0_PWR_EN)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <util/atomic.h>

#ifndef __WIFI_H__
#define __WIFI_H__

#include "../USART/USART.h"
#include "../SD/SDMacro.h"
#include "../SD/ff.h"


class WIFI
{
//variables
public:
protected:
private:

//functions
public:
	WIFI();

	int setupWifi(USART *fUSART, char *USERNAME, char *PASSWORD);
		
	int connect(USART *fUSART);
	int checknetwork(USART *fUSART, char *network_name, int network_len); // this function is to check if there are any networks are around

	int sendSpecial(USART* fUSART);
		
	int send_multipart(FIL cFIL, SDMacro* fSDMacro, USART* fUSART, char* filename, int lines, int FILE_len[100]);
	int send_application(USART* fUSART, char *BUFFER, int BUFFER_len, char *HEADER, int HEADER_len);

	int POST_single(USART* fUSART, char *post_len, char *body_len, char *BUFFER, char *HEADER);
	int POST(FIL cFIL, SDMacro* fSDMacro, USART* fUSART, char* filename, char *post_len, char *body_len, int file_index, int remainder);

	int checkRX(USART* fUSART, char *substring1, int string_length1, char *substring2, int string_length2, int TIMEOUT);


protected:
private:
	WIFI( const WIFI &c );
	WIFI& operator=( const WIFI &c );

}; //WIFI

#endif //__WIFI_H__
