#include "stdafx.h"
#include "OgreLight.h"
#include "Observer.h"

#pragma once
class MyLight : public Observer 
{
private: 
	Ogre::Light* _light;

public:
	MyLight(Ogre::Light* light, int frequentcyRange);
	MyLight();
	~MyLight(void);
	void update(float value);
	Ogre::Light* getLight();
	std::ofstream logFile; 

};

