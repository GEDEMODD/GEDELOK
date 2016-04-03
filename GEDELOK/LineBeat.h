#include "stdafx.h"
#include "Observer.h"
#include "DynamicLines.h"

#include <fstream>

#pragma once

class LineBeat : public Observer
{
private:
	Ogre::SceneNode* _node;
	Ogre::Entity* _entity;
	double _maxSize;
	double _minSize;
	Ogre::Vector3 _scaling;
	std::ofstream logFile; 
	std::deque<Ogre::Vector3> _points;
	DynamicLines *_lines;
public:
	LineBeat(Ogre::SceneManager* sceneManager, 
		std::string name, 
		std::string meshName,
		int frequentcyRange, 
		float threashold);
	~LineBeat(void);

	void update(float value);

	Ogre::SceneNode* getNode();
	void setPosition(Ogre::Vector3 position);
	
	Ogre::Vector3 getScale();
	void setScale(Ogre::Vector3 scale);

	void setMaxSize(double maxSize);
	void setMinSize(double minSize);

	void setScaling(Ogre::Vector3 scaling);
};

