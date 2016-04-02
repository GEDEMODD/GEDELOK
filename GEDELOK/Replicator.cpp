#include "stdafx.h"
#include "Replicator.h"


Replicator::Replicator(Ogre::SceneManager* sceneManager,  
			   std::string name, 
			   std::string meshType,
			   int frequentcyRange, 
			   float threashold) : Observer(frequentcyRange, threashold)
{
	_sceneManager = sceneManager;
	_meshName = name;
	_meshType = meshType;
	_entity = _sceneManager->createEntity(_meshName, _meshType);
	_node = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_node->attachObject(_entity);
	//_node->setScale(Ogre::Vector3(1, 1, 1));
	_node->setPosition(Ogre::Vector3(0, 0, 0));
	logFile.open("replicator.log");
}


Replicator::~Replicator(void)
{
	//delete _entity;
	//delete _node;
	logFile.close();
}

void Replicator::update(float value)
{
	//logFile << getFrequentcyRange() << " :\t " << value << "\n";
	Ogre::Vector3 currentScale = getScale();
	this->setThreashold(0.8*this->getThreashold() + 0.2*value);

	int numOfChildrenToGenerate = value / this->getThreashold() > 1.0 ? ((value / this->getThreashold()) - value) * 10 : 0;
	//logFile  << value / this->getThreashold() << "\t" << "\t" << (value / this->getThreashold())- value << "\t" << numOfChildrenToGenerate << "\n";
	for ( int i = 0; i < numOfChildrenToGenerate; i++ ) {
		createChildren();
	}

	for ( unsigned int i = 0; i < children.size() / 2; i++ ) {
		if ( !children.empty() ) {
			Ogre::Entity* childEnt = children.front();
			Ogre::SceneNode* childNode = childEnt->getParentSceneNode();
			logFile << childNode->getName() << "\t" << childNode->getParentSceneNode()->getName() << "\t" << childNode->getParentSceneNode()->getParentSceneNode()->getName() << "\n";
			childEnt->setVisible(false);
			childNode->setVisible(false);
			childNode->detachObject(childEnt);
			_sceneManager->destroyEntity(childEnt->getName());
			// entity is now destroyed, don't try to use the pointer anymore!
			// optionally destroy node
			_sceneManager->destroySceneNode(childNode->getName());
			children.pop();
		}
	}
}

void Replicator::createChildren()
{
	Ogre::Entity *childEnt = _sceneManager->createEntity(_meshType);
	Ogre::SceneNode* childNode = _node->createChildSceneNode();	
	childNode->attachObject(childEnt);
	
	Ogre::Real childMinSize = getScale().x / 5;
	Ogre::Real childMaxSize = getScale().x / 3;

	childNode->setScale(Ogre::Math::RangeRandom(childMinSize, childMaxSize), 
		Ogre::Math::RangeRandom(childMinSize, childMaxSize), 
		Ogre::Math::RangeRandom(childMinSize, childMaxSize));

	Ogre::Real x = Ogre::Math::RangeRandom(-100,100);
	Ogre::Real z = Ogre::Math::RangeRandom(-100,100);
	Ogre::Real y = Ogre::Math::RangeRandom(-100,100);
	childNode->setPosition(x, y, z);
	children.push(childEnt);
}


Ogre::SceneNode* Replicator::getNode()
{
	return _node;
}

void Replicator::setPosition(Ogre::Vector3 position)
{
	_node->setPosition(position);
}

Ogre::Vector3 Replicator::getScale()
{
	return _node->getScale();
}

void Replicator::setScale(Ogre::Vector3 scale)
{
	_node->setScale(scale);
}


void Replicator::setScaling(Ogre::Vector3 scaling)
{
	_scaling = scaling;
}