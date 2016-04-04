#include "stdafx.h"
#include "Observer.h"

Observer::Observer() {}


Observer::Observer(int frequencyRange)
{
	_frequencyRange = frequencyRange;
	_threshold = 0.0;
}


Observer::~Observer(void)
{
}

int Observer::getFrequencyRange() { return this->_frequencyRange; }

void Observer::setFrequencyRange(int range) { _frequencyRange = range; } 

float Observer::getThreshold() { return _threshold; }

void Observer::setThreshold(float threashold){ _threshold = threashold; }