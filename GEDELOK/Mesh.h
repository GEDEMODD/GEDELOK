#include "stdafx.h"

#pragma once
class Mesh
{
private:
	Ogre::SceneNode* _node;
	Ogre::Entity* _entity;
	double _maxSize;
	double _minSize;
	Ogre::Vector3 _scaling;
	int _freqSubscription;

public:
	Mesh(Ogre::SceneManager* sceneManager, 
		std::string name, 
		std::string meshName);
	~Mesh(void);

	Ogre::SceneNode* getNode();
	void setPosition(Ogre::Vector3 position);
	
	Ogre::Vector3 Mesh::getScale();
	void setScale(Ogre::Vector3 scale);

	void setMaxSize(double maxSize);
	void setMinSize(double minSize);

	void setScaling(Ogre::Vector3 scaling);
	void increase();
	void decrease();

	void setFreqSubscription(int freqSubscription);
	int getFreqSubscription();

};

