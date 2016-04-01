#include "stdafx.h"
#include "OgreLight.h"

#pragma once
class MyLight
{
private: 
	Ogre::Light* _light;

public:
	MyLight(Ogre::Light* light);
	~MyLight(void);
};

