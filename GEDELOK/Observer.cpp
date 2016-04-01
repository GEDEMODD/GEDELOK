#include "stdafx.h"
#include "Observer.h"


Observer::Observer(int frequentcyRange, float threashold)
{
	_frequentcyRange = frequentcyRange;
	_threashold = threashold;
}


Observer::~Observer(void)
{
}

int Observer::getFrequentcyRange() { return this->_frequentcyRange; }

void Observer::setFrequentcyRange(int range) { _frequentcyRange = range; } 

float Observer::getThreashold() { return _threashold; }