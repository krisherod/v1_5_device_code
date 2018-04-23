/* 
* SDMacro.cpp
*
* Created: 1/27/2016 12:00:17 PM
* Author: Kris
*/


#include "SDMacro.h"


// default constructor
SDMacro::SDMacro()
{

} //SDMacro

// default destructor
SDMacro::~SDMacro()
{
	
} //~SDMacro

int SDMacro::CheckFile(FIL cFIL, char* filename)
{
	//sprintf(file, "%s.csv", "hello");
	
	f_mount(&FF, "", 0);
	if (f_open(&cFIL, filename, FA_OPEN_EXISTING) != FR_OK)
	{
		
		f_close(&cFIL);
		if (f_open(&cFIL, filename, FA_CREATE_NEW) == FR_OK)
		f_close(&cFIL);
	}
	return 0;
}

int SDMacro::OverWrite(FIL cFIL, char* filename)
{
	f_mount(&FF, "", 0);
	
	if (f_open(&cFIL, filename, FA_CREATE_ALWAYS) == FR_OK)
	f_close(&cFIL);
	
	return 0;
}

int SDMacro::DeleteFile(FIL cFIL, char* filename)
{
	
	if (f_open(&cFIL, file, FA_OPEN_EXISTING) == FR_OK)
	{
		f_unlink(filename);
	}
	f_close(&cFIL);
	
	return 0;
}

int SDMacro::SendData(FIL* cFIL, char* BUFFER, char* filename)
{
	
	//UINT bw; // i dont think
	if (f_open(cFIL, filename, FA_WRITE | FA_OPEN_ALWAYS) == FR_OK)
	{
		if (f_lseek(cFIL, f_size(cFIL)) == FR_OK) {
			f_write(cFIL, BUFFER, strlen(BUFFER), &bw);
		}
	}
	f_close(cFIL);
	return 0;
}

int SDMacro::GetFileSize(FIL cFIL, char* filename)
{
	if (f_open(&cFIL, filename, FA_READ) == FR_OK);
	int file_size = f_size(&cFIL);
	f_close(&cFIL);
	return file_size;
}

int SDMacro::ReadSD(FIL cFIL, USART* fUSART, char* filename, int location, int index)
{
	//f_lseek(&cFIL, f_size(&cFIL));
	
	//char g[3];
	//sprintf(g, "\r\n%d\r\n", index);
	//fUSART->sendToUSART1(g);
	
	if (f_open(&cFIL, filename, FA_READ) == FR_OK);

	char line[150];
	int i = 0;
	//cli();
	if (f_lseek(&cFIL, location) == FR_OK){
		while (f_gets(line, sizeof line, &cFIL)) {
			//if (i!=0) {
			char y[150];
			sprintf(y, "%s", line);
			fUSART->sendToUSART0(y);
			fUSART->sendToUSART1(y);
			//fUSART->sendToUSART("\r\n");
			//}
			i++;
			/*
			char x[100];
			sprintf(x, "***%d, %d***", i, index);
			fUSART->sendToUSART1(x);
			*/
			if (i>=index) {
				break;
			}
			
		}
	}
	
	/*
	while (f_gets(line, sizeof line, &cFIL)) {
		//if (i!=0) {
		char y[100];
		sprintf(y, "%s", line);
		fUSART->sendToUSART0(y);
		fUSART->sendToUSART1(y);
		//fUSART->sendToUSART("\r\n");
		//}
		i++;
	}
	*/
	//sei();
	f_close(&cFIL);
	/*
	int buflen = 500;
	char buf[buflen];
	int pointerlen;
	
	if (f_open(&cFIL, file, FA_READ) == FR_OK);
	for (int i=0; i<6; i++)
	{
		pointerlen += buflen;
		f_read(&cFIL, buf, buflen, &bw);
		fUSART->sendToUSART(buf);
		f_lseek(&cFIL, pointerlen);
	}
	*/
	return 0;
}



int SDMacro::getCredentials(FIL cFIL, char* BUFFER)
{
	char filename[] = "CONF.txt";
	if (f_open(&cFIL, filename, FA_READ) == FR_OK);
	char line[100];
	char BUFF[500];

	while (f_gets(line, sizeof line, &cFIL)) {
		sprintf(BUFF + strlen(BUFF), "%s", line);
	}

	BUFFER = "sdf";

	return 0;

	/*
	int username_length;
	int password_length;

	char sub1[] = "username:";
	char sub2[] = ";";
	char sub3[] = "password:";

	char* index1 = strstr(BUFF, sub1);
	char* index2 = strstr(BUFF, sub2);
	char* index3 = strstr(BUFF, sub3);

	char* password_raw;
	char* username_raw;

	if (index1 && index2) {
		username_length = index2 - index1+9;
		memcpy(username_raw, BUFF[index1+9], username_length);
		username = username_raw;
	} else { return 0; }

	if (index3) {
		password_length = index3 + 9 - strlen(BUFF);
		memcpy(password_raw, BUFF[index3+9], password_length);
		password = password_raw;
	} else { return 0; }
	*/
}

