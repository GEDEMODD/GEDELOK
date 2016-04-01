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
#include "Mesh.h"
#include "MyLight.h"
#include "Observer.h"

#pragma once
class SongAnalyser : public Ogre::Singleton<SongAnalyser>
{

#define SPECHEIGHT 127
#define BANDS 127
#define FREQUENCIES 128
#define RANGES 8

private:
	Ogre::SceneManager* mSceneMgr;
	DWORD chan;
	Ogre::SceneNode* cubes[BANDS];
	std::vector<Mesh *> observers;
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
	SongAnalyser(Ogre::SceneManager* MySceneManager);
	~SongAnalyser();
	void update();
	void addObservers(Observer* ob);
	void addObserver(Mesh* newObserver);
	void addParticleBeat(ParticleBeat* particleBeat);
	void SongAnalyser::notify();
	void SongAnalyser::changeSong();
};