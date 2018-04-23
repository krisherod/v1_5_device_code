/* 
* LOGGER.cpp
*
* Created: 7/8/2016 12:27:22 PM
* Author: Kris
*/


#include "LOGGER.h"

// default constructor
LOGGER::LOGGER()
{
} //LOGGER

// default destructor
LOGGER::~LOGGER()
{
} //~LOGGER



int LOGGER::readTime(RTC* pRTC, I2C* pI2C)
{
	//memset(BUFFER,0,data_length);

	int year = pRTC->Read(pI2C,0x05);
	uint8_t month = pRTC->Read(pI2C,0x04);
	uint8_t day = pRTC->Read(pI2C,0x03);
	uint8_t hour = pRTC->Read(pI2C,0x02) & 0x7F;
	uint8_t minute = pRTC->Read(pI2C,0x01);
	uint8_t second = pRTC->Read(pI2C,0x00);
	
	int act_yr = (int)((year & 0xf0) >> 4) * 10 + (year & 0x0f);
	int act_mo = (int)((month & 0xf0) >> 4) * 10 + (month & 0x0f);
	int act_dy = (int)((day & 0xf0) >> 4) * 10 + (day & 0x0f);
	int act_hr = (int)((hour & 0xf0) >> 4) * 10 + (hour & 0x0f);
	int act_mn = (int)((minute & 0xf0) >> 4) * 10 + (minute & 0x0f);
	int act_sc = (int)((second & 0xf0) >> 4) * 10 + (second & 0x0f);
	
	// act_yr, act_mo, act_dy, act_hr, act_mn, act_sc
	// year, month, day, hour, minute, second
	
	sprintf(BUFFER + strlen(BUFFER), "%d,\"20%02d-%02d-%02d %02d:%02d:%02d\"", device_id, act_yr, act_mo, act_dy, act_hr, act_mn, act_sc); // i took out the newline for sending
	
	return 0;
}


int LOGGER::logDHT(DHT* pDHT, uint8_t address_DHT)
{
	
	uint16_t temperature;
	uint16_t humidity;

	char vals = pDHT->returnTemperatureHumidity(address_DHT, &temperature, &humidity);
	sprintf(BUFFER+strlen(BUFFER),",%d,%d", temperature, humidity);
	//sprintf(BUFFER+strlen(BUFFER),"temperature%d:%d\r\nhumidity%d:%d\r\n", address, temperature, address, humidity);
	
	return 0;
}


int LOGGER::logMUX(ADCLIB* pADCLIB)
{
	//memset(BUFFER,0,data_length);
	pADCLIB->choose_ADC(MUX0_OUT);
	
	//mux = fADC.Read_Mux(1);
	//sprintf(BUFFER+strlen(BUFFER),"\tMux: %d", fADC.Read_Mux(1));
	
	for (int i = 0; i<16; i++)
	{
		sprintf(BUFFER+strlen(BUFFER), ",%d", pADCLIB->read_mux_sensors(i));
		//sprintf(BUFFER+strlen(BUFFER), "Mux%d:%d\r\n", i,fADC.read_mux_sensors(i));
		//sensors[i] = fADC.read_mux_sensors(i);
	}

	//sprintf(BUFFER+strlen(BUFFER), "\r\nMux: %d", mux);

	return 0;
}


int LOGGER::logADC(ADCLIB* pADCLIB, uint8_t address_ADC, uint8_t ctrl)
{
	
	uint32_t sharp;
	//memset(BUFFER,0,data_length);
	pADCLIB->choose_ADC(address_ADC);
	sharp = pADCLIB->read_sharp(address_ADC, ctrl);
	//sprintf(BUFFER+strlen(BUFFER),"\tsharp: %d", sharp);
	sprintf(BUFFER+strlen(BUFFER),",%d", sharp);

	return 0;
}


int LOGGER::logTGS(ADCLIB* pADCLIB, uint8_t address_TGS)
{
	uint32_t tgs;
	pADCLIB->choose_ADC(address_TGS);
	tgs = pADCLIB->read_tgs(address_TGS);
	sprintf(BUFFER + strlen(BUFFER), ",%d", tgs);

	return 0;
}


