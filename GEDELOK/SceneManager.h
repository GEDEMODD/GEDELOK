#include "OGRE\OgreSceneManager.h"
#include "OGRE\OgreRoot.h"
#include "OGRE\OgreConfigFile.h"
#include "OGRE\OgreRenderWindow.h"
#include "OGRE\OgreEntity.h"
#include "OGRE\OgreMovableObject.h"
#include "OGRE\OgreIteratorWrapper.h"
#include "FrameListener.h"
#include "OGRE\OgreWindowEventUtilities.h"


#pragma once
class SceneManager
{
private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	FrameListener* _listener;
	bool _keepRunning;
	Ogre::SceneNode* _SinbadNode;
	Ogre::Entity* _SinbadEnt;

public:
	SceneManager(void);
	~SceneManager(void);
	void loadResources();
	int startup();
	void createScene();
	void renderOneFrame();
	bool keepRunning();
};

