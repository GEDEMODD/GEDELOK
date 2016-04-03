#include "stdafx.h"
#include "Replicator.h"


Replicator::Replicator(Ogre::SceneManager* sceneManager,  
			   std::string name, 
			   std::string meshType,
			   int frequentcyRange) : Observer(frequentcyRange)
{
	_sceneManager = sceneManager;
	_meshName = name;
	_meshType = meshType;
	_entity = _sceneManager->createEntity(_meshName, _meshType);
	_node = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_node->attachObject(_entity);
	//_node->setScale(Ogre::Vector3(1, 1, 1));
	_node->setVisible(false);
	_node->setPosition(Ogre::Vector3(0, 0, 0));
	logFile.open("replicator.log");

	_materialName = "";
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
	this->setThreashold(0.7*this->getThreashold() + 0.4*value);

	float result = value / this->getThreashold();
	int numOfChildrenToGenerate = result > 1.0 ? (result - value) * 2 : 0;
	//logFile  << value / this->getThreashold() << "\t" << (result - value) * 10 << "\t" << numOfChildrenToGenerate << "\n";
	for ( int i = 0; i < numOfChildrenToGenerate; i++ ) {
		createChildren(numOfChildrenToGenerate);
	}

	for(std::vector<Ogre::Entity*>::size_type i = 0; i < children.size(); ) {
		Ogre::SceneNode* childNode = children[i]->getParentSceneNode();
		Ogre::Real res = childNode->getScale().length();
		if ( res < 0.1 ) {
			children[i]->setVisible(false);
			childNode->setVisible(false);
			childNode->detachObject(children[i]->getName());
			_sceneManager->destroyEntity(children[i]->getName());
			// entity is now destroyed, don't try to use the pointer anymore!
			// optionally destroy node
			_sceneManager->destroySceneNode(childNode->getName());
			 children.erase( children.begin() + i );
		} else {
			Ogre::Vector3 currScale = childNode->getScale();
			childNode->setScale(Ogre::Vector3(currScale.x - currScale.x/3, currScale.y - currScale.y/3, currScale.z - currScale.z/3));
			i++;
		}
	}
}

void Replicator::createChildren(int value)
{
	Ogre::Entity *childEnt = _sceneManager->createEntity(_meshType);
	Ogre::SceneNode* childNode = _node->createChildSceneNode();	
	if ( _materialName != "" ) {
		childEnt->setMaterialName(_materialName);
	}
	childNode->attachObject(childEnt);
	
	Ogre::Real childMinSize = getScale().x * 5;
	Ogre::Real childMaxSize = getScale().x * 10;
	Ogre::Real size = Ogre::Math::RangeRandom(childMinSize, childMaxSize);

	childNode->setScale(size + (value / 1.5), size + (value / 1.5), size + (value / 1.5));
	Ogre::Real x = Ogre::Math::RangeRandom(-300,300);
	Ogre::Real z = Ogre::Math::RangeRandom(-300,300);
	Ogre::Real y = Ogre::Math::RangeRandom(-300,300);
	childNode->setPosition(x, y, z);
	children.push_back(childEnt);
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

void Replicator::setMaterial(std::string materialName)
{
	_materialName = materialName;
	_entity->setMaterialName(_materialName);
}