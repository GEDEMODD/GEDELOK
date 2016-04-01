#include "stdafx.h"
#include "OgreEntity.h"
#include "OgreLogManager.h"
#include "OgreMovableObject.h"
#include "OgreParticleSystem.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "OgreSingleton.h"
#include "OgreStringConverter.h"

#include <fstream>

#include "bass.h"
#include "ParticleBeat.h"
#include "Object.h"
#include "MyLight.h"
#include "Observer.h"

using namespace Ogre;
#pragma once
class SongAnalyser : public Ogre::Singleton<SongAnalyser>
{

#define SPECHEIGHT 127
#define BANDS 127
#define FREQUENCIES 128
#define RANGES 8

private:
	SceneManager* mSceneMgr;
	DWORD chan;
	SceneNode* cubes[BANDS];
	std::vector<Object *> observers;
	std::vector<Observer *> obs;
	std::vector<ParticleBeat*> particleBeats;
	std::vector<MyLight*> lights;
	std::ofstream logFile; 
	float accelerator;
	int ranges[RANGES + 1];
	int _current;
	std::vector<char *> _songs;
						   

public:
	static SongAnalyser& getSingleton(void);
	static SongAnalyser* getSingletonPtr(void);
	SongAnalyser(SceneManager* MySceneManager);
	~SongAnalyser();
	void update();
	void addObservers(Observer* ob);
	void addObserver(Object* newObserver);
	void addParticleBeat(ParticleBeat* particleBeat);
	void SongAnalyser::notify();
	void SongAnalyser::changeSong();
};