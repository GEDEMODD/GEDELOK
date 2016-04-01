#include "stdafx.h"
#include "Object.h"

Object::Object(Ogre::SceneManager* sceneManager,  
			   std::string name, 
			   std::string meshName)
{
	_entity = sceneManager->createEntity(name, meshName);
	_node = sceneManager->getRootSceneNode()->createChildSceneNode();
	_node->attachObject(_entity);
	_node->setScale(Ogre::Vector3(1, 1, 1));
	_node->setPosition(Ogre::Vector3(0, 0, 0));
	_maxSize = 10;
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

void Object::setPosition(Ogre::Vector3 position)
{
	_node->setPosition(position);
}

Ogre::Vector3 Object::getScale()
{
	return _node->getScale();
}

void Object::setScale(Ogre::Vector3 scale)
{
	Ogre::Real xScale = scale.x;
	if ( xScale < _maxSize && xScale > _minSize) {
		_node->setScale(scale);
	}
}

void Object::setMaxSize(double maxSize)
{
	_maxSize = maxSize;
}

void Object::setMinSize(double minSize)
{
	_minSize = minSize;
}

void Object::setScaling(Ogre::Vector3 scaling)
{
	_scaling = scaling;
}

void Object::increase()
{
	Ogre::Vector3 currentScale = getScale();
	setScale(Ogre::Vector3(currentScale.x + _scaling.x, currentScale.y + _scaling.y, currentScale.z + _scaling.z));
}

void Object::decrease()
{
	Ogre::Vector3 currentScale = getScale();
	setScale(Ogre::Vector3(currentScale.x - (_scaling.x * 1.1), currentScale.y - (_scaling.x * 1.1), currentScale.z - (_scaling.x * 1.1)));
}

void Object::setFreqSubscription(int freqSubscription)
{
	_freqSubscription = freqSubscription;
}

int Object::getFreqSubscription()
{
	return _freqSubscription;
}