/*
	SOCAAR Project
	ATMEGA64 Timer Library for AVR
	
	Created by: Tae Young Goh
	Date: August 28, 2014
	Comment:
	- Timing counter for millis()
	- Timing counter for check_ICP() for Shinyei sensors
*/

#ifndef TIMER2_H_
#define TIMER2_H_

class TIMER2 {
	public:
		TIMER2();
		int initialize(void);
		unsigned long millis(void);
		unsigned long check_ICP(void);	
		unsigned long get_sample(void);
	
};



#endif /* TIMER2_H_ */