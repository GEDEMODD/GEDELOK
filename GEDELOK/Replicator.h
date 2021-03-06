#include "stdafx.h"
#include "Observer.h"
#include "OgreMath.h"
#include "OgreMaterial.h"
#include "OgreStaticGeometry.h"
#include "OgreQuaternion.h"

#pragma once
class Replicator : public Observer
{
private:
	std::string _meshName;
	std::string _meshType;
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _node;
	Ogre::Entity* _entity;
	Ogre::Vector3 _scaling;
	std::ofstream logFile; 
	std::vector<Ogre::Entity*> children;
	std::string _materialName;

public:
	Replicator(Ogre::SceneManager* sceneManager, 
		std::string name, 
		std::string meshType,
		int frequentcyRange);

	~Replicator(void);

	void update(float value);

	void createChildren(int value);

	Ogre::SceneNode* getNode();
	void setPosition(Ogre::Vector3 position);
	
	Ogre::Vector3 Replicator::getScale();
	void setScale(Ogre::Vector3 scale);

	void setScaling(Ogre::Vector3 scaling);

	void setMaterial(std::string materialName);
};

