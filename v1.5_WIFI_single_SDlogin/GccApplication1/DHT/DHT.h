/*
* DHT.h
*
* Created: 31/08/2015 1:04:21 PM
* Author: Aluminum
*/

#ifndef __DHT_H__
#define __DHT_H__

#define F_CPU 8000000UL

#include "../PIN/PIN.h"
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>

class DHT
{
	//functions
	public:
	DHT();
	int returnTemperatureHumidity(int pin, uint16_t *temperature, uint16_t *humidity);
	
	private:
	uint16_t startSignal(int pin, uint16_t *temperature, uint16_t *humidity);
	uint8_t bitValue[5];
	uint8_t timeout = 200;
	
}; //DHT

#endif //__DHT_H__
