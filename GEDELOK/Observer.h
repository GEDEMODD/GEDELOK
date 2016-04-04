#include "stdafx.h"

#pragma once
class Observer
{
private:
	int _frequencyRange;
	float _threshold;

public:
	Observer(int frequencyRange);
	Observer();
	~Observer(void);
	virtual void update(float value) = 0;

	int getFrequencyRange();
	void setFrequencyRange(int range);
	float getThreshold();
	void setThreshold(float threshold);
};

