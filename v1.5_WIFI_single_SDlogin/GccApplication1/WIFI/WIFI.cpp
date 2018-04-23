/* 
* WIFI.cpp
*
* Created: 5/5/2016 4:26:56 PM
* Author: Kris
*/

#include "WIFI.h"


char read_buf[300];
int read_buf_index = 0;
int doit = 0;

int TIMEOUT1 = 1000; // 7000 ms
int TIMEOUT2 = 500; // 5000 ms
int TIMEOUT3 = 200; // 2000 ms
int TIMEOUT4 = 1500; // 2000 ms

int IP_status = 0;
int connection_status = 0;
int message_status = 0;

char *messageArray;
int messageArrayLen = 0;
int messageArray_STATUS = 0; // this is to tell what part of the array I am currently in, i.e how many messages I found in the serial
int message_INDEX = 0; // this is to iterate through the character array within the array


int post_STATUS = 0;


ISR(USART0_RX_vect)
{
	char ReceiveByte;
	
	ReceiveByte = UDR0;
	UDR1 = ReceiveByte;
	
	if (doit == 1 && read_buf_index < 300)
	{
		read_buf[read_buf_index] = ReceiveByte;
		read_buf_index ++;
	}
	
}


// default constructor
WIFI::WIFI()
{
} //WIFI


// private function used to send the special character(26) through the serial port *this is required to send the data
int WIFI::sendSpecial(USART* fUSART)
{
	fUSART->Transmit0(char(26));
	return 0;
}


// here is where i check that the response is what i want
int WIFI::checkRX(USART* fUSART, char *substring1, int string_length1, char *substring2, int string_length2, int TIMEOUT)
{
	
	doit = 1;
	int wait = 0;
	int status = 0;
	
	//memset(messageArray, 0, 20);
	messageArray = substring1;
	messageArrayLen = string_length1;
	messageArray_STATUS = 0;
	message_INDEX = 0;


	UCSR0B |= (1 << RXEN0);
	UCSR0B |= (1 << RXCIE0);
	TIMSK &= ~(1 << OCIE1A);

	while (wait < TIMEOUT)
	{

		char cmpr_buf[300];

		ATOMIC_BLOCK(ATOMIC_FORCEON) {
			strcpy(cmpr_buf, read_buf);
		}
		
		if (strstr(cmpr_buf, substring1)){
			status = 1;
			break;
		}

		if (strstr(cmpr_buf, substring2)){
			status = 2;
			break;
		}

		wait ++;
		_delay_ms(10);
	}
	TIMSK |= (1 << OCIE1A);
	UCSR0B &= ~(1 << RXEN0);
	UCSR0B &= ~(1 << RXCIE0);
	
	doit = 0;
	
	
	memset(read_buf, 0, 300);
	read_buf_index = 0;
	
	
	return status;
}


// check if there are any networks around

int WIFI::checknetwork(USART *fUSART, char *network_name, int network_len)
{
	
	fUSART->sendToUSART0("AT+CWLAP\r\n");
	fUSART->sendToUSART1("AT+CWLAP\r\n");
	
	checkRX(fUSART, network_name, network_len, "NONE", 400, TIMEOUT2);
	_delay_ms(10000);
	
	return 0;
}


int WIFI::connect(USART *fUSART)
{

	int reset_flag = 0;

	for (int i = 0; i <= 5; i++)
	{
		
		// check if it tries to connect more than 3 times then send back a flag to reset the wifi
		if (i > 3) return 0;

		fUSART->sendToUSART0("AT+CIPSTART=\"TCP\",\"test.airsensors.ca\",80\r\n");             //start up the connection
		fUSART->sendToUSART1("AT+CIPSTART=\"TCP\",\"test.airsensors.ca\",80\r\n");             //start up the connection
		int status = checkRX(fUSART, "K", 1, "CON", 3, TIMEOUT2);

		if (status ==1) {
			fUSART->sendToUSART1("Connected to Host.\r\n");
			break;
		} 
		if (status == 2) {
			fUSART->sendToUSART1("Already connected.\r\n");
			break;
		}
		if (status == 0) {
			fUSART->sendToUSART1("could not connect. attempting to reconnect");
		}
	
	}
	
	return 1;
}


