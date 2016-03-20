/*
 * EMA.c
 *
 *  Created on: Mar 20, 2016
 *      Author: David
 */

#include "all.h"

filter *currentFilter;
filter *headFilter;

void EMA_Filter_Update(void);



void EMA_Filter_Init(filter *f, Uint16 sampleRate, float alpha){

	f->_lastOutput = 0;
	f->_input = 0;
	f->_sampleRate = sampleRate;
	f->_alpha = alpha;
	f->_filteredOutput = 0;

	if (headFilter == NULL){

		headFilter = f;
		currentFilter = f;
	}
	else {

		currentFilter->_nextFilter = f;
		currentFilter = f;

	}

}

float EMA_Filter_LastOutput(filter *f, float lastOutput){

	return f->_lastOutput = lastOutput;

}

float EMA_Filter_NewInput(filter *f, float input){

	return f->_input = input;

}

float EMA_Filter_GetFilteredOutput(filter *f){

	f->_filteredOutput = (_IQtoF(_IQmpy(_IQ(f->_alpha), _IQ(f->_input)))) + (_IQtoF(_IQmpy(_IQ(1.0-f->_alpha), _IQ(f->_lastOutput))));


	return f->_filteredOutput;

}


