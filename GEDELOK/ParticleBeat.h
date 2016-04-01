#include "stdafx.h"
#include "OgreParticleSystem.h"

#include <time.h>

#pragma once
class ParticleBeat
{
private:
	Ogre::ParticleSystem * _particleSystem;
	Ogre::SceneNode * _sceneNode;
	time_t _startTime;
	bool _active;

public:
	ParticleBeat(Ogre::ParticleSystem * particleSystem, Ogre::SceneNode * sceneNode);
	~ParticleBeat(void);
	void start();
	void stop();
	bool isActive();
	int timeSinceStartedInSeconds();
};

