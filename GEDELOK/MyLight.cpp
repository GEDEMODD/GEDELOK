#include "stdafx.h"
#include "MyLight.h"
	
MyLight::MyLight(Ogre::Light* light, int frequentcyRange, float threashold) : Observer(frequentcyRange, threashold)
{
	_light = light;
}

MyLight::~MyLight(void)
{
}

void MyLight::update(float value)
{
	_light->setPowerScale(value);
}
