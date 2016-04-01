#include "stdafx.h"
#include "OgreParticleSystem.h"
#include "Observer.h"
#include <time.h>

#pragma once
class ParticleBeat : public Observer
{
private:
	Ogre::ParticleSystem * _particleSystem;
	Ogre::SceneNode * _sceneNode;
	time_t _startTime;
	bool _active;

public:
	ParticleBeat(Ogre::ParticleSystem * particleSystem, 
		Ogre::SceneNode * sceneNode,
		int frequentcyRange,
		float threashold);

	~ParticleBeat(void);

	void update(float value);

	void start();
	void stop();
	bool isActive();
	int timeSinceStartedInSeconds();
};

