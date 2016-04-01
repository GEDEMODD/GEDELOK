#include "stdafx.h"
#include "OGRE\OgreCamera.h"
#include "OGRE\OgreFrameListener.h"
#include "OGRE\OgreMeshManager.h"
#include "OGRE\OgreRenderWindow.h"
#include "OGRE\OgreSceneNode.h"
#include "OIS\OIS.h"

#include "SongAnalyser.h"

#pragma once
class MyFrameListener : public Ogre::FrameListener
{
private:
	OIS::InputManager* _InputManager;
	OIS::Keyboard* _Keyboard;
	OIS::Mouse* _Mouse;
	Ogre::Camera* _Cam;
	float _movementSpeed;
	float _WalkingSpeed;
	Ogre::SceneNode* _node;
	Ogre::AnimationState* _aniState;
	Ogre::AnimationState* _aniStateTop;	
	SongAnalyser* _songAnalyser;

public:
	MyFrameListener(void);
	~MyFrameListener(void);
	MyFrameListener(Ogre::RenderWindow* win, 
		Ogre::Camera* cam,
		Ogre::Viewport* viewport, 
		Ogre::SceneNode* node, 
		Ogre::Entity* ent);

	bool frameStarted(const Ogre::FrameEvent& evt);
	void setNode(Ogre::SceneNode* node);
	void setAniState(Ogre::AnimationState* state);
	void setAniStateTop(Ogre::AnimationState* state);
	void setSongAnalyser(SongAnalyser* songAnalyser);
};


