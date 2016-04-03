#include "stdafx.h"
#include "MyLight.h"
	

MyLight::MyLight(Ogre::Light* light, int frequentcyRange) : Observer(frequentcyRange)
{
	_light = light;
}

MyLight::MyLight()
{ 
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
	this->setThreashold(0.97*this->getThreashold()+0.03*value);

	/*for (int i = 0; i < 8; i++){
		if(getFrequentcyRange() == i){
			if(_light->isVisible()){
				_light->setVisible(0);
			} else {
				_light->setVisible(1);
			}	
		}
	}*/
}
