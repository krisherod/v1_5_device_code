/* 
* RTC.cpp
*
* Created: 29/08/2015 5:47:19 PM
* Author: Aluminum
*/

#include <avr/io.h>
#include <util/twi.h>
#include "RTC.h"


// default constructor
RTC::RTC()
{
} //RTC

int RTC::Initialize(void)
{
	TWBR = TWBR_val;
	return 0;
}

uint8_t RTC::Read(I2C* fI2C, uint8_t address)
{

	fI2C->Start(); // first i start the I2C
	fI2C->SLAT(SLA+WRITE); // then I input the address plus the write bit
	fI2C->Write(address); // then i put the address that i want to read
	fI2C->RStart(); // then i do a repeat start
	fI2C->SLAR(SLA+READ); // then i input the address plus the read bit
	uint8_t data = fI2C->Read_NAck(); // then i actually read the data from that address
	fI2C->Stop(); // then i stop the service
	return data; // then I return the data
}

int RTC::Write_RStart(I2C* fI2C, uint8_t address, uint8_t datetime)
{
	fI2C->RStart();
	fI2C->SLAT(SLA+WRITE);
	fI2C->Write(address);
	fI2C->Write(datetime);
	return 0;
}

int RTC::Write_Start(I2C* fI2C, uint8_t address, uint8_t datetime)
{
	fI2C->Start();
	fI2C->SLAT(SLA+WRITE);
	fI2C->Write(address);
	fI2C->Write(datetime);
	return 0;
}

int RTC::Write_Stop(I2C* fI2C, uint8_t address, uint8_t datetime)
{
	fI2C->Start();
	fI2C->SLAT(SLA+WRITE);
	fI2C->Write(address);
	fI2C->Write(datetime);
	fI2C->Stop();
	return 0;
}

int RTC::Set_Time(I2C* fI2C, uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
	Write_Stop(fI2C, 0x08, 0x40); // this is to enable writing to the RTC
	Write_Stop(fI2C, 0x05, year); // this is to input the year
	Write_Stop(fI2C, 0x04, month);
	Write_Stop(fI2C, 0x03, day);
	Write_Stop(fI2C, 0x02, (0x80 | hour));
	Write_Stop(fI2C, 0x01, minute);
	Write_Stop(fI2C, 0x00, second);
	return 0;
}