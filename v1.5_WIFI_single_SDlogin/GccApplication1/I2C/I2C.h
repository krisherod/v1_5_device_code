/*
* I2C.h
*
* Created: 29/08/2015 5:29:44 PM
* Author: Aluminum
*/


#ifndef __I2C_H__
#define __I2C_H__

#include <avr/io.h>

#define F_CPU 8000000UL	// CPU frequency of ATMEGA64
#define F_SCL 400000UL	// SCL frequency of ISL12022
#define TWBR_val (((F_CPU / F_SCL) - 16 ) / 2)

class I2C
{
	
public:
	I2C();
	
	int Initialize(void);
	
	int Start(void);
	int RStart(void);
	int SLAT(uint8_t SLA_W);
	int SLAR(uint8_t SLA_W);
	int Write(uint8_t data);
	uint8_t Read_Ack(void);
	uint8_t Read_NAck(void);
	void Stop(void);
	int ERROR(void);
	

}; //I2C

#endif //__I2C_H__
