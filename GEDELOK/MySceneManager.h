#include "OGRE\OgreSceneManager.h"
#include "OGRE\OgreRoot.h"
#include "OGRE\OgreConfigFile.h"
#include "OGRE\OgreRenderWindow.h"
#include "OGRE\OgreEntity.h"
#include "OGRE\OgreMovableObject.h"
#include "OGRE\OgreIteratorWrapper.h"
#include "MyFrameListener.h"
#include "OGRE\OgreWindowEventUtilities.h"
#include "bass.h"
#include "SongAnalyser.h"

#pragma once
class MySceneManager
{
private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	MyFrameListener* _listener;
	SongAnalyser* _songAnalyser;
	bool _keepRunning;
	Ogre::SceneNode* _SinbadNode;
	Ogre::Entity* _SinbadEnt;

public:
	MySceneManager(void);
	~MySceneManager(void);
	void loadResources();
	int startup();
	void createScene();
	void renderOneFrame();
	bool keepRunning();
};

