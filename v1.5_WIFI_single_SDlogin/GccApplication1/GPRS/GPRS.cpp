/* 
* GPRS.cpp
*
* Created: 1/25/2016 2:22:22 PM
* Author: Kris
*/

#include "GPRS.h"

//
//char read_buf[300];
//int read_buf_index = 0;
//int doit = 0;
//
//int TIMEOUT1 = 700; // 7000 ms
//int TIMEOUT2 = 500; // 5000 ms
//int TIMEOUT3 = 200; // 2000 ms
//
//int IP_status = 0;
//int connection_status = 0;
//int message_status = 0;
//
//char *messageArray;
//int messageArrayLen = 0;
//int messageArray_STATUS = 0; // this is to tell what part of the array I am currently in, i.e how many messages I found in the serial
//int message_INDEX = 0; // this is to iterate through the character array within the array
//
//
//int post_STATUS = 0;
//
//
//ISR(USART0_RX_vect)
//{
	//char ReceiveByte;
	//
	//ReceiveByte = UDR0;
	//UDR1 = ReceiveByte;
	//
	//if (doit == 1 && read_buf_index < 300)
	//{
		//read_buf[read_buf_index] = ReceiveByte;
		//read_buf_index ++;
	//}
	//
//}
//
///*
//ISR(USART0_RX_vect)
//{
	//char ReceiveByte;
	//
	//ReceiveByte = UDR0;
	//UDR1 = ReceiveByte;
	//
	//if (doit == 1)
	//{
		//if (ReceiveByte == messageArray[message_INDEX]) message_INDEX++; // this is used for counting up the index of each message
		//else message_INDEX = 0;
		//
		//if (message_INDEX == messageArrayLen) messageArray_STATUS = 1; // this is where i check that the index is as long as the number of characters in the character array indicating that the message exists on the serial
	//}
//
//}
//*/
//
//// default constructor
//GPRS::GPRS()
//{
//} //GPRS
//
//
//// here is where i check that the response is what i want
//int GPRS::checkRX(USART* fUSART, char *substring, int string_length, int TIMEOUT)
//{
	////char ghgh[20];
	////sprintf(ghgh, "\r\n%d\r\n", string_length);
	////fUSART->sendToUSART1(ghgh);
	//
	//doit = 1;
	//int wait = 0;
	//int status = 0;
	//
	////memset(messageArray, 0, 20);
	//messageArray = substring;
	//messageArrayLen = string_length;
	//messageArray_STATUS = 0;
	//message_INDEX = 0;
	//
	//// check is substring is in string
	////while (messageArray_STATUS == 0)
	//while (!strstr(read_buf, substring))
	//{
		//if (wait >= TIMEOUT)
		//{
			//status = 1;
			//break;
		//}
		//wait ++;
		//_delay_ms(10);
	//}
	//
	//doit = 0;
	//
	//
	//memset(read_buf, 0, 300);
	//read_buf_index = 0;
	//
	//
	//return status;
//}
//
//
//// check if there are any networks around
//
//int GPRS::checknetwork(USART *fUSART, char *network_name, int network_len)
//{
	//
	//fUSART->sendToUSART0("AT+CWLAP\r\n");
	//fUSART->sendToUSART1("AT+CWLAP\r\n");
	//
	//UCSR0B |= (1 << RXEN0);
	//UCSR0B |= (1 << RXCIE0);
	//
	//checkRX(fUSART, network_name, network_len, TIMEOUT2);
	//_delay_ms(10000);
	//
	//UCSR0B &= ~(1 << RXEN0);
	//UCSR0B &= ~(1 << RXCIE0);
	//
	//return 0;
//}
//
//
//
//// private function used to send the special character(26) through the serial port *this is required to send the data
//int GPRS::sendSpecial(USART* fUSART)
//{
	//fUSART->Transmit0(char(26));
	//return 0;
