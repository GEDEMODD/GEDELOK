#include "stdafx.h"
#include "OgreParticleSystem.h"

#include <time.h>
#include "MyFrameListener.h"

class ParticleBeat
{
private:
	Ogre::ParticleSystem * _particleSystem;
	Ogre::SceneNode * _sceneNode;
	time_t _startTime;

public:
	ParticleBeat(Ogre::ParticleSystem * particleSystem, Ogre::SceneNode * sceneNode);
	~ParticleBeat(void);
	int timeSinceStartedInSeconds();
};

