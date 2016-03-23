/*
 * EMA.h
 *
 *  Created on: Mar 20, 2016
 *      Author: David
 */

#ifndef EMA_FILTER
#define EMA_FILTER

typedef struct filter filter;

struct filter
{
	_iq _input;
	Uint16 _sampleRate;
	Uint32 _lastSampleTime;
	_iq _alpha;
	_iq _filteredOutput;
	filter *_nextFilter;
};

void EMA_Filter_Init(filter *f, Uint16 sampleRate);

void EMA_Filter_Update(void);

float EMA_Filter_NewInput(filter *f, float input);

float EMA_Filter_GetFilteredOutput(filter *f);

#endif
