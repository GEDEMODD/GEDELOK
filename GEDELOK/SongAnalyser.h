#ifndef __SongAnalyser_H__
#define __SongAnalyser_H__

#include "Ogre.h"
#include "OgreSingleton.h"
#include "bass.h"

using namespace Ogre;

class SongAnalyser : public Ogre::Singleton<SongAnalyser>
{

#define SPECHEIGHT 127
#define BANDS 28

private:
	SceneManager* mSceneMgr;
	DWORD chan;
	SceneNode* cubes[BANDS];
public:
	static SongAnalyser& getSingleton(void);
	static SongAnalyser* getSingletonPtr(void);
	SongAnalyser(SceneManager* MySceneManager);
	~SongAnalyser();
	void update();
};

#endif