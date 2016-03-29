#include "ParticleBeat.h"

ParticleBeat::ParticleBeat(Ogre::ParticleSystem * particleSystem, Ogre::SceneNode * sceneNode)
{
	_particleSystem = particleSystem;
	_sceneNode = sceneNode;
	_startTime = time(0);
	_sceneNode->attachObject(_particleSystem);
}


ParticleBeat::~ParticleBeat(void)
{
}

int ParticleBeat::timeSinceStartedInSeconds()
{
	return (int) difftime(time(0), _startTime);
}
