#include "stdafx.h"
#include "OgreLight.h"
#include "Observer.h"

#pragma once
class MyLight : public Observer
{
private: 
	Ogre::Light* _light;

public:
	MyLight(Ogre::Light* light);
	~MyLight(void);
	void update(int value);
};