//}
//
//
//int GPRS::setupGPRS(USART* fUSART)
//{
	////LED_ON;
	//
	////_delay_ms(5000);
	////SendToUSARTGPRS("AT+CGATT?\r\n");
	//
	//fUSART->sendToUSART0("ATE0\r\n");
	//fUSART->sendToUSART1("ATE0\r\n");
	//
	//_delay_ms(2000);
	//char cmd[] = "AT+CIPSHUT\r\n";
	//fUSART->sendToUSART0(cmd);
	//
	//_delay_ms(2000);
	//fUSART->sendToUSART0("AT+CIPSTATUS\r\n");
	//
	//_delay_ms(2000);
	//fUSART->sendToUSART0("AT+CIPMUX=0\r\n");
	//
	//_delay_ms(2000);
	//fUSART->sendToUSART0("AT+CSTT=\"internet.com\",\"wapuser1\",\"wap\"\r\n");
	//
	//_delay_ms(2000);
	//fUSART->sendToUSART0("AT+CIICR\r\n");
	//
	//_delay_ms(2000);
	//fUSART->sendToUSART0("AT+CIFSR\r\n");
	//
	//_delay_ms(2000);
	//fUSART->sendToUSART0("AT+CIPSPRT=0\r\n");
	//
	////_delay_ms(3000);
	////SendToUSARTGPRS("AT+CIPSTART=\"tcp\",\"m2.exosite.com\",\"80\"\r\n");
	//
	//_delay_ms(3000);
	//
	////LED_OFF;
	//return 0;
//}
//
//
//
//int GPRS::setupWifi(USART* fUSART)
//{
	////LED_ON;
	//checknetwork(fUSART, "SOCAAR", 6);
	//
	//UCSR0B |= (1 << RXEN0);
	//UCSR0B |= (1 << RXCIE0);
	//
	////_delay_ms(5000);
	////SendToUSARTGPRS("AT+CGATT?\r\n");
	////fUSART->sendToUSART0("ATE0\r\n");
	////fUSART->sendToUSART1("ATE0\r\n");
	//
	//_delay_ms(2000);
	//char cmd[] = "AT+RST\r\n";
	//
	//// try to reset first
	//fUSART->sendToUSART0(cmd);
	//
	//checkRX(fUSART, " CON", 4, TIMEOUT1);
	//
	//if (checkRX(fUSART, "IP", 2, TIMEOUT1) == 0) fUSART->sendToUSART1("Connected\r\n");
	//else 
	//{
		//for (int i = 0; i <= 5; i++)
		//{
			//fUSART->sendToUSART0("AT+CWJAP_CUR=\"SOCAAR\",\"Particle$f1yf@r\"\r\n");
			//
			//if (checkRX(fUSART, " CON", 4, TIMEOUT1) != 0) fUSART->sendToUSART1("Could not connect. Attempting to Reconnect... \r\n");
			//if (checkRX(fUSART, "IP", 2, TIMEOUT2) == 0) {
				//fUSART->sendToUSART1("Connected\r\n");
				//break;
			//} else fUSART->sendToUSART1("Could not get ip address. Attempting to Reconnect... \r\n");
		//}
	//}
//
	//fUSART->sendToUSART0("AT+CWMODE=1\r\n");
	//checkRX(fUSART, "K", 1, TIMEOUT2);
	//
	////UCSR0B |= (1 << RXCIE0);
	//
	////fUSART->sendToUSART0("AT+CWJAP=\"SOCAAR\",\"Particle$f1yf@r\"\r\n");
	////fUSART->sendToUSART1("AT+CWJAP=\"SOCAAR\",\"Particle$f1yf@r\"\r\n");
	////_delay_ms(15000);