int WIFI::setupWifi(USART* fUSART, char *USERNAME, char *PASSWORD)
{
	
	_delay_ms(2000);
	char cmd[100];
	sprintf(cmd, "AT+RST\r\n");
	
	uint8_t connect_bool = 0; // this determines if the reset connected or not

	// try to reset first
	fUSART->sendToUSART0(cmd);
	memset(cmd, 0, 100);
	if (checkRX(fUSART, " CON", 4, "NONE", 300, TIMEOUT3) == 1) connect_bool = 1;

	if (connect_bool == 0) {
		if (checkRX(fUSART, "IP", 2, "NONE", 300, TIMEOUT3) == 1) connect_bool = 1;
	}

	if (connect_bool == 0) {
		sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", USERNAME, PASSWORD);
		//sprintf(cmd, "AT+CWJAP=\"SOCAAR\",\"Particle$f1yf@r\"\r\n", USERNAME, PASSWORD);
					
		fUSART->sendToUSART0(cmd);
		fUSART->sendToUSART1(cmd);
		memset(cmd, 0, 100);

		if (checkRX(fUSART, " CON", 4, "NONE", 300, TIMEOUT1) != 1) {
			fUSART->sendToUSART1("Cound not connect to network\r\n");
			return connect_bool;
		}
		
		
		if (checkRX(fUSART, "IP", 2, "NONE", 300, TIMEOUT4) != 1) {
			fUSART->sendToUSART1("Could not get IP address\r\n");
			return connect_bool;
		}
		

		connect_bool = 1;
	}


	fUSART->sendToUSART0("AT+CWMODE=1\r\n");
	if (checkRX(fUSART, "K", 1, "NONE", 300, TIMEOUT2) != 1) {
		fUSART->sendToUSART1("Could not chance CWMODE\r\n");
		return 0;
	}

	fUSART->sendToUSART0("AT+CIFSR\r\n");
	if (checkRX(fUSART, "192", 3, "NONE", 300, TIMEOUT2) != 1) {
		fUSART->sendToUSART1("No IP address\r\n");
		return 0;
	}
	
	fUSART->sendToUSART0("AT+CIPMUX=0\r\n");
	//fUSART->sendToUSART1("AT+CIPMUX=0\r\n");
	
	_delay_ms(2000);
	int reset_flag;
	reset_flag = connect(fUSART);

	return 1;
}

int WIFI::POST(FIL cFIL, SDMacro* fSDMacro, USART* fUSART, char* filename, char *post_len, char *body_len, int file_index, int remainder)
{

	fUSART->sendToUSART0("AT+CIPSEND=");  //begin send data to remote server
	fUSART->sendToUSART0(post_len);  //begin send data to remote server
	fUSART->sendToUSART0("\r\n");  //begin send data to remote server
	fUSART->sendToUSART1("AT+CIPSEND=");  //begin send data to remote server
	fUSART->sendToUSART1(post_len);  //begin send data to remote server
	fUSART->sendToUSART1("\r\n");  //begin send data to remote server
	_delay_ms(100);
	
	// POST HEADER
	
	fUSART->sendToUSART0("POST /cloud/post3.php HTTP/1.1\r\n");
	fUSART->sendToUSART1("POST /cloud/post3.php HTTP/1.1\r\n");
	
	fUSART->sendToUSART0("Host: test.airsensors.ca\r\n");
	fUSART->sendToUSART1("Host: test.airsensors.ca\r\n");
	
	fUSART->sendToUSART0("Content-Type: multipart/form-data, boundary=AaB03x\r\n");
	fUSART->sendToUSART1("Content-Type: multipart/form-data, boundary=AaB03x\r\n");
	
	
	if (remainder >= 10) {
		fUSART->sendToUSART0("Connection: keep-alive\r\n");
		fUSART->sendToUSART1("Connection: keep-alive\r\n");
		} else {
		fUSART->sendToUSART0("Connection: close\r\n");
		fUSART->sendToUSART1("Connection: close\r\n");
	}

	
	fUSART->sendToUSART0("Content-Length: "); //447\r\n\r\n");
	fUSART->sendToUSART1("Content-Length: "); //447\r\n\r\n");
	
	fUSART->sendToUSART0(body_len);
	fUSART->sendToUSART0("\r\n\r\n");
	
	fUSART->sendToUSART1(body_len);
	fUSART->sendToUSART1("\r\n\r\n");
	
	// POST BODY
	
	fUSART->sendToUSART0("--AaB03x\r\n");
	fUSART->sendToUSART1("--AaB03x\r\n");
	
	fUSART->sendToUSART0("Content-Disposition: form-data; name=\"header\"\r\n");
	fUSART->sendToUSART1("Content-Disposition: form-data; name=\"header\"\r\n");
	
	fUSART->sendToUSART0("\r\n");
	fUSART->sendToUSART1("\r\n");


	fUSART->sendToUSART0("col1,col2,col3,col4,col24,col25,col6,col8,col27,col26,col11,col12,col28,col14,col33,col7,col18,col19,col29,col30,col16,col17,col5,col20,col21\r\n");
	fUSART->sendToUSART1("col1,col2,col3,col4,col24,col25,col6,col8,col27,col26,col11,col12,col28,col14,col33,col7,col18,col19,col29,col30,col16,col17,col5,col20,col21\r\n");
	
	fUSART->sendToUSART0("--AaB03x\r\n");
	fUSART->sendToUSART1("--AaB03x\r\n");
	
	fUSART->sendToUSART0("Content-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\n");
	fUSART->sendToUSART1("Content-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\n");
	
	fUSART->sendToUSART0("Content-Type: text/plain\r\n\r\n");
	fUSART->sendToUSART1("Content-Type: text/plain\r\n\r\n");

	cli();
	fSDMacro->ReadSD(cFIL, fUSART, filename, file_index, remainder);
	sei();
	
	fUSART->sendToUSART0("--AaB03x\r\n");
	fUSART->sendToUSART1("--AaB03x\r\n");
	
	fUSART->sendToUSART0("\r\n");
	fUSART->sendToUSART1("\r\n");
	
	return 0;
}



