#include "stdafx.h"
#include "Object.h"

Object::Object(Ogre::SceneManager* sceneManager, 
			   Ogre::Vector3 initalScale, 
			   Ogre::Vector3 intialPosition, 
			   std::string name, 
			   std::string meshName)
{
	_entity = sceneManager->createEntity(name, meshName);
	_node = sceneManager->getRootSceneNode()->createChildSceneNode();
	_node->attachObject(_entity);
	_node->setScale(initalScale);
	_node->setPosition(intialPosition);
}


Object::~Object(void)
{
	//delete _entity;
	//delete _node;
}

Ogre::SceneNode* Object::getNode()
{
	return _node;
}
