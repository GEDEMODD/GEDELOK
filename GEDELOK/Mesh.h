#include "stdafx.h"
#include "Observer.h"

#include <fstream>

#pragma once
class Mesh : public Observer
{
private:
	Ogre::SceneNode* _node;
	Ogre::Entity* _entity;
	double _maxSize;
	double _minSize;
	Ogre::Vector3 _scaling;
	std::ofstream logFile; 

public:
	Mesh(Ogre::SceneManager* sceneManager, 
		std::string name, 
		std::string meshName,
		int frequentcyRange, 
		float threashold);

	~Mesh(void);

	void update(float value);

	Ogre::SceneNode* getNode();
	void setPosition(Ogre::Vector3 position);
	
	Ogre::Vector3 Mesh::getScale();
	void setScale(Ogre::Vector3 scale);

	void setMaxSize(double maxSize);
	void setMinSize(double minSize);

	void setScaling(Ogre::Vector3 scaling);
};