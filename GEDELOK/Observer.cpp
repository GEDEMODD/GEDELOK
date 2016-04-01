#include "stdafx.h"
#include "Observer.h"


Observer::Observer(void)
{
}


Observer::~Observer(void)
{
}

int Observer::getFrequentcyRange() { return this->_frequentcyRange; }

void Observer::setFrequentcyRange(int range) { _frequentcyRange = range; } 