//
	//fUSART->sendToUSART0("AT+CIFSR\r\n");
	//checkRX(fUSART, "192", 3, TIMEOUT2);
	//
	////fUSART->sendToUSART1("AT+CIFSR\r\n");
	//_delay_ms(2000);
	//
	//fUSART->sendToUSART0("AT+CIPMUX=0\r\n");
	////fUSART->sendToUSART1("AT+CIPMUX=0\r\n");
	//
	//_delay_ms(2000);
	//
	//for (int i = 0; i <= 5; i++)
	//{
		//fUSART->sendToUSART0("AT+CIPSTART=\"TCP\",\"test.airsensors.ca\",80\r\n");             //start up the connection
		//fUSART->sendToUSART1("AT+CIPSTART=\"TCP\",\"test.airsensors.ca\",80\r\n");             //start up the connection
		//if (checkRX(fUSART, "K", 1, TIMEOUT1) ==0 ) {
			//fUSART->sendToUSART1("Connected to Host.\r\n");
			//break;
		//} else fUSART->sendToUSART1("Could not connect. Attempting to Reconnect... \r\n");
		//
		//if (i > 4) setupWifi(fUSART);
	//}
//
	//
	//UCSR0B &= ~(1 << RXEN0);
	//UCSR0B &= ~(1 << RXCIE0);	
	//
	////LED_OFF;
	//return 0;
//}
//
//
//
//
//int GPRS::connect(USART *fUSART)
//{
	////fUSART->sendToUSART0("AT+CIPCLOSE\r\n"); //close the communication
	////fUSART->sendToUSART1("AT+CIPCLOSE\r\n"); //close the communication
	////_delay_ms(2000); //was 1000
//
	//fUSART->sendToUSART0("AT+CIPSTART=\"TCP\",\"test.airsensors.ca\",80\r\n");             //start up the connection
	//fUSART->sendToUSART1("AT+CIPSTART=\"TCP\",\"test.airsensors.ca\",80\r\n");             //start up the connection
		//
	//_delay_ms(2000);
//}
//
//
//
//int GPRS::POST(FIL cFIL, SDMacro* fSDMacro, USART* fUSART, char* filename, char *post_len, char *body_len, int file_index, int remainder)
//{
//
	//fUSART->sendToUSART0("AT+CIPSEND=");  //begin send data to remote server
	//fUSART->sendToUSART0(post_len);  //begin send data to remote server
	//fUSART->sendToUSART0("\r\n");  //begin send data to remote server
	//fUSART->sendToUSART1("AT+CIPSEND=");  //begin send data to remote server
	//fUSART->sendToUSART1(post_len);  //begin send data to remote server
	//fUSART->sendToUSART1("\r\n");  //begin send data to remote server
	//_delay_ms(100);
	//
	//// POST HEADER
	//
	//fUSART->sendToUSART0("POST /cloud/post.php HTTP/1.1\r\n");
	//fUSART->sendToUSART1("POST /cloud/post.php HTTP/1.1\r\n");
	//
	//fUSART->sendToUSART0("Host: test.airsensors.ca\r\n");
	//fUSART->sendToUSART1("Host: test.airsensors.ca\r\n");
	//
	//fUSART->sendToUSART0("Content-Type: multipart/form-data, boundary=AaB03x\r\n");
	//fUSART->sendToUSART1("Content-Type: multipart/form-data, boundary=AaB03x\r\n");
	//
	//
	//if (remainder >= 10) {
		//fUSART->sendToUSART0("Connection: keep-alive\r\n");
		//fUSART->sendToUSART1("Connection: keep-alive\r\n");
		//} else {
		//fUSART->sendToUSART0("Connection: close\r\n");
		//fUSART->sendToUSART1("Connection: close\r\n");
	//}
//
	//
	//fUSART->sendToUSART0("Content-Length: "); //447\r\n\r\n");
	//fUSART->sendToUSART1("Content-Length: "); //447\r\n\r\n");
	//
	//fUSART->sendToUSART0(body_len);
	//fUSART->sendToUSART0("\r\n\r\n");
	//
	//fUSART->sendToUSART1(body_len);
	//fUSART->sendToUSART1("\r\n\r\n");
	//
	//// POST BODY
	//
	//fUSART->sendToUSART0("--AaB03x\r\n");
	//fUSART->sendToUSART1("--AaB03x\r\n");
	//
	//fUSART->sendToUSART0("Content-Disposition: form-data; name=\"header\"\r\n");
	//fUSART->sendToUSART1("Content-Disposition: form-data; name=\"header\"\r\n");
	//
	//fUSART->sendToUSART0("\r\n");
	//fUSART->sendToUSART1("\r\n");
	//
	//fUSART->sendToUSART0("col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23\r\n");
	//fUSART->sendToUSART1("col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23\r\n");
	//
	//fUSART->sendToUSART0("--AaB03x\r\n");
	//fUSART->sendToUSART1("--AaB03x\r\n");
	//
	//fUSART->sendToUSART0("Content-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\n");
	//fUSART->sendToUSART1("Content-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\n");
	//
	//fUSART->sendToUSART0("Content-Type: text/plain\r\n\r\n");
	//fUSART->sendToUSART1("Content-Type: text/plain\r\n\r\n");
