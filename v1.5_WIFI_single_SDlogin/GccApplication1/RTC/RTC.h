/* 
* RTC.h
*
* Created: 29/08/2015 5:47:19 PM
* Author: Aluminum
*/


#ifndef __RTC_H__
#define __RTC_H__

#define F_CPU 8000000UL	// CPU frequency of ATMEGA64
#define F_SCL 400000UL	// SCL frequency of ISL12022
#define TWBR_val (((F_CPU / F_SCL) - 16 ) / 2)

#include "../I2C/I2C.h"

#define SLA 0xDE // this is the address of the slave RTC

#define WRITE 0x00 // added to the SLA address to indicate that it is a write
#define READ 0x01

class RTC
{

//functions
public:
	RTC();
	int Initialize(void);
	uint8_t Read(I2C* fI2C, uint8_t address);
	int Set_Time(I2C* fI2C, uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
	int Write_RStart(I2C* fI2C, uint8_t address, uint8_t datetime);
	int Write_Start(I2C* fI2C, uint8_t address, uint8_t datetime);
	int Write_Stop(I2C* fI2C, uint8_t address, uint8_t datetime);

}; //RTC

#endif //__RTC_H__
