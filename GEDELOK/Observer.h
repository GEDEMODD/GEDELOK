#include "stdafx.h"

#pragma once
class Observer
{
private:
	int _frequentcyRange;
	float _threashold;

public:
	Observer(int frequentcyRange);
	~Observer(void);
	virtual void update(float value) = 0;

	int getFrequentcyRange();
	void setFrequentcyRange(int range);
	float getThreashold();
	void setThreashold(float threashold);
};

