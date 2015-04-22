/*
 * clock.h
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */

#ifndef CLOCK_H_
#define CLOCK_H_

void ClockSetup();

//todo USER: define clock
#define CLOCK_PERIOD 2000 	//uS

#define TICKS_SUSP		1	//500hz
#define TICKS_SPEED		2	//250hz (close enough)
#define TICKS_SHUNTS	100 //5hz
#define TICKS_BRAKE		50 // 10hz
#define TICKS_OTHER		500 //1hz

//todo USER: CLOCK_TICKS_CLEAR should have the same number of zeros as clock_struct has elements (as seen below)
//#define CLOCK_TICKS_CLEAR {0,0}
#define CLOCK_TICKS_CLEAR	{0}

typedef struct CLOCK_TICKS
{
	int susp;
	int speed;
	int shunts;
	int brake;
	int other;
}clock_struct;


#endif /* CLOCK_H_ */
