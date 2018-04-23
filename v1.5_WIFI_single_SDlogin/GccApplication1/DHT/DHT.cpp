/*
* DHT.cpp
*
* Created: 31/08/2015 1:04:21 PM
* Author: Aluminum
*/
//#define F_CPU 8000000UL


#include "DHT.h"

// default constructor
DHT::DHT()
{
} //DHT

uint16_t DHT::startSignal(int pin, uint16_t *temperature, uint16_t *humidity)
{
	//reset port maybe; the data register has be be set as output and the pin high
	DDRE |= (1 << pin); //output
	PORTE |= (1 << pin); //high
	_delay_ms(250);
	
	//start to send the request//
	PORTE &= ~(1 << pin); //set the pin to low
	_delay_ms(20); //wait for atleast 1 ms
	
	PORTE |= (1 << pin); //then set DHT pin to high
	DDRE &= ~(1 << pin); //set the pin to input because it should start to rx info from the sensor
	
	_delay_us(40); //then wait for 40 us
	//if ((PIND & (1<<DHT_PIN))) LED_ON; //check if the pin is high; it should be low
	
	_delay_us(80); // delay for 80 us until the sensor pulls up
	if (!(PINE & (1 << pin))) return 0; //check if the pin is low; it should be high
	
	_delay_us(80); // delay another 80 us until the sensor starts to transmit data
	if ((PINE & (1 << pin))) return 0;
	
	memset(bitValue, 0, sizeof(bitValue)); // reset the all the values to 0
	uint16_t timecount = 0; //reset the timeout
	
	for (int i=0; i<5; i++)
	{
		uint8_t value = 0; // this value holds the current 8 bits of data
		for (int j=0; j<8; j++)
		{
			timecount=0;
			
			while (!(PINE & (1 << pin))) //i will wait until the pin is not low anymore
			{
				timecount ++;
				if (timecount > timeout) return 0;
			}
			
			_delay_us(30); //wait for 30 us to see if the pin is high or low
			if (PINE & (1 << pin)) value |= (1<<(7-j)); //this is where i add the bits to the result; i left shift the bit by whatever bit it is supposed to be on so that it becomes an 8 bit number
			timecount=0;
			
			while (PINE & (1 << pin)); //wait until the pin is low
			{
				timecount ++;
				if (timecount > timeout) return 0;
			}
		}
		bitValue[i] = value;
	}
	
	//reset the port
	DDRE |= (1 << pin); //output
	PORTE |= (1 << pin); //high
	_delay_us(100);
	
	//now check the sum of the
	uint16_t temperature_raw;
	uint16_t humidity_raw;
	
	if ((uint8_t)(bitValue[0] + bitValue[1] + bitValue[2] + bitValue[3]) == bitValue[4]) // this has to be an unsigned int to work
	{
		humidity_raw = bitValue[0]<<8 | bitValue[1];
		*humidity = ((humidity_raw)/10.0);
		
		//temperature_raw = bitValue[3];
		//temperature_raw |= (bitValue[2]<<8); // alternative way of doing things
		
		temperature_raw = bitValue[2]<<8 | bitValue[3];
		*temperature = ((temperature_raw)/10.0);
	}
	
	else return 0;
}


int DHT::returnTemperatureHumidity(int pin, uint16_t *temperature, uint16_t *humidity)
{
	return startSignal(pin, temperature, humidity);
}