//
	//cli();
	//fSDMacro->ReadSD(cFIL, fUSART, filename, file_index, remainder);
	//sei();
	//
	//fUSART->sendToUSART0("--AaB03x\r\n");
	//fUSART->sendToUSART1("--AaB03x\r\n");
	//
	//fUSART->sendToUSART0("\r\n");
	//fUSART->sendToUSART1("\r\n");
	//
	//return 0;
//}
//
//
//int GPRS::sendGPRS_multipart(FIL cFIL, SDMacro* fSDMacro, USART* fUSART, char* filename, int lines, int FILE_len[100])
//{
	//
	////connect(fUSART);
	//
	//// get the length of the file
	//int byte_length = fSDMacro->GetFileSize(cFIL, filename);
	//
	//int index = 0;
	//
	//int array_index = 0;
	//int file_index = 0;
	//
	//int remainder = 10;
	//int remainder_index = 0;
//
	//
	//while (array_index <= (lines-1))
	//{
//
		//int FILE_length = 0;
		//remainder_index ++;
		////for (array_index; array_index < remainder; array_index ++) FILE_length = FILE_length + FILE_len[array_index];
		//
		//
		//if (array_index + 10 <= lines) {
			//for (array_index; array_index < remainder*remainder_index; array_index ++) FILE_length = FILE_length + FILE_len[array_index];
		//} else {
			//remainder = lines - array_index;
			//for (array_index; array_index < lines; array_index ++) FILE_length = FILE_length + FILE_len[array_index];
		//}
		//
		//
		//char head[100];
		//sprintf(head, "\r\n%d, %d, %d, %d, %d\r\n", FILE_length, array_index, lines, remainder, file_index);
		//fUSART->sendToUSART1(head);
			//
		//// the file size adds one extra byte to each line so i need to subtract the number of lines from the byte length
		////int post_length = byte_length + 438 - lines;
		////int body_length = byte_length + 305 - lines;
		//int post_length;
		////post_length = FILE_length + 438 - remainder;
		//
		//if (remainder >= 10) post_length = FILE_length + 438 - remainder + 24;
		//else post_length = FILE_length + 438 - remainder + 19;
		//
		//int body_length = FILE_length + 305 - remainder;
					//
		//char post_len[5];
		//char body_len[5];
					//
		//sprintf(post_len, "%d", post_length);
		//sprintf(body_len, "%d", body_length);
					//
		//int post_STATUS = 1;
					//
		//while (post_STATUS == 1)
		//{
//
			//UCSR0B |= (1 << RXEN0);
			//UCSR0B |= (1 << RXCIE0);
//
			//fUSART->sendToUSART0("AT+CIPSTATUS\r\n");
			//fUSART->sendToUSART1("AT+CIPSTATUS\r\n");
			//if (checkRX(fUSART, ":3", 2, TIMEOUT3) != 0) connect(fUSART);
//
			//// enable receiving and receiving interrupts just to check it AT+CIPSEND works
			//UCSR0B &= ~(1 << RXEN0);
			//UCSR0B &= ~(1 << RXCIE0);
			//
			//POST(cFIL, fSDMacro, fUSART, filename, post_len, body_len, file_index, remainder);
						//
			//UCSR0B |= (1 << RXEN0);
			//UCSR0B |= (1 << RXCIE0);
