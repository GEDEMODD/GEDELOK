#include "stdafx.h"
#include "ParticleBeat.h"

ParticleBeat::ParticleBeat(Ogre::ParticleSystem * particleSystem, 
						   Ogre::SceneNode * sceneNode,
						   int frequencyRange) : Observer(frequencyRange)
{
	_particleSystem = particleSystem;
	_sceneNode = sceneNode;
	_active = false;
	_sceneNode->attachObject(_particleSystem);
	_particleSystem->setEmitting(false);
}


ParticleBeat::~ParticleBeat(void)
{
}

void ParticleBeat::update(float value)
{	
	this->setThreshold(0.97*this->getThreshold()+0.03*value);
	if ( value > this->getThreshold() && !isActive() ) {
		start();
	} else {
		stop();
	}
}

void ParticleBeat::start()
{
	_active = true;
	_startTime = time(0);
	_particleSystem->setEmitting(true);
}

void ParticleBeat::stop()
{
	_active = false;
	_particleSystem->setEmitting(false);
}

bool ParticleBeat::isActive()
{
	return _active;
}

int ParticleBeat::timeSinceStartedInSeconds()
{
	return (int) difftime(time(0), _startTime);
}
