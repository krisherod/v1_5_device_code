/* 
* PIC.h
*
* Created: 4/7/2016 12:19:18 PM
* Author: Kris
*/


#ifndef __PIC_H__
#define __PIC_H__

#include "../I2C/I2C.h"
#define WRITE 0x00 // added to the SLA address to indicate that it is a write
#define READ 0x01

class PIC
{

//functions
public:
	PIC();
	int Set(I2C* fI2C, uint8_t address, uint8_t instruction, uint8_t voltage);
	uint8_t Read(I2C* fI2C, uint8_t address, uint8_t instruction);
	
protected:
private:
	PIC( const PIC &c );
	PIC& operator=( const PIC &c );

}; //PIC

#endif //__PIC_H__
