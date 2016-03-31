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

using namespace Ogre;

class SongAnalyser : public Ogre::Singleton<SongAnalyser>
{

#define SPECHEIGHT 127
#define BANDS 127
#define FREQUENCIES 128

private:
	SceneManager* mSceneMgr;
	DWORD chan;
	SceneNode* cubes[BANDS];
	std::vector<Object *> observers;
	std::vector<ParticleBeat*> particleBeats;
	std::ofstream logFile; 
	float accelerator;

public:
	static SongAnalyser& getSingleton(void);
	static SongAnalyser* getSingletonPtr(void);
	SongAnalyser(SceneManager* MySceneManager);
	~SongAnalyser();
	void update();
	void addObserver(Object* newObserver);
	void SongAnalyser::notify();
};