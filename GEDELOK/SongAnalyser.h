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
	DWORD chan;
	std::vector<Observer *> obs;
	std::ofstream logFile; 
	int ranges[RANGES + 1];
	int _current;
	std::vector<char *> _songs;
	void loadSongs();

public:
	static SongAnalyser& getSingleton(void);
	static SongAnalyser* getSingletonPtr(void);
	SongAnalyser();
	~SongAnalyser();
	void update();
	void addObserver(Observer* ob);
	void SongAnalyser::changeSong();
};