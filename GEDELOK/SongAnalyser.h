#ifndef __SongAnalyser_H__
#define __SongAnalyser_H__

#include "Ogre.h"
#include "OgreSingleton.h"
#include "bass.h"
#include <fstream>

using namespace Ogre;

class SongAnalyser : public Ogre::Singleton<SongAnalyser>
{

#define SPECHEIGHT 127
#define BANDS 28

private:
	SceneManager* mSceneMgr;
	DWORD chan;
	SceneNode* cubes[BANDS];
	std::vector<SceneNode*> observers;
	std::ofstream logFile;

public:
	static SongAnalyser& getSingleton(void);
	static SongAnalyser* getSingletonPtr(void);
	SongAnalyser(SceneManager* MySceneManager);
	~SongAnalyser();
	void update();
	void addObserver(SceneNode* newObserver);
	void SongAnalyser::notify();
};

#endif