//
			//TIMSK &= ~(1 << OCIE1A);				
			//post_STATUS = checkRX(fUSART, "*/", 2, TIMEOUT2);
			//TIMSK |= (1 << OCIE1A);
						//
			//_delay_ms(2000);//200
			//sendSpecial(fUSART);
			//
			//if (post_STATUS != 0) post_STATUS = checkRX(fUSART, "*/", 2, TIMEOUT2);
//
			//_delay_ms(1000); // might need to change this //2000 was 2000
		//}
	//
	//file_index = file_index + FILE_length;
	//}
//
	////_delay_ms(2000); // might need to change this //2000 was 20
//
	//
	//return 0;
	//
//}





/*
int GPRS::receive(USART* fUSART)
{
	
	for (int i = 0; i<20; i++)
	{
		char b;
		b = fUSART->Receive0();
		fUSART->Transmit1(b);
		if (b == '\n' | b == '\r') break;
	}
}

*/

/*
int GPRS::sendGPRS(SDMacro* fSDMacro, USART* fUSART, char* BUFFER)
{	 
	
	//int length = 
	//char buffer_len[5];
	//char buffer[200];
	
	//sprintf(buffer, "test=%s\r\n\r\n", BUFFER);
	//sprintf(buffer_len, "Content-Length: %d\r\n", strlen(buffer));
	
	fUSART->sendToUSART0("AT+CIPSTART=\"TCP\",\"m2.exosite.com\",80\r\n");             //start up the connection
	//fUSART->sendToUSART1("AT+CIPSTART=\"TCP\",\"m2.exosite.com\",80\r\n");             //start up the connection
	_delay_ms(4000);

	fUSART->sendToUSART0("AT+CIPSEND=213\r\n");  //begin send data to remote server
	//fUSART->sendToUSART1("AT+CIPSEND=213\r\n");  //begin send data to remote server
	_delay_ms(4000);

	//_delay_ms(200); //was 500
	fUSART->sendToUSART0("POST /api:v1/stack/alias HTTP/1.1\r\n");
	//fUSART->sendToUSART1("POST /onep:v1/stack/alias HTTP/1.1\r\n");

	fUSART->sendToUSART0("Host: m2.exosite.com\r\n");
	//fUSART->sendToUSART1("Host: m2.exosite.com\r\n");

	fUSART->sendToUSART0("X-Exosite-CIK: 1e6012249cd51557a55b6ec8305543a53ec93d83\r\n");
	//fUSART->sendToUSART1("X-Exosite-CIK: 1e6012249cd51557a55b6ec8305543a53ec93d83\r\n");

	//fUSART->sendToUSART("Accept: application/x-www-form-urlencoded; charset=utf-8\r\n");

	fUSART->sendToUSART0("Content-Type: application/x-www-form-urlencoded\r\n");
	//fUSART->sendToUSART1("Content-Type: application/x-www-form-urlencoded\r\n");
	
	fUSART->sendToUSART0("Content-Length: 9\r\n\r\n");
	//fUSART->sendToUSART1("Content-Length: 9\r\n");

	//fUSART->sendToUSART0("\r\n");
	//fUSART->sendToUSART1("\r\n");

	fUSART->sendToUSART0("test=test\r\n\r\n");
	//fUSART->sendToUSART1("test=test\r\n");
	//fSDMacro->ReadSD(fUSART);
	
	_delay_ms(800);//200

	
	sendSpecial(fUSART);
	  //ShowSerialData();

	_delay_ms(3000); // might need to change this //2000 was 2000

	fUSART->sendToUSART0("AT+CIPCLOSE\r\n"); //close the communication
	//fUSART->sendToUSART1("AT+CIPCLOSE\r\n"); //close the communication
	_delay_ms(1000); //was 1000

	return 0;
}
*/

//send GPRS commmands over tx and rx
/*
int GPRS::SendToUSARTGPRS(USART* fUSART, char command[100])
{
	
	int index = 0;
	while (command[index]!=0)
	{
		fUSART->Transmit(command[index]);
		index++;
	}
	return 0;

}
*/

