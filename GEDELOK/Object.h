#include "stdafx.h"

#pragma once
class Object
{
private:
	Ogre::SceneNode* _node;
	Ogre::Entity* _entity;

public:
	Object(Ogre::SceneManager* sceneManager, 
		Ogre::Vector3 initalScale,
		Ogre::Vector3 intialPosition,
		std::string name, 
		std::string meshName);
	~Object(void);
	Ogre::SceneNode* getNode();

};

