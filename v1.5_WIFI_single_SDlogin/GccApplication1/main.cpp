/*
 * USART_example.c
 *
 * Created: 21/08/2015 3:59:15 PM
 *  Author: Aluminum
 */ 

// clock and baud rate definitions
#define F_CPU 8000000UL  // this is the frequency of the 
#define FOSC 8000000UL
#define BAUD1 38400
#define BAUD0 38400
#define MYUBRR1 F_CPU/16/BAUD1 - 1 // UART baud rate
#define MYUBRR0 F_CPU/16/BAUD0 - 1 // UART baud rate


// logging intervals
#define SNY_INT 30000	// 30 seconds shinyei sensor read interval
#define SEN_INT 1000	// 5 seconds sensor read interval
#define BAD_VECT_TIMEOUT 100 // this tells the code if there were 100 bad vectors then restart


// controls for the usart0 power
#define USART0_OFF PORTE |= (1 << USART0_PWR_EN)
#define USART0_ON PORTE &= ~(1 << USART0_PWR_EN)

// these are the addresses of the potentiometers i.e slave addresses for potentiometers
#define P1 0b01011000
#define P2 0b01011100
#define P3 0b01011010
#define P4 0b01011110

// these are the instructional bits for the potentiometers. These just describe which sensor I want to write to
#define GP2Y010_F1_P1 0x03
#define GP2Y010_F0_P2 0x00
#define MICS2614_14_P1 0x01
#define MICS2614_15_P2 0x02
#define TGS2620_11_P4 0x00
#define TGS2620_2_P3 0x02
#define MICS4514_8_P4 0x02
#define MICS4514_10_P4 0x01
#define MICS5121_6_P3 0x01
#define MICS5524_5_P3 0x00
#define MICS5526_4_P4 0x03
#define MQ3_7_P3 0x03
#define TGS2600_F2_P1 0x00
#define TGS822_3_P1 0x02
#define TGS880_9_P2 0x01


#define data_length 300 //default length of the data array


// include all libraries
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ctype.h>

#include "ADC/ADCLIB.h"
#include "USART/USART.h"
#include "PIN/PIN.h"
#include "I2C/I2C.h"
#include "RTC/RTC.h"
#include "TIMER/TIMER.h"
#include "DHT/DHT.h"
#include "SD/ff.h"
#include "GPRS/GPRS.h"
#include "WIFI/WIFI.h"
#include "SD/SDMacro.h"
#include "PIC/PIC.h"
#include "TIMER/TIMER2.h"
#include "LOGGER/LOGGER.h"

// set up pointers for libraries
ADCLIB fADC;
USART fUSART;
RTC fRTC;
I2C fI2C;
TIMER fTIMER;
TIMER2 fTIMER2;
DHT fDHT;
PIC fPIC;
//GPRS fGPRS;
WIFI fWIFI;
SDMacro fSDMacro;
LOGGER fLOGGER;


// files used for sd card
FIL file; // create file on SD card to log to
FIL tempfile0;
FIL tempfile1;

// buffer related definitions
int sensors[16];
char BUFFER [data_length]; // empty data char array that will be populated with data which will be sent over the UART
char BUFFER_sd[data_length]; // this contains a newline


int FILE_len;

// sinyei related definition
char SINYEI[data_length];
int SINYEI_logged = 0;


uint32_t sharp;
uint32_t mux;

uint16_t temperature;
uint16_t humidity;

uint8_t BAD_VECT_COUNT = 0;

unsigned int times_logged;
int times_logged2;

char filename[] = "NEWATMEL.txt";
char temp_filename0[] = "temp0.txt";
char temp_filename1[] = "temp1.txt";

// username and password for the wifi
char USERNAME[100] = "";
char PASSWORD[100] = "";

// this is to select which file to use
// they will alternate so that one file is not logging while one is sending
bool tempfile_select = false;

int tempfile_select2;

char HEADER[] = "col1,col2,col3,col4,col24,col25,col6,col8,col27,col26,col11,col12,col28,col14,col33,col7,col18,col19,col29,col30,col16,col17,col5,col20,col21";
int HEADER_len = strlen(HEADER);

// timer stuff
volatile uint8_t tot_overflow; // this is for regular logging intervals
volatile uint8_t sinyei_overflow; // this is for sinyei logging intervals
volatile uint8_t tx_overflow;

int lines; // i dont know what this is..


// sinyei stuff
volatile unsigned long sny_lowocc_us_main = 0; // sum of time spent LOW


// create empty char array
int lines_len_size = 100;
int lines_len[100];
volatile int lines_len_INDEX = 0;


// device id
int device_id = 99;



