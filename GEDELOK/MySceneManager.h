#include "stdafx.h"
#include "OGRE\OgreConfigFile.h"
#include "OGRE\OgreEntity.h"
#include "OGRE\OgreIteratorWrapper.h"
#include "OGRE\OgreMovableObject.h"
#include "OGRE\OgreRenderWindow.h"
#include "OGRE\OgreRoot.h"
#include "OgreEntity.h"
#include "OgreSceneManager.h"
#include "OgreWindowEventUtilities.h"
#include "DynamicLines.h"
#include "LineBeat.h"

#include "bass.h"
#include "MyFrameListener.h"
#include "SongAnalyser.h"
#include "Mesh.h"
#include "Replicator.h"

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
	void makeRoom();

public:
	MySceneManager(void);
	~MySceneManager(void);
	void loadResources();
	int startup();
	void createScene();
	void renderOneFrame();
	bool keepRunning();
};

