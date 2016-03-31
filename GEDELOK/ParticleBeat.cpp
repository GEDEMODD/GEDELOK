#include "stdafx.h"
#include "ParticleBeat.h"

ParticleBeat::ParticleBeat(Ogre::ParticleSystem * particleSystem, Ogre::SceneNode * sceneNode)
{
	_particleSystem = particleSystem;
	_sceneNode = sceneNode;
	_active = false;
}


ParticleBeat::~ParticleBeat(void)
{
}

void ParticleBeat::start()
{
	_active = true;
	_startTime = time(0);
	_sceneNode->attachObject(_particleSystem);
}

void ParticleBeat::stop()
{
	_active = false;
	_particleSystem->clear();
}

bool ParticleBeat::isActive()
{
	return _active;
}

int ParticleBeat::timeSinceStartedInSeconds()
{
	return (int) difftime(time(0), _startTime);
}
