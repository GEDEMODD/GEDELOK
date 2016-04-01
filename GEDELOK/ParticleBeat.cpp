#include "stdafx.h"
#include "ParticleBeat.h"

ParticleBeat::ParticleBeat(Ogre::ParticleSystem * particleSystem, 
						   Ogre::SceneNode * sceneNode,
						   int frequentcyRange,
						   float threashold) : Observer(frequentcyRange, threashold)
{
	_particleSystem = particleSystem;
	_sceneNode = sceneNode;
	_active = false;
	_sceneNode->attachObject(_particleSystem);
	//_particleSystem->setVisible(false);
	_particleSystem->setEmitting(false);

}


ParticleBeat::~ParticleBeat(void)
{
}

void ParticleBeat::update(float value)
{
	if ( value > this->getThreashold() && !isActive() ) {
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
	//_particleSystem->setVisible(true);
}

void ParticleBeat::stop()
{
	_active = false;
	_particleSystem->setEmitting(false);
	//_particleSystem->setVisible(false);
	//_particleSystem->clear();
}

bool ParticleBeat::isActive()
{
	return _active;
}

int ParticleBeat::timeSinceStartedInSeconds()
{
	return (int) difftime(time(0), _startTime);
}
