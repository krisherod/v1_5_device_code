/* 
* PIC.cpp
*
* Created: 4/7/2016 12:19:18 PM
* Author: Kris
*/


#include "PIC.h"

#define RD 0b00000000
#define SLAVE 0b01011000

#define WD 0b00000000

//#define volt 0b00000111

// default constructor
PIC::PIC()
{
} //PIC


int PIC::Set(I2C* fI2C, uint8_t address, uint8_t instruction, uint8_t voltage)
{
	
	fI2C->Start();
	fI2C->SLAT(address+WRITE);
	fI2C->Write(instruction);
	fI2C->Write(voltage);
	fI2C->Stop();
	return 0;
	
}


uint8_t PIC::Read(I2C* fI2C, uint8_t address, uint8_t instruction)
{
	fI2C->Start(); // first i start the I2C
	fI2C->SLAT(SLAVE+WRITE); // then I input the address plus the write bit
	fI2C->Write(RD); // then i put the address that i want to read
	fI2C->RStart(); // then i do a repeat start
	fI2C->SLAR(SLAVE+READ); // then i input the address plus the read bit
	uint8_t data = fI2C->Read_Ack(); // then i actually read the data from that address
	fI2C->Stop(); // then i stop the service
	return data; // then I return the data
	
}