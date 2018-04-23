/* 
* TIMER.h
*
* Created: 31/08/2015 5:10:48 PM
* Author: Aluminum
*/

#define F_CPU 8000000UL  // this is the frequency of the

#ifndef __TIMER_H__
#define __TIMER_H__


class TIMER
{

//functions
public:
	TIMER();
	int TIMER1_init(void);
	uint16_t readTimer(void);
}; //TIMER

#endif //__TIMER_H__