int LOGGER::logSINYEI(USART* pUSART, unsigned long lowocc_us, unsigned long sampletime_ms)
{
		
	//float ratio; // fraction of time spent LOW
	//float concentration = 0;
	//
	//ratio = lowocc_us / (sampletime_ms * 1000.0) * 100.0;
	//concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
	
	sprintf(SINYEI + strlen(SINYEI), ",%lu,%lu", sampletime_ms, lowocc_us);
	SINYEI_logged = 1;
	//pUSART->sendToUSART1(SINYEI);
	return 0;
}


int LOGGER::send_to_USART(USART* pUSART)
{
	//memset(BUFFER, 0, data_length);
	//sprintf(BUFFER+strlen(BUFFER), "\r\n");
	int index = 0;
	while (BUFFER[index]!=0)
	{
		pUSART->Transmit1(BUFFER[index]);
		index++;
	}

	return 0;
}


int LOGGER::send_to_SD(USART* pUSART, SDMacro* pSDMacro, FIL* file, char* filename)
{
	//fUSART.sendToUSART1(BUFFER);

	// create a temporary BUFFER that has a new line on it
	//char BUFFER_SD[data_length];
	//strncpy(BUFFER_SD, BUFFER, strlen(BUFFER));
	//sprintf(BUFFER_SD + strlen(BUFFER_SD), "\r\n");
	//pUSART->sendToUSART1(BUFFER);

	sprintf(BUFFER + strlen(BUFFER), "\r\n");

	ATOMIC_BLOCK(ATOMIC_FORCEON) pSDMacro->SendData(file, BUFFER, filename);
	//memset(BUFFER_SD, 0, data_length);

	return 0;
}


int LOGGER::send_to_WIFI(WIFI* pWIFI, USART* pUSART, char* HEADER, int HEADER_len)
{
	int BUFFER_len = strlen(BUFFER);

	//if (pWIFI.send_application(&fUSART, BUFFER, BUFFER_len, HEADER, HEADER_len) == 1) pWIFI.setupWifi(&fUSART, USERNAME, PASSWORD);
	uint8_t send_to_WIFI_FLAG = pWIFI->send_application(pUSART, BUFFER, BUFFER_len, HEADER, HEADER_len);
	return send_to_WIFI_FLAG;
}


int LOGGER::resetBUFFER()
{
	memset(BUFFER,0,data_length);
	return 0;
}


// this function is used to check if sinyei has logged yet or not
int LOGGER::preSEND(USART* pUSART)
{
	
	//char h[3];
	//sprintf(h, "%d", SINYEI_logged);
	//pUSART->sendToUSART1(h);

	if (SINYEI_logged == 1) {
		sprintf(BUFFER + strlen(BUFFER), "%s", SINYEI);
		SINYEI_logged = 0;
		memset(SINYEI, 0, strlen(SINYEI));
	}
	else sprintf(BUFFER + strlen(BUFFER), ",NULL,NULL");

}


int LOGGER::logALL(USART* pUSART, RTC* pRTC, I2C* pI2C, DHT* pDHT, ADCLIB* pADC)
{
	
	resetBUFFER();

	readTime(pRTC, pI2C);

	// DHT22_2_SNS will be first for device 23, 24, 25, 26
	logDHT(pDHT, DHT22_2_SNS);
	logDHT(pDHT, DHT22_1_SNS);
	// DHT22_2_SNS will be second for device 19, 20, 21, 22, 27, 28
	//logDHT(pDHT, DHT22_2_SNS);


	logMUX(pADC);

	logADC(pADC, GP2Y010_1_SNS, GP2Y1010_1_CTRL);
	logADC(pADC, GP2Y010_2_SNS, GP2Y1010_2_CTRL);

	logTGS(pADC, TGS2600_SNS);

	preSEND(pUSART);

	return 0;

}

