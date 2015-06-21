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
#define CLOCK_PERIOD 1000 //uS //thousandth of a second

#define EIGHT_THOUSAND_HZ		125	//8 kHz
#define NINE_THOUSAND_HZ		111 	//9 kHz
#define TEN_HUNDRED_HZ			100
#define ELEVEN_HUNDRED_HZ		91
#define TWELVE_HUNDRED_HZ		83
#define THIRTEEN_HUNDRED_HZ		77
#define FOURTEEN_HUNDRED_HZ		71
#define FIFTEEN_HUNDRED_HZ		67
#define SIXTEEN_HUNDRED_HZ		63	//16 kHz


//todo USER: CLOCK_TICKS_CLEAR should have the same number of zeros as clock_struct has elements (as seen below)
//#define CLOCK_TICKS_CLEAR {0,0}
#define CLOCK_TICKS_CLEAR	{0}

typedef struct CLOCK_TICKS
{
	int DataOut;
}clock_struct;


#endif /* CLOCK_H_ */
