#include "stdafx.h"
#include "MyLight.h"
	
MyLight::MyLight()
{ 
}

MyLight::MyLight(Ogre::Light* light, int frequentcyRange, float threashold) : Observer(frequentcyRange, threashold)
{
	_light = light;
}

MyLight::~MyLight(void)
{
}

Ogre::Light* MyLight::getLight()
{
	return _light;
}

void MyLight::update(float value)
{
	//_light->setPowerScale(value);
	for (int i = 0; i < 8; i++){
		if(getFrequentcyRange() == i){
			if(_light->isVisible()){
				_light->setVisible(0);
			} else {
				_light->setVisible(1);
			}	
		}
	}
}