int WIFI::send_multipart(FIL cFIL, SDMacro* fSDMacro, USART* fUSART, char* filename, int lines, int FILE_len[100])
{
	
	//connect(fUSART);
	
	// get the length of the file using the SD card function, not very effective in this case
	//int byte_length = fSDMacro->GetFileSize(cFIL, filename);
	
	int index = 0;
	
	int array_index = 0;
	int file_index = 0;
	
	int remainder = 10;
	int remainder_index = 0;

	
	while (array_index <= (lines-1))
	{

		int FILE_length = 0;
		remainder_index ++;
		//for (array_index; array_index < remainder; ayrray_index ++) FILE_length = FILE_length + FILE_len[array_index];
		
		
		if (array_index + 10 <= lines) {
			for (array_index; array_index < remainder*remainder_index; array_index ++) FILE_length = FILE_length + FILE_len[array_index];
		} else {
			remainder = lines - array_index;
			for (array_index; array_index < lines; array_index ++) FILE_length = FILE_length + FILE_len[array_index];
		}
		
		
		char head[100];
		sprintf(head, "\r\n%d, %d, %d, %d, %d\r\n", FILE_length, array_index, lines, remainder, file_index);
		fUSART->sendToUSART1(head);
			
		// the file size adds one extra byte to each line so i need to subtract the number of lines from the byte length
		//int post_length = byte_length + 438 - lines;
		//int body_length = byte_length + 305 - lines;
		int post_length;
		//post_length = FILE_length + 438 - remainder;

		int body_length = FILE_length + 318 - remainder;

		// in this part i add an extra digit depending on whether the body length is 3 or 4 digits long
		int extra_digit = 0;
		if (body_length > 999) extra_digit = 1;
		
		if (remainder >= 10) post_length = FILE_length + 450 - remainder + 24 + extra_digit;
		else post_length = FILE_length + 450 - remainder + 19 + extra_digit;
					
		char post_len[5];
		char body_len[5];
					
		sprintf(post_len, "%d", post_length);
		sprintf(body_len, "%d", body_length);
					
		int post_STATUS = 0;
					
		while (post_STATUS != 1)
		{

			UCSR0B |= (1 << RXEN0);
			UCSR0B |= (1 << RXCIE0);

			fUSART->sendToUSART0("AT+CIPSTATUS\r\n");
			fUSART->sendToUSART1("AT+CIPSTATUS\r\n");
			
			int status_temp = checkRX(fUSART, ":3", 2, ":4", 2, TIMEOUT3);
			if (status_temp != 1) connect(fUSART);

			// enable receiving and receiving interrupts just to check it AT+CIPSEND works
			UCSR0B &= ~(1 << RXEN0);
			UCSR0B &= ~(1 << RXCIE0);
			
			POST(cFIL, fSDMacro, fUSART, filename, post_len, body_len, file_index, remainder);
						
			UCSR0B |= (1 << RXEN0);
			UCSR0B |= (1 << RXCIE0);

			TIMSK &= ~(1 << OCIE1A);				
			post_STATUS = checkRX(fUSART, "*/", 2, "NONE", 300, TIMEOUT2);
			TIMSK |= (1 << OCIE1A);
						
			_delay_ms(2000);//200
			sendSpecial(fUSART);
			
			if (post_STATUS != 1) post_STATUS = checkRX(fUSART, "*/", 2, "NONE", 300, TIMEOUT2);

			_delay_ms(1000); // might need to change this //2000 was 2000
		}
	
	file_index = file_index + FILE_length;
	}
	
	return 0;
	
}




