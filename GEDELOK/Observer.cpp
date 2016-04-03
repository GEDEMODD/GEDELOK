#include "stdafx.h"
#include "Observer.h"


Observer::Observer(int frequentcyRange)
{
	_frequentcyRange = frequentcyRange;
	_threashold = 0.0;
}


Observer::~Observer(void)
{
}

int Observer::getFrequentcyRange() { return this->_frequentcyRange; }

void Observer::setFrequentcyRange(int range) { _frequentcyRange = range; } 

float Observer::getThreashold() { return _threashold; }

void Observer::setThreashold(float threashold){ _threashold = threashold; }