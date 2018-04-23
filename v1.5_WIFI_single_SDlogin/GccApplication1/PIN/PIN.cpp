/*
	SOCAAR Project
	ATMEGA64 PIN CONFIGURATION FILE for AVR
	
	Created by: Tae Young Goh
	Date: August 27, 2014
	Comment: 
	- Configure all the pins here for each specific board
*/

#include "PIN.h"
#include <avr/io.h>

void pin_setup(void)
{
	// Pin Setup
	// Set Ports as Output
	
	//DDRA = (1 << C_2610) | (1 << C_880) | (1 << C_706) | (1 << SS0) | (1 << SS1) | (1 << SS2) | (1 << SS3);
	DDRA = (1 << MUX0_S3) | (1 << MUX0_S2) | (1 << MUX0_S1) | (1 << MUX0_S0) | (1 << GP2Y1010_2_CTRL) | (1 << GP2Y1010_1_CTRL);
	// Set Initial Value. 0 to Control pin means turning sensor on.
	//PORTA = (1 << C_2610) | (0 << C_880) | (1 << C_706) | (0 << SS0) | (0 << SS1) | (0 << SS2) | (0 << SS3);
	PORTA = (0 << MUX0_S3) | (0 << MUX0_S2) | (0 << MUX0_S1) | (0 << MUX0_S0) | (0 << GP2Y1010_2_CTRL) | (0 << GP2Y1010_1_CTRL);
	
	// port b is used for the SD card
	DDRB = (1 << SPI_CS_N) | (1 << SPI_CLK) | (1 << SPI_MOSI) | (0 << SPI_MISO) | (0 << SD_DETECT_3V3);
	PORTB = (1 << SPI_CS_N) | (1 << SPI_CLK);
	PORTB &= ~(1 << SPI_MOSI);

	DDRC = 0;
	PORTC = 0;

	//DDRD = (1 << SCL) | (1 << SDA) | (1 << C_FAN) | (1 << SHP_D) | (0 << PPD) | (0 << DHT_PIN) | (1 << C_MQ3) | (1 << C_24);
	DDRD = (1 << I2C_SCL) | (1 << I2C_SDA) | (1 << USART1_PWR_EN);
	PORTD = (1 << I2C_SCL) | (1 << I2C_SDA) | (1 << USART1_PWR_EN);

	DDRE = (0 << PPD42_SNS) | (0 << DHT22_1_SNS) | (0 << DHT22_2_SNS) | (1 << USART0_PWR_EN);
	PORTE = (1 << DHT22_1_SNS) | (1 << DHT22_2_SNS) | (0 << USART0_PWR_EN);
	//PORTE = (0 << PRG4) | (0 << PRG3) | (0 << PRG2) | (0 << PRG1);
	
	DDRF = (0 << GP2Y010_1_SNS) | (0 << GP2Y010_2_SNS) | (0 << TGS2600_SNS) | (0 << MUX0_OUT);
	
	
}
