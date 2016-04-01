#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh(Ogre::SceneManager* sceneManager,  
			   std::string name, 
			   std::string meshName,
			   int frequentcyRange, 
			   float threashold) : Observer(frequentcyRange, threashold)
{
	_entity = sceneManager->createEntity(name, meshName);
	_node = sceneManager->getRootSceneNode()->createChildSceneNode();
	_node->attachObject(_entity);
	_node->setScale(Ogre::Vector3(1, 1, 1));
	_node->setPosition(Ogre::Vector3(0, 0, 0));
	_maxSize = 10;
	logFile.open("mesh.log");
}


Mesh::~Mesh(void)
{
	//delete _entity;
	//delete _node;
	logFile.close();
}

void Mesh::update(float value)
{
	logFile << getFrequentcyRange() << " :\t " << value << "\n";
	Ogre::Vector3 currentScale = getScale();
	this->setThreashold(0.8*this->getThreashold()+0.2*value);
	if ( value > this->getThreashold() ) {
		setScale(Ogre::Vector3(currentScale.x + _scaling.x, currentScale.y + _scaling.y, currentScale.z + _scaling.z));
	} else {
		setScale(Ogre::Vector3(currentScale.x - (_scaling.x * 1.1), currentScale.y - (_scaling.x * 1.1), currentScale.z - (_scaling.x * 1.1)));
	}
}

Ogre::SceneNode* Mesh::getNode()
{
	return _node;
}

void Mesh::setPosition(Ogre::Vector3 position)
{
	_node->setPosition(position);
}

Ogre::Vector3 Mesh::getScale()
{
	return _node->getScale();
}

void Mesh::setScale(Ogre::Vector3 scale)
{
	Ogre::Real xScale = scale.x;
	if ( xScale < _maxSize && xScale > _minSize) {
		_node->setScale(scale);
	}
}

void Mesh::setMaxSize(double maxSize)
{
	_maxSize = maxSize;
}

void Mesh::setMinSize(double minSize)
{
	_node->setScale(Ogre::Vector3(minSize, minSize, minSize));
	_minSize = minSize;
}

void Mesh::setScaling(Ogre::Vector3 scaling)
{
	_scaling = scaling;
}