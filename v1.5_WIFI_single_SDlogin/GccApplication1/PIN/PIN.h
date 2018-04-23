/*
	SOCAAR Project
	ATMEGA64 PIN CONFIGURATION FILE for AVR
	
	Created by: Tae Young Goh
	Date: August 27, 2014
	Comment: 
	- Configure all the pins here for each specific board
*/


#ifndef PIN_H_
#define PIN_H_

// Port A Definitions

#define MUX0_S3 1	//Multiplexer control
#define MUX0_S2 2
#define MUX0_S1 3
#define MUX0_S0 4
#define GP2Y1010_2_CTRL 5	// digital control for sharp dust sensor
#define GP2Y1010_1_CTRL 6	


// Port B Definitions

#define SPI_CS_N 0	// SPI chip select
#define SPI_CLK 1	// SPI clock
#define SPI_MOSI 2	// SPI master out slave in
#define SPI_MISO 2	// SPI master in slave out
#define SD_DETECT_3V3 4	// SD card detect (keep low during startup)


// Port C Definitions

// all debug


// Port D Definitions

#define I2C_SCL 0	// I2C clock
#define I2C_SDA 1	// I2C data
#define USART1_CLK 5	// USART1 clock
#define USART1_PWR_EN 7	// USART1 5V power control


// Port E Definitions

#define USART0_CLK 2	// USART0 clock
#define PPD42_SNS 3	// PPD42 Sensor Input
#define DHT22_1_SNS 4	// DHT22_1 sensor input
#define DHT22_2_SNS 5	// DHT22_2 sensor input
#define USART0_PWR_EN 6	// USART0 5V power control


// Port F Definitions (analog)

#define GP2Y010_2_SNS 0	// sharp 2 input
#define GP2Y010_1_SNS 1	// sharp 1 input
#define TGS2600_SNS 2	// TGS 2600 Gas Sensor Input
#define MUX0_OUT 3	// multiplexer output
#define JTAG_TCK 4	// JTAG test clock
#define JTAG_TMS 5	// JTAG test mode select
#define JTAG_TDO 6	// JTAG test data out
#define JTAG_TDI 7	// JTAG test data in


void pin_setup(void);
void toggle_sensor_pwr(void);

#endif /* PIN_H_ */