// this function sets the initial resistances of the potentiometers
void setupPotentiometer(void)
{
	fPIC.Set(&fI2C, P1, GP2Y010_F1_P1, 13); // setup GP2Y010_F1_P1
	fPIC.Set(&fI2C, P2, GP2Y010_F0_P2, 13); // setup GP2Y010_F0_P2
	fPIC.Set(&fI2C, P1, MICS2614_14_P1, 25); // setup MICS2614_14_P1
	fPIC.Set(&fI2C, P2, MICS2614_15_P2, 50); // setup MICS2614_15_P2
	fPIC.Set(&fI2C, P4, TGS2620_11_P4, 13); // setup TGS2620_11_P4
	fPIC.Set(&fI2C, P3, TGS2620_2_P3, 13); // setup TGS2620_2_P3
	fPIC.Set(&fI2C, P4, MICS4514_8_P4, 25); // setup MICS4514_8_P4
	fPIC.Set(&fI2C, P4, MICS4514_10_P4, 255); // setup MICS4514_10_P4
	fPIC.Set(&fI2C, P3, MICS5121_6_P3, 255); // setup MICS5121_6_P3
	fPIC.Set(&fI2C, P3, MICS5524_5_P3, 255); // setup MICS5524_5_P3
	fPIC.Set(&fI2C, P4, MICS5526_4_P4, 255); // setup MICS5526_4_P4
	fPIC.Set(&fI2C, P3, MQ3_7_P3, 255); // setup MQ3_7_P3
	fPIC.Set(&fI2C, P1, TGS2600_F2_P1, 255); // setup TGS2600_F2_P1
	fPIC.Set(&fI2C, P1, TGS822_3_P1, 25); // setup TGS822_3_P1
	fPIC.Set(&fI2C, P2, TGS880_9_P2, 255); // setup TGS880_9_P2fda
}


// this function will read the voltage of a potentiometer
// the address is the address of the potentiometer and the instruction is the selection of the wiper on the potentiometer
void readPotentiometer(uint8_t address, uint8_t instruction)
{
	uint8_t voltage = fPIC.Read(&fI2C, address, instruction);
	sprintf(BUFFER + strlen(BUFFER), ",%d", voltage);
}


int getCredentials(FIL cFIL)
{

	if (f_open(&cFIL, "network.txt", FA_READ) == FR_OK);
	else fUSART.sendToUSART1("failed to open network.txt");
	char line[10];

	while (f_gets(line, sizeof(line), &cFIL)) {
		sprintf(USERNAME + strlen(USERNAME), "%s", line);
	}

	if (f_open(&cFIL, "password.txt", FA_READ) == FR_OK);
	else fUSART.sendToUSART1("dsf");
	
	while (f_gets(line, sizeof(line), &cFIL)) {
		sprintf(PASSWORD + strlen(PASSWORD), "%s", line);
	}

	return 0;

}


void setupWIFI(void)
{
	uint8_t toggle_wifi_power = 0;

	while (fWIFI.setupWifi(&fUSART, USERNAME, PASSWORD) == 0)
	{

		fLOGGER.logALL(&fUSART, &fRTC, &fI2C, &fDHT, &fADC);
		fLOGGER.send_to_SD(&fUSART, &fSDMacro, &file, filename);

		toggle_wifi_power ++;

		if (toggle_wifi_power >= 5) {
			USART0_OFF;
			_delay_ms(500);
			USART0_ON;
		}
	}
	
}


void logger(void)
{
	//fUSART.sendToUSART1("start logging");
	fLOGGER.logALL(&fUSART, &fRTC, &fI2C, &fDHT, &fADC);

	// check that the post was sent properly
	if (fLOGGER.send_to_WIFI(&fWIFI, &fUSART, HEADER, HEADER_len) == 0) setupWIFI();

	//fLOGGER.send_to_USART(&fUSART);
	fLOGGER.send_to_SD(&fUSART, &fSDMacro, &file, filename);

}



//void setup

void setup(void)
{
	pin_setup();

	//start the uart
	fUSART.Initialize1(MYUBRR1);
	fUSART.Initialize0(MYUBRR0);
	
	fUSART.sendToUSART1("setup");
	//start the adc
	fADC.Initialize();
	
	//start the RTC
	fI2C.Initialize();
	
	//setup the potentiometers
	setupPotentiometer();
	
	// setting time is weird since the decimal gets converted to hex or something. for example if you want to set 59 you need to put 89
	//fRTC.Set_Time(&fI2C, 0x16, 0x07, 0x29, 0x14, 0x1, 0x00);

	_delay_ms(200);
	//PORTE &= ~0b00001111;
	
	// check if these files are already created or not
	fSDMacro.CheckFile(file, filename);
	
	//get wifi network name and password
	getCredentials(file);
	fUSART.sendToUSART1(USERNAME);
	fUSART.sendToUSART1(PASSWORD);

	sei();

	//WIFI setup
	setupWIFI();
	
	// init timer2 instead
	//fTIMER.TIMER1_init();
	fTIMER2.initialize();
	
}


// catch all unhandled ISRs which could be causing the program to reset
ISR(BADISR_vect)
{
	//if (BAD_VECT_COUNT > BAD_VECT_TIMEOUT) main();
	UDR1 = '!';
	//setup();
	//for(;;) UDR1 = '!';
}




int main(void)
{
	
	_delay_ms(1000);

	setup();
	
	unsigned long sny_lowocc_us = 0; // sum of time spent LOW
	unsigned long last_sen_read = fTIMER2.millis();
	unsigned long last_sny_read = fTIMER2.millis();
	
    while(1)
    {
		
		if ((fTIMER2.millis() - last_sen_read) > SEN_INT){
			logger();
			
		}
		
		if ((fTIMER2.millis() - last_sny_read) > SNY_INT) {
			sny_lowocc_us = fTIMER2.get_sample();
			fLOGGER.logSINYEI(&fUSART, sny_lowocc_us, fTIMER2.millis() - last_sny_read);
			last_sny_read = fTIMER2.millis();
			sny_lowocc_us = 0;
		}
		
		
		_delay_ms(100);
    }
}
