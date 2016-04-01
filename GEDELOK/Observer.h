#include "stdafx.h"

#pragma once
class Observer
{
private:
	int _frequentcyRange;

public:
	Observer(void);
	~Observer(void);
	virtual void update(int value);

	int getFrequentcyRange();
	void setFrequentcyRange(int range);
};

