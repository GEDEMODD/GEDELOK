#include "stdafx.h"
#include "MyLight.h"
	

MyLight::MyLight(Ogre::Light* light, int frequencyRange) : Observer(frequencyRange)
{
	_light = light;
	//logFile.open("light.log");
}

MyLight::MyLight()
{ 
	//logFile.open("light.log");
}


MyLight::~MyLight(void)
{
	//logFile.close();
}

Ogre::Light* MyLight::getLight()
{
	return _light;
}

void MyLight::update(float value)
{
	//_light->setPowerScale(value);
	this->setThreshold(0.9*this->getThreshold()+0.1*value);
	if ( value > getThreshold() ) {
		_light->setVisible(1);
	} else {
		if ( Ogre::Math::RangeRandom(0,1) > 0.3 ) {
			_light->setVisible(0);
		}
	}
}
