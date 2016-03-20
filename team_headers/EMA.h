/*
 * EMA.h
 *
 *  Created on: Mar 20, 2016
 *      Author: David
 */

#ifndef EMA_FILTER
#define EMA_FILTER

typedef struct {

	float _lastOutput;
	float _input;
	Uint16 _sampleRate;
	float _alpha;
	float _filteredOutput;
	struct filter *_nextFilter;

} filter;



void EMA_Filter_Init(filter *f, Uint16 sampleRate, float alpha);

float EMA_Filter_LastOutput(filter *f, float lastOutput);

float EMA_Filter_NewInput(filter *f, float input);

float EMA_Filter_GetFilteredOutput(filter *f);

#endif