int WIFI::POST_single(USART* fUSART, char *post_len, char *body_len, char *BUFFER, char *HEADER)
{

	fUSART->sendToUSART0("AT+CIPSEND=");  //begin send data to remote server
	fUSART->sendToUSART0(post_len);  //begin send data to remote server
	fUSART->sendToUSART0("\r\n");  //begin send data to remote server
	fUSART->sendToUSART1("AT+CIPSEND=");  //begin send data to remote server
	fUSART->sendToUSART1(post_len);  //begin send data to remote server
	fUSART->sendToUSART1("\r\n");  //begin send data to remote server
	_delay_ms(100);


	// POST HEADER
	
	fUSART->sendToUSART0("POST /cloud/post3.php HTTP/1.1\r\n");
	fUSART->sendToUSART1("POST /cloud/post3.php HTTP/1.1\r\n");
	
	fUSART->sendToUSART0("Host: test.airsensors.ca\r\n");
	fUSART->sendToUSART1("Host: test.airsensors.ca\r\n");
	
	fUSART->sendToUSART0("Content-Type: application/x-www-form-urlencoded\r\n");
	fUSART->sendToUSART1("Content-Type: application/x-www-form-urlencoded\r\n");

	fUSART->sendToUSART0("Content-Length: "); //447\r\n\r\n");
	fUSART->sendToUSART1("Content-Length: "); //447\r\n\r\n");
	
	fUSART->sendToUSART0(body_len);
	fUSART->sendToUSART0("\r\n\r\n");
	
	fUSART->sendToUSART1(body_len);
	fUSART->sendToUSART1("\r\n\r\n");


	fUSART->sendToUSART0("vector=");
	fUSART->sendToUSART0(BUFFER);
	fUSART->sendToUSART0("&header=");
	fUSART->sendToUSART0(HEADER);
	fUSART->sendToUSART0("\r\n\r\n");

	fUSART->sendToUSART1("vector=");
	fUSART->sendToUSART1(BUFFER);
	fUSART->sendToUSART1("&header=");
	fUSART->sendToUSART1(HEADER);
	fUSART->sendToUSART1("\r\n");


	return 0;
}


int WIFI::send_application(USART* fUSART, char *BUFFER, int BUFFER_len, char *HEADER, int HEADER_len)
{
	
	int body_length = BUFFER_len + HEADER_len + 19;
	int post_length = body_length + 130;
	
	char post_len[5];
	char body_len[5];
	
	sprintf(post_len, "%d", post_length);
	sprintf(body_len, "%d", body_length);

	int post_STATUS = 0;
	int reset_flag = 0;

	while (post_STATUS != 1)
	{

		fUSART->sendToUSART0("AT+CIPSTATUS\r\n");
		fUSART->sendToUSART1("AT+CIPSTATUS\r\n");
		
		int status_temp = checkRX(fUSART, ":3", 2, ":4", 2, TIMEOUT3);
		if (status_temp != 1) {
			if (connect(fUSART) ==0) return 0;
		}
		
		POST_single(fUSART, post_len, body_len, BUFFER, HEADER);

		TIMSK &= ~(1 << OCIE1A);
		post_STATUS = checkRX(fUSART, "*/", 2, "ERR", 3, TIMEOUT2);
		if (post_STATUS == 2) return 2;

		TIMSK |= (1 << OCIE1A);
		
		_delay_ms(1000);//200
		sendSpecial(fUSART);
		
		if (post_STATUS != 1) post_STATUS = checkRX(fUSART, "*/", 2, "NONE", 300, TIMEOUT2);

		_delay_ms(500); // might need to change this //2000 was 2000
		post_STATUS = 1;
	}


	return 1;
}

