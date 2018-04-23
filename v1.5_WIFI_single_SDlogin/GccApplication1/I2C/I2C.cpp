/*
* I2C.cpp
*
* Created: 29/08/2015 5:29:44 PM
* Author: Aluminum
*/

#include <avr/io.h>
#include <util/twi.h>
#include "I2C.h"

#define START 0x08
#define RSTART 0x10

int flag;

// default constructor
I2C::I2C()
{
} //I2C

int I2C::ERROR()
{
	uint8_t flag = 1;
	UDR1 = 'f';
	return flag;
}



int I2C::Initialize(void)
{
	TWBR = TWBR_val;
	return 0;
}



int I2C::Start()
{
	
	TWCR = 0;
	//set the start condition
	//TWINT is the flag, this must be set to 1 because it will become 0 when the start condition is met
	//TWSTA is to start, TWEN is to enable
	
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	//wait for the TWINT flag set which tells if the start condition has been transmitted
	while (!(TWCR & (1<<TWINT)));
	//check the TWI status
	if ((TWSR & 0xF8) != TW_START) ERROR();
	
	return 0;
}

int I2C::RStart()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != RSTART) ERROR(); //the only difference between this and a normal start is that the status is different
	return 0;
}

int I2C::SLAT(uint8_t SLA_W)
{
	
	//this is where I input the address of the slave
	TWDR = SLA_W;
	//clear the TWINT bit in the
	TWCR = (1<<TWINT) | (1<<TWEN);
	//wait for the TWINT flag to indicate that the slave address has been sent
	while (!(TWCR & (1<<TWINT)));
	//check that the slave address was received, otherwise reference the ERROR function
	if ((TWSR & 0xF8) != TW_MT_SLA_ACK) ERROR();
	return 0;
}

int I2C::SLAR(uint8_t SLA_W)
{
	//this is where I input the address of the slave
	TWDR = SLA_W;
	//clear the TWINT bit in the
	TWCR = (1<<TWINT) | (1<<TWEN);
	//wait for the TWINT flag to indicate that the slave address has been sent
	
	while (!(TWCR & (1<<TWINT)));
	
	//check that the slave address was received, otherwise reference the ERROR function
	if ((TWSR & 0xF8) != TW_MR_SLA_ACK) ERROR();
	return 0;
}

int I2C::Write(uint8_t data)
{
	//load the data into the TWDR register
	TWDR = data;
	//clear the TWINT bit
	TWCR= (1<<TWINT) | (1<<TWEN);
	//wait for the TWINT flag to indicate that the process was completed
	while (!(TWCR & (1<<TWINT)));
	//check that the data was sent
	if ((TWSR & 0xF8) != TW_MT_DATA_ACK) ERROR();
	return 0;
}


uint8_t I2C::Read_Ack(void)
{
	//need to write the TWEA ack so that the slave knows that you want to read another byte after
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	
	//wait for transmission
	while(!(TWCR & (1<<TWINT)));
	//make sure that the status register confirms that data was received
	if ((TWSR & 0xF8) != TW_MR_DATA_ACK) ERROR();
	return TWDR;
}

uint8_t I2C::Read_NAck(void)
{
	
	//need to write the TWEA ack so that the slave knows that you want to read another byte after
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	//wait for transmission
	while(!(TWCR & (1<<TWINT)));
	//make sure that the status register confirms that data was received
	if ((TWSR & 0xF8) != TW_MR_DATA_NACK) ERROR();
	return TWDR;
}

void I2C::Stop(void)
{
	//transmit the stop condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

